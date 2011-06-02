using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

public class Constant : Expression
{

    protected double value;

    public Constant(double val)
    {
        value = val;
    }

    public double evaluate()
    {
        return value;
    }
}