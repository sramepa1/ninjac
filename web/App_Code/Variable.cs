using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

public class Variable : Expression
{

    protected Ninjac n;

    protected string name;

    public Variable(string varName, Ninjac ninjac)
    {
        n = ninjac;
        name = varName;
    }



    public double evaluate()
    {
        return evalVar(name, n);
    }


    public static double evalVar(string name, Ninjac n)
    {
        if (n.localVarStack.Count == 0)
        {

            if (n.globalVars.ContainsKey(name))
            {
                return n.globalVars[name];
            }
            else
            {
                return 0.0;
            }

        }
        else
        {
            if (n.localVarStack.Peek().ContainsKey(name))
            {
                return n.localVarStack.Peek()[name];
            }
            else if (n.globalVars.ContainsKey(name))
            {
                return n.globalVars[name];
            }
            else
            {
                return 0.0;
            }
        }
    }

}