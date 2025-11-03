#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <semaphore.h>
#include <ctype.h>

#define MIN_WORD_LEN    (4U)
#define MAX_CHAR_NUM    (32U)
#define MAX_WORD_LENGTH (100U)
#define MAX_DICTIONARIES (10U)
#define OUTPUT_FILE "found_words.txt"
#define SEM_NAME "/dict_search_sem"

/* Global semaphore for file access synchronization */
sem_t *file_sem;

/**
 * Function to check if a word can be formed from given characters
 *
 * @param[in] word  Check whether this word can be formed.
 * @param[in] chars The array of characters to form the word from.
 *
 * @retval 0 if word cannot be formed
 * @retval 1 if word can be formed
 */
int can_form_word(const char *word, const char *chars)
{
    char temp_chars[strlen(chars) + 1];
    strcpy(temp_chars, chars);

    for (int i = 0; word[i] != '\0'; i++) {
        char *found = strchr(temp_chars, tolower(word[i]));
        if (found == NULL) {
            found = strchr(temp_chars, toupper(word[i]));
            if (found == NULL) {
                return 0;
            }
        }
    }
    return 1;
}

/**
 * Function to process a single dictionary file
 *
 * @param[in] dict_filename     The name of the dictionary file.
 * @param[in] search_chars      Array of characters form the word.
 * @param[in] mandatory_char    The character that must be part of every word.
 */
void process_dictionary(const char *dict_filename, const char *search_chars, const char mandatory_char)
{
    FILE *dict_file = fopen(dict_filename, "r");
    if (dict_file == NULL) {
        printf("Error: Cannot open dictionary file %s\n", dict_filename);
        return;
    }

    char word[MAX_WORD_LENGTH];
    int words_found = 0;

    printf("Processing dictionary: %s\n", dict_filename);

    while (fgets(word, sizeof(word), dict_file)) {
        /* Remove newline character */
        word[strcspn(word, "\n")] = 0;

        /* Skip lines with too short words */
        if ((strlen(word) < MIN_WORD_LEN) || (strchr(word, mandatory_char) == NULL))
        {
            continue;
        }

        if (can_form_word(word, search_chars)) {
            /* Acquire semaphore for file access */
            sem_wait(file_sem);

            /* Open output file for appending */
            int output_fd = open(OUTPUT_FILE, O_WRONLY | O_CREAT | O_APPEND, 0644);
            if (output_fd == -1) {
                printf("Error: Cannot open output file\n");
                sem_post(file_sem);
                continue;
            }

            /* Write the word to file */
            char buffer[MAX_WORD_LENGTH + 2]; // +2 for newline and null terminator
            snprintf(buffer, sizeof(buffer), "%s\n", word);
            write(output_fd, buffer, strlen(buffer));

            close(output_fd);
            words_found++;

            /* Release semaphore */
            sem_post(file_sem);

            printf("Found word in %s: %s\n", dict_filename, word);
        }
    }

    fclose(dict_file);
    printf("Finished processing %s: Found %d words\n", dict_filename, words_found);
}

/**
 * Get the mandatory character from the user.
 *
 * @note Will terminate the program on erroneous input.
 *
 * @returns The mandatory character.
 */
char get_mandatory_character(void)
{
    char mandatory_char = EOF;

    printf("Enter mandatory character: ");
    mandatory_char = getchar();
    if (mandatory_char == EOF) {
        printf("Error reading input\n");
        exit(EXIT_FAILURE);
    }
    /* Expect buffered input, so we need to omit the trailing newline */
    getchar();
    return mandatory_char;
}

/**
 * Get search characters from user
 *
 * @param[out] search_chars  The array to store the characters in.
 * @param[in] mandatory_char The mandatory character to include.
 */
void get_search_chars(char *search_chars, const char mandatory_char)
{
    printf("Enter characters to search for: ");
    if (fgets(search_chars, sizeof(search_chars), stdin) == NULL) {
        printf("Error reading input\n");
        exit(EXIT_FAILURE);
    }
    /* add mandatory character at the end */
    search_chars[strcspn(search_chars, "\n")] = mandatory_char; // Remove newline
}

/**
 * Get the dictionary file names from the user.
 *
 * @param[in,out] dict_files The array to store the file names.
 *
 * @return The number of dictionaries the user has specified.
 */
int get_dictionaries(char dict_files[MAX_DICTIONARIES][MAX_WORD_LENGTH])
{
    int dict_count = 0;
    printf("Enter dictionary file names (one per line, empty line to finish):\n");
    while (dict_count < MAX_DICTIONARIES) {
        printf("Dictionary %d: ", dict_count + 1);
        if (fgets(dict_files[dict_count], sizeof(dict_files[dict_count]), stdin) == NULL) {
            break;
        }

        /* Remove newline character */
        dict_files[dict_count][strcspn(dict_files[dict_count], "\n")] = 0;

        /* Check for empty line to finish input */
        if (strlen(dict_files[dict_count]) == 0) {
            break;
        }

        dict_count++;
    }

    return dict_count;
}

/**
 * Clears the output file or create it if necessary.
 */
void clear_output_file(void)
{
    int output_fd = open(OUTPUT_FILE, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (output_fd == -1) {
        printf("Error creating output file\n");
        sem_close(file_sem);
        sem_unlink(SEM_NAME);
        exit(EXIT_FAILURE);
    }
    close(output_fd);
}

/**
 * Create a process per dictionary.
 *
 * @param[in] dict_count    Number of dictionary files in use
 * @param[in] dict_files        The list of dictionaries
 * @param[in] search_chars      The array of characters to form the words.
 * @param[in] mandatory_char    The mandatory character
 */
void dict_runner(unsigned dict_count,
                 const char dict_files[MAX_DICTIONARIES][MAX_WORD_LENGTH],
                 const char *search_chars,
                 const char mandatory_char)
{
    /* Create child processes for each dictionary */
    pid_t pids[MAX_DICTIONARIES];

    for (int i = 0; i < dict_count; i++) {
        pids[i] = fork();

        if (pids[i] == 0) {
            /* Child process */
            process_dictionary(dict_files[i], search_chars, mandatory_char);
            exit(EXIT_SUCCESS);
        } else if (pids[i] < 0) {
            printf("Error creating process for dictionary %s\n", dict_files[i]);
        }
    }

    /* Wait for all child processes to complete */
    for (int i = 0; i < dict_count; i++) {
        if (pids[i] > 0) {
            waitpid(pids[i], NULL, 0);
        }
    }

}

/**
 * Display the results to stdout.
 */
void display_results(void)
{
    printf("\n=== SEARCH COMPLETE ===\n");
    printf("Results saved to: %s\n", OUTPUT_FILE);

    /* Read and display the found words */
    int result_fd = open(OUTPUT_FILE, O_RDONLY);
    if (result_fd != -1) {
        printf("\nFound words:\n");
        char buffer[MAX_WORD_LENGTH];
        ssize_t bytes_read;

        while ((bytes_read = read(result_fd, buffer, sizeof(buffer) - 1)) > 0) {
            buffer[bytes_read] = '\0';
            printf("%s", buffer);
        }
        close(result_fd);
    } else {
        printf("No words found or error reading results.\n");
    }
}

int main(int c, char *argv[])
{
    char search_chars[MAX_CHAR_NUM];
    char dict_files[MAX_DICTIONARIES][MAX_WORD_LENGTH];
    unsigned dict_count = 0;

    memset(search_chars, 0, sizeof(search_chars));
    memset(dict_files, 0, sizeof(dict_files));

    /* get character set from user */
    char mandatory_char = get_mandatory_character();
    get_search_chars(search_chars, mandatory_char);

    /* Get dictionary files from user */
    dict_count = get_dictionaries(dict_files);
    if (dict_count == 0) {
        printf("No dictionary files provided.\n");
        return EXIT_FAILURE;
    }
    printf("\nSearching for words using characters: %s\n", search_chars);
    printf("Using %d dictionary files\n", dict_count);

    /* Initialize semaphore (named semaphore for process sharing) */
    file_sem = sem_open(SEM_NAME, O_CREAT, 0644, 1);
    if (file_sem == SEM_FAILED) {
        perror("sem_open failed");
        return EXIT_FAILURE;
    }

    /* Clear output file */
    clear_output_file();

    dict_runner(dict_count, dict_files, search_chars, mandatory_char);

    /* Cleanup semaphore */
    sem_close(file_sem);
    sem_unlink(SEM_NAME);

    /* Display results */
    display_results();
    return 0;
}

