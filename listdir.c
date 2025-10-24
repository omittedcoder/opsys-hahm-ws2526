#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/types.h>
#include <dirent.h>

/*
1. If no command line arguments are given, the files and directories within the current
directory are listed with a newline (\n) after each name including the last one. By
default, any file or directory name whose first character is . will not be listed unless
the hidden flag is set (see below).

2. An optional flag, -h (for hidden), may be specified which will list all files or directories
including those that have . as a first character.

3. One or more command line arguments may be given. Each argument that does
not start with a - is treated as a directory name. The content of each of these
directories should be listed, i.e., listdir a02 a03 should list the files in directories
a02 and a03. If any of the specified directory files cannot be accessed, the error
Cannot access a02 should be printed.

4. You must create a Makefile such that when someone types make in your working
directory it will compile the program with the name listdir.

use system commands opendir, closedir, readdir, (getopt)
*/

int main(int argc, char *argv[]) {

    // set h flag
    bool hiddenflag = false;
    for(int i = 1; i < argc; i++) {
        if(argv[i][0] == '-' && argv[i][1] == 'h') {
                hiddenflag = true;
        }
    }

    // read all directories from paramaters
    for(int i = 1; i < argc; i++) {
        // skip flags
        if(argv[i][0] == '-')
            continue;
        
        DIR *d;
        struct dirent *dir;
        
        // handle error
        d = opendir(argv[i]);
        if (!d) {
            //perror(argv[0]);
            //exit(1);
            printf("Cannot access %s\n", argv[i]);
            closedir(d);
            continue;
        }

        // list directory
        printf("%s:\n", argv[i]);
        while ((dir = readdir(d)) != NULL) {
            // skip hidden files if hidden flag not set
            if(!hiddenflag && dir->d_name[0] == '.')
                continue;
            printf("  %s\n", dir->d_name);
        } 

        closedir(d);
    }

    return 0;
}
