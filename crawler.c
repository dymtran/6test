<<<<<<< HEAD
=======

>>>>>>> main
#include <stdio.h>
#include <stdlib.h>

#include "crawler.h"
#include "curl.h"
#include "pagedir.h"
#include "hashtable (1).h"

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
    if (maxDepth < 0 || maxDepth > 10) {
        printf(stderr, "Error: maxDepth must be in range [0 ... 10]\n");
        exit(3);
    }
    // ● if any trouble is found, print an error to stderr and exit non-zero.
    if (pagedir_init(*pageDirectory)) {
        printf("ran pagedir_init\n")
    } else {
        printf(stderr, "Error: %s is not a directory\n", *pageDirectory);
        exit(2);
    }

}

/**
 * Crawls webpages given a seed URL, a page directory and a max depth.
 */
static void crawl(char *seedURL, char *pageDirectory, const int maxDepth) {
    // Fill in with your implementation
    //initialize the hashtable and add the seedURL

    // initialize the bag and add a webpage representing the seedURL at depth 0
    // while bag is not empty:
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
 * Scans a webpage for URLs.
 */
static void pageScan(webpage_t *page, bag_t *pagesToCrawl, hashtable_t *pagesSeen) {
    // Fill in with your implementation

    //while there is another URL in the page:
    // if that URL is internal:
    // insert the webpage into the hashtable
    // if that succeeded:
    // create a webpage_t for it
    // insert the webpage into the bag
    // free the URL

    //     That is, your code should scan for occurrences of <a href="url"> (again,
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
<<<<<<< HEAD
=======

>>>>>>> main
