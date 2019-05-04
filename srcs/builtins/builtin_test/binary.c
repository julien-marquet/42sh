/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   binary.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: legrivel <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/11 21:01:37 by legrivel     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/11 21:01:38 by legrivel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "builtins/builtin_test/builtin_test.h"

int	make_binary_test(char **av)
{
	int	nbr1;
	int nbr2;

	if (ft_strcmp("=", av[1]) == 0)
		return (!(ft_strcmp(av[0], av[2]) == 0));
	else if (ft_strcmp("!=", av[1]) == 0)
		return (!(ft_strcmp(av[0], av[2]) != 0));
	if (check_args(av) != 0)
		return (2);
	nbr1 = ft_atoi(av[0]);
	nbr2 = ft_atoi(av[2]);
	if (ft_strcmp("-eq", av[1]) == 0)
		return (!(nbr1 == nbr2));
	else if (ft_strcmp("-ne", av[1]) == 0)
		return (!(nbr1 != nbr2));
	else if (ft_strcmp("-ge", av[1]) == 0)
		return (!(nbr1 >= nbr2));
	else if (ft_strcmp("-lt", av[1]) == 0)
		return (!(nbr1 < nbr2));
	else if (ft_strcmp("-le", av[1]) == 0)
		return (!(nbr1 <= nbr2));
	return (1);
}
