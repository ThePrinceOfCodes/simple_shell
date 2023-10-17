#include "shell.h"

/**
 * _strlen - find the length of a string
 * @s: pointer to the string to check
 * Return: void
 */

int _strlen(const char *s)
{
    int i = 0;

    while (s[i])
        i++;

    return (i);
}


char *_strcpy(char *dest, const char *src)
{
    int i = -1;

    do
    {
        i++;
        dest[i] = src[i];
    } while (src[i] != '\0');

    return (dest);
}
/**
 * _strcat - concatenates 2 strings
 * @dest: input value
 * @src: input value
 *
 * Return: void
 */

char *_strcat(char *dest, char *src)
{
    int i;
    int j;

    i = 0;
    while (dest[i] != '\0')
    {
        i++;
    }
    j = 0;
    while (src[j] != '\0')
    {
        dest[i] = src[j];
        i++;
        j++;
    }
    dest[i] = '\0';
    return (dest);
}
/**
 * _strcmp - check string values
 * @s1: input value
 * @s2: input value
 *
 * Return: s1[i] - s2[i]
 */
int _strcmp(char *s1, char *s2)
{
    int i;

    i = 0;
    while (s1[i] != '\0' && s2[i] != '\0')
    {
        if (s1[i] != s2[i])
        {
            return (s1[i] - s2[i]);
        }
        i++;
    }
    return (0);
}
/**
 * _strtok - check string values
 * @s: input value
 * @d: input value
 *
 * Return: s
 */

char *_strtok(char *s, char d)
{
    char *result;
    int i = 0;
    static char *input;

    if (s != NULL)
        input = s;

    if (input == NULL)
        return (NULL);
    result = (char *)malloc(sizeof(_strlen(input) + 1));

    for (; input[i] != '\0'; i++)
    {
        if (input[i] != d)
            result[i] = input[i];

        else
        {
            result[i] = '\0';
            input = input + i + 1;
            return (result);
        }
    }

    result[i] = '\0';
    input = NULL;

    return (result);
}