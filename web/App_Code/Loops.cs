using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

public abstract class Loop : Statement
{
    protected Ninjac n;
    protected bool topLevel;

    public Statement stmt { get; set; }

    public Loop(bool top, Ninjac ninjac)
    {
        topLevel = top;
        n = ninjac;
        stmt = null;
    }

    public abstract void execute();
}


public class ForLoop : Loop
{
    protected string vName;

    public Expression fromExpr { get; set; }
    public Expression toExpr { get; set; }
    public Expression stepExpr { get; set; }

    public ForLoop(string varName, bool top, Ninjac n)
        : base(top, n)
    {
        vName = varName;
    }

    public override void execute()
    {
        double from = fromExpr.evaluate();
        double to = toExpr.evaluate();
        double step = Math.Abs(stepExpr.evaluate());
        bool up = to >= from;

        double varValue = from;
        while ((up && (varValue <= to + Ninjac.DELTA))
              || (!up && (varValue >= to - Ninjac.DELTA)))
        {

            n.assignVar(vName, varValue);
            stmt.execute();
            varValue = up ? varValue + step : varValue - step;
        }

        if ((varValue == from))
        {
            n.assignVar(vName, from);
        }

        if (n.ia() && topLevel)
        {
            n.outputLine("OK");
        }
    }
}


public abstract class CondLoop : Loop
{
    public Expression cond { get; set; }

    public CondLoop(bool top, Ninjac n)
        : base(top, n)
    {
        cond = null;
    }

    //public abstract void execute();
}


public class RepeatLoop : CondLoop
{
    public RepeatLoop(bool top, Ninjac n)
        : base(top, n)
    { }

    public override void execute()
    {
        do
        {
            stmt.execute();
        } while (Math.Abs(cond.evaluate()) <= Ninjac.DELTA);

        if (n.ia() && topLevel)
        {
            n.outputLine("OK");
        }
    }
}


public class WhileLoop : CondLoop
{
    public WhileLoop(bool top, Ninjac n)
        : base(top, n)
    { }

    public override void execute()
    {
        while (Math.Abs(cond.evaluate()) > Ninjac.DELTA)
        {
            stmt.execute();
        }

        if (n.ia() && topLevel)
        {
            n.outputLine("OK");
        }
    }
}


