/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtins_utils2.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: legrivel <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/05 06:33:36 by legrivel     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/05 06:33:36 by legrivel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "builtins/builtins_utils.h"

t_builtin_context		*duplicate_builtin_context(t_builtin_context *context)
{
	t_builtin_context	*new_context;

	if ((new_context = ft_memalloc(sizeof(t_builtin_context))) == NULL)
		return (NULL);
	if ((new_context->origin = ft_strdup(context->origin)) == NULL)
	{
		free(new_context);
		return (NULL);
	}
	return (new_context);
}

const char				**get_builtins_names(void)
{
	static const char	*assoc_names[BUILTINS_NB + 1] = {BUILTINS_NAMES};

	return (assoc_names);
}

int						builtin_exist(const char *name)
{
	const char	**assoc_names;
	int			i;

	assoc_names = get_builtins_names();
	i = 0;
	while (assoc_names[i] != NULL)
	{
		if (ft_strcmp(assoc_names[i], name) == 0)
			return (1);
		i++;
	}
	return (0);
}

const t_builtin_func	*get_builtins_funcs(void)
{
	static const t_assoc_func	assoc_funcs = {BUILTINS_FUNCS};

	return (assoc_funcs);
}

int						str_is_digit(const char *av)
{
	int		i;

	i = 0;
	while (av[i] != '\0')
	{
		if (!ft_isdigit(av[i]))
			return (0);
		i++;
	}
	return (1);
}
