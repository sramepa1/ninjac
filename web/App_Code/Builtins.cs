using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

public class BuiltInPi : Expression
{
    public double evaluate()
    {
        return Math.PI;
    }
}

public class BuiltInE : Expression
{
    public double evaluate()
    {
        return Math.E;
    }
}

public class BuiltInRand : Expression
{
    protected Random rnd = new Random();
    public double evaluate()
    {
        return rnd.NextDouble();
    }
}

public class BuiltInNot : Expression
{
    protected Ninjac n;
    public BuiltInNot(Ninjac ninjac)
    {
        n = ninjac;
    }

    public double evaluate()
    {
        return (Variable.evalVar("firstarg", n) <= Ninjac.DELTA) ? 1.0 : 0.0;
    }
}

public class BuiltInSqrt : Expression
{
    protected Ninjac n;
    public BuiltInSqrt(Ninjac ninjac)
    {
        n = ninjac;
    }

    public double evaluate()
    {
        return Math.Sqrt(Variable.evalVar("firstarg", n));
    }
}


public class BuiltInAbs : Expression
{
    protected Ninjac n;
    public BuiltInAbs(Ninjac ninjac)
    {
        n = ninjac;
    }

    public double evaluate()
    {
        return Math.Abs(Variable.evalVar("firstarg", n));
    }
}

public class BuiltInRound : Expression
{
    protected Ninjac n;
    public BuiltInRound(Ninjac ninjac)
    {
        n = ninjac;
    }

    public double evaluate()
    {
        return Math.Round(Variable.evalVar("firstarg", n));
    }
}

public class BuiltInSin : Expression
{
    protected Ninjac n;
    public BuiltInSin(Ninjac ninjac)
    {
        n = ninjac;
    }

    public double evaluate()
    {
        return Math.Sin(Variable.evalVar("firstarg", n));
    }
}

public class BuiltInCos : Expression
{
    protected Ninjac n;
    public BuiltInCos(Ninjac ninjac)
    {
        n = ninjac;
    }

    public double evaluate()
    {
        return Math.Cos(Variable.evalVar("firstarg", n));
    }
}

public class BuiltInTan : Expression
{
    protected Ninjac n;
    public BuiltInTan(Ninjac ninjac)
    {
        n = ninjac;
    }

    public double evaluate()
    {
        return Math.Tan(Variable.evalVar("firstarg", n));
    }
}

public class BuiltInASin : Expression
{
    protected Ninjac n;
    public BuiltInASin(Ninjac ninjac)
    {
        n = ninjac;
    }

    public double evaluate()
    {
        return Math.Asin(Variable.evalVar("firstarg", n));
    }
}

public class BuiltInACos : Expression
{
    protected Ninjac n;
    public BuiltInACos(Ninjac ninjac)
    {
        n = ninjac;
    }

    public double evaluate()
    {
        return Math.Acos(Variable.evalVar("firstarg", n));
    }
}

public class BuiltInATan : Expression
{
    protected Ninjac n;
    public BuiltInATan(Ninjac ninjac)
    {
        n = ninjac;
    }

    public double evaluate()
    {
        return Math.Atan(Variable.evalVar("firstarg", n));
    }
}

public class BuiltInLog : Expression
{
    protected Ninjac n;
    public BuiltInLog(Ninjac ninjac)
    {
        n = ninjac;
    }

    public double evaluate()
    {
        return Math.Log10(Variable.evalVar("firstarg", n));
    }
}

public class BuiltInLn : Expression
{
    protected Ninjac n;
    public BuiltInLn(Ninjac ninjac)
    {
        n = ninjac;
    }

    public double evaluate()
    {
        return Math.Log(Variable.evalVar("firstarg", n));
    }
}

public class BuiltInExp : Expression
{
    protected Ninjac n;
    public BuiltInExp(Ninjac ninjac)
    {
        n = ninjac;
    }

    public double evaluate()
    {
        return Math.Exp(Variable.evalVar("firstarg", n));
    }
}

public class BuiltInSgn : Expression
{
    protected Ninjac n;
    public BuiltInSgn(Ninjac ninjac)
    {
        n = ninjac;
    }

    public double evaluate()
    {
        double d = Variable.evalVar("firstarg", n);
        return (Math.Abs(d) <= Ninjac.DELTA ? 0.0 : Math.Sign(d));
    }
}

public class BuiltInPow : Expression
{
    protected Ninjac n;
    public BuiltInPow(Ninjac ninjac)
    {
        n = ninjac;
    }

    public double evaluate()
    {
        return Math.Pow(Variable.evalVar("firstarg", n), Variable.evalVar("secondarg", n));
    }
}

public class BuiltInMax : Expression
{
    protected Ninjac n;
    public BuiltInMax(Ninjac ninjac)
    {
        n = ninjac;
    }

    public double evaluate()
    {
        return Math.Max(Variable.evalVar("firstarg", n), Variable.evalVar("secondarg", n));
    }
}

public class BuiltInMin : Expression
{
    protected Ninjac n;
    public BuiltInMin(Ninjac ninjac)
    {
        n = ninjac;
    }

    public double evaluate()
    {
        return Math.Min(Variable.evalVar("firstarg", n), Variable.evalVar("secondarg", n));
    }
}

