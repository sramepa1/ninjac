using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

public struct Func
{
    public List<string> args;
    public Statement body;
    public Expression retExpr;
}

public class FunctionDeclaration : Statement
{
    protected Ninjac n;

    protected string name;
    protected Func function;

    public FunctionDeclaration(string funcName, Ninjac ninjac)
    {
        n = ninjac;
        name = funcName;

        function = new Func { args = new List<string>(), body = null, retExpr = null };
    }

    public bool hasArgument(string arg)
    {
        return function.args.Contains(arg);
    }

    public void addArgument(string arg)
    {
        function.args.Add(arg);
    }

    public void setBody(Statement body)
    {
        function.body = body;
    }

    public void setReturn(Expression expr)
    {
        function.retExpr = expr;
    }

    public void execute()
    {
        n.functions.Add(name, function);

        if (n.ia())
        {
            n.outputLine(string.Format("Function {0} of {1} argument{2} successfully declared.", name, function.args.Count, function.args.Count == 1 ? "" : "s"));
        }
    }
}


public class FunctionCall : Expression
{
    protected Ninjac n;

    protected string name;
    protected List<Expression> values;
    protected int line;


    public FunctionCall(string funcName, int lin, Ninjac ninjac)
    {
        n = ninjac;
        name = funcName;
        line = lin;

        values = new List<Expression>();
    }

    public void addValue(Expression val)
    {
        values.Add(val);
    }

    public double evaluate()
    {
        if (!n.functions.ContainsKey(name))
        {
            throw new NinjacException(true, string.Concat("unknown function: ", name), line);
        }

        Func fn = n.functions[name];
        int expArgs = fn.args.Count;
        if (expArgs != values.Count)
        {
            throw new NinjacException(true, String.Format("argument count mismatch - expected {0}, found {1}", expArgs, values.Count), line);
        }

        if (n.localVarStack.Count >= 1000)
        {
            throw new NinjacException(true, "stack overflow", line);
        }

        Dictionary<string, double> argmap = new Dictionary<string, double>();
        for (int i = 0; i < expArgs; i++)
        {
            argmap[fn.args[i]] = values[i].evaluate();
        }

        n.localVarStack.Push(argmap);

        if (fn.body != null)
        {
            fn.body.execute();
        }

        double result = fn.retExpr.evaluate();

        n.localVarStack.Pop();

        if (Double.IsNaN(result) || Double.IsInfinity(result))
        {
            throw new NinjacException(true, "argument(s) outside function's domain", line);
        }

        return result;
    }
}