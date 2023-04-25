/*
 *  BISMILLAHIRRAHMANIRRAHIM
 *  @Project : Veri Yapilari-Odev5 - BAYRAM YARIM - 18010011067
 *  @Author  : Bayram YARIM [byyarim@gmail.com]
 *  @File    : 18010011067.cpp
 *  @Desc    : AVL Tree (AVL Agac Yapisi - Ekleme - Silme)
 *  @Create  : 06.12.2022 01:47
 *  @Update  : 06.12.2022 04:04
 *  @Version : v-
 *  @Build   : #-
 *  @OS      : Debian-Linux
 *  @IDE     : Qt Creator - qMake Compiler
 */

#include <stdio.h>
#include <stdlib.h>

//OS System Select
#ifdef __linux__
#define clrscr system("clear");
#elif _WIN32
#define clrscr system("@cls");
#else
#define clrscr system("@cls");
#endif

typedef struct TAVL
{
    int data;
    int height;
    struct TAVL *left;
    struct TAVL *right;
}AVL;


AVL *insert(AVL *,int);
AVL *Delete(AVL *,int);
void preorder(AVL *);
void inorder(AVL *);
int height(AVL *);
AVL *rotateright(AVL *);
AVL *rotateleft(AVL *);
AVL *RR(AVL *);
AVL *LL(AVL *);
AVL *LR(AVL *);
AVL *RL(AVL *);
int BF(AVL *);

int main()
{
    AVL *root=NULL;
    int x,op;
    do
    {
        printf("\n1)Ekle:");
        printf("\n2)Sil:");
        printf("\n3)Yazdir:");
        printf("\n4)Cikis:");
        printf("\n\nSecim Yapiniz:");
        scanf("%d",&op);
        switch(op)
        {
        case 1:
            printf("\nSayi giriniz:");
            scanf("%d",&x);
            root=insert(root,x);
        break;
        case 2:
            printf("\nSilinecek sayi giriniz:");
            scanf("%d",&x);
            root=Delete(root,x);
        break;
        case 3:
            printf("\nPreorder siralama:\n");
            preorder(root);
            printf("\n\nInorder siralama:\n");
            inorder(root);
            printf("\n");
        break;
        }//switch End
    }while(op!=4);
    return 0;
}

AVL * insert(AVL *T,int x)
{
    if(T==NULL)
    {
        T=(AVL*)malloc(sizeof(AVL));
        T->data=x;
        T->left=NULL;
        T->right=NULL;
    }
    else
    if(x > T->data)
    {
        T->right=insert(T->right,x);
        if(BF(T)==-2)
        if(x>T->right->data)
            T=RR(T);
        else
            T=RL(T);
    }
    else
    if(x<T->data)
    {
        T->left=insert(T->left,x);
        if(BF(T)==2)
        if(x < T->left->data)
            T=LL(T);
        else
            T=LR(T);
    }
    T->height=height(T);
    return(T);
}

AVL * Delete(AVL *T,int x)
{
    AVL *p;
    if(T==NULL)
    {
        return NULL;
    }
    else
    if(x > T->data)
    {
        T->right=Delete(T->right,x);
        if(BF(T)==2)
        if(BF(T->left)>=0)
            T=LL(T);
        else
            T=LR(T);
    }
    else
    if(x<T->data)
    {
        T->left=Delete(T->left,x);
        if(BF(T)==-2)
        if(BF(T->right)<=0)
            T=RR(T);
        else
            T=RL(T);
    }
    else
    {
        if(T->right!=NULL)
        {
            p=T->right;
            while(p->left!= NULL)
                p=p->left;
            T->data=p->data;
            T->right=Delete(T->right,p->data);
            if(BF(T)==2)
            if(BF(T->left)>=0)
                T=LL(T);
            else
                T=LR(T);
        }
        else
        return(T->left);
    }
    T->height=height(T);
    return(T);
}

int height(AVL *T)
{
    int lh,rh;
    if(T==NULL) return(0);
    if(T->left==NULL)
        lh=0;
    else
        lh=1+T->left->height;

    if(T->right==NULL)
        rh=0;
    else
        rh=1+T->right->height;
    if(lh>rh)
        return(lh);
    return(rh);
}

AVL * rotateright(AVL *x)
{
    AVL *y;
    y=x->left;
    x->left=y->right;
    y->right=x;
    x->height=height(x);
    y->height=height(y);
    return(y);
}

AVL * rotateleft(AVL *x)
{
    AVL *y;
    y=x->right;
    x->right=y->left;
    y->left=x;
    x->height=height(x);
    y->height=height(y);
    return(y);
}

AVL * RR(AVL *T)
{
    T=rotateleft(T);
    return(T);
}

AVL * LL(AVL *T)
{
    T=rotateright(T);
    return(T);
}

AVL * LR(AVL *T)
{
    T->left=rotateleft(T->left);
    T=rotateright(T);
    return(T);
}

AVL * RL(AVL *T)
{
    T->right=rotateright(T->right);
    T=rotateleft(T);
    return(T);
}

int BF(AVL *T)
{
    int lh,rh;
    if(T==NULL) return(0);

    if(T->left==NULL)
        lh=0;
    else
        lh=1+T->left->height;

    if(T->right==NULL)
        rh=0;
    else
        rh=1+T->right->height;

    return(lh-rh);
}

void preorder(AVL *T)
{
    if(T!=NULL)
    {
        printf("%d-",T->data);
        preorder(T->left);
        preorder(T->right);
    }
}

void inorder(AVL *T)
{
    if(T!=NULL)
    {
        inorder(T->left);
        printf("%d-",T->data);
        inorder(T->right);
    }
}
