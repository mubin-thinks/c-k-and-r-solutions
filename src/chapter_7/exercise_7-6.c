#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LEN 1000

struct file_with_line_t {
        FILE *fp;
        char line[MAX_LINE_LEN];
};

int main(int argc, char **argv) {
        if (argc != 3) {
                fprintf(stderr, "error: provide two files.\n");
                exit(1);
        }
        int line_number = 1;
        struct file_with_line_t file_1, file_2;
        file_1.fp = fopen(argv[1], "r");
        file_2.fp = fopen(argv[2], "r");
        if (!file_1.fp || !file_2.fp) {
                if (!file_1.fp && !file_2.fp) printf("error: cannot open files.\n");
                else printf("error: cannot open '%s'\n", file_1.fp ? argv[2] : argv[1]);
                exit(2);
        }
        for (
                ;
                fgets(file_1.line, sizeof(file_1.line), file_1.fp) &&
                fgets(file_2.line, sizeof(file_2.line), file_2.fp);
                line_number++
        ) {
                if (strcmp(file_1.line, file_2.line) != 0) {
                        printf(
                                "first line of diff at line %d:\n"
                                "    %16s: %s    %16s: %s",
                                line_number,
                                argv[1], file_1.line,
                                argv[2], file_2.line
                        );
                        break;
                }
        }
        fclose(file_1.fp);
        fclose(file_2.fp);
        return 0;
}
