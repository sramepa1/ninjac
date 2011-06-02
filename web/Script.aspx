<%@ Page Language="C#" AutoEventWireup="true" CodeFile="Script.aspx.cs" Inherits="Script" MasterPageFile="~/MasterPage.master" Title="NINJAC - skriptový mód" %>

<asp:Content ID="ScriptMode" ContentPlaceHolderID="Main" Runat="Server">
    <asp:ScriptManager ID="ScriptModeScriptManager" runat="server">
    </asp:ScriptManager>

    
        <textarea id="textarea" cols="20" rows="10"></textarea>
        <input id="script" type="file" />
    

</asp:Content>

