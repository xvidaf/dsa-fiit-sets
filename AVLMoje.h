//
// Created by vidaf on 4/10/2020.
//

#ifndef DSAZADANIE2_AVLMOJE_H
#define DSAZADANIE2_AVLMOJE_H

struct node;

struct node *newNode(int data);

int searchAVL(int searchData, struct node *root);

void changeHeight(struct node *root);

struct node *leftRotate(struct node *root1);

struct node *rightRotate(struct node *root2);

struct node *insertNode(int data, struct node *root);

void print_tree(struct node *root);


#endif //DSAZADANIE2_AVLMOJE_H
