! Clipul cu prezentarea este public si pe youtube la adresa: https://www.youtube.com/watch?v=hMvkB9nbgdk

! Pentru ca sunetul sa poata functiona trebuie sa intram in Code Blocks la Compiler, selectam Linker Settings, in caseta la Other Linker Options trebuie sa avem urmatoarele :
 -lbgi -lgdi32 -lcomdlg32 -luuid -loleaut32 -lole32 -lwinmm

Echipa: Anfimov Vladimir, Lăzurcă Samuel-Ionuț


Meniul principal al aplicatiei noastre are 4 optiuni:

1. DIAGRAMA SIMPLA:	

Acest buton va desena diagrama pentru codul primit din fisier("algoritm_in_pseudocod.txt").

Codul trebuie scris corect! Daca codul nu este scris corect diagrama ar putea fi desenata intr-un mod eronat.

2. DIAGRAMA CU EXECUTIE:

Acest buton va desena deasemenea diagrama pentru codul primit din fisier("algoritm_in_pseudocod.txt"), dar doar daca este corect sintactic (in caz ca sunt greseli se va afisa un mesaj
de eroare ce va contine linia erorii, tipul erorii si sugestii pentru gasirea ei).
Daca la diagrama simpla conditiile si actiunile puteau fi propozitii, aici trebuie obligatoriu ca sa folosim operatorii stabiliti de noi(vezi mai jos).
Aici se va afisa si un rezultat in partea din dreapta sus sau un mesaj daca de exemplu nu a fost initializata o variabila.

3. INSTRUCTIUNI:

Apasand acest buton se pot vizualiza blocurile si pseudocodul nostru folosit la varianta diagramei cu executie.

4. IESIRE:

Apasand pe acest buton iesim din aplicatie. 

PSEUDOCODUL FOLOSIT:

Instructiuni:

*acololadele sau parantezele nu trebuie sa lipseasca!

Urmatoarele instructiuni pot fi folosite la ambele tipuri de diagrame:

actiune; //este o propozitie sau un operator si trebuie sa aiba ; la final
----------------------------
daca(conditie)
{
	bloc de instructiuni;
}
----------------------------
daca(conditie)
{
	bloc de instructiuni;
}
altfel
{
	bloc de instructiuni;
}
----------------------------
cat timp(conditie)
{
	bloc de instructiuni;
}
----------------------------
repeta
{

}cat timp(conditie);

Urmatoarele instructiuni sunt EXCLUSIV doar pentru diagrama simpla:

pentru(variabila=valoare initiala,valoare finala,pas)
{
	bloc de instructiuni;
}
----------------------------
selectati cazul()
{
	caz()
	{
		bloc de instructiuni;
	}
	caz()
	{
		bloc de instructiuni;
	}
	...
	caz(implicit)
	{
		bloc de instructiuni;
	}
}
----------------------------
intrerupe(); //asemanator cu break din C++

OPERATORI:

OPERATORI VOID(nu returneaza nimic si nu pot fi folositi ca conditii):

a. muta(variabila, variabila/constanta/operator cu return) variabila = variabila/constanta/operator cu return
b. init(lista variabile) // variabilele primesc valoarea initiala 0
c. afiseaza(lista variablile/operatori cu return) //pune automat spatiu intre variabile
d. incr(variabila) //variabila++
e. decr(variabila) //variabila--
f. sum(variabila, variabila/constanta/operator cu return)
g. dif(variabila, variabila/constanta/operator cu return)
h. prod(variabila, variabila/constanta/operator cu return)
i. imp(variabila, variabila/constanta/operator cu return)
j. exp(variabila, variabila/constanta/operator cu return) // pow
k. mod(variabila, variabila/constanta/operator cu return) 
(in afara de afiseaza si init, acesti operatori modifica valoarea primului parametru)

OPERATORI CU RETURN(returneaza 1 sau 0 si nu pot fi folositi ca actiuni):

a. egal(variabila/constanta/operator cu return, variabila/constanta/operator cu return) (==)
b. inegal(variabila/constanta/operator cu return, variabila/constanta/operator cu return) (!=)
c. mare(variabila/constanta/operator cu return, variabila/constanta/operator cu return) (>)
d. mic(variabila/constanta/operator cu return, variabila/constanta/operator cu return) (<)
e. mareg(variabila/constanta/operator cu return, variabila/constanta/operator cu return) (>=)
f. micg(variabila/constanta/operator cu return, variabila/constanta/operator cu return) (<=)
g. si(variabila/constanta/operator cu return, variabila/constanta/operator cu return) (&&)
h. sau(variabila/constanta/operator cu return, variabila/constanta/operator cu return) (||)
i. neg(variabila/constanta/operator cu return) (not)
