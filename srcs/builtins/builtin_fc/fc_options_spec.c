/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   fc_options_spec.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mmoya <mmoya@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/06 06:32:43 by mmoya        #+#   ##    ##    #+#       */
/*   Updated: 2019/05/06 06:33:38 by mmoya       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "builtins/builtin_fc.h"

int	fc_option_s(const char **av, t_fc_infos *fc_infos, int i)
{
	size_t	len;

	len = 0;
	fc_infos->replace = 1;
	if (av[i] && av[i + 1] && ft_strchr(av[i + 1], '='))
	{
		i++;
		ft_strdel(&fc_infos->pat);
		ft_strdel(&fc_infos->rep);
		while (av[i][len] && av[i][len] != '=')
			len++;
		if (!(fc_infos->pat = ft_strndup(av[i], len)))
			return (-1);
		if (!(fc_infos->rep = ft_strdup(av[i] + len + 1)))
			return (-1);
	}
	return (i);
}

int	fc_option_e(const char **av, t_fc_infos *fc_infos, int i,
t_builtin_context *context)
{
	if (av[i] != NULL)
	{
		ft_strdel(&fc_infos->editor);
		if (!(fc_infos->editor = ft_strdup(av[i])))
			return (-1);
	}
	else
	{
		print_error(context->origin, "-e: option requires an argument", 2);
		return (0);
	}
	return (i);
}
