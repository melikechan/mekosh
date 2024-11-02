#include "../lib/utils.h"

#define TOKEN_DELIM " \t\r\n\a"

char **parse_line(char *line)
{
    char **args = malloc(MAX_LEN * sizeof(char *));
    char *token = strtok(line, TOKEN_DELIM);

    int i = 0;
    while (token != NULL)
    {
        args[i++] = token;
        token = strtok(NULL, TOKEN_DELIM);
    }
    args[i] = NULL;

    return args;
}

int if_process_runs_in_background(char **args)
{
    int i = 0;
    while (args[i] != NULL)
    {
        i++;
    }

    if (strcmp(args[i - 1], "&") == 0)
    {
        args[i - 1] = NULL;
        return 1;
    }

    return 0;
}

void redirect_io(char **args)
{
    int i = 0;
    int fd[2] = {STDIN_FILENO, STDOUT_FILENO};

    for (i = 0; args[i] != NULL; i++)
    {
        if (strcmp(args[i], ">") == 0)
        {
            args[i] = NULL;

            if (args[i + 1] == NULL)
            {
                printf("No output file specified\n");
                break;
            }

            char *output_file = args[i + 1];
            fd[1] = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        }
        else if (strcmp(args[i], "<") == 0)
        {
            args[i] = NULL;

            if (args[i + 1] == NULL)
            {
                printf("No input file specified\n");
                break;
            }

            char *input_file = args[i + 1];
            fd[0] = open(input_file, O_RDONLY);
        }
    }

    if (fd[0] != 0)
    {
        dup2(fd[0], STDIN_FILENO);
        close(fd[0]);
    }

    if (fd[1] != 1)
    {
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);
    }
}

void launch_process(char **args, int background)
{
    pid_t pid = fork();

    if (pid == 0)
    {
        if (execvp(args[0], args) == -1)
        {
            perror("Error");
        }
        exit(EXIT_FAILURE);
    }
    else if (pid < 0)
    {
        perror("Error");
    }
    else
    {
        if (!background)
        {
            int status;
            waitpid(pid, &status, 0);
        }
    }
}