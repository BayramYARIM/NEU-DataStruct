/*
 *  BISMILLAHIRRAHMANIRRAHIM
 *  @Project : Veri Yapilari-Odev3 - BAYRAM YARIM - 18010011067
 *  @Author  : Bayram YARIM [byyarim@gmail.com]
 *  @File    : 18010011067.cpp
 *  @Desc    : Infix to Postfix Converter (Stack - Linked List)
 *  @Create  : 23.10.2022 18:35
 *  @Update  : 23.10.2022 22:29
 *  @Version : v-
 *  @Build   : #-
 *  @OS      : Debian-Linux
 *  @IDE     : Qt Creator - qMake Compiler
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct tsStack
{
    char data;
    struct tsStack *next;
}TStack;

TStack *root=NULL, *BeginStack=NULL;
char inputData[100];

void I2P_WriteOperator()
{
    TStack *bay;
    bay = root;
    if (bay!= NULL)
    {
        while (bay != NULL) {
            printf("%c", bay->data);
            bay = bay->next;
        }
        printf("\n");
    }
}

/*
Stack yapisina veri ekleme islemini yapan fonksiyondur.
*/
void I2P_Add(char ch)
{
    TStack *temp,*newrecord;
    newrecord=(TStack*)malloc(sizeof(TStack));
    newrecord->next=NULL;
    newrecord->data=ch;
    temp=BeginStack;
    printf("%s\t\t", inputData);
    if(BeginStack==NULL)
    {
        BeginStack=newrecord;
        //printf("%c", newrecord->data);
        printf("\n");
    }
    else
    {

        while(temp->next!=NULL)
        {
            printf("%c", temp->data);
            temp=temp->next;
        }
        temp->next=newrecord;

        printf("\t\t\t");
        I2P_WriteOperator();
    }
}

/*
PUSH :: Stack yapisinin ust kismina
veri ekleme islemini yapan fonksiyondur.
*/
void I2P_Push (char symbol)
{
    TStack*pRecord;
    pRecord=(TStack*)malloc(sizeof(TStack));
    pRecord->data=symbol;

    if(root==NULL)
    {
        root=pRecord;
        pRecord->next=NULL;
    }
    else
    {
        pRecord->next=root;
        root=pRecord;
    }
}

/*
POP :: Stack yapisindan veri cikarma
islemini yapan fonksiyondur.
*/
char  I2P_Pop()
{
    TStack *temp;
    char ch;
    if(root!=NULL)
    {
        temp=root;
        root=root->next;
        ch=temp->data;
        free(temp);
        temp=NULL;
        return ch;
    }
    return 0;
}



void ResultPostfixData()
{
    TStack *temp;
    if(BeginStack!=NULL)
    {
        printf("\n\nPostfixData: ");
        temp=BeginStack;
        while(temp!=NULL)
        {
            printf("%c",temp->data);
            temp=temp->next;
        }
        printf("\n\n");
    }
}
/*
Fonksiyona gonderilen karakterin
islem sira numarasini geri donduren fonksiyondur.
*/
int characterControl(char ch)
{
    switch (ch)
    {
    case '^':
        return 5;
        break;
    case '*':
    case '/':
        return 4;
        break;
    case '+':
    case '-':
        return 3;
        break;
    default: return 2;
    }
}

void InfixToPostfix(char infix[])
{
    int dataLength, i=0;
    char symbol,temp;
    dataLength=strlen(infix);
    while(dataLength>i)
    {
        symbol=infix[i];
        switch(symbol)
        {
        case '(':
            I2P_Push(symbol);
        break;

        case ')':
            temp=I2P_Pop();
            while(temp!='(')
            {
                I2P_Add(temp);
                temp=I2P_Pop();
            }
        break;

        case '^':
        case '+':
        case '-':
        case '*':
        case '/':
            if(root==NULL)
            {
                I2P_Push(symbol);
            }
            else
            {
                while(root!=NULL && (characterControl(root->data)>=characterControl(symbol)))
                {
                    temp=I2P_Pop();
                    I2P_Add(temp);
                }
                I2P_Push(symbol);
            }
        break;

        default: I2P_Add(symbol);

         }//Switch::End
         i=i+1;
    }//While::End

    while(root!=NULL)
    {
        temp=I2P_Pop();
        I2P_Add(temp);
    }
    return;
}


int main()
{
    //https://www.free-online-calculator-use.com/infix-to-postfix-converter.htmls
    //system("clear");
    printf("Lutfen infix ifadesini giriniz: ");
    fgets(inputData, sizeof (inputData), stdin);
    inputData[strlen(inputData)-1]='\0';
    printf("\n------------------------------------------------------------------\n");
    printf("InputString\t\tOutput Stack\t\tOperator\n");
    printf("------------------------------------------------------------------\n");
    InfixToPostfix(inputData);
    ResultPostfixData();
    return 0;
}

