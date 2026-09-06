#include <stdio.h>
#include <stdarg.h>
#include <limits.h>

void min_scanf(char *fmt, ...);

int main() {
        int a;
        char b;
        float c;
        unsigned int d;
        char s[100];
        min_scanf("some tests: %d %c %f %u %s\n", &a, &b, &c, &d, s);
        printf("result: %d %c %f %u %s\n", a, b, c, d, s);
        return 0;
}

void min_scanf(char *fmt, ...) {
        va_list arg;
        va_start(arg, fmt);
        for (char *p = fmt; *p; p++) {
                if (*p != '%') {
                        getchar();
                        continue;
                }
                switch (*(++p)) {
                case 'i':
                        scanf("%i", va_arg(arg, int *));
                        break;
                case 'd':
                        scanf("%d", va_arg(arg, int *));
                        break;
                case 'o':
                        scanf("%o", va_arg(arg, int *));
                        break;
                case 'x': case 'X':
                        scanf("%x", va_arg(arg, int *));
                        break;
                case 'u':
                        scanf("%u", va_arg(arg, unsigned int *));
                        break;
                case 'c':
                        scanf("%c", va_arg(arg, char *));
                        break;
                case 's':
                        scanf("%s", va_arg(arg, char *));
                        break;
                case 'f':
                        scanf("%f", va_arg(arg, float *));
                        break;
                case 'e': case 'E':
                        scanf("%e", va_arg(arg, float *));
                        break;
                case 'g': case 'G':
                        scanf("%g", va_arg(arg, float *));
                        break;
                default:
                        putchar(*p);
                        break;
                }
        }
        va_end(arg);
}
