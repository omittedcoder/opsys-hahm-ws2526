#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <dirent.h>

/**
 * @brief print all entries of a directory
 *
 * @param[in] curdir        The current directory to print
 * @param[in] show_hidden   Whether hidden files and directories should be printed
 */
void print_dir_listing(DIR *curdir, bool show_hidden)
{
    struct dirent *curdirent = readdir(curdir);
    while (curdirent != NULL)
    {
        if (show_hidden || (curdirent->d_name[0] != '.'))
        {
            printf("%s\n", curdirent->d_name);
        }
        curdirent = readdir(curdir);
    }
}

/**
 * @brief Open, print, and close directory
 *
 * @param[in] dir           The name of the current directory
 * @param[in] show_hidden   Whether hidden files and directories should be printed
 */
void list_dir(const char* dir, bool show_hidden)
{
    DIR *curdir = opendir(dir);
    if (curdir == NULL)
    {
        printf("Cannot access %s\n", dir);
    }
    else
    {
        print_dir_listing(curdir, show_hidden);
        closedir(curdir);
    }
}

int main(int argc, char **argv)
{
    int opt;
    bool show_hidden = 0;
    /* parse command line options */
    while ((opt = getopt(argc, argv, "h")) != -1) {
        switch (opt) {
            case 'h':
                show_hidden = true;
                break;
            default: /* '?' */
                break;
        }
    }

    /* if no additional arguments are given */
    if (optind >= argc) {
        list_dir(".", show_hidden);
    }
    else
    {
        /* iterate over all arguments */
        while (optind < argc)
        {
            list_dir(argv[optind], show_hidden);
            ++optind;
        }
    }
    return EXIT_SUCCESS;
}
