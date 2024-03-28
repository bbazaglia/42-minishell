#include "../include/minishell.h"

int check_n_flag(char *arg)
{
    if (*arg == '-')
    {
        arg++;
        while (*arg == 'n')
            arg++;
        if (*arg == '\0')
            return (1);
    }
    return (0);
}

void print_args(char **args, int n_flag)
{
    if (n_flag)
        ft_putchar_fd(' ', STDOUT_FILENO);
    else
        ft_putchar_fd('\n', STDOUT_FILENO);
    while (*args)
    {
        ft_putstr_fd(*args, STDOUT_FILENO);
        if (*(args + 1))
            ft_putchar_fd(' ', STDOUT_FILENO);
        args++;
    }
}

void echo_builtin(char **args)
{
    int n_flag;

    n_flag = 0;
    while (*args && check_n_flag(*args))
    {
        n_flag = 1;
        args++;
    }
    print_args(args, n_flag);
}
