#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void push(char *a, int x, FILE *f, char *n);
void pop(char *a, int x, FILE *f, char *n);
void arithmetic(char *a, FILE *f);
void label(char *a, FILE *f);
void go_to(char *a, FILE *f);
void if_go_to(char *a, FILE *f);
void call(char *a, int x, FILE *f);
void function(char *a, int x, FILE *f);
void ret(FILE *f);
