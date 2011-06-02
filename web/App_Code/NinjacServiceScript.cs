using System;
using System.IO;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Services;


[WebService(Namespace = "http://localhost/")]
[WebServiceBinding(ConformsTo = WsiProfiles.BasicProfile1_1)]
// To allow this Web Service to be called from script, using ASP.NET AJAX, uncomment the following line. 
[System.Web.Script.Services.ScriptService]
public class NinjacServiceScript : System.Web.Services.WebService
{

    public NinjacServiceScript()
    {
    }

    [WebMethod]
    public string executeScript(string script)
    {
        StringWriter output = new StringWriter();
        Ninjac n = new Ninjac(false);
        n.run(new StringReader(script), output);
        return output.GetStringBuilder().ToString();
    }

}
