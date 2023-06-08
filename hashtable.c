

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "set.h"
#include "hashtable.h"



/*struct hashtable {
  int num_slots;
  set_t **sets;
};*/

hashtable_t *hashtable_new(const int num_slots) { // hashtable new function and malloc values
  hashtable_t *ht = malloc(sizeof(hashtable_t)); 
  if (ht == NULL) {  // checking null 
    return NULL;
  }

  ht->num_slots = num_slots;
  ht->sets = malloc(sizeof(set_t *) * num_slots); // keeping track of memory
  if (ht->sets == NULL) {
    free(ht); // free memory
    return NULL;
  }

  for (int i = 0; i < num_slots; i++) { // looping through num slots to access sets value
    ht->sets[i] = set_new();
  }

  return ht;
}

bool hashtable_insert(hashtable_t *ht, const char *key, void *item) { // hashtable insert function check null all
  if (ht == NULL || key == NULL || item == NULL) {
    return false;
  }

  int hash = (int)strlen(key) % ht->num_slots; // hash variable
  if (!set_insert(ht->sets[hash], key, item)) { // checking sets hash, accessing key and item
    return false;
  }

  return true;
}

void *hashtable_find(hashtable_t *ht, const char *key) {
  if (ht == NULL || key == NULL) {
    return NULL;      // checking ht and key equal to null
  }

  int hash = (int)strlen(key) % ht->num_slots; 
  return set_find(ht->sets[hash], key); // end
}

void hashtable_print(hashtable_t *ht, FILE *fp, void (*itemprint)(FILE *fp, const char *key, void *item)) {
  if (ht == NULL || fp == NULL) {
    return;
  }

  for (int i = 0; i < ht->num_slots; i++) { // print values through num slots
    set_print(ht->sets[i], fp, itemprint);
  }
}

void hashtable_iterate(hashtable_t *ht, void *arg, void (*itemfunc)(void *arg, const char *key, void *item)) {
  if (ht == NULL || itemfunc == NULL) { // checking ht and itemfunc equal null
    return;
  }

  for (int i = 0; i < ht->num_slots; i++) { // iterate through num slots
    set_iterate(ht->sets[i], arg, itemfunc);
  }
}

void hashtable_delete(hashtable_t *ht, void (*itemdelete)(void *item)) {
  if (ht == NULL) {
    return;
  }

  for (int i = 0; i < ht->num_slots; i++) {
    set_delete(ht->sets[i], itemdelete);
  }

  free(ht->sets); // free all memory no leaks
  free(ht);
}
