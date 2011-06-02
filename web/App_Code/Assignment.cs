using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

public class Assignment : Statement
{

    protected bool topLevel;
    protected Ninjac n;

    protected string vName;
    protected Expression val;

    public Assignment(string varName, bool top, Ninjac ninjac)
    {
        vName = varName;
        topLevel = top;
        n = ninjac;
    }

    public void setValue(Expression value)
    {
        val = value;
    }

    public void execute()
    {
        double newVal = val.evaluate();
        n.assignVar(vName, newVal);

        if (n.ia())
        {
            n.outputLine(string.Format("Variable ${0} is now {1}", vName, n.formatDouble(newVal)));
        }
    }
}