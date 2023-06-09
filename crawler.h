#ifndef CRAWLER_H
#define CRAWLER_H

#include <stddef.h>

typedef struct {
	char *url;
	char *html;
	size_t length;
	int depth;
} webpage_t;

typedef struct {
	// Fill in with your implementation
	webpage_t **webpages;
	int numWebpages;
	int capacity;
} bag_t;

typedef struct {
	// Fill in with your implementation
	//int num_slots;
	//set_t **sets;
} hashtable_t;

webpage_t *webpage_new(char *url, int depth, char *html);

bag_t *bag_new(int capacity);

void bag_insert(bag_t *bag, webpage_t *page);


#endif
