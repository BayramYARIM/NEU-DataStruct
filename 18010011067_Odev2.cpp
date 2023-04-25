/*
 *  BISMILLAHIRRAHMANIRRAHIM
 *  @Project : Veri Yapilari-Odev2 - BAYRAM YARIM - 18010011067
 *  @Author  : Bayram YARIM [byyarim@gmail.com]
 *  @File    : 18010011067.cpp
 *  @Desc    : Cift Yonlu Bagli Liste (Double Linked List)
 *  @Create  : 16.10.2022 21:48
 *  @Update  : 16.10.2022 23:34
 *  @Version : v-
 *  @Build   : #-
 *  @OS      : Debian-Linux
 *  @IDE     : Qt Creator - qMake Compiler
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

//Doubly Linked List
typedef struct tsDLL
{
    int data;
    int SequenceID; //Sira numarasini gormek icin eklendi
    struct tsDLL *Next;
    struct tsDLL *Prev;
} TDLL;

TDLL *FirstList, *SecondList, *MergeList;
int count =0; //Yazdirma sirasinda sira numarasini gostermek icin eklendi


//1-1000 arasi random sayi ureten fonksiyondur.
int RandomNumber()
{
    return rand() % 1000 + 1;
}

/*
Parametre olarak gonderilen struct yapisina
parametre olarak gondeilen int tipindeki random
sayiyi ekler.
*/
TDLL * DLLInsert(TDLL *head, int data)
{
    count++;
    if (head == NULL)
    {
        head = (TDLL*)malloc(sizeof (TDLL));
        head->data = data;
        head->SequenceID = count;
        head->Next = NULL; //(TDLL*)malloc(sizeof (TDLL));
        head->Prev = NULL; //(TDLL*)malloc(sizeof (TDLL));
        printf("DLLInsert : %d(0x%x) - %d\n", head, head, data);
        return head;
    }
    else
    {
        TDLL *newrec = (TDLL*)malloc(sizeof (TDLL));
        TDLL *newiter = head;

        while (newiter->Next != NULL) {
            newiter = newiter->Next;
        }
        newrec->SequenceID = count;
        newrec->data = data;
        newrec->Next = NULL; //(TDLL*)malloc(sizeof (TDLL));
        newrec->Prev = (TDLL*)malloc(sizeof (TDLL));
        newrec->Prev = newiter;
        newiter->Next = newrec;
        printf("DLLInsert : %d(0x%x) - %d\n", newrec, newrec, data);
        return newiter;
    }
}

//Parametre olarak gonderilen struct yapisini liste seklinde yazdirir.
void DLLListPrint(TDLL *head)
{
    TDLL *iRecord = head;
    if (iRecord != NULL)
    {
        printf("====================================================\n");
        printf("[SN]\tAdress-Int-Hex\t\tValue\n");
        printf("====================================================\n");
        printf("[%.2d]\t%d (0x%x)\t\t%d\n", iRecord->Next->SequenceID, iRecord->Next, iRecord->Next, iRecord->Next->data);
        while (iRecord != NULL) {
            //printf("%d<-- %d -->%d\n", iRecord->Prev->data, iRecord->data, iRecord->Next->data);
            printf("[%.2d]\t%d (0x%x)\t\t%d\n", iRecord->SequenceID, iRecord, iRecord, iRecord->data);
            iRecord = iRecord->Prev;
        }
        printf("====================================================\n\n\n");
    }
}

/*
Recursive olmayan fonksiyon.
Iki farkli listeyi hafizadaki adresine gore birlestirir.
*/
void DLLMergeNoneRec()
{
    MergeList = NULL;//(TDLL*)malloc(sizeof (TDLL));
    if ((FirstList != NULL) && (SecondList != NULL))
    {
        do {
            TDLL * tmp = NULL;
            if (FirstList > SecondList)
            {
                tmp = FirstList;
                FirstList = FirstList->Prev;
            }
            else
            {
                tmp = SecondList;
                SecondList = SecondList->Prev;
            }

            if (MergeList == NULL)
            {
                MergeList = tmp;
                MergeList->Prev = NULL;
            }
            else
            {
                MergeList->Next = tmp;
                tmp->Prev = MergeList;
                MergeList = MergeList->Next;
            }
        } while ((FirstList != NULL) && (SecondList != NULL));
    }//If::End
}//Procedure::End

/*
Parametre olarak gonderilen iki farkli listeyi
hafizadaki adresine gore birlestirir.
Fonksiyon recursive yapisinda olusturulmustur.
*/
TDLL *DLLMerge(TDLL* list1, TDLL* list2)
{
    TDLL* temp1 = list1;
    TDLL* temp2 = list2;

    if (temp1 == NULL) { return temp2; }
    if (temp2 == NULL) { return temp1; }

    if (temp1 > temp2)
    {
        temp1->Prev = DLLMerge(temp1->Prev, temp2);
        return temp1;
    }
    else
    {
        temp2->Prev = DLLMerge(temp1, temp2->Prev);
        return temp2;
    }
}

/*
Parametre olarak gonderilen listeyi icersinde tum verileri ters cevirir.
*/
TDLL * DLLReverse(TDLL * reverseList)
{
    TDLL* temp = NULL;
    TDLL* current = reverseList->Next;
    while (current != NULL) {
        temp = current;
        current->Prev = current->Next;
        current->Next = temp;
        current = current->Prev;
    }
    return reverseList;
}

int main()
{
    int iValue=10;
    printf("CIFT YONLU BAGLI LISTE\n\n");
    printf("Lutfen bir sayi giriniz(Varsayilan=10):");
    scanf("%d", &iValue);
    if ((iValue <= 0) || (iValue >= 100)) iValue=10;

    // girilen deger kadar dongu ile struct yapilarina kayit ekleme islemi burada cagiriliyor.
    for (int var = 0; var < iValue; ++var) {
       FirstList =  DLLInsert(FirstList, RandomNumber());
       SecondList = DLLInsert(SecondList, RandomNumber());
    }

    //Ilk liste yazdirma yeri
    printf("\n\n[FirstList Print]\n");
    DLLListPrint(FirstList);


    //Ikinci liste yazdirma yeri
    printf("[SecondList Print]\n");
    DLLListPrint(SecondList);

    //DLLMergeNoneRec(); //Recursive olmayan fonksiyon.

    //Iki listeyi birlestirme ve sonrasinda yazdirma yeri
    MergeList =  DLLMerge(FirstList, SecondList);
    printf("[MergeList Print]\n");
    DLLListPrint(MergeList);


    //Birlestirilen listeyi cevirme ve tekrar yazdirma yeri
    MergeList = DLLReverse(MergeList);
    printf("[Reverse MergeList Print]\n");
    DLLListPrint(MergeList);
    return 0;
}
