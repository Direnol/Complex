#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Mycomplex.h"

#define SIZE_BUF 64

typedef Mycomplex (*func_l)(Mycomplex, Mycomplex);

void readLine(char *string)
{
    int i = 0;
    while ((string[i++] = (char) getchar()) != '\n') { }
    string[i - 1] = '\0';
}

char *read_pipe(FILE * input)
{
    size_t buf = 64;
    size_t readed = 0;
    char *output = (char *) calloc(buf, sizeof(char));
    while (!feof(input)) {
        if (readed == buf) {
            buf += 64;
            output = (char *) realloc(output, buf);
        }
        output[readed] = fgetc(input);
        readed++;
    }
    output[readed] = '\0';
    return output;
}

int parseELF(char *elf, char **buf, int free_pos)
{
    int n = strlen(elf);
    for (int i = 5; i < n - 4; ++i) {
        if (elf[i - 1] == 'T' && elf[i - 2] == ' ' && elf[i] == ' ' && elf[i + 1] != '_') {
            ++i;
            int pos = 0;
            while (elf[i] != '\n') {
                buf[free_pos][pos] = elf[i];
                ++i;
                ++pos;
            }
            ++free_pos;
        }
    }
    return free_pos;
}

int readFunc(char *filename, char **buf, int free_pos)
{
    char *cmd = (char *) malloc(sizeof(char) * ( 4 + strlen(filename)));
    strcpy(cmd, "nm ");
    strcat(cmd, filename);
    FILE *f = popen(cmd, "r");
    if (!f) {
      perror(NULL);
      exit(1);
    }
    char *pipe = read_pipe(f);
    free_pos = parseELF(pipe, buf, free_pos);
    free(cmd);
    free(pipe);
    pclose(f);
    return free_pos;
}

int main()
{
    char *buf = (char *) calloc(SIZE_BUF, sizeof(char));
    void **handles = (void **) malloc(SIZE_BUF);
    char **functions = (char **) calloc(SIZE_BUF, sizeof(char *));
    func_l *calls = (func_l *) calloc(SIZE_BUF, sizeof(func_l *));
    for (int i = 0; i < SIZE_BUF; ++i) {
        functions[i] = (char *) calloc(SIZE_BUF, sizeof(char));
    }
    
    int count_handles = 0;
    int free_pos = 0;

    printf("Enter path of library or \"-1\"\n");
    readLine(buf);
    while(strcmp(buf, "-1") != 0) {
        handles[count_handles] = dlopen(buf, RTLD_LAZY);
        if (!handles[count_handles]) {
            fprintf(stderr, "[dlopen][%s]\n", dlerror());
            return 0;
        }
        printf("Lib [%s] is opened\n", buf);
        int prev = free_pos;
        free_pos = readFunc(buf, functions, free_pos);
        for (int i = prev; i < free_pos; ++i) {
            calls[i] = (func_l) dlsym(handles[count_handles], functions[i]);
        }
        ++count_handles;
        readLine(buf);
    }
    
    Mycomplex a, b;
    do {
        printf("Choose number of func and enter args or \"-1\"\n");
        for (int i = 0; i < free_pos; ++i) {
            printf("[%d] %s\n", i, functions[i]);
        }
        int choose;
        scanf("%d", &choose);
        if (choose < 0) break;
        printf("Enter 2 args\n");
        scanf("%lf%lf%lf%lf", &a.re, &a.lm, &b.re, &b.lm);
        Mycomplex res = calls[choose](a, b);
        printf("Result[%s] = re [%lf] : lm [%lf]\n", buf, res.re, res.lm);
    } while (1);

    free(buf);
    for (int i = 0; i < count_handles; ++i) dlclose(handles[i]);
    free(handles);
    for (int i = 0; i < SIZE_BUF; ++i) {
        free(functions[i]);
    }
    free(functions);
    free(calls);
    return 0;
}
