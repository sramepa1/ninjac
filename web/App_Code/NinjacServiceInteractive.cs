using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Services;
using System.IO;

[WebService(Namespace = "http://localhost/")]
[WebServiceBinding(ConformsTo = WsiProfiles.BasicProfile1_1)]
// To allow this Web Service to be called from script, using ASP.NET AJAX, uncomment the following line. 
[System.Web.Script.Services.ScriptService]
public class NinjacServiceInteractive : System.Web.Services.WebService
{

    public NinjacServiceInteractive()
    {
    }

    [WebMethod(EnableSession = true)]
    public string executeLine(string line)
    {

        Ninjac n = Session["ninjac"] as Ninjac;
        StringWriter writer = new StringWriter();
        StringReader reader = new StringReader(line);

        if (n == null)
        {
            n = new Ninjac(true);
            Session["ninjac"] = n;
        }

        n.run(reader, writer);

        return String.Concat(writer.GetStringBuilder().ToString(), "|", n.getVariables());
    }


    [WebMethod(EnableSession = true)]
    public void reset()
    {
        Session["ninjac"] = new Ninjac(true);
    }

}
