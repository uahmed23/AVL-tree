/*
Name: Umer Ahmed
ID: 1010091
Date: November 26th 2018
Assignment 4
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <stdbool.h>
#include <ctype.h>
#include "a4.h"


node* make_avltree(){

  FILE *fp =NULL;
  char buffer[1000];
  char key[20];
  int i,j,k;
  node *root = NULL;
  node *newNode = NULL;

  fp = fopen("A4_data_f18.txt","r");

  if (fp== NULL)
  {
    printf("ERROR: Can't open or find A4_data_f18.txt\n");
  }
  else
  {
    printf("Initializing tree...\n" );
     while ( fgets(buffer,1000,fp) != NULL )
     {
        for(i=0; i<strlen(buffer); i++)
        {
          if( tolower(buffer[i])>= 'a' && tolower(buffer[i])<= 'x')
          {
            k = 0;
            for(j=i; (tolower(buffer[j])>= 'a' && tolower(buffer[i])<= 'x') || ( buffer[j] >= '0' && buffer[j]<= '9');j++ )
            {
              key[k] = buffer[j];
              k++;
            }
            key[k]= '\0';
            i= j-1;

            newNode = new_node(key);
            insert_node(&root, newNode);
          }
        }
      }
      printf("Done.\n");
    }
    fclose(fp);
    return root;
}

void insert_node(node **tp, node *toInsert){

  if( *tp== NULL )
  {
    *tp = toInsert;
  }
  else if(strcmp((*tp)->key, toInsert->key) < 0 )
  {
    insert_node(&(*tp)->rightChild, toInsert);
  }
  else if(strcmp((*tp)->key, toInsert->key) > 0 )
  {
    insert_node(&(*tp)->leftChild, toInsert);
  }
  else if(strcmp((*tp)->key,toInsert->key) == 0)
  {
    (*tp)->count = (*tp)->count +1;
  }
  else
  {
  }
  //INSERTED NOW CHECK BALANCE
  if(balance_factor(*tp) > 1 || balance_factor(*tp)< -1  )
  {
    if ((*tp)->rightChild != NULL && strcmp( (*tp)->key, toInsert->key) < 0   )
    {
      if(strcmp( (*tp)->rightChild->key, toInsert->key) < 0 )
      {
        SL_rotation(tp);
      }
      else if(strcmp( (*tp)->rightChild->key, toInsert->key) > 0)
      {
        RL_rotation(tp);
      }
    }
    else if((*tp)->leftChild != NULL  && strcmp( (*tp)->key, toInsert->key) > 0 )
    {
      if(strcmp( (*tp)->leftChild->key, toInsert->key) > 0)
      {
        SR_rotation( tp);
      }
      else if(strcmp( (*tp)->leftChild->key, toInsert->key) < 0)
      {
        LR_rotation(&(*tp));
      }
    }
  }
}

void remove_node(node **root, node *toRemove){

  node *temp;

  if( *root== NULL )
  {
    //printf("No_such_key\n" );

  }
  else if(strcmp( (*root)->key, toRemove->key) < 0 )
  {
    remove_node( &(*root)->rightChild, toRemove);
  }
  else if(strcmp( (*root)->key, toRemove->key) > 0 )
  {
    remove_node( &(*root)->leftChild, toRemove);
  }
  else if(strcmp( (*root)->key,toRemove->key) == 0)
  {
    //no child
    if((*root)->count > 1)
    {
      (*root)->count =   (*root)->count - 1;
    }
    else
    {
      if( ((*root)->leftChild) == NULL && (*root)->rightChild == NULL )
      {
        *root =NULL;
        free(*root);
      }
      //one child
      else if( ((*root)->leftChild) != NULL && (*root)->rightChild == NULL )
      {
        temp = *root;
        *root = (*root)->leftChild;
        free(temp);

      }
      else if( ((*root)->leftChild) == NULL && (*root)->rightChild != NULL )
      {
        temp = *root;
        *root = (*root)->rightChild;
        free(temp);
      }
      else
      {
        temp = inOrder_next( (*root)->rightChild);
        strcpy((*root)->key, temp->key);
        (*root)->count = temp->count;
        remove_node( &((*root)->rightChild), temp);
      }
    }
  }

  //DELETED NOW ReBaLaNcE

  if(*root != NULL)
  {
    if(balance_factor(*root) > 1 || balance_factor(*root)< -1  )
    {
      if( tree_height((*root)->rightChild) > tree_height((*root)->leftChild))
      {
        if(tree_height((*root)->rightChild->rightChild) > tree_height((*root)->rightChild->leftChild) )
        {
          SL_rotation(root);
        }
        else if(tree_height((*root)->rightChild->rightChild) < tree_height((*root)->rightChild->leftChild) )
        {
          RL_rotation(root);
        }
      }
      else if(tree_height((*root)->rightChild) < tree_height((*root)->leftChild) )
      {
        if(tree_height((*root)->leftChild->leftChild) > tree_height((*root)->leftChild->rightChild) )
        {
          SR_rotation( root);

        }
        else if(tree_height((*root)->leftChild->leftChild) < tree_height((*root)->leftChild->rightChild))
        {
          LR_rotation(&(*root));
        }
      }
    }
  }
}

node* inOrder_next(node* top ){

  node *min = top;

  while(min->leftChild != NULL )
  {
    min = min->leftChild;
  }
  return min;
}


void SL_rotation( node** grandparent)
{
    node *temp;

    temp = (*grandparent)->rightChild;
    (*grandparent)->rightChild = temp->leftChild;
    temp->leftChild = (*grandparent);
    (*grandparent) = temp;
}

void SR_rotation( node** grandparent)
{
    node *temp;

    temp = (*grandparent)->leftChild;
    (*grandparent)->leftChild = temp->rightChild;
    temp->rightChild = (*grandparent);
    (*grandparent) = temp;
}


void RL_rotation( node** grandparent)
{
    SR_rotation(&((*grandparent)->rightChild));
    SL_rotation(&(*grandparent) );
}


void LR_rotation( node** grandparent)
{
    SL_rotation(&((*grandparent)->leftChild));
    SR_rotation(grandparent);
}

void find_key(node *root, char toFind[10]){

  if( root== NULL )
  {
    printf("No_such_key\n" );

  }
  else if(strcmp((root)->key, toFind) < 0 )
  {
    find_key(root->rightChild, toFind);
  }
  else if(strcmp( (root)->key, toFind) > 0 )
  {
    find_key(root->leftChild, toFind);
  }
  else if(strcmp((root)->key,toFind) == 0)
  {
    printf("key: %s, frequency: %d\n", root->key, root->count );
  }
  else
  {
  }

}


void find_all(node *root, int frequency){

  if(root->count >= frequency)
  {
    printf("key: %s, frequency: %d\n",root->key, root->count);
  }

  if(root->leftChild != NULL)
  {
    find_all(root->leftChild, frequency );
  }
  if(root->rightChild != NULL)
  {
    find_all(root->rightChild, frequency  );
  }


}

void get_size(node *root, int *size, int *totalCount){

  if(root != NULL)
  {
    *size = *size +1;
    *totalCount = *totalCount + root->count;
  }
  if(root->leftChild != NULL)
  {
    get_size(root->leftChild ,size, totalCount);
  }
  if(root->rightChild != NULL)
  {
    get_size(root->rightChild,size,totalCount  );
  }


}


void preOrder_print(node* top ){

  printf("%s %d ",top->key, top->count);

  if(top->leftChild != NULL)
  {
    preOrder_print(top->leftChild );
  }
  if(top->rightChild != NULL)
  {
    preOrder_print(top->rightChild  );
  }

}

node *new_node(char key[10]){

  node* np;
  if( (np = malloc(sizeof (node))) == NULL )
  {
    printf("new_car: dynamic allocation failed. \n");
    exit(0);
  }
  strcpy(np->key, key);
  np->count = 1;
  np->leftChild =NULL;
  np->rightChild = NULL;

  return np;
}

int balance_factor(node* np){
  int bFactor;

  bFactor = tree_height(np->leftChild) - tree_height(np->rightChild);
  return bFactor;
}

int tree_height(node* np){

  int heightL,heightR;

  if (np == NULL)
  {
    return 0;
  }
  else
  {
    heightL = tree_height(np->leftChild);
    heightR = tree_height(np->rightChild);
  }

  if(heightL > heightR)
  {
    return (heightL + 1);
  }
  else
  {
    return (heightR + 1);
  }

}

int userOptions(){

  int options;

  printf("\n1. Initialization\n");
  printf("2. Find\n");
  printf("3. Insert\n");
  printf("4. Remove\n");
  printf("5. Check Height, Size, and Total Count\n");
  printf("6. Find All(above a given frequency)\n");
  printf("7. Exit\n");
  printf("Enter a code (1 – 7) and hit Return\n" );
  printf("avl/> ");
  scanf("%d", &options);

  return options;
}

void initializationCheck() {

     printf("ERROR: Please initialize your tree first.\n" );

}
