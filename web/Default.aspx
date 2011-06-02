<%@ Page Language="C#"  CodeFile="Default.aspx.cs" Inherits="_Default" MasterPageFile="~/MasterPage.master" Title="NINJAC - interaktivní mód" %>

<asp:Content ID="InteractiveMode" ContentPlaceHolderID="Main" Runat="Server">
    <asp:ScriptManager ID="InteractiveModeScriptManager" runat="server">
        <Services>
            <asp:ServiceReference Path="~/NinjacServiceInteractive.asmx" InlineScript="True" />
        </Services>
    </asp:ScriptManager>

    <div id="console"></div>

    <script type="text/javascript">
        //reset
        function successReset() {

            document.getElementById('console').innerHTML = "";

           // $("#console").scrollTop($("#console")[0].scrollHeight);

            $("#command").focus();

        }

        function failureReset() {
            alert("Failure!");
        }

        function loadReset() {
            NinjacServiceInteractive.reset(successReset, failureReset, null);
        }


        //load results
        function successResut(result) {

            var tag = document.createElement("span");

            tag.innerHTML = result;

            document.getElementById('console').appendChild(tag);

            $("#console").scrollTop($("#console")[0].scrollHeight);

            $("#command").focus();

        }

        function failureResut() {
            alert("Failure!");
        }

        function loadResut() {
            NinjacServiceInteractive.executeLine($("#command").val(), successResut, failureResut, null);
        }


        //enter
        function catchEnter(e) {
            if (!e) {
                e = window.event;
            }

            var code = (e.keyCode) ? e.keyCode : e.which;

            if (code == 13) {
                loadResut();
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
                            <input id="command_enter" class="command_button" type="button" value="Enter" onclick="loadResut();"/>
                        </td>
                    </tr>
                </table>

    </div>

    <script type="text/javascript">
        $("#command").focus();
    </script>

</asp:Content>
