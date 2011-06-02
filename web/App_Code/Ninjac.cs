using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.IO;
using System.Text;


public class Ninjac
{

    protected bool interactive;
    protected string format;
    protected Parser parser;

    public Dictionary<string, double> globalVars { get; set; }
    public Stack<Dictionary<string, double>> localVarStack { get; set; }
    public Dictionary<string, Func> functions { get; set; }

    TextWriter writer;

    public Block program { get; set; }

    public static readonly double DELTA = 1e-12;

    public Ninjac(bool ia)
    {
        interactive = ia;
        globalVars = new Dictionary<string, double>();
        localVarStack = new Stack<Dictionary<string, double>>();
        functions = new Dictionary<string, Func>();

        parser = new Parser(this);

        format = "0.############";

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
        return d.ToString(format);
    }

    public string getVariables()
    {
        StringBuilder b = new StringBuilder();
        foreach (var item in globalVars)
        {
            b.AppendLine(String.Format("${0} = {1}<br/>", item.Key, item.Value));
        }
        return b.ToString();
    }

    public int setPrecision(double precision)
    {
        precision = Math.Abs(precision);
        int prec = (int)Math.Round(precision);

        prec = Math.Max(1, prec);
        prec = Math.Min(15, prec);

        System.Text.StringBuilder sb = new System.Text.StringBuilder("0.");

        for (int i = 0; i < prec; i++)
        {
            sb.Append('#');
        }

        format = sb.ToString();

        return prec;
    }


    public void run(TextReader reader, TextWriter writer)
    {
        this.writer = writer;
        program = new Block(false, this);
        try
        {
            parser.parse(reader);
            program.execute();
        }
        catch (NinjacException e)
        {
            outputException(e);
            if (!interactive) outputLine(string.Format("  on line {0}. Script execution stopped.", e.line));
        }
        parser.reset();
        localVarStack.Clear();
    }


    public void outputException(NinjacException e)
    {
        outputLine(String.Format("{0} error: {1}", (e.isRuntime ? "Runtime" : "Parse"), e.message));
    }


    public void outputLine(string line)
    {
        writer.WriteLine(String.Concat("#&gt; ", line, "<br />"));
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