using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

public class Block : Statement
{

    protected Ninjac n;
    protected bool topLevel;

    protected List<Statement> statements;


    public Block(bool top, Ninjac ninjac)
    {
        topLevel = top;
        n = ninjac;

        statements = new List<Statement>();
    }

    public void append(Statement s)
    {
        statements.Add(s);
    }


    public void execute()
    {
        foreach (var stmt in statements)
        {
            stmt.execute();
        }

        if (n.ia() && topLevel)
        {
            n.outputLine("OK");
        }
    }
}