#include <stdio.h>

char lookup_table[128]; void lookup_table_init();
int isupper_saving_space(char c);
int isupper_saving_time(char c);

int main() {
        lookup_table_init();
        printf(
                "%d\n%d\n%d\n%d\n",
                isupper_saving_space('A'),
                isupper_saving_space(' '),
                isupper_saving_time('A'),
                isupper_saving_time(' ')
        );
        return 0;
}

void lookup_table_init() {
        for (int i = 0; i < 128; i++) if (i >= 'A' && i <= 'Z') lookup_table[i] = 1;
}

int isupper_saving_space(char c) {
        return c >= 'A' && c <= 'Z';
}

int isupper_saving_time(char c) {
        return lookup_table[c];
}
