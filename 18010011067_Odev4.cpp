/*
 *  BISMILLAHIRRAHMANIRRAHIM
 *  @Project : Veri Yapilari-Odev4 - BAYRAM YARIM - 18010011067
 *  @Author  : Bayram YARIM [byyarim@gmail.com]
 *  @File    : 18010011067.cpp
 *  @Desc    : Binary Search Tree (ikili arama agaci)
 *  @Create  : 28.11.2022 23:05
 *  @Update  : 28.11.2022 03:35
 *  @Version : v-
 *  @Build   : #-
 *  @OS      : Debian-Linux
 *  @IDE     : Qt Creator - qMake Compiler
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//OS System Select
#ifdef __linux__
#define clrscr system("clear");
#elif _WIN32
#define clrscr system("@cls");
#else
#define clrscr system("@cls");
#endif

typedef struct TBST {
    int data;
    struct TBST *LL; //left leaf
    struct TBST *RL; //right leaf
}BST;

BST *root=NULL;

//Function List
void MainMenu();
BST * BSTInsert(BST *n, int value);
void BSTAdd();
void BSTDelete();
BST * BSTDeleteX(BST *n, int value);
BST* BSTSearch(int value);
void BSTInorderList(BST *n);
int BSTHeightCalculate(BST *n);
void ProgramAbout();
void ProgramExit();
void ShowMessage(int MenuNo, char *eMessage);

int GetKeyboardValue()
{
    #ifdef __linux__
        int result = getchar();
    #elif _WIN32
        int result = getch();
    #else
        int result = getch();
    #endif
    return result;
}

BST * BSTInsert(BST *n, int value)
{
    if (n == NULL)
    {
        BST *root = (BST *)malloc(sizeof (BST));
        root->LL = NULL;
        root->RL = NULL;
        root->data = value;
        return root;
    }

    if (n->data < value)
    {
        n->RL = BSTInsert(n->RL,value);
        return n;
    }

    n->LL = BSTInsert(n->LL, value);
    return n;
}

/*
Agaca veri ekleme fonksiyonudur.
BSTInsert fonksiyonu burada cagirilir.
*/
void BSTAdd()
{
    clrscr;
    int value;
    printf("%40s","Eklenecek numara: ");
    scanf("%d", &value);
    root = BSTInsert(root, value);
    ShowMessage(1, "KAYIT EKLEME TAMAMLANDI\n");
}

BST* BSTSearch(int value){
   BST *current = root;
   while(current->data != value){
      if(current != NULL) {
         printf("%d ",current->data);
         if(current->data > value){
            current = current->LL;
         }
         else {
            current = current->RL;
         }
         if(current == NULL){
            return NULL;
         }
      }
   }
   return current;
}

void BSTDelete()
{
    clrscr;
    int value;
    printf("%40s","Silinecek numara: ");
    scanf("%d", &value);
    if (BSTSearch(value) != NULL)
    {
        root = BSTDeleteX(root, value);
        ShowMessage(2, " ");
    }
    else
    {
        ShowMessage(2, "Silinecek deger bulunamadi");
    }
}

/*
Agac icerisindeki verileri kucukten buyuge listeleyen fonksiyondur.
*/
void BSTInorderList(BST *n)
{
    if (n != NULL)
    {
        BSTInorderList(n->LL);
        printf("%d ", n->data);
        BSTInorderList(n->RL);
    }
}
/*
Agac yuksekligini hesaplama fonksiyonu
Agac yuksekligine root dahil edilmistir.
Agac yuksekligine root dahil edilmezse sonuca -1 eklenir.
*/
int BSTHeightCalculate(BST *n)
{
    if (n != NULL)
    {
        int lCount = BSTHeightCalculate(n->LL);
        int rCount = BSTHeightCalculate(n->RL);
        if (lCount > rCount)
            return (lCount +1);
        else
            return (rCount +1);
    }
    else
    {
        return 0;
    }
}

bool FullTreeControl(BST *n)
{
    if (n == NULL)
        return true;
    if ((n->LL == NULL) && (n->RL == NULL))
        return true;

    if ((n->LL) && (n->RL))
        return (FullTreeControl(n->LL) && FullTreeControl(n->RL));
    return false;
}

int getLeftValue(BST *n) {
    int minValue = n->data;
    while (n->LL != NULL) {
        minValue = n->LL->data;
        n = n->LL;
    }
    return minValue;
}

BST * BSTDeleteX(BST *n, int value) {
    if (n == NULL)
        return n;

    if (value < n->data) {
        n->LL = BSTDeleteX(n->LL, value);
    } else if (value > n->data) {
        n->RL = BSTDeleteX(n->RL, value);
    } else {

        if (n->LL == NULL) {
            return n->RL;
        }
        else
            if (n->RL == NULL)
            return n->LL;

        n->data = getLeftValue(n->RL);
        n->RL = BSTDeleteX(n->RL, n->data);
    }

    return root;

}

void ProgramAbout()
{
    clrscr;
    printf("================================================================================\n");
    printf("\t\t\tProgram : VERI YAPILARI - ODEV4\n");
    printf("\t\t\tAuthor  : Bayram YARIM\n");
    printf("\t\t\tSchoolNo: 18010011067\n");
    printf("\t\t\tMail    : byyarim@gmail.com\n");
    printf("================================================================================\n");
    ShowMessage(0," ");
}

void ProgramExit()
{
    printf("\n\t\t[ Programdan cikis yapiliyor...Bye!]\n\n");
    exit(0);
}

void ShowMessage(int MenuNo, char *eMessage)
{
    printf("\n\n\n");
    printf("%20s%s\n\n"," " ,eMessage);
    printf("\t\tAna menuye donmek icin ENTER tusuna basiniz...");
    int iSelect = GetKeyboardValue();
    #ifdef __linux__
        GetKeyboardValue();
    #endif
    switch(iSelect)
    {
    case 27: //ESC
    case 13: //Enter
        MainMenu();
        break;
    case 32:
        switch (MenuNo)
        {
        case 1: BSTAdd(); break;
        case 2: BSTDelete(); break;
        case 3: BSTInorderList(root); break;
        case 4: BSTHeightCalculate(root); break;
        default: MainMenu(); break;
        }
        break;
    default:
        MainMenu();
        ShowMessage(0, eMessage);
        break;
    }
}

void MainMenu()
{
    int MenuSelect;
    clrscr;
    printf("*******************************************************************************\n");
    printf("\t\t\t [1] : EKLE\n");
    printf("\t\t\t [2] : SIL\n");
    printf("\t\t\t [3] : INORDER LISTELE\n");
    printf("\t\t\t [4] : AGAC YUKSEKLIGI \n");
    printf("\t\t\t [5] : FULL BINARY - COMPLETE BINARY\n");
    printf("\t\t\t[h/H]: PROGRAM HAKKINDA\n");
    printf("\t\t\t[e/E]: CIKIS\n");
    printf("*******************************************************************************\n");
    printf("\t\t\tMENUDEN ISLEM SECINIZ:\n");
    MenuSelect = GetKeyboardValue();
    switch(MenuSelect)
    {
    case 49: //1
        BSTAdd();
        break;

    case 50: //2
        BSTDelete();
        break;

    case 51: //3
        clrscr;
        BSTInorderList(root);
        ShowMessage(3, "Binary Search Tree Listelendi...");
        break;

    case 52: //4
        printf("Agac yuksekligi: %d\n", BSTHeightCalculate(root)-1);
        ShowMessage(0, " ");
        break;

    case 53: //5
        if (FullTreeControl(root))
            ShowMessage(5, "Agac yapisi ==> FULL TREE");
        else
            ShowMessage(5, "Agac yapisi ==> FULL TREE DEGIL");
        break;

    case 'H': case 'h': case 'A': case 'a':
        ProgramAbout();
        break;

    case 'E': case 'e': case 'Q': case 'q':
        ProgramExit();
        break;
    default:
        MainMenu();
        break;
    }

}

int main()
{
    MainMenu();
    return 0;
}
