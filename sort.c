#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>

int compare(const void *a, const void *b) {
    return strcasecmp(* (char * const *) a, * (char * const*) b);
}

void cleanup(char **lines, int lines_number) {
    for (int i=0; i<lines_number; i++) {
        free(lines[i]);
    }
    free(lines);
}

int main(int argc, char *argv[]) {
    FILE *file;
    char *path = argv[1];
    file = fopen(path, "r");

    if (file == NULL) {
        printf("Could not open file\n");
        return -1;
    }
   
    char **lines = malloc(sizeof(char*));
    char *line = NULL;
    int lines_number = 0;
    int index = 0;
    size_t len = 0;
    while (getline(&line, &len, file) != -1) {
        lines = realloc(lines, ++lines_number * sizeof(char*));
        lines[index++] = line;
        line = NULL;
    }
    free(line);
    fclose(file);

    qsort(lines, lines_number, sizeof(char*), compare);
    for (int i=0; i<lines_number; i++) {
        fputs(lines[i], stdout);
    }
    cleanup(lines, lines_number);

    return 0;
}
