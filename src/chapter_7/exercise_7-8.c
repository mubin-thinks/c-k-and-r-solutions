#include <stdio.h>
#include <stdlib.h>

#define PAGE_SIZE 50
#define LINE_CAPACITY 1000

int print_heading(const char *name, int page_count);

int main(int argc, char **argv) {
        if (argc < 2) {
                fprintf(stderr, "error: at least provide one file.\n");
                exit(1);
        }
        FILE *fp;
        char line[LINE_CAPACITY];
        for (int page_count = 1; --argc && ++argv; page_count = 1) {
                if ((fp = fopen(*argv, "r")) == NULL) {
                        fprintf(stderr, "error: cannot open '%s'.\n", *argv);
                        continue;
                }
                for (int line_number = 0; fgets(line, sizeof(line), fp); line_number++) {
                        if (line_number % PAGE_SIZE == 0)
                                print_heading(*argv, page_count++);
                        printf("%s", line);
                }
                fclose(fp);
        }
        return 0;
}

int print_heading(const char *name, int page_count) {
        printf("+--------------------------------------------------+\n");
        printf("|%-39s Page %5d|\n", name, page_count);
        printf("+--------------------------------------------------+\n");
}
