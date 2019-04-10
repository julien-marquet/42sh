/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   binary.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: legrivel <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/09 20:18:06 by legrivel     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/09 20:18:07 by legrivel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "builtins/builtin_test/builtin_test.h"

int     make_binary_test(const char *arg1, const char *op, const char *arg2)
{
    int nbr1;
    int nbr2;

    if (ft_strcmp("=", op) == 0)
        return !(ft_strcmp(arg1, arg2) == 0);
    else if (ft_strcmp("!=", op) == 0)
        return !(ft_strcmp(arg1, arg2) != 0);
    nbr1 = ft_atoi(arg1);
    nbr2 = ft_atoi(arg2);
    if (ft_strcmp("-eq", op) == 0)
        return !(nbr1 == nbr2);
    else if (ft_strcmp("-ne", op) == 0)
        return !(nbr1 != nbr2);
    else if (ft_strcmp("-ge", op) == 0)
        return !(nbr1 >= nbr2);
    else if (ft_strcmp("-lt", op) == 0)
        return !(nbr1 < nbr2);
    else if (ft_strcmp("-le", op) == 0)
        return !(nbr1 <= nbr2);
    return (1);
}

