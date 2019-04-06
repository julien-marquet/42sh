/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtins_dispatcher.c                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/05 19:00:26 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/05 23:02:18 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "builtins/builtins_dispatcher.h"

static t_builtin_func	get_builtins_func(char *name)
{
	static char	*assoc_name[BUILTINS_NB + 1] = {"set", "env", NULL};
	static int	(*assoc_func[BUILTINS_NB + 1])(void *, int) = {builtins_set, builtins_env, NULL};
	size_t		i;

	i = 0;
	while (assoc_name[i] != NULL)
	{
		if (ft_strcmp(assoc_name[i], name) == 0)
			return (assoc_func[i]);
		i++;
	}
	return (NULL);
}

int						builtins_dispatcher(char *name, void *data, int fd_out)
{
	t_builtin_func	f;

	if ((f = get_builtins_func(name)) != NULL)
		return (f(data, fd_out));
	else
		return (0);
}
