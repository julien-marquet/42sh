/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   fc_options.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mmoya <mmoya@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/26 20:22:19 by mmoya        #+#   ##    ##    #+#       */
/*   Updated: 2019/05/06 02:27:37 by mmoya       ###    #+. /#+    ###.fr     */
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

static int	fc_option_s(const char **av, t_fc_infos *fc_infos, int i)
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

static int	fc_option_e(const char **av, t_fc_infos *fc_infos, int i,
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

void		add_valid(t_fc_infos *fc_infos, char new)
{
	size_t len;

	len = ft_strlen(fc_infos->opts);
	if (!ft_strchr(fc_infos->opts, new))
		fc_infos->opts[len] = new;
}

int			fc_options(const char **av, t_fc_infos *fc_infos,
t_builtin_context *context)
{
	int i;
	int j;

	i = 1;
	while (av[i] && is_builtin_option(av[i]))
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
		else
		{
			j = 1;
			while (av[i][j])
			{
				if (ft_strchr("lnr-", av[i][j]))
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
