#include "shell.h"
#include <string.h>

/**
 * execute - executes the command
 * @cmd: command to run
 * @main_path: path to environment variable
 * Return: 0 on success1 -1 if cmd is exit and 1 on any other error
 */
int execute(char **cmd, char *main_path)
{
    pid_t child_pid;
    int status;

    child_pid = fork();
    if (child_pid == -1)
    {
        perror("Error");
        return (1);
    }
    else if (child_pid == 0)
    {
        if (**(cmd + 0) == '/')
        {
            execve(*(cmd + 0), cmd, environ);
            if (execve(*(cmd + 0), cmd, environ) == -1)
            {
                perror("./shell");
            }
        }
        else
        {
            _strcat(main_path, "/");
            _strcat(main_path, cmd[0]);
            execve(main_path, cmd, environ);
            if (execve(main_path, cmd, environ) == -1)
            {
                perror("./shell");
            }
        }
    }
    else
        wait(&status);

    return (0);
}

/**
 *get_path - function to get the path environment variable
 *@path: environment variable
 *Return: 0
 */
char *get_path(char *path)
{
    char *main_path;
    char *cutpath;

    cutpath = _strtok(path, ':');
    while (cutpath != NULL)
    {
        if (!_strcmp(cutpath, "/usr/bin"))
            main_path = cutpath;
        cutpath = _strtok(NULL, ':');
    }
    return (main_path);
}

/**
 * main - main simple shell
 * @argc: number of arguments
 * @argv: list of command line arguments
 * Return: Always 0, -1 on error.
 */

int main(int argc, char **argv)
{
    int response, character, isPipe = 0;
    size_t bufsize = BUFSIZ;
    char **tokens = (char **)malloc(sizeof(char **) * bufsize);
    char *buffer, *path;
    char *main_path = (char *)malloc(sizeof(char *) * bufsize);

    if (argc >= 2)
    {
        if (execve(argv[1], argv, NULL) == -1)
        {
            exit(-1);
        }
        return (0);
    }
    buffer = (char *)malloc(bufsize * sizeof(char));
    if (buffer == NULL)
    {
        perror("Unable to allocate buffer");
        exit(1);
    }
    path = _getenv("PATH", environ);
    main_path = get_path(path);
    do
    {
        if (isatty(fileno(stdin)))
        {
            isPipe = 1;
            _puts("user@dexter$ ");
        }
        character = getline(&buffer, &bufsize, stdin);
        if (character == EOF)
            exit(1);
        buffer[_strlen(buffer) - 1] = '\0';
        if (!_strcmp("exit", buffer))
            exit(1);
        tokens = stringToTokens(buffer);
        response = execute(tokens, main_path);
    } while (isPipe && response != -1);
    free(buffer);
    free(tokens);
    return (0);
}