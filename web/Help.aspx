<%@ Page Language="C#" AutoEventWireup="true" CodeFile="Help.aspx.cs" Inherits="Help" MasterPageFile="~/MasterPage.master" Title="NINJAC - nápověda" %>

<asp:Content ID="NinjacHelp" ContentPlaceHolderID="Main" Runat="Server">
<h2>O programu</h2>
<p>Program NINJAC (NINJAC Is Not Just A Calculator) je interaktivní programovatelná kalkulačka s webovým uživatelským rozhraním. Zároveň jde o interpreta jednoduchého skriptovacího jazyka vytvořeného pro řešení nepříliš složitých matematických úloh. Skriptovací jazyk umožňuje práci s proměnnými, větvení kódu (úplný i neúplný příkaz if), cykly s pevným počtem opakování, s podmínkou na začátku i na konci a deklaraci uživatelských funkcí. Kalkulačka umí vyhodnocovat algebraické výrazy libovolné složitosti a nabízí běžnou sadu operátorů, vestavěných funkcí a konstant.</p>

<h2>Použití programu</h2>

<h3>Interaktivní režim</h3>
<p>Interaktivní režim je výchozí při otevření webu. V interaktivním režimu se NINJAC chová takto:</p>
<ul>
<li>Vstup je načítán po řádcích, uživatel tedy napíše příkazy nebo výrazy a spustí jejich vyhodnocení.</li>
<li>Výsledek výrazů na místě příkazu není zahozen, ale vypsán – pro jednoduché vstupy se tedy program skutečně chová jako kalkulačka.</li>
<li>Ostatní příkazy, jsou-li na nejvyšší úrovni ve skriptu, dají na výstupu najevo svůj úspěšný průběh.</li>
<li>Ať už je vstup zpracován úspěšně, nebo skončí chybou, vnitřní stav je před dalším vstupem vymazán, kromě tabulky funkcí a globálních proměnných.</li>
<li>Chyby jsou hlášeny stručně (řádek, na kterém mohly nastat, je stejně pouze jeden) a po chybovém hlášení lze normálně pokračovat v další práci s programem. Nastala-li chyba za běhu, všechny změny tabulky funkcí a globálních proměnných, které byly vykonány před ní, zůstanou v platnosti.</li>
</ul>

<h3>Skriptový režim</h3>
<p>Skriptový režim je k dispozici na zvláštní záložce webu a slouží pro práci se souborovým vstupem. V tomto režimu NINJAC načítá celý vstup (až do konce souboru) a následně spustí načtený program.</p>
<ul>
<li>Jediné, co se dostane na výstup, jsou výsledky vyhodnocení výrazů za příkazy print a případná chybová hlášení.</li>
<li>Nastane-li chyba, NINJAC oznámí, na kterém řádku vstupu k ní došlo (i v případě, že se jedná o chybu za běhu – pozice problémových příkazů ve zdroji je známa), a ukončí se s nenulovou návratovou hodnotou.</li>
</ul>

<h3>Příklady použití</h3>

<code>
<pre>
3+3
#> 6
for $i from 1 to 5 do $i
#> 1
#> 2
#> 3
#> 4
#> 5
#> OK
3+(2-1
#> Parse error: unmatched parthenses
3+2*5
#> 13
pi
#> 3.14159265359
ln(2) * 100
#> 69.314718056
set $test := 40 + 2
#> Variable $test is now 42
</pre>
</code>


<h2>Skriptovací jazyk</h2>
<h3>Základní vlastnosti</h3>
<p>Skriptovací jazyk je velmi jednoduchý a byl vytvořen na míru svému použití v programovatelné kalkulačce. Hned na úvod tedy zmíním, že podporuje pouze jediný datový typ (proměnných, konstant, návratových hodnot…) a to desetinné číslo, vnitřně double.</p>

<p>Další podporované vlastnosti jsou větvení kódu, cykly, bloky příkazů, funkce (včetně deklarace uživatelských funkcí), přiřazování hodnot proměnným, příkaz pro výstup (v dávkovém režimu nutný), příkaz pro nastavení zobrazované přesnosti a příkaz pro ukončení běhu interpreta.</p>

<p>Syntaxe zápisu programů je zčásti převzata z jazyka Pascal, především pokud jde o 
    roli středníku – jde striktně o oddělovač příkazů, nikoliv o ukončení příkazu. 
    Používá se tedy pouze a právě tam, kde je potřeba oddělit dva příkazy na stejné 
    úrovni (uvnitř bloku), jiné použití povede k chybě parsování (bude očekáván 
    další příkaz). Na konci programu není nic – koncem je buď konec řádku v 
    interaktivním nebo konec souboru v dávkovém režimu.</p>

<p>Jazyk je case-sensitive pro všechna klíčová slova, názvy proměnných i funkcí a je do značné míry whitespace-insensitive. Proměnná je uvozena znakem $, po kterém bezprostředně následuje její název (řetězec malých/velkých písmen). Volání funkce není uvozeno nijak a její název je také řetězec malých/velkých písmen.</p>

<p>Jsou podporovány také komentáře – uvozují se znakem # a končí odřádkováním.</p>

<h3>Výrazy a operátory</h3>
<p>Kalkulačka rozumí standardnímu způsobu zápisu matematických výrazů, tedy například toto je platný výraz:</p>

<code>
<pre>
-3 * ln(exp(42)) + 2 / (350.25*3 / 5) + rand * pow(3,8) + sqrt(2)
</pre>
</code>

<p>Konstanty se zapisují s desetinnou tečkou (nesmí být prvním znakem a nesmí okolo ní být bílé znaky) a mohou začínat mínusem (opět mezi mínusem a první číslicí nesmí být mezera, operátor „unární mínus“ zde neexistuje).</p>
<p>Parametry funkcí se píší do závorek a oddělují se čárkami. Pokud funkce žádné vstupní parametry nemá, prázdné závorky známé z C se nepíší.</p>
<p>Všechny operátory jsou binární a levostranně asociativní, priority jsou stejné jako v jazyku C. Relační a booleovské operátory vždy vrací 0 nebo 1, booleovské uvažují operandy nenula (pravda) / nula (nepravda). Práh nulovosti (rovnosti) je „absolutní hodnota čísla (rozdílu) menší rovna 10<sup>-12</sup>“.</p>

<table>
<thead>
<tr><th>Operátor</th><th>význam</th></tr>
</thead>
<tbody>
<tr><td>+</td><td>sčítání</td></tr>
<tr><td>-</td><td>odčítání</td></tr>
<tr><td>/</td><td>dělení</td></tr>
<tr><td>*</td><td>násobení</td></tr>
<tr><td>\</td><td>celočíselné dělení (zaokrouhlí operandy)</td></tr>
<tr><td>%</td><td>zbytek po celočíselném dělení</td></tr>
<tr><td>&lt;</td><td>menší než</td></tr>
<tr><td>&gt;</td><td>větší než</td></tr>
<tr><td>&lt;=</td><td>menší rovno</td></tr>
<tr><td>&gt;=</td><td>větší rovno</td></tr>
<tr><td>= nebo ==</td><td>rovno</td></tr>
<tr><td>&lt;&gt;</td><td>nerovno</td></tr>
<tr><td>&amp; nebo &amp;&amp;</td><td>logický součin (AND)</td></tr>
<tr><td>| nebo ||</td><td>logický součet (OR)</td></tr>
</tbody>
</table>

<p>Logická negace nemá operátor, je realizována vestavěnou funkcí not(…). Logický součet a součin jsou vždy vyhodnocovány zkráceně (short-circuit).</p>

<p>Vestavěné funkce jsou:</p>
<ul>
<li>Bez parametrů: pi, e, rand</li>
<li>S jedním parametrem: not, sqrt, abs, sgn, round, ln, exp, log, sin, asin, cos, acos, tan, atan</li>
<li>Se dvěma parametry: pow, max, min</li>
</ul>

<p>Většina vestavěných funkcí je přímo přejata (název, chování a vlastně i implementace) z matematické knihovny C++. Liší se pouze log (přejmenovaný log10) a přibyly pi, e (konstantní funkce, odpovídají 
    konstantám matematické knihovny), not, max, min (jejich význam je zřejmý z názvu) a sgn (signum).</p>

<h3>Proměnné</h3>
<p>NINJAC rozlišuje globální a lokální proměnné. Globální jsou všechny proměnné ve vlastním skriptu včetně případné řídící proměnné for-cyklu, rozsahy platnosti (scope) podporovány nejsou. 
    Tabulku globálních proměnných a jejich hodnot NINJAC v interaktivním módu 
    vypisuje. Lokální proměnné jsou uvažovány ve funkcích a mohou zastínit své stejnojmenné globální protějšky. Je-li globální proměnná zastíněna, nelze k ní z funkce přistoupit. Při vyhodnocování hodnoty proměnné se postupuje takto:</p>

<ol>
<li>Nenachází-li se řízení ve funkci, hledá se v globálních proměnných</li>
<li>Nachází-li se řízení ve funkci a proměnná je nalezena mezi lokálními, použije se tato hodnota</li>
<li>Nachází-li se řízení ve funkci a proměnná není nalezena mezi lokálními, hledá se v globálních</li>
</ol>

<p>Hodnota proměnné, která není nalezena (nebyla inicializována) je vždy 0.</p>

<p>Přiřazování probíhá takto:</p>

<ol>
<li>Nenachází-li se řízení ve funkci, přiřadí se globální proměnné (ať existovala nebo ne)</li>
<li>Nachází-li se řízení ve funkci a proměnná je nalezena mezi lokálními, hodnota je přiřazena sem</li>
<li>Nachází-li se řízení ve funkci a proměnná není nalezena mezi lokálními:</li>
<ol>
<li>Existuje-li mezi globálními, je hodnota přiřazena tam</li>
<li>Neexistuje-li vůbec, je vytvořena nová lokální proměnná</li>
</ol>
</ol>

<p>Přiřazení je uvozeno klíčovým slovem set, následuje cílová proměnná, operátor přiřazení ( : nebo := ) a libovolný výraz. Ve výsledku to vypadá takto:</p>

<code>
<pre>
$myVar + 1                      # vyhodnoceno na nulu, platny vyraz
#> 1
set $myVar := 10                # prirazeni
#> Variable $myVar is now 10
set $myVar : $myVar + 1         # take prirazeni
#> Variable $myVar is now 11
print $myVar + 10               # vyhodnoceni – $myVar je i sam o sobe vyraz
#> 21
</pre>
</code>

<h3>Větvení</h3>
<p>Pro větvení kódu je k dispozici příkaz if s volitelnou částí else. Syntaxe je následující:</p>

<code>
<pre>
if &lt;výraz&gt; then &lt;příkaz&gt; [else &lt;příkaz&gt;]
</pre>
</code>

<p>Výraz v podmínce se vyhodnocuje jako v jazyce C na nulu (nepravda) a nenulu (pravda). Práh nulovosti je pro všechny podobné příkazy a booleovské operátory 10<sup>-12</sup>.</p>

<h3>Bloky</h3>
<p>Za then, else a jinými klíčovými slovy očekává NINJAC vždy právě jeden příkaz. Chceme-li použít posloupnost více příkazů, je nutné je uzavřít do bloku a vzájemně oddělit středníky (pro názornost opět příklad s ifem):</p>

<code>
<pre>
if &lt;výraz&gt; then
begin
    &lt;příkaz 1&gt;;
    &lt;příkaz 2&gt;;
    &lt;příkaz 3&gt;
end
</pre>
</code>

<h3>Cykly</h3>
<p>Cyklus s podmínkou na začátku (while-cyklus) je opakován, dokud podmínka platí. Zápis:</p>

<code>
<pre>
while &lt;výraz&gt; do &lt;příkaz&gt;
</pre>
</code>

<p>Cyklus s podmínkou na konci je opakován, dokud podmínka platit nezačne. Implicitně se chová jako blok.</p>

<code>
<pre>
repeat
    &lt;příkaz 1&gt;;
    &lt;příkaz 2&gt;;
    &lt;příkaz 3&gt;
until &lt;výraz&gt;
</pre>
</code>

<p>Cyklus s pevným počtem opakování (for-cyklus) je trochu komplikovanější – potřebuje řídící proměnnou a dvě meze, volitelně lze nastavit velikost kroku (implicitně 1). Proměnné je přiřazena hodnota první meze a cyklus je opakován, dokud řídící proměnná nepřesáhne druhou z mezí (pokud je jí rovna, poslední iterace ještě proběhne). Přesažení je chápáno logicky podle směru iterace – ta může probíhat nahoru i dolů, rozhoduje hodnota mezí. Při nastavení kroku nelze jít do mínusu, program uvažuje pouze absolutní hodnotu výrazu. Lze použít nulu, což však přirozeně vede na nekonečnou smyčku (a z té není úniku, žádný break není podporován). Hodnoty mezí a velikosti kroku interpret vypočítá před první iterací a dále už je neaktualizuje, ani kdyby výrazy obsahovaly proměnnou, jejíž hodnota se v těle cyklu mění. Řídící proměnná postupně nabývá hodnoty tak, jak jí přikazuje cyklus a po skončení cyklu zůstane na hodnotě platné při poslední iteraci. Zápis je následující:</p>

<code>
<pre>
for &lt;proměnná&gt; from &lt;výraz&gt; to &lt;výraz&gt; [step &lt;výraz&gt;] do &lt;příkaz&gt;
</pre>
</code>

<p>Kvůli hrozbě zahlcení webu je běh všech smyček ve skriptu globálně omezen na přibližně dvacet milionů
    opakování. Při překročení tohoto limitu je ohlášena chyba.</p>

<h3>Funkce</h3>
<p>NINJAC dovoluje deklaraci uživatelských funkcí. Deklarace funkce musí být příkaz nejvyšší úrovně (nelze deklarovat podmíněně, v cyklech nebo v jiných funkcích) a jméno funkce nesmí být obsazeno (pozor na vestavěné funkce). Přestože lze funkce deklarovat i v interaktivním režimu, počítá se s nimi hlavně pro skripty, takže ani příliš nevadí, že jednou deklarované funkce už se zbavíte jen restartem interpreta.</p>
<p>Funkce může, ale nemusí mít parametry (libovolný počet a budou vždy chápány jako lokální proměnné), může a nemusí mít tělo (posloupnost příkazů – blok je implikován podobně jako u cyklu repeat) a musí vracet nějakou hodnotu (končí libovolným výrazem). Zápis je takovýto:</p>

<code>
<pre>
function &lt;jméno&gt; [of &lt;proměnná 1&gt;, &lt;proměnná 2&gt;, &lt;proměnná 3&gt;] is
   [&lt;příkaz 1&gt;;
    &lt;příkaz 2&gt;;
    &lt;příkaz 3&gt;]
return &lt;výraz&gt;
</pre>
</code>

<p>Je-li nalezeno volání funkce, je naparsováno i s argumenty tak, jak bylo zapsáno. Existence funkce a souhlas počtu argumentů se testují až za běhu – to umožňuje zápis rekurzivních funkcí bez nutnosti dopředné deklarace hlavičky.</p>

<h3>Zvláštní příkazy</h3>

<table>
<thead>
<tr><th>Příkaz</th><th>význam</th></tr>
</thead>
<tbody>
<tr><td><code>print &lt;výraz&gt</code></td><td>Výpis hodnoty výrazu na výstup. Nutný v dávkovém režimu.</td></tr>
<tr><td><code>precision &lt;výraz&gt</code></td><td>Nastavení přesnosti zobrazení výsledků. 
    Určí počet zobrazených významných číslic pro veškerý další výstup.</td></tr>
</tbody>
</table>
</asp:Content>
