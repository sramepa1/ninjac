using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

public abstract class ExprStatement : Statement
{

    protected Ninjac n;

    public Expression expr { get; set; }

    public ExprStatement(Ninjac ninjac)
    {
        n = ninjac;

        expr = null;
    }

    public abstract void execute();
}


public class ExpressionStatement : ExprStatement
{
    public ExpressionStatement(Ninjac ninjac)
        : base(ninjac)
    { }

    public override void execute()
    {
        double result = expr.evaluate();

        if (n.ia())
        {
            n.outputLine(n.formatDouble(Math.Abs(result) < Ninjac.DELTA ? 0.0 : result));
        }
    }
}


public class PrintStatement : ExprStatement
{
    public PrintStatement(Ninjac ninjac)
        : base(ninjac)
    { }

    public override void execute()
    {
        double result = expr.evaluate();
        n.outputLine(n.formatDouble(Math.Abs(result) < Ninjac.DELTA ? 0.0 : result));
    }
}


public class PrecisionStatement : ExprStatement
{
    public PrecisionStatement(Ninjac ninjac)
        : base(ninjac)
    { }

    public override void execute()
    {
        int result = n.setPrecision(expr.evaluate());

        if (n.ia())
        {
            n.outputLine(String.Format("Display set to {0} decimal place{1}.", result, result == 1 ? "" : "s"));
        }
    }
}
