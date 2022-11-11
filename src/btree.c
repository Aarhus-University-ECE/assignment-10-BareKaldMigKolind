#include "btree.h"

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>



struct tree_node *Insert(int x, struct tree_node *t) {
  // Insert item x into the tree t


   //Basecase er at t == NULL 
  if(t == NULL){ 
    t = createNode(x);
   // printf("Insert %d\n",t->item);
    return t;
  } else if(x <= t->item){
    //printf("insert->left\n");
    t->left = Insert(x,t->left);
    return t;
  } else  {
   // printf("Insert->rigth\n");
    t->right = Insert(x,t->right);
    return t;
  }
}
  

struct tree_node *Remove(int x, struct tree_node *t) {
  // Remove one item from the tree t
  //printf("x == %d\n",x);
  //assert(Contains(x,t) == 1);
  
  if(Contains(x,t)){
  // 
  if(t->item == x){

    //Remove hvis t har to børn. 
    if(t->left != NULL && t->right != NULL){
    struct tree_node *temp = t->right;
    while (temp->left != NULL){
      temp = temp->left;
    }
    t->item = temp->item;
    free(temp);
    return t;
    }
    //Kun har højre barn eller ingen børn
    if(t->left == NULL) {
      struct tree_node *temp = t->right;
      free(t);
      return temp;
    }
    //Kun venstre barn. 
      if(t->right == NULL) {
      struct tree_node *temp = t->left;
      free(t);
      return temp;
    }



  //Det her er recursion til at finde t
  } else if(x < t->item){
   t->left = Remove(x, t->left);
    return t;
  } else if (x > t->item) {
    t->right = Remove(x, t->right);
    return t;
  }

  return NULL;
  } else {
    return t;
  }
}

int Contains(int x, struct tree_node *t) {
  // Return true if the tree t contains item x. Return false otherwise.

  if (t == NULL){
   // printf("t == NULL\n");
    return 0;
  } 
  else if (t->item == x) {
   // printf("t->item == x\n");
   //printf("Succes: %d == %d\n\n", t->item, x);
    return 1;
  } 
  else if (x < t->item) {
   // printf("x == %d\n", x);
   // printf("x < t->item\n");
    return Contains(x,t->left);
  } 
  else if (x > t->item) {
   // printf("x < t->item\n");
    return Contains(x,t->right);
  } else {
   // printf("Det her er en fejl\n");
    return 2;
  }

}

struct tree_node *Initialize(struct tree_node *t) {
  // Create an empty tree
  t == NULL;
  return t;
}

int Empty(struct tree_node *t) {
  // Test if empty
  if(t == NULL){
    return 1;
  }
  return 0;
}

int Full(struct tree_node *t) {
  // Test if full
  return 0;
}

struct tree_node *createNode(int value)
{
  struct tree_node *nodePtr = malloc(sizeof(struct tree_node));
  nodePtr->item = value;
  nodePtr->left = NULL;
  nodePtr->right = NULL;
  return nodePtr;
}

void printTree(struct tree_node *t, int depth){
  if (t == NULL) {
    return;
  }
  for (int i = 0; i < depth; i++) {
    printf("-");
  }
  printf("|%d\n", t->item);

  printTree(t->left, depth + 1);
  printTree(t->right, depth +1);
}

