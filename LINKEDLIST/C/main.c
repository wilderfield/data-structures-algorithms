#include <stdio.h>  // printf
#include <stdlib.h> // malloc/free
#include <stdbool.h> // bool type true/false

struct node {
  int val;
  struct node* next;
};

void print(struct node* head) {
  //printf("Starting Linked List Print Function\n");

  struct node* curr;

  for(curr=head;curr!=NULL;curr=curr->next) {
    //printf("Curr %p\n",curr);
    //printf("Val %i\n",curr->val);
    //printf("Next %p\n",curr->next);
    printf("%i ",curr->val);
  }

  printf("\n");

}

void push(struct node** headref,int val) {
  //printf("Starting Linked List Push Function\n");

  struct node* curr = (struct node*) malloc(sizeof(struct node));
  curr->val = val;
  // Because we are passed a pointer to the head pointer
  // We can change the head pointer, and not rely on the caller
  // We will first point our node to the address of the old head node
  // Then make the head pointer point to our newly created node
  curr->next = *headref;
  *headref = curr;

}

int pop(struct node** headref) {
  //printf("Starting Linked List Pop Function\n");

  struct node* curr = *headref;

  int val;
  
  val = curr->val;
  *headref = curr->next;

  free(curr);

  return val;

}

void reverse(struct node** headref) {
  printf("Starting Linked List Reverse Function\n");

  struct node* curr;
  struct node* next;
  struct node* prev = NULL;
  
  for(curr=*headref;curr!=NULL;curr=next) {
    if(curr->next == NULL) // If we are at the tail
      *headref = curr;     // This is the new head 
    next       = curr->next; // Save next for proper traversal
    curr->next = prev;       // Reverse pointer
    prev       = curr;       // Save current for next iteration
  }
}

bool isCircular(struct node* head) {
  printf("Starting Linked List isCircular Function\n");
  
  struct node* curr1;
  struct node* curr2;


  curr1 = head; // First pointer starts at first node

  if((curr1 == NULL)||(curr1->next==NULL)) // Need at least two nodes to be circular
    return false;

  curr2 = curr1->next; // Second pointer starts at second node

  while(curr1!=curr2) { // Iterate until the pointers match
    if(curr2->next == NULL)
      return false;
    else if(curr2->next->next == NULL)
      return false;
    else
      curr2 = curr2->next->next;
    if(curr1->next == NULL)
      return false;
    else
      curr1 = curr1->next;
  }
  
  return true; // If we escape while loop then this list is circular

}

void makeCircle(struct node* head) {
  //printf("Starting Linked List makeCircle Function\n");

  struct node* curr;

  for(curr=head;curr!=NULL;curr=curr->next) {
    if(curr->next == NULL) { // If we are at the tail
      curr->next = head;     // Create circle 
      break;
    } 
  }

}

int length(struct node* head) {
  //printf("Starting Linked List Length Function\n");

  int len = 0;
  struct node* curr;

  for(curr=head;curr!=NULL;curr=curr->next)
    len++;

  return len;

}

//void dedup(struct node* head) { // Remove duplicates with a hash table
//- don't have time
//
//}

int main (void) {

  printf("Starting Linked List Test Function\n");
  
  struct node* list = NULL;

  int test;
  int len; 

  bool circ = false;

  push(&list,0);
  push(&list,1);
  push(&list,2);
  push(&list,3);
  push(&list,4);
 
  print(list);
  /*
  len  = length(list);
  printf("%i\n",len);
  
  test = pop(&list);
  
  len  = length(list);
  printf("%i\n",len);
  */

  //makeCircle(list);

  circ = isCircular(list);
 
  if(circ)
    printf("The list is circular\n");
  else
    printf("The list is linear\n");


  //reverse(&list);

  //print(list);

  //printf("%i\n",test);

  return 0;

}
