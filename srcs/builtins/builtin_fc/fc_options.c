/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   fc_options.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mmoya <mmoya@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/26 20:22:19 by mmoya        #+#   ##    ##    #+#       */
/*   Updated: 2019/05/06 22:41:12 by mmoya       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "builtins/builtin_fc.h"

static int	is_builtin_option(const char *str)
{
	size_t	i;
	size_t	digit;

	i = 0;
	digit = 0;
	while (str[i])
		digit += ft_isdigit(str[i++]);
	return (str && str[0] == '-' && str[1] != '\0' && digit == 0);
}

void		add_valid(t_fc_infos *fc_infos, char new)
{
	size_t len;

	len = ft_strlen(fc_infos->opts);
	if (!ft_strchr(fc_infos->opts, new))
		fc_infos->opts[len] = new;
}

static int	fc_options_spec(const char **av, int i, t_fc_infos *fc_infos,
t_builtin_context *context)
{
	if (ft_strcmp("-e", av[i]) == 0)
	{
		if ((i = fc_option_e(av, fc_infos, i + 1, context)) <= 0)
			return (i);
	}
	else if (ft_strcmp("-s", av[i]) == 0)
	{
		if ((i = fc_option_s(av, fc_infos, i)) <= 0)
			return (i);
	}
	else if (ft_strcmp("--", av[i]) == 0)
		return (i + 1);
	return (i);
}

int			fc_options(const char **av, t_fc_infos *fc_infos,
t_builtin_context *context)
{
	int i;
	int j;

	i = 1;
	while (av[i] && is_builtin_option(av[i]))
	{
		if (ft_strcmp("-e", av[i]) == 0 || ft_strcmp("-s", av[i]) == 0 ||
		ft_strcmp("--", av[i]) == 0)
			i = fc_options_spec(av, i, fc_infos, context);
		else
		{
			j = 1;
			while (av[i][j])
			{
				if (ft_strchr("lnr", av[i][j]))
					add_valid(fc_infos, av[i][j++]);
				else
					return (0);
			}
		}
		if (i == -1)
			return (-1);
		av[i] ? i++ : 0;
	}
	return (i);
}
