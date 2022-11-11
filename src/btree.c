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
    return t;

    //Først tjekker jeg om x er mindre end eller lig med t->item. 
  } else if(x <= t->item){
    //Hvis den er det, så kører jeg recursion på t->left. 
    t->left = Insert(x,t->left);
    return t;
  } else  {
   // Når vi herned er x større end t->value. 
   //Så kører jeg recursion på t-right
    t->right = Insert(x,t->right);
    return t;
  }
}
  
struct tree_node *Remove(int x, struct tree_node *t) {
  // Remove one item from the tree t
  
  //If sætning som tjekker om træet indeholder x. Hvis ikke så returner jeg bare træet. 
  if(Contains(x,t)){

    //En if sætning, som kun gælder når vi har fundet vores node, der skal slettes. 
    if(t->item == x){

      //Remove hvis t har to børn. Det er lidt noget bøvl.
     if(t->left != NULL && t->right != NULL){
      //Laver en temp node, som er t->right. 
      struct tree_node *temp = t->right;
      //Et while loop, som sørger for at temp bliver værdien tættest på x. Altså længst mod venstre. 
      while (temp->left != NULL){
        temp = temp->left;
      }
      //Nu bytter jeg rundt på værdien af t og temp. 
      t->item = temp->item;
      //For at sørge for at free en node ved remove, kører jeg remove på t(som er den oprindelige t)->right
      Remove(t->item,t->right);
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

    //return NULL;

  } else {
      return t;
    }
}

int Contains(int x, struct tree_node *t) {
  // Return true if the tree t contains item x. Return false otherwise.

  //Tjekker om træet er tomt.
  if (t == NULL){
    return 0;
  } 

  //Hvis t->item == x
  else if (t->item == x) {
    return 1;
  } 
  //Hvis x < t->item, så skal jeg kun tjekke den venstre side af træet
  else if (x < t->item) {
    return Contains(x,t->left);
  } 
  //Hvis x > t-item, så skal jeg kun tjekke den højre side af træet. 
  else if (x > t->item) {
    return Contains(x,t->right);
  }
  //Skulle helst ikke ende her,  
  else {
    printf("Det her er ikke helt godt\n");
    return 2;
  }

}

struct tree_node *Initialize(struct tree_node *t) {
  // Create an empty tree
  //returner bare Null. 
  t == NULL;
  return t;
}

int Empty(struct tree_node *t) {
  // Test if empty
  //Tester om t == NULL 
  if(t == NULL){
    return 1;
  }
  return 0;
}

//Giver ikke mening. 
int Full(struct tree_node *t) {
  // Test if full
  return 0;
}

//Har lavet en createNode funktion. Troede jeg ville få lidt mere brug for den en jeg faktisk gjorde. ÆV BÆV
struct tree_node *createNode(int value)
{
  struct tree_node *nodePtr = malloc(sizeof(struct tree_node));
  nodePtr->item = value;
  nodePtr->left = NULL;
  nodePtr->right = NULL;
  return nodePtr;
}

//En printTree funktion, som printer træet. Primært brugt til debugging. 
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

