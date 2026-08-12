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

    // opendir() returns a pointer to dir. 
    DIR *dir = opendir("./img/full-res/");

    if (dir == NULL) { // opendir returns NULL if couldn't open directory 
        printf("Could not open current directory" );
        return 0;
    }

    const char *pictureFileName = NULL;

    FILE *picsFinalFile = fopen("./pics.html", "w");
    FILE *picsTemplateFile = fopen("./templates/pics-template.html", "r"); 

    printf("Insert template into final file");

    // read template to var
    char template[512];
    while (fgets(template, 512, picsTemplateFile)) {
        fprintf(picsFinalFile, template);
    }
    
    fclose(picsTemplateFile);

    while ((de = readdir(dir)) != NULL) {
        pictureFileName = de->d_name;

        // skip hidden entries and non-jpg files
        if (pictureFileName[0] == '.') {
            continue;
        }

        size_t len = strlen(pictureFileName);
        if (len < 5 || strcmp(pictureFileName + len - 4, ".jpg") != 0) {
            continue;
        }

        // check if thumbnail exists
        char thumbnailPath[256];
        snprintf(thumbnailPath, sizeof thumbnailPath, "./img/thumb/%.*s-thumb.jpg", (int)(len - 4), pictureFileName);
        FILE *file = fopen(thumbnailPath, "r");

        if (file == NULL) {
            printf("Thumbnail for %s does not exist\n", pictureFileName);
            continue;
        }

        // insert into HTML output
        printf("Inserting %s\n", pictureFileName);
        // i was too lazy to write a way for it to read from a file, so this is what I jankily placed
        // good luck to future me that wants to redesign my website
        fprintf(picsFinalFile, "    <a href=\"./img/full-res/%s\"><div class=\"image-container\"><img class=\"image-thumb\" src=\"%s\"/><p>%s</p></div></a>\n",pictureFileName, thumbnailPath, pictureFileName);

        fclose(file);

    }

    // i also didn't want to have this in the template to figure out.
    // maybe I'll do these later
    fprintf(picsFinalFile, "</body>\n</html>");

    // clean up
    fclose(picsFinalFile);
    closedir(dir);

    return 0;
}