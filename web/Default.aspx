<%@ Page Language="C#"  CodeFile="Default.aspx.cs" Inherits="_Default" MasterPageFile="~/MasterPage.master" Title="NINJAC - interaktivní mód" %>

<asp:Content ID="InteractiveMode" ContentPlaceHolderID="Main" Runat="Server">
    <asp:ScriptManager ID="InteractiveModeScriptManager" runat="server">
</asp:ScriptManager>

    <div id="console">
        
    </div>

    <div id="commandLine">
        <asp:UpdatePanel ID="UpdatePanel1" runat="server">
            <ContentTemplate>
                <table cellpadding="0" cellspacing="0" width="100%" class="commandHolder">
                    <tr>
                        <td>
                            <input id="command" type="text" />
                        </td>
                        <td style="width:50px">
                            <asp:Button ID="Enter" runat="server" Text="Enter" />
                        </td>
                    </tr>
                </table>
            </ContentTemplate>
        </asp:UpdatePanel>
    </div>

</asp:Content>
