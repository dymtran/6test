#include "pagedir.h"
#include <stdio.h>

/*bool pagedir_init(const char *pageDirectory) {
    // Fill in with your implementation
    // we need to create a file named .crawler in pageDirectory.
    char filePath[150];
    snprintf(filePath, sizeof(filePath), "%s/.crawler", pageDirectory);
    printf("%s", filePath);
    FILE *file = fopen(filePath, "r+");
    if (file == NULL) {
        printf("Error opening file\n");
        return false;
    }

    fclose(file);
    return true;
}

void pagedir_save(const webpage_t *page, const char *pageDirectory, const int documentID) {
    // Fill in with your implementation
	 
}
*/

bool pagedir_init(const char *pageDirectory) {
	if (pageDirectory == NULL) {
		return false;
	}
	
	char file[100];
	sprintf(file, sizeof(file), "%s/crawler", pageDirectory);
	
	FILE *open = fopen(file, "r+"):
	
	if (open == NULL) {
		return false;
	}
	
	fclose(open);
	return true;
}

void pagedir_save(const webpage_t *page, const char *pageDirectory, const int documentID) {
    // Fill in with your implementation
	 
}

