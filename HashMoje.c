#include <stdio.h>
#include <stdlib.h>

int size = 199; //Velkost tabulky, prvocislo
int prime [1299710]; // Nevyuzite


int getHash(int key)
{
    return key%size;
}

struct hashElement
{
    int data;
    int key;
    struct hashElement *next;
};

struct hashTable
{
    int numberOfElements;
    struct hashElement **elements;
};

struct hashTable *table;
// Inicializuje table na pouzitie
void initialize()
{
    table = malloc(sizeof(struct hashTable));

    table -> elements = malloc(sizeof(struct hashElement) * size);

    table -> numberOfElements = 0;

    for(int i = 0; i<size; ++i)
    {
        table -> elements[i] = NULL;
    }
}
//Vytvory novy node
struct hashElement *newHashNode(int data, int key)
{
    struct hashElement *newElement = malloc(sizeof(struct hashElement));

    newElement -> data = data;
    newElement -> key = key;
    newElement -> next = NULL;

    return newElement;
}
//Najde dalsi prime od argumentu size
int nextPrime(int size)
{
    /*
    for(int i=0;i<1299709;i++)
    {
        if(prime[i] != 0)
        {
            if(prime[i] >= size)
            {
                //printf("Je to %d\n",prime[i]);
                return prime[i];
            }
        }
    }*/
    int table [23] = {389,769,1543,3079,6151,12289,24593,49157,98317,196613,393241,786433,1572869,3145739,6291469,12582917,25165843,50331653,100663319,201326611,402653189,805306457,1610612741};
    for(int i=0;i<23;i++)
    {
        if(table[i] > size)
        {
            return table[i];
        }
    }
}
//Resizne hash na dalsie dostupne prvocislo
void resizeHash()
{
    int oldSize = size;
    size = nextPrime(size);
    //printf("Resizujeme hash na velkost %d z %d, pocetElementov je %d\n",size,oldSize,table->numberOfElements);
    struct hashElement **newElements = malloc(sizeof(struct hashElement) * size);

    int numberOfElements = 0;
    //newElements[0] = NULL;
    //printf("Dostali sme sa sem\n");
    for(int i = 0; i<size; ++i)
    {
        newElements[i] = NULL;
    }
    int key;
    int newIndex;
    int data;
    struct hashElement *temp;
    for(int i = 0; i<oldSize; ++i)
    {
        temp = table -> elements[i];
        if(temp != NULL)
        {
            //printf("Temp je %d\n", temp ->data);
            while(temp != NULL) {
                key = temp->key;
                newIndex = getHash(key);
                data = temp ->data;
                if (newElements[newIndex] == NULL) {
                    newElements[newIndex] = newHashNode(data,key);
                    //printf("Inserted on index %d \n", newIndex);
                }
                else
                {
                    //printf("\nKOLIZIA\n");
                    struct hashElement *temp1;
                    temp1 = newElements[newIndex];
                    while(temp1 -> next != NULL)
                    {
                        temp1 = temp1 -> next;
                    }
                    temp1 -> next = newHashNode(data,key);

                }
                temp = temp -> next;
            }
        }
    }
    free(table -> elements);
    table -> elements = newElements;


}
//Hlada miesto na insert noveho node
void insertHashNode(int data, int key)
{
    int index = getHash(key);
    //printf("Original hash %d \n", index);
    if (table->elements[index] == NULL) {
        table->elements[index] = newHashNode(data, key);
        //printf("Inserted on index %d \n", index);
        table -> numberOfElements = table -> numberOfElements + 1;
        //Resizne table ak je zaplnenost viac ako 0.5
        if((double)table -> numberOfElements / (double)size >= 0.5)
        {
            resizeHash();
        }
    }
    else if(table->elements[index] -> key == key)
    {
        //printf("Prepisujeme data\n");
        table->elements[index] -> data = data;
    }
    else
    {
        //printf("\nKOLIZIA\n");
        struct hashElement *temp;
        temp = table->elements[index];
        while(temp -> next != NULL)
        {
            temp = temp -> next;
        }
        //printf("Inserted on index %d \n", index);
        table -> numberOfElements = table -> numberOfElements + 1;
        struct hashElement *temp1;
        temp1 = newHashNode(data, key);
        temp -> next = temp1;

    }
}
//Hlada key v tabulke
int searchHash(int key)
{
    int index = getHash(key);
    struct hashElement *temp;
    temp = table->elements[index];
    while(temp != NULL)
    {
        if (temp -> key == key ) {
            //printf("The data is  %d\n", temp -> data);
            return temp -> data;
        }
        temp = temp -> next;
    }
    //printf("Nenaslo sa \n");
}

void printTable()
{
    for(int i=0; i < size; ++i)
    {
        if(table -> elements[i] != NULL)
        {
            printf("%d\n",table -> elements[i] ->data);
        }
    }
}
//nevyuzite
void initializePrime()
{
    int cislo = 1;
    for(int i=0;i<1299709;i++)
    {
        prime[i]=cislo;
        ++cislo;
    }

    for (int i=1; i<1299709;i++)
    {
        if(prime[i]!=0)
        {
            for(int l=(i+i)+1; l<=1299709 ; l+=prime[i])
            {
                prime[l]=0;
            }
        }
    }

    /*for(int i=0;i<1299709;i++)
    {
        if(prime[i] != 0)
        {
            printf("%d\n",prime[i]);
        }
    }*/
}


/*int main()
{
    initialize();
    initializePrime();
    insertHashNode(99,405);
    insertHashNode(420,666);
    searchHash(405);
    for(int i =0,  j = 1 ; i < 60; ++i,++j)
    {
        insertHashNode(i,j);
    }
    printTable();
    for(int i =60,  j = 61 ; i < 120; ++i,++j)
    {
        insertHashNode(i,j);
    }
    printTable();
    for(int i =1000,  j = 1001 ; i < 1500; ++i,++j)
    {
        insertHashNode(i,j);
    }
    //insertHashNode(99,405);
    searchHash(405);
    //searchHash(50);
    //insertHashNode(10,20);
    //searchHash(54);
    //printf("%d",size);
    return 0;
}*/