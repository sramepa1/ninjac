using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

public class NinjacException : Exception
{
    public bool isRuntime { get; set; }
    public int line { get; set; }
    public string message { get; set; }

    public NinjacException(bool runtime, string msg, int lin)
    {
        line = lin;
        message = msg;
        isRuntime = runtime;
    }
}