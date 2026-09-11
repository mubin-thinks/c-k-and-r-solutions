#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
#define LINE_CAPACITY 1000

struct args_t {
        int is_number, is_except;
        const char *pattern;
};

void args_get(struct args_t *args, int *argc, char ***argv);
void print_diff(const struct args_t *args, FILE *fp, char *line, int line_size);

int main(int argc, char **argv) {
        struct args_t args;
        args_get(&args, &argc, &argv);
        char line[LINE_CAPACITY];
        if (!argc) print_diff(&args, stdin, line, sizeof(line));
        else for (FILE *fp; argc--; argv++) {
                fp = fopen(*argv, "r");
                if (!fp) {
                        fprintf(stderr, "error: cannot open '%s'\n", *argv);
                        continue;
                }
                printf("%s:\n", *argv);
                print_diff(&args, fp, line, sizeof(line));
                fclose(fp);
        }
        return 0;
}

void args_get(struct args_t *args, int *argc, char ***argv) {
        const char *program_name = **argv;
        args->is_number = args->is_except = FALSE;
        for (char c; --(*argc) && **(++(*argv)) == '-'; ) for (; c = *(++(**argv)); ) {
                if (c == 'n') args->is_number = TRUE;
                else if (c == 'x') args->is_except = TRUE;
                else {
                        fprintf(stderr, "error: invalid option '%d'\n", c);
                        exit(1);
                }
        }
        if (*argc < 1) {
                fprintf(stderr, "usage: %s -n -x <pattern> [files...]\n", program_name);
                exit(2);
        }
        args->pattern = **argv;
        (*argc)--;
        (*argv)++;
}

void print_diff(const struct args_t *args, FILE *fp, char *line, int line_size) {
        for (int line_number = 1; fgets(line, line_size, fp); line_number++)
                if ((strstr(line, args->pattern) != NULL) != args->is_except) {
                        if (args->is_number) printf("%7d: ", line_number);
                        printf("%s", line);
                }
}
