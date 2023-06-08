#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "set.h"
#include "hashtable.h"


set_t *set_new(void) {
  set_t *set = malloc(sizeof(struct set));  // malloc into set
  if (set == NULL) {
    return NULL;   //checking for null in set
  }

  set->head = NULL;  // pointing values null and zero
  set->size = 0;

  return set;  // end
}

bool set_insert(set_t *set, const char *key, void *item) { // set insert function
  if (set == NULL || key == NULL || item == NULL) {  // checking set, key, item are null
    return false;
  }

  struct set_node *node = malloc(sizeof(struct set_node));  // malloc struct
  if (node == NULL) { // checking node full
    return false;
  }

  node->key = strdup(key);  // pointing values 
  node->item = item;

  // Check to see if the key already exists in the set.
  if (set_find(set, key) != NULL) { // checking not equal null
    	free(node->key);  // free memory 
        free(node);	
	return false;
  }

  // Insert the node into the set.
  node->next = set->head;
  set->head = node;
  set->size++;

 // free(node->key);

  return true;
} 




void *set_find(set_t *set, const char *key) {
  if (set == NULL || key == NULL) {    // checking for null for set and key
    return NULL;
  }

  struct set_node *node = set->head;   // struct set
  while (node != NULL) {    // while loop for node null
    if (strcmp(node->key, key) == 0) {
      return node->item;  // end
    }

    node = node->next;
  }

  return NULL;
}

void set_print(set_t *set, FILE *fp, void (*itemprint)(FILE *fp, const char *key, void *item)) {
  if (set == NULL || fp == NULL) {
    return;
  }

  struct set_node *node = set->head;    //pointing to head
  while (node != NULL) {
    if (itemprint != NULL) {
      itemprint(fp, node->key, node->item);   // pointing further to item 
    } else {
      fprintf(fp, "(%s, %p)\n", node->key, node->item);
    }

    node = node->next; // pointing to node next
  }
}

void set_iterate(set_t *set, void *arg, void (*itemfunc)(void *arg, const char *key, void *item)) {
  if (set == NULL || itemfunc == NULL) {  // set iterate function to checking set and itemfunc null
    return;
  }

  struct set_node *node = set->head;
  while (node != NULL) { // while loop for null
    itemfunc(arg, node->key, node->item);
    node = node->next; // pointing memory value 
  }
}

void set_delete(set_t *set, void (*itemdelete)(void *item)) {
  if (set == NULL) { // set delete function checking null
    return;  // checking set equal to null
  }

  struct set_node *node = set->head;
  while (node != NULL) {
    struct set_node *next = node->next;

    if (itemdelete != NULL) {
      itemdelete(node->item);
    }

    free(node->key);
    free(node);

    node = next;
  }

  free(set);  // freeing memory at the end
}
