using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

public abstract class Operator : Expression
{

    public Expression left { get; set; }
    public Expression right { get; set; }

    public Operator()
    {
        left = null;
        right = null;
    }

    public abstract double evaluate();
}

class PlusOperator : Operator
{
    public PlusOperator()
        : base()
    { }

    public override double evaluate()
    {
        return left.evaluate() + right.evaluate();
    }
}

class MinusOperator : Operator
{
    public MinusOperator()
        : base()
    { }

    public override double evaluate()
    {
        return left.evaluate() - right.evaluate();
    }
}

class MulOperator : Operator
{
    public MulOperator()
        : base()
    { }

    public override double evaluate()
    {
        return left.evaluate() * right.evaluate();
    }
}

class DivOperator : Operator
{
    protected int line;

    public DivOperator(int lin)
        : base()
    { line = lin; }

    public override double evaluate()
    {
        double numer = left.evaluate();
        double denom = right.evaluate();
        if (Math.Abs(denom) <= Ninjac.DELTA)
        {
            throw new NinjacException(true, "division by zero", line);
        }

        return numer / denom;
    }
}


class IntDivOperator : DivOperator
{
    public IntDivOperator(int line)
        : base(line)
    { }

    public override double evaluate()
    {
        double numer = left.evaluate();
        double denom = right.evaluate();

        if (Math.Abs(numer) > (double)long.MaxValue || Math.Abs(denom) > (double)long.MaxValue)
        {
            throw new NinjacException(true, "operand too large for integer division", line);
        }

        if (Math.Abs(denom) <= Ninjac.DELTA)
        {
            throw new NinjacException(true, "division by zero", line);
        }

        return (double)((long)numer / (long)denom);
    }
}


class ModulusOperator : DivOperator
{
    public ModulusOperator(int line)
        : base(line)
    { }

    public override double evaluate()
    {
        double numer = left.evaluate();
        double denom = right.evaluate();

        if (Math.Abs(numer) > (double)long.MaxValue || Math.Abs(denom) > (double)long.MaxValue)
        {
            throw new NinjacException(true, "operand too large for modulus calculation", line);
        }

        if (Math.Abs(denom) <= Ninjac.DELTA)
        {
            throw new NinjacException(true, "division by zero", line);
        }

        return (double)((long)numer % (long)denom);
    }
}


class AndOperator : Operator
{
    public AndOperator()
        : base()
    { }

    public override double evaluate()
    {
        double l = left.evaluate();
        if (Math.Abs(l) <= Ninjac.DELTA)
        {
            return 0.0;
        }

        return Math.Abs(right.evaluate()) <= Ninjac.DELTA ? 0.0 : 1.0;
    }
}


class OrOperator : Operator
{
    public OrOperator()
        : base()
    { }

    public override double evaluate()
    {
        double l = left.evaluate();
        if (Math.Abs(l) > Ninjac.DELTA)
        {
            return 1.0;
        }

        return Math.Abs(right.evaluate()) <= Ninjac.DELTA ? 0.0 : 1.0;
    }
}


class EqualsOperator : Operator
{
    public EqualsOperator()
        : base()
    { }

    public override double evaluate()
    {
        return Math.Abs(left.evaluate() - right.evaluate()) <= Ninjac.DELTA ? 1.0 : 0.0;
    }
}


class NotEqualsOperator : Operator
{
    public NotEqualsOperator()
        : base()
    { }

    public override double evaluate()
    {
        return Math.Abs(left.evaluate() - right.evaluate()) > Ninjac.DELTA ? 1.0 : 0.0;
    }
}


class LessOperator : Operator
{
    public LessOperator()
        : base()
    { }

    public override double evaluate()
    {
        return (left.evaluate() < (right.evaluate() - Ninjac.DELTA)) ? 1.0 : 0.0;
    }
}


class LTEOperator : Operator
{
    public LTEOperator()
        : base()
    { }

    public override double evaluate()
    {
        return (left.evaluate() <= (right.evaluate() + Ninjac.DELTA)) ? 1.0 : 0.0;
    }
}


class GreaterOperator : Operator
{
    public GreaterOperator()
        : base()
    { }

    public override double evaluate()
    {
        return (left.evaluate() > (right.evaluate() + Ninjac.DELTA)) ? 1.0 : 0.0;
    }
}


class GTEOperator : Operator
{
    public GTEOperator()
        : base()
    { }

    public override double evaluate()
    {
        return (left.evaluate() >= (right.evaluate() - Ninjac.DELTA)) ? 1.0 : 0.0;
    }
}
