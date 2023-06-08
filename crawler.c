#include <stdio.h>
#include <stdlib.h>

#include "crawler.h"
#include "curl.h"
#include "pagedir.h"

/**
 * Parses command-line arguments, placing the corresponding values into the pointer arguments seedURL,
 * pageDirectory and maxDepth. argc and argv should be passed in from the main function.
 */
static void parseArgs(const int argc, char *argv[], char **seedURL, char **pageDirectory, int *maxDepth) {
	// Fill in with your implementation
	// ./crawler seedURL pageDirectory maxDepth
	// where seedURL is to be used as the initial URL,
	// ■ where pageDirectory is the (existing) directory in which to write downloaded
	// web pages, and
	// ■ where maxDepth is an integer in range [0..10] indicating the maximum crawl
	// depth.
	// Fill in with your implementation
	
	printf("URL: %s\n", *seedURL);
    printf("Directory: %s\n", *pageDirectory);
    printf("Depth: %d\n", *maxDepth);

	//Given arguments from the command line, extract them into the function parameters;
	// return only if successful.
	// ● for pageDirectory, call pagedir_init()
	// ● for maxDepth, ensure it is an integer in specified range [0 ... 10]
	if (*maxDepth < 0 || *maxDepth > 10) {
		fprintf(stderr, "Error: maxDepth must be in range [0 ... 10]\n");
		exit(2);
	}
	// ● if any trouble is found, print an error to stderr and exit non-zero.
	if (pagedir_init(*pageDirectory)) {
		printf("ran pagedir_init\n");
	} else {
		fprintf(stderr, "Error: %s is not a directory\n", *pageDirectory);
		exit(2);
	}

}

/**
 * Crawls webpages given a seed URL, a page directory and a max depth.
 */
static void crawl(char *seedURL, char *pageDirectory, const int maxDepth) {
	// Fill in with your implementation
	//initialize the hashtable and add the seedURL
	hashtable_t *pagesSeen = hashtable_new(1000);
	hashtable_insert(pagesSeen, seedURL, NULL);
	// initialize the bag and add a webpage representing the seedURL at depth 0
	bag_t *bagOfPages = bag_new(10);
	webpage_t *seedPage = webpage_new(seedURL, 0, NULL);
	bag_insert(bagOfPages, seedPage);
	// while bag is not empty:
	// while (bagOfPages->numWebpages > 0) {

	// }
	// pull a webpage from the bag
	// fetch the HTML for that webpage
	// if fetch was successful:
	// save the webpage to pageDirectory
	// if the webpage is not at maxDepth:
	// pageScan that HTML
	// delete that webpage
	// delete the hashtable
	// delete the bag
}

/**
 * Creates a webpage_t struct
 * 
 */

static webpage_t *webpage_new(char *url, int depth, char *html) {
	// Fill in with your implementation
	// a webpage is a struct with a url, depth, and html
	webpage_t *page = malloc(sizeof(webpage_t));
	if (page == NULL) {
		fprintf(stderr, "Error: malloc failed\n");
		exit(2);
	}
	page->url = url;
	page->depth = depth;
	page->html = html;
	return page;
}

/**
 * Creates a new bag_t struct
 * 
 * 
 */
static bag_t *bag_new(int capacity) {
	// Fill in with your implementation
	// a bag is essentially going to be a list of webpages
	// dynamically allocated array of webpages
	bag_t *bag = malloc(sizeof(bag_t));
	if (bag == NULL) {
		fprintf(stderr, "Error: malloc failed\n");
		exit(2);
	}
	bag->webpages = malloc(sizeof(webpage_t) * capacity);
	bag->webpages = 0;
	bag->capacity = capacity;
	if (bag->webpages == NULL) {
		fprintf(stderr, "Error: malloc failed\n");
		exit(2);
	}
	return bag;
}


/**
 * Adds a webpage to the bag.
 * 
 */
static void bag_insert(bag_t *bag, webpage_t *page) {
	// if the bag is full, double its size
	if (bag->numWebpages == bag->capacity) {
		bag->capacity = (bag->capacity * 2) + 1;
		bag->webpages = realloc(bag->webpages, sizeof(webpage_t) * bag->capacity);
	}
	// insert the webpage into the bag
	bag->webpages[bag->numWebpages] = page;
}

/**
 * Scans a webpage for URLs.
 */
static void pageScan(webpage_t *page, bag_t *pagesToCrawl, hashtable_t *pagesSeen) {
	// Fill in with your implementation
	// use curl to download the webpage

	//while there is another URL in the page:
	// if that URL is internal:
	// insert the webpage into the hashtable
	// if that succeeded:
	// create a webpage_t for it
	// insert the webpage into the bag
	// free the URL

	// 	That is, your code should scan for occurrences of <a href="url"> (again,
	// the url part varies) and extract the contained URLs so they can be crawled.
}

int main(const int argc, char *argv[]) {
	// The main function simply calls parseArgs and crawl, then exits zero.
	// ./crawler seedURL pageDirectory maxDepth
	if (argc < 4) {
    	printf("Usage: %s seedURL pageDirectory maxDepth\n", argv[0]);
        exit(1);
    }
	char* seedURL = argv[1];
	char* pageDirectory = argv[2];
	char* maxDepth = argv[3];
	int intMaxDepth = atoi(maxDepth);
	parseArgs(argc, argv, &seedURL, &pageDirectory, &intMaxDepth);
	crawl(seedURL, pageDirectory, intMaxDepth);
	//
	return 0;
}
