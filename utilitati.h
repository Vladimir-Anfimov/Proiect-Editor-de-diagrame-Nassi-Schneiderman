#ifndef UTILITATI_H_INCLUDED
#define UTILITATI_H_INCLUDED

#include <cctype>

void trim(char text[])
{
    unsigned int i = 0;
    while(text[i] == ' ')
        strcpy(text + i, text + i + 1);

    int pozLast = strlen(text) - 1;
    while(i<strlen(text))
    {
        if(text[i] != ' ') pozLast = i;
        i++;
    }
    text[pozLast + 1] = '\0';
}

void extragereConditie(char conditie[])
{
    unsigned int pozFirst, pozLast;
    for (int i=0;i<strlen(conditie);i++)
        if(conditie[i] == '(')
        {
            pozFirst = i+1;
            break;
        }

    for (int i=strlen(conditie)-1;i>=0;i--)
        if(conditie[i] == ')')
        {
            pozLast = i;
            break;
        }

    conditie[pozLast] = '\0';
    strcpy(conditie, conditie+pozFirst);
}

bool isNumber(char str[])
{
    trim(str);
    if(!(isdigit(str[0]) || str[0] == '-'))
        return false;

    for(int i=1;i<strlen(str);i++)
        if(!isdigit(str[i]) || str[i] == '-' && i != 0)
            return false;

    return true;
}

bool isSintaticVar(char str[])
{
    trim(str);
    if(!isalpha(str[0])) return false;

    for(int i=1;i<strlen(str);i++)
        if(!isalnum(str[i]))
            return false;
    return true;
}

bool incepeCu(char sir1[], char sir2[])
{
    for(int i=0;i<strlen(sir2);i++)
        if(sir1[i] != sir2[i])
            return false;
    return true;
}

void refArgumente(char arg1[], char arg2[], char buffer[])
{
    strcpy(arg1, "");
    strcpy(arg2, "");

    int nrParanteze=0, poz_virgula = -1;
    for(int i=0;i<strlen(buffer) && poz_virgula == -1;i++)
    {
        if(buffer[i]=='(') nrParanteze++;
        else if(buffer[i]==')') nrParanteze--;
        else if(buffer[i]==',' && nrParanteze==0) poz_virgula=i;
    }

    strcpy(arg1, buffer);
    arg1[poz_virgula] = '\0';
    strcpy(arg2, buffer+poz_virgula+1);

    //std::cout<<buffer<<" "<<arg1<<" "<<arg2<<" ARGS"<<std::endl;
}

void strtok_custom(char items[][100], char text[100], int &item_number)
{
    item_number = 0;
    int paranteze = 0, item_length = 0;
    for(int i=0;i<strlen(text);i++)
    {
        if(text[i] == ',' && paranteze == 0)
        {
            items[item_number][item_length] = '\0';
            item_length = 0;
            item_number++;
        }
        else {
            if(text[i] == '(') paranteze++;
            else if(text[i] == ')') paranteze--;
            items[item_number][item_length++] = text[i];
        }
    }
    items[item_number][item_length] = '\0';
}

void numar_in_char(int numar,char numar_char[])
{
    int i=0;
    while(numar>0)
    {
        numar_char[i]=numar%10+'0';
        i++;
        numar=numar/10;
    }
    numar_char[i]='\0';
    strrev(numar_char);
}

void afisare_output(char output[150], int max_len, int x, int y)
{
    char *var = strtok(output, " ");
    int actual_len = 0;
    while(var != NULL)
    {
        if(actual_len + textwidth(var) >= max_len)
        {
            actual_len = 0;
            y += 20;
        }
        outtextxy(x + actual_len, y, var);
        actual_len += textwidth(var) + 5;
        var = strtok(NULL , " ");
    }
}
#endif // UTILITATI_H_INCLUDED

