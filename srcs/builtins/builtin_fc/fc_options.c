/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   options.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mmoya <mmoya@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/26 20:22:19 by mmoya        #+#   ##    ##    #+#       */
/*   Updated: 2019/04/26 20:26:08 by mmoya       ###    #+. /#+    ###.fr     */
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

static int	fc_option_e(const char **av, t_fc_infos *fc_infos, int i, t_builtin_context *context)
{
	if (av[++i] != NULL)
	{
		if (fc_infos->editor != NULL)
			ft_strdel(&fc_infos->editor);
		if (!(fc_infos->editor = ft_strdup(av[i])))
			return (-1);
	}
	else
	{
		print_error(context->origin, "-e: option requires an argument", context->fds.err);
		return (0);
	}
	return (i);
}

void	    add_valid(t_fc_infos *fc_infos, char new)
{
	size_t len;
	
	len = ft_strlen(fc_infos->opts);
	if (!ft_strchr(fc_infos->opts, new))
		fc_infos->opts[len] = new;
}

int         fc_options(const char **av, t_fc_infos *fc_infos, t_builtin_context *context)
{
	int i;
	int j;

	i = 1;
	while (av[i] && is_builtin_option(av[i]))
	{
		if (ft_strcmp("-e", av[i]) == 0)
		{
			if ((i = fc_option_e(av, fc_infos, i, context)) <= 0)
				return (i);
		}
		else
		{
			j = 1;
			while (av[i][j])
			{
				if (ft_strchr("lnrs", av[i][j]))
					add_valid(fc_infos, av[i][j++]);
				else
					return (0);
			}
		}
		av[i] ? i++ : 0;
	}
	return (i);
}
