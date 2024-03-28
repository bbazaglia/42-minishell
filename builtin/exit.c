#include "../include/minishell.h"

// to do: add atol to libft
long ft_atol(char *str)
{
    long nb;
    int sign;

    nb = 0;
    sign = 1;
    while (*str == ' ' || (*str >= 9 && *str <= 13))
        str++;
    if (*str == '-')
        sign *= -1;
    if (*str == '-' || *str == '+')
        str++;
    while (*str && *str >= '0' && *str <= '9')
        nb = nb * 10 + (*str++ - '0');
    return (nb * sign);
}

int check_numeric_arg(char *arg)
{
    int i;

    i = 0;
    while (arg[i])
    {
        // - or + are allowed ?
        if (!isdigit(arg[i]))
        {
            ft_putstr_fd("exit: numeric argument required\n", STDERR_FILENO);
            return (0);
        }
        i++;
    }
    return (1);
}

int check_numeric_limits(long num)
{
    if (num > INT_MAX || num < INT_MIN)
    {
        ft_putstr_fd("exit: numeric argument required\n", STDERR_FILENO);
        return (0);
    }
    return (1);
}

int builtin_exit(char **args)
{
    long num;

    if (args[2])
    {
        ft_putstr_fd("exit: too many arguments\n", STDOUT_FILENO);
        return (STDOUT_FILENO); // does not exit shell: return 1 ?
    }
    if (args[1])
    {
        num = ft_atol(args[1]);
        if (!check_numeric_arg(args[1]) || !check_numeric_limits(num))
            return (STDERR_FILENO);
        else
            return (num);
    }
    ft_putstr_fd("exit\n", STDOUT_FILENO);
    return (0);
}
