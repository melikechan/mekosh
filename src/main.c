#include <stdio.h>
#include "lib/utils.h"

const char *prompt = "mekosh > ";
const char *exit_commands[] = {"q", "quit", "exit"};

int main(void)
{
    char **args;
    char line[MAX_LEN];
    int still_running = 1;

    while (still_running)
    {
        printf("%s", prompt);
        fflush(stdout);

        if (fgets(line, sizeof(line), stdin) == NULL)
        {
            printf("Error reading input\n");
            return 1;
        }

        // While parsing the line, remove the newline character
        line[strcspn(line, "\n")] = '\0';

        for (size_t i = 0; i < sizeof(exit_commands) / sizeof(exit_commands[0]); i++)
        {
            if (strcmp(line, exit_commands[i]) == 0)
            {
                still_running = 0;
                break;
            }
        }

        if (!still_running)
        {
            printf("Exiting...\n");
            break;
        }

        args = parse_line(line);
        int background = if_process_runs_in_background(args);
        int original_stdin = dup(STDIN_FILENO);
        int original_stdout = dup(STDOUT_FILENO);

        redirect_io(args);
        launch_process(args, background);

        // Reset file descriptors
        dup2(original_stdin, STDIN_FILENO);
        dup2(original_stdout, STDOUT_FILENO);

        close(original_stdin);
        close(original_stdout);

        free(args);
    }

    return 0;
}