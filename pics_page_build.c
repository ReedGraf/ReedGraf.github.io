/* 
    For each file in the full-res picture folder:
    1. Get the file names
    2. Check for a thumbnail file for each
    3. Report if missing
    4. Add an entry of the file based on the HTML template
*/

#include <stdio.h>
#include <string.h>
#include <dirent.h>


int main(void) {
    struct dirent *de;  // Pointer for directory entry

    // opendir() returns a pointer of DIR type. 
    DIR *dir = opendir("./img/full-res/");

    if (dir == NULL) { // opendir returns NULL if couldn't open directory 
        printf("Could not open current directory" );
        return 0;
    }

    const char *currentFile = NULL;

    // Create template insertion here

    while ((de = readdir(dir)) != NULL) {
        currentFile = de->d_name;

        // skip hidden entries and non-jpg files
        if (currentFile[0] == '.') {
            continue;
        }

        size_t len = strlen(currentFile);
        if (len < 5 || strcmp(currentFile + len - 4, ".jpg") != 0) {
            continue;
        }

        // check if thumbnail exists
        char fullThumbPath[256];

        snprintf(fullThumbPath, sizeof fullThumbPath, "./img/thumb/%.*s-thumb.jpg", (int)(len - 4), currentFile);

        FILE *file = fopen(fullThumbPath, "r");

        if (file == NULL) {
            printf("Thumbnail for %s does not exist\n", currentFile);
            continue;
        }

        // add image insertion here

        fclose(file);

    }
    
    // clean up
    fclose(picsFinalFile);
    closedir(dir);

    return 0;
}