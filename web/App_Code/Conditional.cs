using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

public class Conditional : Statement
{
    protected Ninjac n;
    protected bool topLevel;

    public Expression cond { get; set; }
    public Statement ifTrue { get; set; }
    public Statement ifFalse { get; set; }

    public Conditional(bool top, Ninjac ninjac)
    {
        n = ninjac;
        topLevel = top;

        cond = null;
        ifTrue = null;
        ifFalse = null;
    }


    public void execute()
    {
        if (Math.Abs(cond.evaluate()) > Ninjac.DELTA)
        {
            ifTrue.execute();
        }
        else if (ifFalse != null)
        {
            ifFalse.execute();
        }

        if (n.ia() && topLevel)
        {
            n.outputLine("OK");
        }
    }
}