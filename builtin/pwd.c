#include "../include/minishell.h"

int builtin_pwd(void)
{
    char *cwd;
    char buffer[PATH_MAX];

    cwd = getcwd(buffer, PATH_MAX);
    if (!cwd)
    {
        ft_putstr_fd("pwd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n", STDERR_FILENO);
        return (ERROR);
    }
    ft_putstr_fd(cwd, STDOUT_FILENO);
    ft_putstr_fd("\n", STDOUT_FILENO);
    free(cwd);
    return (OK);
}