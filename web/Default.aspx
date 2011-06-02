<%@ Page Language="C#"  CodeFile="Default.aspx.cs" Inherits="_Default" MasterPageFile="~/MasterPage.master" Title="NINJAC - interaktivní mód" %>

<asp:Content ID="InteractiveMode" ContentPlaceHolderID="Main" Runat="Server">
    <asp:ScriptManager ID="InteractiveModeScriptManager" runat="server">
        <Services>
            <asp:ServiceReference Path="~/NinjacServiceInteractive.asmx" InlineScript="True" />
        </Services>
    </asp:ScriptManager>

    <div id="console" class="console"></div>

    <script type="text/javascript">
        var disabled;

        function disable() {
            disabled = true;
            document.getElementById("command_enter").disabled = true;
            document.getElementById("command_reset").disabled = true;

            document.getElementById("command_enter").className = "disabled";
            document.getElementById("command_reset").className = "disabled";
        }

        function enable() {
            disabled = false;
            document.getElementById("command_enter").disabled = false;
            document.getElementById("command_reset").disabled = false;

            document.getElementById("command_enter").className = "command_button";
            document.getElementById("command_reset").className = "command_button";
        }

        //reset
        function successReset() {
            document.getElementById('console').innerHTML = "";
            $("#command").focus();
            $("#command").select();
            document.getElementById('variables').innerHTML = "";
            document.getElementById('info').style.display = "none";
            enable();
        }

        function failureReset() {
            alert("Reset failed. Server may not be responding, please check your connection.");
            enable();
        }

        function loadReset() {
            disable();
            NinjacServiceInteractive.reset(successReset, failureReset, null);
        }


        //load results
        function parseVariables(data) {
            var container = document.getElementById('variables');
            container.innerHTML = data;

            if (data == "") {
                document.getElementById('info').style.display = "none";
            } else {
                document.getElementById('info').style.display = "block";
                container.innerHTML = data;
            }
        }

        function successResult(result) {
            var parts = result.split('\|', 2);
            parseVariables(parts[1]);

            var tag = document.createElement("span");
            tag.className = "bot";

            if (parts[0].match('#!')) {
                tag.className = "bot error";
            } else {
                tag.className = "bot";
            }

            tag.innerHTML = parts[0];
            document.getElementById('console').appendChild(tag);

            $("#console").scrollTop($("#console")[0].scrollHeight);

            $("#command").focus();
            $("#command").select();
            enable();
        }

        function failureResult() {
            alert("Execution failed. Your script line may have generated an excessively long output, or the server stopped responding.");
            enable();
        }

        function loadResult() {
            disable();

            var tag = document.createElement("span");
            tag.className = "human";
            tag.innerHTML = $("#command").val() + "<br>";
            document.getElementById('console').appendChild(tag);

            NinjacServiceInteractive.executeLine($("#command").val(), successResult, failureResult, null);
        }


        //enter
        function catchEnter(e) {
            if (!e) {
                e = window.event;
            }

            var code = (e.keyCode) ? e.keyCode : e.which;

            if (code == 13) {
                if (!disabled) {
                    loadResult();
                }
                return false;
            } else if (code == 3) {
                return false;
            } else {
                return true;
            }

        }

        window.onload = function () {
            document.onkeypress = catchEnter; 
        };

    </script>

    <div id="commandLine">

                <table cellpadding="0" cellspacing="0" width="100%" class="commandHolder">
                    <tr>
                        <td style="width:50px">
                            <input id="command_reset" class="command_button" type="button" value="Reset" onclick="loadReset();"/>
                        </td>
                        <td>
                            <input id="command" type="text" />
                        </td>
                        <td style="width:50px">
                            <input id="command_enter" class="command_button" type="button" value="Enter" onclick="loadResult();"/>
                        </td>
                    </tr>
                </table>

    </div>

    <div id="info" style="display:none">
    <h3>Proměnné</h3>
    <div id="variables"></div>
    </div>

    <script type="text/javascript">
        $("#command").focus();
    </script>

</asp:Content>
