/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   utils.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: legrivel <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/05 04:01:41 by legrivel     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/05 04:01:42 by legrivel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "builtins/builtin_test/builtin_test.h"

int		xit(char **arr, int ret)
{
	ft_freetab(&arr);
	return (ret);
}

char	**remove_negate(char **av)
{
	size_t	i;

	free(av[1]);
	i = 1;
	while (av[i])
	{
		av[i] = av[i + 1];
		i += 1;
	}
	return (av);
}
