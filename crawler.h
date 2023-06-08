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
} hashtable_t;

#endif
