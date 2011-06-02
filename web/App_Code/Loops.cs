using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

public abstract class Loop : Statement
{
    protected Ninjac n;
    protected bool topLevel;

    protected int lin;
    public Statement stmt { get; set; }

    public static readonly uint LOOP_MAX = 20000000;

    public Loop(bool top, Ninjac ninjac, int line)
    {
        topLevel = top;
        n = ninjac;
        stmt = null;
        line = lin;
    }

    public void checkCounter()
    {
        if (++n.loopCounter >= LOOP_MAX)
        {
            throw new NinjacException(true, "loop limit exceeded", lin);
        }
    }

    public abstract void execute();
}


public class ForLoop : Loop
{
    protected string vName;

    public Expression fromExpr { get; set; }
    public Expression toExpr { get; set; }
    public Expression stepExpr { get; set; }

    public ForLoop(string varName, bool top, Ninjac n, int line)
        : base(top, n, line)
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

            checkCounter();
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

    public CondLoop(bool top, Ninjac n, int line)
        : base(top, n, line)
    {
        cond = null;
    }

    //public abstract void execute();
}


public class RepeatLoop : CondLoop
{
    public RepeatLoop(bool top, Ninjac n, int line)
        : base(top, n, line)
    { }

    public override void execute()
    {
        do
        {
            stmt.execute();
            checkCounter();    
        
        } while (Math.Abs(cond.evaluate()) <= Ninjac.DELTA);

        if (n.ia() && topLevel)
        {
            n.outputLine("OK");
        }
    }
}


public class WhileLoop : CondLoop
{
    public WhileLoop(bool top, Ninjac n, int line)
        : base(top, n, line)
    { }

    public override void execute()
    {
        while (Math.Abs(cond.evaluate()) > Ninjac.DELTA)
        {
            stmt.execute();
            checkCounter();
        }

        if (n.ia() && topLevel)
        {
            n.outputLine("OK");
        }
    }
}


