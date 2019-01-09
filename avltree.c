/*
Name: Umer Ahmed
ID: 1010091
Date: November 26th 2018
Assignment 4
*/

#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>
#include "a4.h"

int main(int argc, char const *argv[]) {

  int userSelect;
  int initializeFirst = 0;
  node *root = NULL;
  node *newNode = NULL;
  int i;
  char key[10];
  int frequency;
  int height=0;
  int size=0;
  int totalCount=0;

  do
  {
    userSelect = userOptions();

    switch (userSelect)
    {
        case 1:
          root = make_avltree();
          initializeFirst = 1;
           /*
           1. Initialization
           Open A4_data_f18.txt...
           reads and insert keys into the AVL tree on the word by word basis.
           */
           break;

        case 2:

          if(initializeFirst == 0)
          {
            initializationCheck();
            break;
          }

          printf("find key: ");
          getchar(); // empties stdin of extra spaces
          fgets(key, 10, stdin);
          for(i=0; i<strlen(key); i++ ){ //removes a newline char from string
            if(key[i] == '\n'){
              key[i] = '\0';
            }
          }

          find_key(root, key);
          /*
          2. Find
          Ask for a key,
          then searches the AVL tree and display the key and its frequency count if it finds the key,
          or display No_such_key if it could not find the key in the tree.
          */
          break;

        case 3:

          if(initializeFirst == 0)
          {
            initializationCheck();
            break;
          }

          printf("insert key: ");
          getchar(); // empties stdin of extra spaces
          fgets(key, 10, stdin);
          for(i=0; i<strlen(key); i++ ){ //removes a newline char from string
            if(key[i] == '\n'){
              key[i] = '\0';
            }
          }

          newNode = new_node(key);
          insert_node(&root, newNode);
          find_key(root, key);
          /*
          3. Insert
          Your program should ask for the key to be inserted and then search for
          the position where the key should be placed.
          Your insertion function shall increase the count
          if the key has already been in the AVL tree,
          or carry out the actual insertion if the key is a new one
          (set the count to be 1).
          */

          break;

        case 4:
          if(initializeFirst == 0)
          {
            initializationCheck();
            break;
          }

          printf("remove key: ");
          getchar(); // empties stdin of extra spaces
          fgets(key, 10, stdin);
          for(i=0; i<strlen(key); i++ ){ //removes a newline char from string
            if(key[i] == '\n'){
              key[i] = '\0';
            }
          }

          newNode = new_node(key);
          remove_node(&root, newNode);
          find_key(root, key);

        /*
        4. Remove
        your program should ask for the key to be removed
        and then search for the matching key.
        If it could not find the given key, it should display
        No_such_key
        If it finds the key, it removes the tree node only if the frequency
        count of the key is 1, or it decreases the count of the node by 1 otherwise.
        */

          break;

        case 5:

          if(initializeFirst == 0)
          {
            initializationCheck();
            break;
          }
          height= tree_height(root);
          size= 0;
          totalCount = 0;
          get_size(root,&size,&totalCount);
          printf("height: %d, size: %d, total count: %d\n",height,size, totalCount );
        /*
        5. Check Height, Size, and Total Count
        When option 5 is selected, your program should compute and display the
        height and the size of the AVL tree, which is the number of nodes,
         and the totalcount (sum of all the counts).
        */
        break;

        case 6:

          if(initializeFirst == 0)
          {
            initializationCheck();
            break;
          }

          printf("frequency: ");
          scanf("%d",&frequency );

          find_all(root, frequency);

        /*
        6. Find All (above a given frequency)
        When option 6 is selected, your program should ask for a positive integer,
         and then display all keys whose frequency counts are greater than or
         equal to the given integer.
        */
        break;

        case 7:
          
          break;

        default:
          printf("Please select enter an integer from 1-7.\n");

      }

    }while(userSelect !=7);


  return 0;
}
