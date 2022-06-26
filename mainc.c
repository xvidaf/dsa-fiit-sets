//
// Created by vidaf on 4/2/2020.
//
//#include "main.c"
//#include "RBT.c"
#include <stdio.h>
#include <stdlib.h>
#include "AVLMoje.h"
#include<time.h>
#include <windows.h>
#include "RBTPrevzate.c"
#include "HashMoje.c"
#include "hashPrevzaty.c"

void testTree(int amount, int nOfSearch)
{
    printf("/////////////////////////////////////////////////////////////////////////////////\n");
    LARGE_INTEGER frequency;
    LARGE_INTEGER start;
    LARGE_INTEGER end;
    double interval;
    printf("Insertujeme %d prvkov, hladame %d\n",amount,nOfSearch);
    printf("Vlastna Implementacia\n");
    srand(time(0));
    //static int poleTestov[1000000];
    int *poleTestov;
    poleTestov=(int *) malloc(sizeof(int) * amount);
    for(int i = 0; i<amount; i++)
    {
        poleTestov[i] = rand();
    }

    int *hladaneHodnoty = (int *) malloc(sizeof(int) * nOfSearch);
    for(int i = 0; i<nOfSearch; i++)
    {
        hladaneHodnoty[i] = rand() % amount;
    }

    struct node *root = NULL;

    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&start);

    for(int i = 0; i<amount; i++)
    {
        root = insertNode(poleTestov[i],root);
    }
    QueryPerformanceCounter(&end);
    interval = (double) (end.QuadPart - start.QuadPart) / frequency.QuadPart;

    printf("Insert : %f\n", interval);

    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&start);

    for(int i = 0; i<nOfSearch; i++)
    {
        searchAVL(poleTestov[hladaneHodnoty[i]],root);
    }

    QueryPerformanceCounter(&end);
    interval = (double) (end.QuadPart - start.QuadPart) / frequency.QuadPart;

    printf("Search : %f\n", interval);
    printf("Prevzata Implementacia\n");
    //Prevzaty

    NILL = malloc(sizeof(struct node));
    NILL->color = BLACK;

    ROOT = NILL;

    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&start);

    for(int i = 0; i<amount; i++)
    {
        red_black_insert(poleTestov[i]);
    }

    QueryPerformanceCounter(&end);
    interval = (double) (end.QuadPart - start.QuadPart) / frequency.QuadPart;

    printf("Insert : %f\n", interval);

    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&start);

    for(int i = 0; i<nOfSearch; i++)
    {

       tree_search(poleTestov[hladaneHodnoty[i]]);
    }

    QueryPerformanceCounter(&end);
    interval = (double) (end.QuadPart - start.QuadPart) / frequency.QuadPart;

    printf("Search: %f\n",interval);


}

void testHash(int amount, int nOfSearch)
{
    LARGE_INTEGER frequency;
    LARGE_INTEGER start;
    LARGE_INTEGER end;
    double interval;

    printf("Insertujeme %d prvkov, hladame %d\n",amount,nOfSearch);
    printf("Vlastna Implementacia\n");

    initialize();

    srand(time(0));
    int *poleTestov;
    int *poleKeyov;
    poleTestov=(int *) malloc(sizeof(int) * amount);
    poleKeyov=(int *) malloc(sizeof(int) * amount);
    for(int i = 0; i<amount; i++)
    {
        poleTestov[i] = rand();
        poleKeyov[i] = i;
        //poleKeyov[i] = rand();
        //printf("%d\n",poleKeyov[i]);
    }

    int *hladaneHodnoty = (int *) malloc(sizeof(int) * nOfSearch);
    for(int i = 0; i<nOfSearch; i++)
    {
        hladaneHodnoty[i] = rand() % amount;
    }

    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&start);

    for(int i = 0; i<amount; i++)
    {
        insertHashNode(poleTestov[i],poleKeyov[i]);
        /*if(i%1000000==0) {
            printf("%d\n", i);
            printf("%d\n", table -> numberOfElements);
            printf("%d\n", size);
        }*/
    }

    QueryPerformanceCounter(&end);
    interval = (double) (end.QuadPart - start.QuadPart) / frequency.QuadPart;

    printf("Insert : %f\n", interval);

    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&start);

    for(int i = 0; i<nOfSearch; i++)
    {
        searchHash(hladaneHodnoty[i]);
    }

    QueryPerformanceCounter(&end);
    interval = (double) (end.QuadPart - start.QuadPart) / frequency.QuadPart;

    printf("Search : %f\n", interval);
    free(table);


    dummyItem = (struct DataItem*) malloc(sizeof(struct DataItem));
    dummyItem->data = -1;
    dummyItem->key = -1;

    printf("Prevzata Implementacia\n");

    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&start);

    for(int i = 0; i<amount; i++)
    {
        insert(poleKeyov[i],poleTestov[i]);
        /*if(i%10000==0) {
            printf("%d\n", i);
            printf("%d\n", table -> numberOfElements);
        }*/
    }


    QueryPerformanceCounter(&end);
    interval = (double) (end.QuadPart - start.QuadPart) / frequency.QuadPart;

    printf("Insert : %f\n", interval);

    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&start);

    for(int i = 0; i<nOfSearch; i++)
    {
        if(search(hladaneHodnoty[i])== NULL)
        {
            printf("Chyba");
        }
    }

    QueryPerformanceCounter(&end);
    interval = (double) (end.QuadPart - start.QuadPart) / frequency.QuadPart;

    printf("Search : %f\n", interval);


    free(dummyItem);




}


void testAVLPos(int amount, int nOfSearch)
{
    printf("/////////////////////////////////////////////////////////////////////////////////\n");
    LARGE_INTEGER frequency;
    LARGE_INTEGER start;
    LARGE_INTEGER end;
    double interval;
    printf("Vlastna Implementacia\n");
    srand(time(0));
    //static int poleTestov[1000000];
    int *poleTestov;
    poleTestov=(int *) malloc(sizeof(int) * amount);
    for(int i = 0; i<amount; i++)
    {
        poleTestov[i] = i;
    }

    struct node *root = NULL;

    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&start);

    for(int i = 0; i<amount; i++)
    {
        root = insertNode(poleTestov[i],root);
    }
    QueryPerformanceCounter(&end);
    interval = (double) (end.QuadPart - start.QuadPart) / frequency.QuadPart;

    printf("Insert : %f\n", interval);

    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&start);

    for(int i = 0; i<nOfSearch; i++)
    {
        searchAVL(poleTestov[i],root);
    }

    QueryPerformanceCounter(&end);
    interval = (double) (end.QuadPart - start.QuadPart) / frequency.QuadPart;

    printf("Search : %f\n", interval);

    printf("Prevzata Implementacia\n");

    NILL = malloc(sizeof(struct node));
    NILL->color = BLACK;

    ROOT = NILL;

    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&start);

    for(int i = 0; i<amount; i++)
    {
        red_black_insert(poleTestov[i]);
    }

    QueryPerformanceCounter(&end);
    interval = (double) (end.QuadPart - start.QuadPart) / frequency.QuadPart;

    printf("Insert : %f\n", interval);

    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&start);

    for(int i = 0; i<nOfSearch; i++)
    {

        tree_search(poleTestov[i]);
    }

    QueryPerformanceCounter(&end);
    interval = (double) (end.QuadPart - start.QuadPart) / frequency.QuadPart;

    printf("Search: %f\n",interval);


    free(dummyItem);
    free(table);

    //print_preorder(root);
}

void testAVLvsHash(int amount, int nOfSearch)
{
    LARGE_INTEGER frequency;
    LARGE_INTEGER start;
    LARGE_INTEGER end;
    double interval;

    printf("Insertujeme %d prvkov, hladame %d\n",amount,nOfSearch);
    printf("Vlastna Implementacia AVL\n");


    srand(time(0));
    int *poleTestov;
    int *poleKeyov;
    poleTestov=(int *) malloc(sizeof(int) * amount);
    poleKeyov=(int *) malloc(sizeof(int) * amount);
    for(int i = 0; i<amount; i++)
    {
        poleTestov[i] = i;
        poleKeyov[i] = i;
        //poleKeyov[i] = rand();
        //printf("%d\n",poleKeyov[i]);
    }

    int *hladaneHodnoty = (int *) malloc(sizeof(int) * nOfSearch);
    for(int i = 0; i<nOfSearch; i++)
    {
        hladaneHodnoty[i] = rand() % amount;
    }

    struct node *root = NULL;

    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&start);

    for(int i = 0; i<amount; i++)
    {
        root = insertNode(poleTestov[i],root);
    }
    QueryPerformanceCounter(&end);
    interval = (double) (end.QuadPart - start.QuadPart) / frequency.QuadPart;

    printf("Insert : %f\n", interval);

    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&start);

    for(int i = 0; i<nOfSearch; i++)
    {
        searchAVL(poleTestov[hladaneHodnoty[i]],root);
    }

    QueryPerformanceCounter(&end);
    interval = (double) (end.QuadPart - start.QuadPart) / frequency.QuadPart;

    printf("Search : %f\n", interval);




    printf("Vlastna Implementacia Hash\n");

    initialize();


    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&start);

    for(int i = 0; i<amount; i++)
    {
        insertHashNode(poleTestov[i],poleKeyov[i]);
    }

    QueryPerformanceCounter(&end);
    interval = (double) (end.QuadPart - start.QuadPart) / frequency.QuadPart;

    printf("Insert : %f\n", interval);

    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&start);

    for(int i = 0; i<nOfSearch; i++)
    {
        searchHash(hladaneHodnoty[i]);
    }

    QueryPerformanceCounter(&end);
    interval = (double) (end.QuadPart - start.QuadPart) / frequency.QuadPart;

    printf("Search : %f\n", interval);

}



int main() {

    //testTree(1000, 10);
    //testTree(1000, 100);
    //testTree(1000, 1000);
    //testTree(100000, 100);
    //testTree(100000, 1000);
    //testTree(100000, 100000);
    //testTree(1000000, 10);
    //testTree(1000000, 10000);
    //testTree(1000000, 1000000);
    //testTree(5000000, 1000000);
    //testTree(10000000, 10000000);
    //testTree(10000000, 100000);
    //testTree(10000000, 10000000);
    //testTree(20000000, 20000000);

    //testTree(10000000, 10000000);

    //testTree(1000000, 1000000);
    //testHash(1000, 1000);
    //testHash(100000, 100000);
    //testHash(1000000, 1000000);
    //testHash(5000000, 5000000);
    //testHash(10000000, 10000000);
    //testHash(20000000, 20000000);


    testHash(1000,10);
    //testHash(100000,10);
    //testHash(1000000,10);
    //testHash(10000000,10000000);
    //testHashPos(10000000,10);


    //testAVLPos(10000000,10000000);
    //testAVLPos(20000000,20000000);
    //testTree(10000000, 10000000);

    //testAVLvsHash(10000000, 10000000);





    //root = insertNode(9,root);
    //printf("%d",root->data);
    //printf("%d", search(9,root));
    return 0;
}
