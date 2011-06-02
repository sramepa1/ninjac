using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.IO;
using System.Globalization;

public class Parser
{
    public string oneCharOper { get; set; }
    public SortedSet<string> twoCharOper { get; set; }
    public SortedSet<string> keywords { get; set; }

    protected Tokenizer tok;
    protected int line;
    protected bool topLevel;

    protected Ninjac n;

    public Parser(Ninjac ninjac)
    {
        n = ninjac;

        tok = new Tokenizer(this);

        reset();

        keywords = new SortedSet<string>();
        twoCharOper = new SortedSet<string>();

        keywords.Add("begin");
        keywords.Add("end");

        keywords.Add("if");
        keywords.Add("then");
        keywords.Add("else");

        keywords.Add("while");
        keywords.Add("do");

        keywords.Add("repeat");
        keywords.Add("until");

        keywords.Add("for");
        keywords.Add("from");
        keywords.Add("to");
        keywords.Add("step");

        keywords.Add("function");
        keywords.Add("of");
        keywords.Add("is");
        keywords.Add("return");

        keywords.Add("precision");

        keywords.Add("print");

        keywords.Add("set");

        keywords.Add("exit");

        oneCharOper = "+-*/\\%&|=<>";

        twoCharOper.Add("==");
        twoCharOper.Add("<>");
        twoCharOper.Add("&&");
        twoCharOper.Add("||");
        twoCharOper.Add("<=");
        twoCharOper.Add(">=");
    }

    public void reset()
    {
        topLevel = true;
        line = 1;
        tok.reset();
    }

    public void parse(TextReader reader)
    {
        Token t = tok.getToken(reader, ref line);

        if (t.type == TokenType.END)
        {
            n.outputError("What am I supposed to do with empty input?!");
            return;
        }

        for (; ; )
        { // parse top-level statements, separated by separators
            n.program.append(parseStmt(reader));
            t = tok.getToken(reader, ref line);
            if (t.type == TokenType.END) break;
            if (t.type != TokenType.STMT_SEP)
            {
                throw new NinjacException(false, "expected ';'", t.line);
            }
            tok.tokenOK();
            topLevel = true; // reset the flag - the next statement will be a top-level one
        }
    }

    public Statement parseStmt(TextReader reader)
    {
        Token t = tok.getToken(reader, ref line);

        switch (t.type)
        {
            case TokenType.KEYWORD:
                return parseKeyword(reader);
            case TokenType.FUNC:
                goto case TokenType.VAR;
            case TokenType.LEFT_P:
                goto case TokenType.VAR;
            case TokenType.NUM:
                goto case TokenType.VAR;
            case TokenType.VAR:
                {
                    ExpressionStatement es = new ExpressionStatement(n);
                    es.expr = parseExpr(reader);
                    return es;
                }
            default:
                throw new NinjacException(false, "expected statement", t.line);
        };
    }

    private Expression parseExpr(TextReader reader)
    {
        // shunting-yard algorithm: infix -> RPN queue
        Queue<Token> output = new Queue<Token>();
        shuntingYard(reader, output);

        Stack<Expression> stack = new Stack<Expression>();   // the main working stack - will contain the root Expression in the end
        Stack<Expression> tmpStack = new Stack<Expression>(); // only a way to reorder function arguments correctly
        do
        {
            Token t = output.Peek();
            switch (t.type)
            {
                case TokenType.NUM:
                    stack.Push(new Constant(Double.Parse(t.value, CultureInfo.InvariantCulture)));
                    break;
                case TokenType.VAR:
                    stack.Push(new Variable(t.value, n));
                    break;
                case TokenType.OPER:
                    {
                        Operator op = getOperator(t.value, t.line);
                        if (stack.Count < 2)
                        {
                            throw new NinjacException(false, "not enough operands for operator", t.line);
                        }
                        op.right = stack.Pop();
                        op.left = stack.Pop();
                        stack.Push(op);
                        break;
                    }
                case TokenType.FUNC:
                    FunctionCall fc = new FunctionCall(t.value, t.line, n);
                    if (stack.Count < t.argc)
                    {
                        throw new NinjacException(false, "missing argument(s)", t.line);
                    }
                    for (int i = 0; i < t.argc; i++)
                    {
                        tmpStack.Push(stack.Pop());
                    }
                    while (tmpStack.Count > 0)
                    {
                        fc.addValue(tmpStack.Pop());
                    }
                    stack.Push(fc);
                    break;
            }
            // this is the final destination of even the most long-lived tokens
            output.Dequeue();
        } while (output.Count > 0);

        if (stack.Count > 1)
        {
            throw new NinjacException(false, "not an expression", line);
        }

        return stack.Peek();
    }


    protected void shuntingYard(TextReader reader, Queue<Token> output)
    {
        Stack<Token> tokStack = new Stack<Token>(); // the main working stack
        Stack<int> argCntStack = new Stack<int>(); // function argument counter stack (correct argument count is unknown during parsing)
        bool end = false; // a flag

        do
        {
            Token t = tok.getToken(reader, ref line);

            switch (t.type)
            {
                case TokenType.NUM:
                    goto case TokenType.VAR; //fall-through
                case TokenType.VAR:
                    output.Enqueue(t);
                    tok.tokenOK();
                    break;
                case TokenType.FUNC:
                    argCntStack.Push(0);
                    goto case TokenType.LEFT_P; //fall-through;
                case TokenType.LEFT_P:
                    tokStack.Push(t);
                    tok.tokenOK();
                    break;
                case TokenType.RIGHT_P:
                    while ((tokStack.Count > 0) && tokStack.Peek().type != TokenType.LEFT_P)
                    {
                        output.Enqueue(tokStack.Pop());
                    }
                    if (tokStack.Count == 0)
                    {
                        throw new NinjacException(false, "unmatched parthenses", t.line);
                    }

                    tokStack.Pop();
                    if ((tokStack.Count > 0) && tokStack.Peek().type == TokenType.FUNC)
                    {
                        Token f = tokStack.Pop();
                        f.argc = argCntStack.Pop() + 1; // one for the parthensis itself - zero-argument functions don't have them
                        output.Enqueue(f);
                    }
                    tok.tokenOK();
                    break;
                case TokenType.OPER:
                    // simplification: NINJAC only has binary, left-associative operators -> the only thing to check is precedence
                    while ((tokStack.Count > 0) && (tokStack.Peek().type == TokenType.FUNC || (tokStack.Peek().type == TokenType.OPER && tok.hasLTEpriority(t, tokStack.Peek()))))
                    {
                        output.Enqueue(tokStack.Pop());
                    }
                    tokStack.Push(t);
                    tok.tokenOK();
                    break;
                case TokenType.ARG_SEP:
                    {
                        while ((tokStack.Count > 0) && tokStack.Peek().type != TokenType.LEFT_P)
                        {
                            output.Enqueue(tokStack.Pop());
                        }
                        if (tokStack.Count == 0)
                        {
                            throw new NinjacException(false, "misplaced argument separator or unmatched parthenses", t.line);
                        }
                        int tmp = argCntStack.Pop() + 1; // add a notch
                        argCntStack.Push(tmp);

                        tok.tokenOK();
                        break;
                    }
                default:
                    end = true; // other token, not a part of the expression
                    break;
            }
        } while (!end);


        while ((tokStack.Count > 0))
        {
            if (tokStack.Peek().type == TokenType.LEFT_P)
            {
                int ln = tokStack.Peek().line;
                throw new NinjacException(false, "unmatched parthenses", ln);
            }
            output.Enqueue(tokStack.Pop());
        }

        if (output.Count == 0)
        {
            throw new NinjacException(false, "expected an expression", line);
        }
    }

    protected Statement parseKeyword(TextReader reader)
    {
        Token t = tok.getToken(reader, ref line);

        if (t.value == "set")
        {
            tok.tokenOK();
            return parseAssign(reader);

        }
        else if (t.value == "begin")
        {
            tok.tokenOK();
            return parseBlock(reader);

        }
        else if (t.value == "for")
        {
            tok.tokenOK();
            return parseFor(reader);

        }
        else if (t.value == "while")
        {
            tok.tokenOK();
            return parseWhile(reader);

        }
        else if (t.value == "repeat")
        {
            tok.tokenOK();
            return parseRepeat(reader);

        }
        else if (t.value == "function")
        {
            if (!topLevel)
            {
                throw new NinjacException(false, "function declaration must be a top level statement", t.line);
            }
            tok.tokenOK();
            topLevel = false;
            return parseFunc(reader);

        }
        else if (t.value == "if")
        {
            tok.tokenOK();
            return parseIf(reader);

            // the last three ones are so simple they don't need subfunctions - parse'em right away
        }
        else if (t.value == "print")
        {
            tok.tokenOK();
            Expression expr = parseExpr(reader);
            PrintStatement p = new PrintStatement(n);
            p.expr = expr;
            return p;

        }
        else if (t.value == "precision")
        {
            tok.tokenOK();
            Expression expr = parseExpr(reader);
            PrecisionStatement p = new PrecisionStatement(n);
            p.expr = expr;
            return p;

        }
        else
        {
            throw new NinjacException(false, string.Concat("unexpected keyword: ", t.value), t.line);
        }
    }


    protected void expect(string keyword, TextReader reader)
    {
        Token t = tok.getToken(reader, ref line);
        if (t.type != TokenType.KEYWORD || t.value != keyword)
        {
            throw new NinjacException(false, String.Format("expected \"{0}\"", keyword), t.line);
        }
        tok.tokenOK();
    }

    protected string parseVar(TextReader reader)
    {
        Token t = tok.getToken(reader, ref line);
        if (t.type != TokenType.VAR)
        {
            throw new NinjacException(false, "expected a variable", t.line);
        }
        tok.tokenOK();
        string s = t.value;
        return s;
    }

    protected Statement parseIf(TextReader reader)
    {
        Conditional c = new Conditional(topLevel, n);
        topLevel = false; // contained statement surely isn't a top-level one

        c.cond = parseExpr(reader);
        expect("then", reader);
        c.ifTrue = parseStmt(reader);
        Token t = tok.getToken(reader, ref line);
        if (t.type == TokenType.KEYWORD && t.value == "else")
        {
            tok.tokenOK();

            c.ifFalse = parseStmt(reader);
        }

        return c;
    }

    protected Statement parseFunc(TextReader reader)
    {
        Token t = tok.getToken(reader, ref line);
        if (t.type != TokenType.FUNC)
        {
            throw new NinjacException(false, "expected function name", t.line);
        }
        if (n.functions.ContainsKey(t.value))
        {   // check for existence
            throw new NinjacException(false, String.Format("function {0} is already declared", t.value), t.line);
        }
        FunctionDeclaration fd = new FunctionDeclaration(t.value, n);
        Block b = new Block(false, n);
        fd.setBody(b);
        tok.tokenOK();

        t = tok.getToken(reader, ref line);
        if (t.type != TokenType.KEYWORD || (t.value != "of" && t.value != "is"))
        {
            throw new NinjacException(false, "expected \"of\" or \"is\"", t.line);
        }
        bool args = t.value == "of";
        tok.tokenOK();

        if (args)
        {
            for (; ; )
            {
                string arg = parseVar(reader);
                if (fd.hasArgument(arg))
                {
                    throw new NinjacException(false, "argument name duplication", line);
                }
                fd.addArgument(arg);
                t = tok.getToken(reader, ref line);
                if (t.type == TokenType.KEYWORD && t.value == "is")
                {
                    tok.tokenOK();

                    break;
                }
                if (t.type != TokenType.ARG_SEP)
                {
                    throw new NinjacException(false, "expected argument separator or \"is\"", t.line);
                }
                tok.tokenOK();

            }
        }
        // in either case, 'is' token was already acknowledged
        t = tok.getToken(reader, ref line);
        if (t.type != TokenType.KEYWORD || t.value != "return")
        {
            for (; ; )
            {
                b.append(parseStmt(reader));
                t = tok.getToken(reader, ref line);
                if (t.type == TokenType.KEYWORD && t.value == "return") break;
                if (t.type != TokenType.STMT_SEP)
                {
                    throw new NinjacException(false, "expected ';'", t.line);
                }
                tok.tokenOK();

            }
        }
        tok.tokenOK();

        fd.setReturn(parseExpr(reader));

        return fd;
    }

    protected Statement parseRepeat(TextReader reader)
    {
        RepeatLoop r = new RepeatLoop(topLevel, n, line);
        Block b = new Block(false, n);
        r.stmt = b;
        topLevel = false; // may contain other statements - they surely aren't top-level ones

        Token t;
        for (; ; )
        {
            b.append(parseStmt(reader));
            t = tok.getToken(reader, ref line);
            if (t.type == TokenType.KEYWORD && t.value == "until") break;
            if (t.type != TokenType.STMT_SEP)
            {
                throw new NinjacException(false, "expected ';'", t.line);
            }
            tok.tokenOK();

        }
        tok.tokenOK();

        r.cond = parseExpr(reader);

        return r;
    }

    protected Statement parseWhile(TextReader reader)
    {
        WhileLoop w = new WhileLoop(topLevel, n, line);
        topLevel = false; // contained statement surely isn't a top-level one
        w.cond = parseExpr(reader);
        expect("do", reader);
        w.stmt = parseStmt(reader);
        return w;
    }

    protected Statement parseFor(TextReader reader)
    {
        ForLoop f = new ForLoop(parseVar(reader), topLevel, n, line);
        topLevel = false; // contained statement surely isn't a top-level one

        expect("from", reader);
        f.fromExpr = parseExpr(reader);
        expect("to", reader);
        f.toExpr = parseExpr(reader);
        Token t = tok.getToken(reader, ref line);
        if (t.type != TokenType.KEYWORD || (t.value != "do" && t.value != "step"))
        {
            throw new NinjacException(false, "expected \"do\" or \"step\"", t.line);
        }
        bool step = t.value == "step";
        tok.tokenOK();
        if (step)
        {
            f.stepExpr = parseExpr(reader);
            expect("do", reader);
        }
        else
        {
            f.stepExpr = new Constant(1.0);
        }
        f.stmt = parseStmt(reader);

        return f;
    }

    protected Statement parseBlock(TextReader reader)
    {
        Token t = tok.getToken(reader, ref line);
        if (t.type == TokenType.KEYWORD && t.value == "end")
        {
            tok.tokenOK();
            return new Block(topLevel, n);
        }
        Block b = new Block(topLevel, n);
        topLevel = false; // may contain other statements - they surely aren't top-level ones
        for (; ; )
        {

            b.append(parseStmt(reader));
            t = tok.getToken(reader, ref line);

            if (t.type == TokenType.KEYWORD && t.value == "end") break;
            if (t.type != TokenType.STMT_SEP)
            {
                throw new NinjacException(false, "expected ';'", t.line);
            }
            tok.tokenOK();
        }
        tok.tokenOK();

        return b;
    }

    protected Statement parseAssign(TextReader reader)
    {
        Assignment ass = new Assignment(parseVar(reader), topLevel, n);

        Token t = tok.getToken(reader, ref line);
        if (t.type != TokenType.ASSIGN)
        {
            throw new NinjacException(false, "expected assignment operator", t.line);
        }
        tok.tokenOK();
        Expression expr = parseExpr(reader);
        ass.setValue(expr);

        return ass;
    }


    protected Operator getOperator(string oper, int line)
    {
        if (oper == "+") return new PlusOperator();
        if (oper == "-") return new MinusOperator();
        if (oper == "/") return new DivOperator(line);
        if (oper == "*") return new MulOperator();
        if (oper == "\\") return new IntDivOperator(line);
        if (oper == "%") return new ModulusOperator(line);
        if (oper == "<") return new LessOperator();
        if (oper == ">") return new GreaterOperator();
        if (oper == ">=") return new GTEOperator();
        if (oper == "<=") return new LTEOperator();
        if (oper == "<>") return new NotEqualsOperator();
        if (oper == "=" || oper == "==") return new EqualsOperator();
        if (oper == "&" || oper == "&&") return new AndOperator();
        if (oper == "|" || oper == "||") return new OrOperator();

        return null;
    }

}