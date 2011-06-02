<%@ Page Language="C#" AutoEventWireup="true" CodeFile="Script.aspx.cs" Inherits="Script" MasterPageFile="~/MasterPage.master" Title="NINJAC - skriptový mód" %>

<asp:Content ID="ScriptMode" ContentPlaceHolderID="Main" Runat="Server">
    <asp:ScriptManager ID="ScriptModeScriptManager" runat="server">
        <Services>
            <asp:ServiceReference Path="~/NinjacServiceScript.asmx" InlineScript="True" />
        </Services>
    </asp:ScriptManager>

    <div id="console" style="height:50px"></div>

    <script type="text/javascript">
        var disabled;

        function disable() {
            disabled = true;
            document.getElementById("command_enter").disabled = true;
            document.getElementById("command_clean").disabled = true;
        }

        function enable() {
            disabled = false;
            document.getElementById("command_enter").disabled = false;
            document.getElementById("command_clean").disabled = false;
        }

        //clean
        function clean() {
            var scriptarea = document.getElementById('scriptarea');
            scriptarea.value = "";
        }

        //load results
        function successResut(result) {
            var console = document.getElementById('console');
            console.innerHTML = result;
            $("#console").scrollTop($("#console")[0].scrollHeight);
            enable();
        }

        function failureResut() {
            alert("Execution failed. Your script line may have generated an excessively long output, or the server stopped responding.");
            enable();
        }

        function loadResut() {
            disable();
            NinjacServiceScript.executeScript($("#scriptarea").val(), successResut, failureResut, null);
        }


    </script>

    <div id="commandLine">

                <table cellpadding="0" cellspacing="0" width="100%" class="commandHolder">
                    <tr>
                        <td colspan="3">
                            <textarea style="width:99%;height:300px" id="scriptarea"></textarea>
                        </td>
                    </tr>

                    <tr>
                        <td style="width:50px">
                            <input id="command_clean" class="command_button" type="button" value="Clean" onclick="clean();"/>
                        </td>
                        <td>
                            
                        </td>
                        <td style="width:50px">
                            <input id="command_enter" class="command_button" type="button" value="Enter" onclick="loadResut();"/>
                        </td>
                    </tr>
                </table>

    </div>

    <script type="text/javascript">
        $("#command").focus();
    </script>
    
</asp:Content>

