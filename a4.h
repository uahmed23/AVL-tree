/*
Name: Umer Ahmed
ID: 1010091
Date: November 26th 2018
Assignment 4
*/

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>



#ifndef A4_H
#define A4_H

typedef struct node{
  char key[10];
  int count;
  struct node* leftChild;
  struct node* rightChild;

}node;


int userOptions();
node* make_avltree();
node *new_node(  char key[10]);
int tree_height(node* np);
void insert_node(node **tp, node *toInsert);
int balance_factor(node* np);
void preOrder_print(node* top );
void SL_rotation( node** grandparent);
void SR_rotation( node** grandparent);
void RL_rotation( node** grandparent);
void LR_rotation(node** grandparent);
void initializationCheck();
void find_key(node *root, char toFind[10]);
void find_all(node *root, int frequency);
void get_size(node *root,int *size, int *totalCount);
void remove_node(node **root, node *toRemove);
node* inOrder_next(node* top );
void free_node(node **root,node* tofree);





#endif
