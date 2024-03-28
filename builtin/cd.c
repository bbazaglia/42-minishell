#include "../include/minishell.h"

int builtin_cd(char **args)
{
    if (args[1] == NULL)
    {
        chdir(getenv("HOME"));
        return (OK);
    }
    else if (chdir(args[1]) == -1)
    {
        ft_putstr_fd("cd: no such file or directory: ", STDERR_FILENO);
        ft_putstr_fd(args[1], STDERR_FILENO);
        ft_putstr_fd("\n", STDERR_FILENO);
        return (ERROR);
    }
    return (OK);
}