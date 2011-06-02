using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.IO;
using System.Text;
using System.Globalization;


public class Ninjac
{

    protected bool interactive;
    protected string format;
    protected Parser parser;

    public SortedDictionary<string, double> globalVars { get; set; }
    public Stack<Dictionary<string, double>> localVarStack { get; set; }
    public SortedDictionary<string, Func> functions { get; set; }

    TextWriter writer;

    public Block program { get; set; }
    public uint loopCounter { get; set; }

    public static readonly double DELTA = 1e-12;

    public Ninjac(bool ia)
    {
        interactive = ia;
        globalVars = new SortedDictionary<string, double>();
        localVarStack = new Stack<Dictionary<string, double>>();
        functions = new SortedDictionary<string, Func>();

        parser = new Parser(this);

        format = "G12";

        initBuiltIn();
    }

    public void assignVar(string var, double val)
    {
        if (localVarStack.Count == 0 || (globalVars.ContainsKey(var) && !localVarStack.Peek().ContainsKey(var)))
        {
            globalVars[var] = val;
        }
        else
        {
            localVarStack.Peek()[var] = val;
        }
    }

    public bool ia()
    {
        return interactive;
    }

    public string formatDouble(double d)
    {
        return d.ToString(format, CultureInfo.InvariantCulture);
    }

    public string getVariables()
    {
        StringBuilder b = new StringBuilder();

        foreach (var item in globalVars)
        {
            b.AppendLine(String.Format("<span><strong>${0}</strong>&nbsp;=&nbsp;{1}</span> ", item.Key, formatDouble(item.Value)));
        }
        return b.ToString();
    }

    public int setPrecision(double precision)
    {
        precision = Math.Abs(precision);
        int prec = (int)Math.Round(precision);

        prec = Math.Max(1, prec);
        prec = Math.Min(16, prec);

        format = String.Format("G{0}", prec);

        return prec;
    }


    public void run(TextReader reader, TextWriter writer)
    {
        this.writer = writer;
        loopCounter = 0;
        program = new Block(false, this);
        try
        {
            parser.parse(reader);
            program.execute();
        }
        catch (NinjacException e)
        {
            outputException(e);
            if (!interactive) outputError(string.Format("  on line {0}. Script execution stopped.", e.line));
        }
        parser.reset();
        localVarStack.Clear();
    }


    public void outputException(NinjacException e)
    {
        outputError(String.Format("{0} error: {1}", (e.isRuntime ? "Runtime" : "Parse"), e.message));
    }


    public void outputLine(string line)
    {
        writer.WriteLine(String.Concat("<span class=\"bot\">#&gt; ", line, "<br /></span>"));
    }

    public void outputError(string line)
    {
        writer.WriteLine(String.Concat("<span class=\"bot error\">#! ", line, "<br /></span>"));
    }

    protected void initBuiltIn()
    {
        functions["pi"] = new Func { args = new List<string>(), body = null, retExpr = new BuiltInPi() };
        functions["e"] = new Func { args = new List<string>(), body = null, retExpr = new BuiltInE() };
        functions["rand"] = new Func { args = new List<string>(), body = null, retExpr = new BuiltInRand() };
        functions["not"] = new Func { args = new List<string>(new string[] { "firstarg" }), body = null, retExpr = new BuiltInNot(this) };
        functions["sqrt"] = new Func { args = new List<string>(new string[] { "firstarg" }), body = null, retExpr = new BuiltInSqrt(this) };
        functions["abs"] = new Func { args = new List<string>(new string[] { "firstarg" }), body = null, retExpr = new BuiltInAbs(this) };
        functions["round"] = new Func { args = new List<string>(new string[] { "firstarg" }), body = null, retExpr = new BuiltInRound(this) };
        functions["sin"] = new Func { args = new List<string>(new string[] { "firstarg" }), body = null, retExpr = new BuiltInSin(this) };
        functions["cos"] = new Func { args = new List<string>(new string[] { "firstarg" }), body = null, retExpr = new BuiltInCos(this) };
        functions["tan"] = new Func { args = new List<string>(new string[] { "firstarg" }), body = null, retExpr = new BuiltInTan(this) };
        functions["asin"] = new Func { args = new List<string>(new string[] { "firstarg" }), body = null, retExpr = new BuiltInASin(this) };
        functions["acos"] = new Func { args = new List<string>(new string[] { "firstarg" }), body = null, retExpr = new BuiltInACos(this) };
        functions["atan"] = new Func { args = new List<string>(new string[] { "firstarg" }), body = null, retExpr = new BuiltInATan(this) };
        functions["log"] = new Func { args = new List<string>(new string[] { "firstarg" }), body = null, retExpr = new BuiltInLog(this) };
        functions["ln"] = new Func { args = new List<string>(new string[] { "firstarg" }), body = null, retExpr = new BuiltInLn(this) };
        functions["exp"] = new Func { args = new List<string>(new string[] { "firstarg" }), body = null, retExpr = new BuiltInExp(this) };
        functions["sgn"] = new Func { args = new List<string>(new string[] { "firstarg" }), body = null, retExpr = new BuiltInSgn(this) };
        functions["pow"] = new Func { args = new List<string>(new string[] { "firstarg", "secondarg" }), body = null, retExpr = new BuiltInPow(this) };
        functions["max"] = new Func { args = new List<string>(new string[] { "firstarg", "secondarg" }), body = null, retExpr = new BuiltInMax(this) };
        functions["min"] = new Func { args = new List<string>(new string[] { "firstarg", "secondarg" }), body = null, retExpr = new BuiltInMin(this) };
    }


}