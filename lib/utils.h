#ifndef UTILS_H
#define UTILS_H
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#define MAX_LEN 1024
#endif

char **parse_line(char *line);

int if_process_runs_in_background(char **args);

void redirect_io(char **args);

void launch_process(char **args, int background);