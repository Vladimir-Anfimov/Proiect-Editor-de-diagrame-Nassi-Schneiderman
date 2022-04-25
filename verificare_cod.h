#ifndef VERIFICARE_COD_H_INCLUDED
#define VERIFICARE_COD_H_INCLUDED

#include "mesaje_eroare.h"

const int OP1=3;
const int OP2=15;
const int OPn=3;
const int NR_KWORDS=6;   //nr key words
const char DACA='D';
const char ALTFEL='A';
const char REPETA='R';
const char CAT_TIMP='C';
const char NUL='N';

char cuvinte_cheie[NR_KWORDS][12]={"daca","altfel","cat timp","pentru","repeta","intrerupe()"};
char op_un_membru[OP1][5]={"incr","decr","neg"};
char op_doi_membri[OP2][7]={"sum","dif","prod","imp","exp","mod","muta","egal","inegal","mare","mic","mareg","micg","si","sau"};
char op_n_membri[OPn][9]={"init","citeste","afiseaza"};

struct Nod{
    char tip;
    Nod *urm;
};

struct Stiva{
    Nod *varf;
};

void pop(Stiva &S)
{
    Nod *urm;

    if(S.varf!=NULL)
    {
        urm=S.varf->urm;
        delete(S.varf);
        S.varf=urm;
    }
}
void push(Stiva &S,char element)
{
    Nod *p=new Nod;
    p->tip=element;
    if(S.varf==NULL)
    {
        p->urm=NULL;
        S.varf=p;
    }
    else
    {
        p->urm=S.varf;
        S.varf=p;
    }
}
char top(Stiva S)
{
    if(S.varf!=NULL)
    {
        return S.varf->tip;
    }
    else return NUL;
}

int verificare_operator(char*);

int caracter_valid(char caracter)
{
    return (caracter>='a' && caracter<='z') || (caracter>='A' && caracter<='Z') || (caracter>='0' && caracter<='9');
}
int verificare_caractere(char buffer[BUFFER_SIZE])
{
    if(caracter_valid(buffer[0])==0 || (buffer[0]>='0' && buffer[0]<='9') ) return 0;

    for(int i=1;i<strlen(buffer);i++)
        if(caracter_valid(buffer[i])==0) {return 0;}

    return 1;
}
bool returneaza(char buffer[BUFFER_SIZE])
{
    if(strstr(buffer,"neg(")==buffer) return true;
    for(int i=7;i<OP2;i++)
        if(strstr(buffer,op_doi_membri[i])==buffer) return true;
    return false;
}
int variabila(char buffer[BUFFER_SIZE])
{
    int i;
    if(verificare_caractere(buffer)==0)
    {
        return 0;
    }
    for(i=0;i<OP1;i++)
        if(strcmp(buffer,op_un_membru[i])==0) {
                cout<<"denumire gresita a variabilei: "<<buffer<<endl;
                return 0;
        }
    for(i=0;i<OP2;i++)
        if(strcmp(buffer,op_doi_membri[i])==0) {
                cout<<"denumire gresita a variabilei: "<<buffer<<endl;
                return 0;
        }
    for(i=0;i<OPn;i++)
        if(strcmp(buffer,op_n_membri[i])==0) {
                cout<<"denumire gresita a variabilei: "<<buffer<<endl;
                return 0;
        }
    for(i=0;i<NR_KWORDS;i++)
        if(strcmp(buffer,cuvinte_cheie[i])==0) {
                cout<<"denumire gresita a variabilei: "<<buffer<<endl;
                return 0;
        }
    return 1;
}
int constanta(char buffer[BUFFER_SIZE])
{
    if((buffer[0]<'0' || buffer[0]>'9') && (buffer[0]!='-' || (buffer[0]=='-' && strlen(buffer)<=1))) return 0;

    for(int i=1;i<strlen(buffer);i++)
        if(buffer[i]<'0' || buffer[i]>'9') return 0;
    return 1;
}
bool verificare_virgula(char buffer[BUFFER_SIZE],int &poz_virgula)
{
    int nrParanteze=0;
    for(int i=0;i<strlen(buffer);i++)
    {
        if(buffer[i]=='(') nrParanteze++;
        else if(buffer[i]==')') nrParanteze--;
        else if(buffer[i]==',' && nrParanteze==0){
                if((caracter_valid(buffer[i-1])==0 && buffer[i-1]!=')') || (caracter_valid(buffer[i+1])==0 && buffer[i+1]!='-')) return false;
                poz_virgula=i;
                return true;
              }
    }
    return false;
}
int verificare_operator_un_membru(char buffer[BUFFER_SIZE],int rtr)
{
    if(variabila(buffer)) return 1;
    else if(rtr==1 && (constanta(buffer) || (returneaza(buffer) && verificare_operator(buffer)==1))) return 1;
         else return 0;
}
int verificare_operator_doi_membri(char buffer[BUFFER_SIZE],int logic)
{
    int poz_virgula=-1;
    char membru1[BUFFER_SIZE],membru2[BUFFER_SIZE];
    if(logic==1)
    {
       if(verificare_virgula(buffer,poz_virgula))
       {
           strcpy(membru1,buffer);
           membru1[poz_virgula]='\0';
           strcpy(membru2,buffer+poz_virgula+1);
           if((variabila(membru1) || constanta(membru1) || (returneaza(membru1) && verificare_operator(membru1))) &&
            (variabila(membru2) || constanta(membru2) || (returneaza(membru2) && verificare_operator(membru2)))) return 1;
           else return 0;
       }
       else return 0;
    }
    else
    {
        if(verificare_virgula(buffer,poz_virgula))
        {
           strcpy(membru1,buffer);
           membru1[poz_virgula]='\0';
           strcpy(membru2,buffer+poz_virgula+1);
           if((variabila(membru1) && verificare_operator(membru1)==0) && (variabila(membru2) || constanta(membru2) || (returneaza(membru2) && verificare_operator(membru2)))) return 1;
           else return 0;
        }
        else return 0;
    }
}
int verificare_operator_n_membri(char buffer[BUFFER_SIZE])
{
    int lungime=strlen(buffer);
    char *membru;

    if(caracter_valid(buffer[lungime-1])==0) return 0;
    membru=strtok(buffer,",");
    if(membru!=NULL)
    {
        while(membru!=NULL)
        {
        if(variabila(membru)==0) return 0;
        membru=strtok(NULL,",");
        }
        return 1;
    }
    else return 0;
}
int verificare_repeta_cat_timp(char buffer[BUFFER_SIZE],Stiva &S)
{
    int lungime,nrParanteze=0;
    lungime=strlen(buffer);

    if(top(S)!=REPETA) return 0;

    if(buffer[lungime-1]!=';' || buffer[lungime-2]!=')')
    {
        cout<<"cat timp e scris gresit"<<endl;
        return 0;
    }
    else
    {
      strcpy(buffer,buffer+strlen("}cat timp"));
      for(unsigned int i=0;i<strlen(buffer);i++)
            if(buffer[i]==')' && buffer[i-1]!='(') nrParanteze--;
            else if(buffer[i]=='(') nrParanteze++;

      if(nrParanteze!=0) {
            cout<<"parenteze puse gresit!!!";
            return 0;
      }
      else
      {
          buffer[strlen(buffer)-2]='\0';
          strcpy(buffer,buffer+1);
          if(returneaza(buffer) && verificare_operator(buffer))
            return 1;
          else
            return 0;
      }
    }
}
int verificare_acolade1(char buffer[BUFFER_SIZE])
{
    trim(buffer);
    if(strcmp(buffer,"{"))
    {
        cout<<"atentie la acolade!!!";
        return 0;
    }
    return 1;
}
int verificare_acolade2(char buffer[BUFFER_SIZE],Stiva &S,int &nrAcolade,bool &daca_lastseen)
{
    if((strlen(buffer)>1 && strstr(buffer,"cat timp")!=buffer+1) || nrAcolade<1)
    {
        cout<<"atentie la acolade!!!";
        return 0;
    }
    if(strstr(buffer,"}cat timp")==buffer)
    {
        if(verificare_repeta_cat_timp(buffer,S)==0) return 0;
        else
        {
            nrAcolade--;
            return 1;
        }
    }
    if(top(S)==NUL || top(S)==REPETA) return 0;

    if(top(S)==DACA) daca_lastseen=1;

    pop(S);
    nrAcolade--;

    return 1;
}
int verificare_daca(char buffer[BUFFER_SIZE])
{
   char *p;
   int nrParanteze=0;
   p=strstr(buffer,"daca");
   p=p+4;
   if(p==NULL)
   {
       cout<<"daca e scris incorect!"<<endl;
       return 0;
   }
   else
   {
      strcpy(buffer,p);
      for(unsigned int i=0;i<strlen(buffer);i++)
            if(buffer[i]==')' && buffer[i-1]!='(') nrParanteze--;
            else if(buffer[i]=='(') nrParanteze++;

      if(nrParanteze!=0) {
            cout<<"parenteze puse gresit!!!";
            return 0;
      }
      else
      {
          buffer[strlen(buffer)-1]='\0';
          strcpy(buffer,buffer+1);
          if(returneaza(buffer) && verificare_operator(buffer))
          {
            return 1;
          }
          else
            return 0;
      }
   }

}
int verificare_cat_timp(char buffer[BUFFER_SIZE])
{
    int lungime,nrParanteze=0;
    lungime=strlen(buffer);
    if(buffer[lungime-1]!=')')
    {
        cout<<"cat timp e scris gresit"<<endl;
        return 0;
    }
    else
    {
      strcpy(buffer,buffer+strlen("cat timp"));
      for(unsigned int i=0;i<strlen(buffer);i++)
            if(buffer[i]==')' && buffer[i-1]!='(') nrParanteze--;
            else if(buffer[i]=='(') nrParanteze++;

      if(nrParanteze!=0) {
            cout<<"parenteze puse gresit!!!";
            return 0;
      }
      else
      {
          buffer[strlen(buffer)-1]='\0';
          strcpy(buffer,buffer+1);
          if(returneaza(buffer) && verificare_operator(buffer))
            return 1;
          else
            return 0;
      }
    }
}
int verificare_repeta(char buffer[BUFFER_SIZE])
{
    if(strcmp(buffer,"repeta")) return 0;
    else return 1;
}
int verificare_altfel(char buffer[BUFFER_SIZE])
{
    if(strcmp(buffer,"altfel")) return 0;
    else return 1;
}
int verificare_intrerupe(char buffer[BUFFER_SIZE])
{
    if(strcmp(buffer,"intrerupe();")) return 0;
    else return 1;
}
int verificare_afiseaza(char buffer[BUFFER_SIZE])
{
    int i,poz_virgula=-1;
    char copie[BUFFER_SIZE],membru[BUFFER_SIZE];
    strcpy(copie,buffer);

    if(variabila(buffer) || constanta(buffer)) return true;
    else
    {
    int nrParanteze=0;
    for(i=0;i<strlen(buffer);i++)
    {
        if(buffer[i]=='(') nrParanteze++;
        else if(buffer[i]==')') nrParanteze--;
        else if(buffer[i]==',' && nrParanteze==0){
                if((caracter_valid(buffer[i-1])==0 && buffer[i-1]!=')') || (caracter_valid(buffer[i+1])==0 && buffer[i+1]!='-')) return false;
                strcpy(copie,buffer);
                buffer[i]='\0';
                strcpy(membru,buffer+poz_virgula+1);
                strcpy(buffer,copie);
                cout<<membru<<endl;
                if(variabila(membru)==0 && constanta(membru)==0 && !(returneaza(membru)==1 && verificare_operator(membru)==1)) return false;
                poz_virgula=i;
              }
    }
    buffer[i]='\0';
    strcpy(membru,buffer+poz_virgula+1);
    if(variabila(membru)==0 && constanta(membru)==0 && !(returneaza(membru)==1 && verificare_operator(membru)==1)) return false;
    return true;
    }
}
int verificare_actiune(char buffer[BUFFER_SIZE])
{
   if(variabila(buffer)==0 && buffer[strlen(buffer)-1]==';')
    {
        buffer[strlen(buffer)-1]='\0';
        return verificare_operator(buffer);
    }
   else
   {
       cout<<"actiune incorecta";
       return 0;
   }
}
int verificare_operator(char buffer[BUFFER_SIZE])
{
   int i,lungime;

   lungime=strlen(buffer);

   if(buffer[lungime-1]!=')') return 0;

   for(i=0;i<OP1;i++)
        if(strstr(buffer,op_un_membru[i])==buffer && buffer[strlen(op_un_membru[i])]=='(')
        {
            int rtr=1;
            buffer[lungime-1]='\0';
            strcpy(buffer,buffer+strlen(op_un_membru[i])+1);
            if(i<2) rtr=0;
            return verificare_operator_un_membru(buffer,rtr);
            i=OP1+1;
        }
    if(i==OP1)
    {
        for(i=0;i<OP2;i++)
        if(strstr(buffer,op_doi_membri[i])==buffer && buffer[strlen(op_doi_membri[i])]=='(')
        {
            int logic=1;
            if(i<=6) logic=0;
            buffer[lungime-1]='\0';
            strcpy(buffer,buffer+strlen(op_doi_membri[i])+1);
            return verificare_operator_doi_membri(buffer,logic);
            i=OP2+1;
        }
    }
    if(i==OP2)
    {
        for(i=0;i<OPn;i++)
         if(strstr(buffer,op_n_membri[i])==buffer && buffer[strlen(op_n_membri[i])]=='(')
         {
            buffer[lungime-1]='\0';
            strcpy(buffer,buffer+strlen(op_n_membri[i])+1);
            if(i==OPn-1) return verificare_afiseaza(buffer);
            else return verificare_operator_n_membri(buffer);
            i=OPn+1;
         }
    }

    if(i==OPn) return 0;

    return 1;

}
int verificare_cod(char mesaj_eroare[1000])
{
    char buffer[BUFFER_SIZE],nrlinie[5];
    int nrAcolade=0,linie=1;
    bool altfel_valid=0,daca_lastseen=0,cod_inainte=0;
    Stiva stiva;
    stiva.varf=NULL;

    ifstream fin("algoritm_in_pseudocod.txt");

    while(fin.getline(buffer,BUFFER_SIZE))
    {
        trim(buffer);
        //cout<<buffer<<" "<<top(stiva)<<" "<<daca_lastseen<<" "<<altfel_valid<<endl;

        if(daca_lastseen==1) altfel_valid=1;
        else altfel_valid=0;

        if(strlen(buffer)==0)
        {
            numar_in_char(linie,nrlinie);
            strcpy(mesaj_eroare,"Linia: ");
            strcat(mesaj_eroare,nrlinie);
            strcat(mesaj_eroare,mesaj_nimic);
            return 0;
        }
        else if(strcmp(buffer,"{")==0)
            {
                numar_in_char(linie,nrlinie);
                strcpy(mesaj_eroare,"Linia: ");
                strcat(mesaj_eroare,nrlinie);
                strcat(mesaj_eroare,mesaj_acolade);
                return 0;
            }
        else if(strstr(buffer,"}"))
            {
                if(!verificare_acolade2(buffer,stiva,nrAcolade,daca_lastseen) || cod_inainte==0)
                {
                    numar_in_char(linie,nrlinie);
                    strcpy(mesaj_eroare,"Linia: ");
                    strcat(mesaj_eroare,nrlinie);
                    strcat(mesaj_eroare,mesaj_acolade);
                    return 0;
                }
                cod_inainte=1;
            }
        else if(strstr(buffer,"daca("))
            {
                if(!verificare_daca(buffer))
                {
                    numar_in_char(linie,nrlinie);
                    strcpy(mesaj_eroare,"Linia: ");
                    strcat(mesaj_eroare,nrlinie);
                    strcat(mesaj_eroare,mesaj_daca);
                    return 0;
                }
                else
                    {
                        if(fin.getline(buffer,BUFFER_SIZE) && verificare_acolade1(buffer))
                        {
                            push(stiva,DACA);
                        }
                        else
                          {
                              numar_in_char(linie,nrlinie);
                              strcpy(mesaj_eroare,"Linia: ");
                              strcat(mesaj_eroare,nrlinie);
                              strcat(mesaj_eroare,mesaj_daca);
                              return 0;
                          }
                        linie++;
                        nrAcolade++;
                    }
                cod_inainte=0;
            }
        else if(strcmp(buffer,"altfel")==0)
            {
                if(!verificare_altfel(buffer))
                {
                   numar_in_char(linie,nrlinie);
                   strcpy(mesaj_eroare,"Linia: ");
                   strcat(mesaj_eroare,nrlinie);
                   strcat(mesaj_eroare,mesaj_altfel);
                   return 0;
                }
                else
                {
                    if(fin.getline(buffer,BUFFER_SIZE) && verificare_acolade1(buffer) && altfel_valid==1)
                    {
                        altfel_valid=0;
                        daca_lastseen=0;
                        push(stiva,ALTFEL);
                    }
                    else
                    {
                        numar_in_char(linie,nrlinie);
                        strcpy(mesaj_eroare,"Linia: ");
                        strcat(mesaj_eroare,nrlinie);
                        strcat(mesaj_eroare,mesaj_altfel);
                        return 0;
                    }
                    linie++;
                    nrAcolade++;
                }
                cod_inainte=0;
            }
        else if(strstr(buffer,"cat timp(")==buffer)
            {
                if(!verificare_cat_timp(buffer))
                {
                    numar_in_char(linie,nrlinie);
                    strcpy(mesaj_eroare,"Linia: ");
                    strcat(mesaj_eroare,nrlinie);
                    strcat(mesaj_eroare,mesaj_ctmp);
                    return 0;
                }
                else
                {
                    if(fin.getline(buffer,BUFFER_SIZE) && verificare_acolade1(buffer)) push(stiva,CAT_TIMP);
                    else
                    {
                        numar_in_char(linie,nrlinie);
                        strcpy(mesaj_eroare,"Linia: ");
                        strcat(mesaj_eroare,nrlinie);
                        strcat(mesaj_eroare,mesaj_ctmp);
                        return 0;
                    }
                    linie++;
                    nrAcolade++;
                }
                cod_inainte=0;
            }
        else if(strcmp(buffer,"repeta")==0)
            {
                if(!verificare_repeta(buffer))
                {
                    numar_in_char(linie,nrlinie);
                    strcpy(mesaj_eroare,"Linia: ");
                    strcat(mesaj_eroare,nrlinie);
                    strcat(mesaj_eroare,mesaj_repeta);
                    return 0;
                }
                else
                {
                    if(fin.getline(buffer,BUFFER_SIZE) && verificare_acolade1(buffer)) push(stiva,REPETA);
                    else
                      {
                          numar_in_char(linie,nrlinie);
                          strcpy(mesaj_eroare,"Linia: ");
                          strcat(mesaj_eroare,nrlinie);
                          strcat(mesaj_eroare,mesaj_repeta);
                          return 0;
                      }
                    linie++;
                    nrAcolade++;
                }
                cod_inainte=0;
            }
        else
            {
                char copie[BUFFER_SIZE];
                strcpy(copie,buffer);
                if(!verificare_actiune(buffer))
                {
                    numar_in_char(linie,nrlinie);
                    strcpy(mesaj_eroare,"Linia: ");
                    strcat(mesaj_eroare,nrlinie);
                    strcat(mesaj_eroare,mesaj_actiune);
                    return 0;
                }
                cod_inainte=1;
            }

    if(altfel_valid==1) daca_lastseen=0;

    linie++;
    }
    fin.close();
    if(nrAcolade!=0)
    {
        strcpy(mesaj_eroare,mesaj_acolade);
        return 0;
    }

    return 1;
}

#endif // VERIFICARE_COD_H_INCLUDED
