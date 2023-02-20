#include "../inc/cubed.h"

void    ft_error(char *str)
{
    printf("Error\n%s\n", str);
    exit (1);
}

void    ft_error_code(int code)
{
    printf("Error\n%s\n", code_erreur(code));
    exit (1);
}

char *code_erreur(int code)
{
    if (code == 101)
        return("There must be 1 player");
    if (code == 102)
        return("There can only be 1 player");
    if (code == 103)
        return("Map can only be '1', '0', ' ', 'W', 'E', 'S', 'N'");
    if (code == 104)
        return("Wrong layout, map must be closed");
    return(NULL);
}