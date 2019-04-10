/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   unary.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: legrivel <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/09 20:41:16 by legrivel     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/09 20:41:17 by legrivel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "builtins/builtin_test/builtin_test.h"

static int  check_permissions(char op, const char *path)
{
    int mode;

    if (op == 'r')
        mode = R_OK;
    else if (op == 'w')
        mode = W_OK;
    else
        mode = X_OK;
    if (access((char *)path, mode) == -1)
    {
        if (errno == EACCES)
            return (1);
        else
            return (-1);
    }
    return (0);
}

static int  check_op(char op, struct stat stats, const char *path)
{
    if (op == 'b')
        return !(S_ISBLK(stats.st_mode));
    else if (op == 'r' || op == 'w' || op == 'x')
        return (check_permissions(op, path));
    else if (op == 'c')
        return !(S_ISCHR(stats.st_mode));
    else if (op == 'd')
        return !(S_ISDIR(stats.st_mode));
    else if (op == 'e')
        return (0);
    else if (op == 'f')
        return !(S_ISREG(stats.st_mode));
    else if (op == 'g')
        return !(stats.st_mode == S_ISGID);
    else if (op == 'L')
        return !(S_ISLNK(stats.st_mode));
    else if (op == 'p')
        return !(S_ISFIFO(stats.st_mode));
    else if (op == 'S')
        return !(S_ISSOCK(stats.st_mode));
    else if (op == 's')
        return !(stats.st_size > 0);
    else if (op == 'u')
        return !(stats.st_mode == S_ISUID);
    return (0);
}

int         make_unary_test(char op, const char *arg)
{
    struct stat stats;

    if (op == 'z')
        return !(ft_strlen(arg) == 0);
    if (access(arg, F_OK) == -1)
    {
        if (errno == ENOENT)
            return (1);
        return (-1);
    }
    if (stat(arg, &stats) == -1)
        return (-1);
    return (check_op(op, stats, arg));
}

