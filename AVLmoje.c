#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node *left;
    struct node *right;
    int balance;
    int height;
};
//Vytvori novy node
struct node *newNode(int data)
{
    struct node *temp =  (struct node *)malloc(sizeof(struct node));
    temp->data = data;
    temp->left = NULL;
    temp->right = NULL;
    temp->height = 1;
    temp->balance = 0;
    return temp;
}
//Rekurzivne prehlada strom
int searchAVL(int searchData, struct node *root)
{
    if(root == NULL)
    {
        printf("Chyba\n");
        return -1;
    }
    else if(root -> data == searchData)
    {
        return root -> data;
    }
    else if(root -> data > searchData)
    {
        searchAVL(searchData, root -> left);
    }
    else if(root -> data < searchData)
    {
        searchAVL(searchData, root -> right);
    }

}
//zmena balance a height stromu po inserte
void changeHeight(struct node *root)
{
    //Zmena height a balance
    if(root->right != NULL && root->left != NULL)
    {
        if(root->right->height > root->left->height)
        {
            root->height = 1 + root->right->height;
        } else{
            root->height = 1 + root->left->height;
        }
        root -> balance = root->left->height - root->right->height;
    }
    else if(root->right != NULL)
    {
        root->height = 1 + root->right->height;
        root -> balance = 0 - root->right->height;
    }
    else if(root->left != NULL)
    {
        root->height = 1 + root->left->height;
        root -> balance = root->left->height - 0;
    }
    else if(root->left == NULL && root->right == NULL)
    {
        root->height = 1;
        root -> balance = 0;
    }
}

struct node *leftRotate(struct node *root1)
{
    struct node *son = root1->right;
    struct node *grandSon = son -> left;

    root1 -> right = grandSon;
    son ->  left = root1;
    //changeHeight(grandSon);
    changeHeight(root1);
    changeHeight(son);
    return son;
}

struct node *rightRotate(struct node *root2)
{
    struct node *son = root2->left;
    struct node *grandSon = son -> right;

    root2 -> left = grandSon;
    son ->  right = root2;
    //changeHeight(grandSon);
    changeHeight(root2);
    changeHeight(son);
    return son;
}
//Insertne node
struct node *insertNode(int data, struct node *root)
{
    //Insert
    if(root == NULL)
    {
        return newNode(data);
    }
    else if(data > root -> data)
    {
        root -> right = insertNode(data, root -> right);
    }
    else if(data <= root -> data)
    {
        root -> left = insertNode(data, root -> left);
    }
    //Zmena height a balance
    if(root->right != NULL && root->left != NULL)
    {
        if(root->right->height > root->left->height)
        {
            root->height = 1 + root->right->height;
        } else{
            root->height = 1 + root->left->height;
        }
        root -> balance = root->left->height - root->right->height;
    }
    else if(root->right != NULL)
    {
        root->height = 1 + root->right->height;
        root -> balance = 0 - root->right->height;
    }
    else if(root->left != NULL)
    {
        root->height = 1 + root->left->height;
        root -> balance = root->left->height - 0;
    }
    //Posunutia
    /*
    if(root -> balance > 1 &&  root-> data < root->left->data)
    {
        root = rightRotate(root);
    }
    if(root -> balance < -1 && root-> data < root->right->data)
    {
        root = leftRotate(root);
    }
    if(root -> balance > 1 && root-> data < root->left->data)
    {
        root -> left = leftRotate(root -> left);
        root = rightRotate(root);
    }
    if(root -> balance < -1 && root-> data < root->right->data)
    {
        root -> right = rightRotate(root -> right);
        root = leftRotate(root);
    }
     */
    //Pouzitie rotacii ak je srom nevyvazeni
    if(root -> balance > 1){ //Vela nalavo
        if(root -> left -> balance < 0 )
        {
            root -> left = leftRotate(root -> left);
            root = rightRotate(root);
        }
        else{
            root = rightRotate(root);
        }
    }
    else if(root -> balance < -1 ) //Vela napravo
    {
        if(root -> right -> balance > 0 )
        {
            root -> right = rightRotate(root -> right);
            root = leftRotate(root);
        }
        else{
            root = leftRotate(root);
        }
    }
    return root;
}
// nevyuzite
void printTree(struct node *root) {
    if (root) {
        if(root -> balance >= 2 || root -> balance <= -2)
        {
            printf("Zle");
        }
        printTree(root->left);
        printTree(root->right);
    }
}
/*
int main() {
    struct node *root = NULL;

    root = insertNode(1,root);
    root = insertNode(2,root);
    root = insertNode(3,root);


    root = insertNode(3,root);
    root = insertNode(2,root);
    root = insertNode(1,root);

    root = insertNode(1,root);
    root = insertNode(4,root);
    root = insertNode(5,root);
    root = insertNode(6,root);
    root = insertNode(7,root);
    root = insertNode(8,root);
    //root = insertNode(9,root);
    //printf("%d",root->data);
    printf("%d", search(6,root));
    return 0;
}
*/

