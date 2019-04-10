/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtin_test.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: legrivel <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/08 22:03:27 by legrivel     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/08 22:03:28 by legrivel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "builtins/builtin_test/builtin_test.h"
#pragma GCC diagnostic ignored "-Wunused-parameter"

static int  error(char *file, char *msg)
{
    if (file != NULL)
        dprintf(2, "-%s: test: %s: %s\n", NAME, file, msg);
    else
        dprintf(2, "-%s: test: %s\n", NAME, msg);
    return (1);
}

static int  is_unary_op(const char *arg)
{
    return (ft_strlen(arg) == 2 &&
            arg[0] == '-' &&
            ft_strchr("bcdefgLprSsuwxz", arg[1]) != NULL);
}

static int  is_binary_op(const char *arg)
{
    return (ft_strcmp("-eq", arg) == 0 ||
        ft_strcmp("-ne", arg) == 0 ||
        ft_strcmp("-ge", arg) == 0 ||
        ft_strcmp("-lt", arg) == 0 ||
        ft_strcmp("-le", arg) == 0 ||
        ft_strcmp("=", arg) == 0 ||
        ft_strcmp("!=", arg) == 0);
}

static int  treate_args(int ac, const char **av)
{
    int     result;

    if (ac < 3)
        return (error(NULL, "unknown error"));
    result = 1;
    dprintf(2, "HelloWorld %i\n", is_binary_op(av[1]));
    if (is_binary_op(av[1]))
        result = make_binary_test(av[0], av[1], av[2]);
    else
        return (error((char *)av[1], "binary operator expected"));
    if (ft_strcmp("!", av[0]) == 0)
        result = make_unary_test(av[1][1], av[2]);
    if (ft_strcmp("(", av[0]) == 0 && ft_strcmp(")", av[2]) == 0) {
        if (av[1][0] != '\0')
            result = 0;
    }
    // ELSE IS FALSE
    if (result == -1)
        return (error(NULL, "unknown error"));
    if (ac > 3)
        return treate_args(ac - 3, av + 3);
    // Check if -1
    return (result);
}

int        builtin_test(t_sh_state *sh_state, int ac, const char **av, int fd_out)
{
    size_t  negate;

    negate = 0;
    sh_state->status = 1;
    if (ac == 1)
        return (0);
    if (ac == 2) {
        if (av[1][0] != '\0')
            sh_state->status = 0;
    } else {
        if (ft_strcmp("!", av[1]) == 0) {
            negate = 1;
            dprintf(2, "Negating...\n");
        }
        if (ac == 3) {
            if (negate && av[2][0] == '\0') {
                sh_state->status = 0;
                return (0);
            }
            dprintf(2, "HelloWorld\n");
            if (is_unary_op(av[1]))
                sh_state->status = make_unary_test(av[1][1], av[2]);
            else
                return (0);
            dprintf(2, "HelloWorld: %i\n", sh_state->status);
            if (sh_state->status > 1)
                return (1);
        }
        else
        {
            if (ft_strcmp("!", av[1]) == 0)
            {
                if (ac > 5)
                    return (error(NULL, "too many arguments"));
                if ((sh_state->status = treate_args(ac - 2, av + 2)) > 1)
                    return (1);
            }
            else
            {
                if (ac > 4)
                    return (error(NULL, "too many arguments"));
                if ((sh_state->status = treate_args(ac - 1, av + 1)) > 1)
                    return (1);
            }
        }
    }
    if (negate)
        sh_state->status = !sh_state->status;
    return (0);
}
