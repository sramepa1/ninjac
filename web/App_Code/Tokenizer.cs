using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.IO;
using System.Text;

public enum TokenType
{
    OPER,
    NUM,
    FUNC,
    LEFT_P,
    RIGHT_P,
    ARG_SEP,
    VAR,
    KEYWORD,
    STMT_SEP,
    ASSIGN,
    END
}

public class Token
{
    public Token()
    { }

    public TokenType type { get; set; }
    public string value { get; set; }
    public int line { get; set; }

    public int argc { get; set; }
}



public class Tokenizer
{
    protected Parser parser;
    protected Token cache;
    protected TokenType lastToken;

    protected Dictionary<string, int> prior;

    public Tokenizer(Parser p)
    {
        parser = p;
        reset();

        prior = new Dictionary<string, int>();

        prior["*"] = 6;
        prior["/"] = 6;
        prior["\\"] = 6;
        prior["%"] = 6;

        prior["+"] = 5;
        prior["-"] = 5;

        prior["<"] = 4;
        prior[">"] = 4;
        prior["<="] = 4;
        prior[">="] = 4;

        prior["="] = 3;
        prior["=="] = 3;
        prior["<>"] = 3;

        prior["&"] = 2;
        prior["&&"] = 2;

        prior["|"] = 1;
        prior["||"] = 1;
    }


    public Token getToken(TextReader reader, int line)
    {
        if (cache != null)
        {
            return cache;
        }
        int c;
        Token t = new Token();
        bool comment = false;
        StringBuilder val = new StringBuilder();

        // skip whitespace and comments
        do
        {
            c = reader.Read();
            if (c < 0)
            {
                t.type = TokenType.END;
                t.line = line;
                cache = t;
                return t;
            }
            if (c == '\n')
            {
                line++;
                comment = false;
            }
            else if (c == '#')
            {
                comment = true;
            }
        } while (Char.IsWhiteSpace((char)c) || comment);

        // identify token
        if (c == '(')
        {
            t.type = TokenType.LEFT_P;
        }
        else if (c == ')')
        {
            t.type = TokenType.RIGHT_P;
        }
        else if (c == ',')
        {
            t.type = TokenType.ARG_SEP;
        }
        else if (c == ';')
        {
            t.type = TokenType.STMT_SEP;
        }
        else if (c == ':')
        {
            t.type = TokenType.ASSIGN;
            if (reader.Peek() == '=')
            {
                reader.Read();
            }
        }
        else if (Char.IsDigit((char)c) || (c == '-' && lastToken != TokenType.NUM && lastToken != TokenType.FUNC && lastToken != TokenType.RIGHT_P && lastToken != TokenType.VAR))
        {
            /* That if-monstrosity is because "-" followed by a digit is the only ambiguous thing in the NINJAC language.
             * It may be the beginning of a constant *OR* an operator followed by a constant.
             * And since this is a single-pass parser, I can't guess and then go back in the stream
             * So I keep track of what was the last token to determine whether it could
             * be folloewd by a negative constant or not.
             */
            t.type = TokenType.NUM;
            val.Append((char)c);
            if (c == '-' && !Char.IsDigit((char)reader.Peek()))
            {
                t.type = TokenType.OPER; //negative constant could have been here, but it actually was an operator
            }
            else
            {
                for (; ; )
                {
                    c = reader.Peek();
                    if (Char.IsDigit((char)c) || c == '.')
                    {
                        c = reader.Read();
                        val.Append((char)c); // store the string char-by-char
                    }
                    else break;
                }
            }
        }
        else if (c == '$')
        {
            t.type = TokenType.VAR;
            if (!Char.IsLetter((char)reader.Peek()))
            {
                throw new NinjacException(false, "expected variable name", line);
            }
            for (; ; )
            {
                c = reader.Peek();
                if (Char.IsLetter((char)c))
                {
                    c = reader.Read();
                    val.Append((char)c);
                }
                else break;
            }
        }
        else if (Char.IsLetter((char)c))
        {
            val.Append((char)c);
            for (; ; )
            {
                c = reader.Peek();
                if (Char.IsLetter((char)c))
                {
                    c = reader.Read();
                    val.Append((char)c);
                }
                else break;
            }
            t.type = parser.keywords.Contains(val.ToString()) ? TokenType.KEYWORD : TokenType.FUNC;
        }
        else if (parser.oneCharOper.Contains((char)c))
        {
            t.type = TokenType.OPER;
            val.Append((char)c);
            StringBuilder tmp = new StringBuilder();
            tmp.Append((char)c);
            tmp.Append((char)reader.Peek()); // try to construct two chars
            if (parser.twoCharOper.Contains(tmp.ToString()))
            {
                val.Append((char)reader.Read());
            }
        }
        else
        {
            throw new NinjacException(false, string.Format("unexpected character: {0}", (char)c), line);
        }

        lastToken = t.type;
        cache = t;

        t.value = val.ToString();
        t.line = line;
        t.argc = 0;

        return t;
    }

    public void tokenOK()
    {
        cache = null;
    }

    public void reset()
    {
        cache = null;
        lastToken = TokenType.END;
    }

    public bool hasLTEpriority(Token first, Token second)
    {
        return prior[first.value] <= prior[second.value];
    }
}