/*
 *  BISMILLAHIRRAHMANIRRAHIM
 *  @Project : Veri Yapilari-Odev1 - BAYRAM YARIM - 18010011067
 *  @Author  : Bayram YARIM [byyarim@gmail.com]
 *  @File    : 18010011067.cpp
 *  @Desc    : DataStruct
 *  @Create  : 02.10.2022 20:55
 *  @Update  : 02.10.2022 23:18
 *  @Version : v-
 *  @Build   : #-
 *  @OS      : Debian-Linux
 *  @IDE     : Qt Creator - qMake Compiler
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

//OS System Select
#ifdef __linux__
#define clrscr system("clear");
#elif _WIN32
#define clrscr system("@cls");
#else
#define clrscr system("@cls");
#endif

//Circle Linked List
typedef struct tsCLL
{
    char Name[20];
    char Surname[20];
    long int Phone;
    struct tsCLL *NextCLL;
} TCLL;

TCLL *root=NULL, *iTemp;

void MainMenu();
void CLLList();
void CLLAdd();
void CLLSearchPhone();
void CLLSearchName();
void CLLDelete();
void CLLSort();
void ProgramAbout();
void ProgramExit();

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

void ShowMessage(int MenuNo, char *eMessage)
{
    printf("\n\n\n");
    printf("%20s%s\n\n"," " ,eMessage);
    printf("\t\tAna menuye donmek icin ENTER tusuna basiniz...");
    int iSelect = GetKeyboardValue();
    #ifdef __linux__
        GetKeyboardValue();
    #endif
    //printf("%d",iSelect);
    switch(iSelect)
    {
    case 27: //ESC
    case 13: //Enter
        MainMenu();
        break;
    case 32:
        switch (MenuNo)
        {
        case 1: CLLAdd(); break;
        case 2: CLLList(); break;
        case 3: CLLSearchPhone(); break;
        case 4: CLLSearchName(); break;
        case 5: CLLDelete(); break;
        case 6: CLLSort(); break;
        default: MainMenu(); break;
        }
        break;
    default:
        MainMenu();
        ShowMessage(0, eMessage);
        break;
    }
}


TCLL *GetDataRecord()
{
    TCLL *iRecord = (TCLL*)malloc(sizeof (TCLL));
    printf("%40s","Ad Giriniz:");
    scanf("%s", &(iRecord->Name));
    printf("%40s","Soyad Giriniz:");
    scanf("%s", &(iRecord->Surname));
    printf("%40s","Telefon Giriniz:");
    scanf("%d", &(iRecord->Phone));
    return iRecord;
}

/*
 * Telefon Numarasi kontrolu
 * Kayit var ise return True
 * Kayit yok ise return False
 */
bool CLLPhoneControl(int phoneNo)
{
    bool result=false;
    iTemp = root;
    if (iTemp != NULL)
    {
        do {
            if (iTemp->Phone == phoneNo)
            {
                result=true;
                break;
            }
            iTemp = iTemp->NextCLL;
        } while (iTemp != root);
    }
    return result;
}

/*
 * KAYIT EKLEME FONKSIYONU
 * Kayit en basa eklenir.
 */
void CLLAdd()
{
    TCLL *rec = GetDataRecord();
    if (root == NULL )
    {
        root = rec;
        root->NextCLL = rec;
    }
    else
    {
        if (CLLPhoneControl(rec->Phone) == true)
        {
            ShowMessage(0, "Girilen bu telefon baska kayitta mevcut. Kayit Eklenemez!");
            return;
        }
        iTemp = root;
        while (iTemp->NextCLL != root) {
            iTemp = iTemp->NextCLL;
        }
        iTemp->NextCLL = rec;
        rec->NextCLL = root;
    }
    ShowMessage(1, "KAYIT EKLEME TAMAMLANDI\n");
}

/*
 * Tum kayitlari listeleme fonksiyonu
 * Tum kayitlari listeler ve kayit sayisini gosterir
 * Kayit yok ise mesaj verir!
 *
*/
void CLLList()
{
    clrscr;
    int recCount=0;
    iTemp = root;
    if (iTemp != NULL)
    {
        printf("Ad\t\tSoyad\t\tTelefon\n");
        printf("==========================================================\n");
        do {
            printf("%s\t\t%s\t\t%ld\n", iTemp->Name, iTemp->Surname, iTemp->Phone);
            iTemp = iTemp->NextCLL;
            recCount++;
        } while (iTemp != root);
        printf("==========================================================\n");
        printf("\tToplam %d kayit listelendi", recCount);
    }
    else
    {
        ShowMessage(2, "Rehberde listelenecek kayit bulunamadi!");
    }
    ShowMessage(2, " ");
}

/*
 * Telefon numarasina gore tum kayitlari tarar
 * Kayit var ise bilgilerini gosterir
 * Kayit yok ise uyari mesaji verir!
 *
*/
void CLLSearchPhone()
{
    long int phoneNo;
    bool result=false;
    iTemp = root;
    if (iTemp != NULL)
    {
        printf("%40s","Aranacak Telefon No Giriniz:");
        scanf("%ld", &phoneNo);
        do {
            if (iTemp->Phone == (int)(phoneNo))
            {
                printf("%ld numarasi %s %s kisisine kayitlidir.\n", phoneNo, iTemp->Name, iTemp->Surname);
                result = true;
                break;
            }
            iTemp = iTemp->NextCLL;
        } while (iTemp != root);
    }
    else
    {
        ShowMessage(3, "Aranacak bir veri bulunamamaktadir!");
    }
    if (result == false) printf("%ld numarasi herhangi bir kayitta bulunamadi!", phoneNo);
    ShowMessage(0, " ");
}

/*
 * Ad bilgisine gore tum kayitlari tarar
 * Kayit var ise bilgilerini gosterir
 * Kayit yok ise uyari mesaji verir!
 *
*/
void CLLSearchName()
{
    char uName[20];
    bool result=false;
    iTemp = root;
    if (iTemp != NULL)
    {
        printf("%40s","Aranacak kisi ismini giriniz:");
        scanf("%s", &uName);
        printf("Ad\t\tSoyad\t\tTelefon\n");
        printf("==========================================================\n");
        do {
            if (strcmp(iTemp->Name, uName) == 0)
            {
                printf("%s\t\t%s\t\t%ld\n", iTemp->Name, iTemp->Surname, iTemp->Phone);
                result = true;
            }
            iTemp = iTemp->NextCLL;
        } while (iTemp != root);
        printf("==========================================================\n");
    }
    else
    {
        ShowMessage(4, "Aranacak bir veri bulunamamaktadir!");
    }
    if (result == false) printf("\t%s isimli herhangi bir kayit bulunamadi!", uName);
    ShowMessage(0, " ");
}

/*
 * Telefon numarasina gore tum kayitlari tarar
 * Kayit var ise kayit silinir
 * Kayit yok ise uyari mesaji verir!
 *
*/
void CLLDelete()
{
    long int phoneNo;
    bool result=false;
    iTemp = root;
    TCLL *firstRec = NULL;
    if (iTemp != NULL)
    {
        printf("%40s","Silinecek kayitin Telefon No Giriniz:");
        scanf("%ld", &phoneNo);
        do {

            if (iTemp->Phone == (int)(phoneNo))
            {
                result = true;
                break;
            }
            firstRec = iTemp;
            iTemp = iTemp->NextCLL;
        } while (iTemp != root);

        if (result == true)
        {
            if (firstRec == NULL)
            {
                root = NULL;
            }
            else
            {
                firstRec->NextCLL = iTemp->NextCLL;
                free(iTemp);
                ShowMessage(5, " Kayit silindi!");
            }
        }
        else
        {
            ShowMessage(0, "Aranilan kayit bulunamadi!");
        }
    }
    else
    {
        ShowMessage(0, "Silinecek bir veri bulunmamaktadir!");
    }
}

/*
 * iki kaydi degistirir.
 *
*/
void CLLSwap(TCLL *L1, TCLL *L2)
{
    TCLL *swTemp = NULL;
    memcpy(&swTemp, &L1, sizeof(L1));
    memcpy(&L1, &L2, sizeof(L2));
    memcpy(&L2, &swTemp, sizeof(swTemp));
}

/*
 * Tum kayitlari tarar ve soyadina gore siralama yapar
 *
*/
void CLLSort()
{
    TCLL *aTemp = root, *sortL1 = NULL;

    if (aTemp != NULL)
    {
        do{
            sortL1 = aTemp->NextCLL;
            while(sortL1 != root) {
                if (strcmp((char*)aTemp->Surname, (char*)sortL1->Surname) >= 0)
                {
                    CLLSwap(aTemp, sortL1);
                }
                sortL1= sortL1->NextCLL;
            }
            aTemp =aTemp->NextCLL;
        }while(aTemp->NextCLL != root);

        printf("========SIRALI LISTE========\n");
        printf("Ad\t\tSoyad\t\tTelefon\n");
        printf("==========================================================\n");
        do {
            printf("%s\t\t%s\t\t%ld\n", aTemp->Name, aTemp->Surname, aTemp->Phone);
            aTemp = aTemp->NextCLL;
        } while (aTemp->NextCLL != root);
    }
    else
    {
        ShowMessage(6, "Listelenecek kayit bulunmamaktadir!");
    }
    ShowMessage(2, " ");
}

void ProgramAbout()
{
    clrscr;
    printf("================================================================================\n");
    printf("\t\t\tProgram : VERI YAPILARI - ODEV1\n");
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

void MainMenu()
{
    int MenuSelect;
    clrscr;
    printf("*******************************************************************************\n");
    printf("\t\t\tTELEFON REHBERI\n");
    printf("*******************************************************************************\n");
    printf("\t\t\t [1] : KAYIT EKLE\n");
    printf("\t\t\t [2] : KAYIT LISTELE\n");
    printf("\t\t\t [3] : KAYIT ARA ( TELEFON )\n");
    printf("\t\t\t [4] : KAYIT ARA ( AD ) \n");
    printf("\t\t\t [5] : KAYIT SIL ( TELEFON )\n");
    printf("\t\t\t [6] : KAYIT SIRALA ( SOYAD ) \n");
    printf("\t\t\t[h/H]: PROGRAM HAKKINDA\n");
    printf("\t\t\t[e/E]: CIKIS\n");
    printf("*******************************************************************************\n");
    printf("\t\t\tMENUDEN ISLEM SECINIZ:\n");
    MenuSelect = GetKeyboardValue();
    switch(MenuSelect)
    {
    case 49: //1
        CLLAdd();
        break;

    case 50: //2
        CLLList();
        break;

    case 51: //3
        CLLSearchPhone();
        break;

    case 52: //4
        CLLSearchName();
        break;

    case 53: //5
        CLLDelete();
        break;

    case 54: //6
        CLLSort();
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
