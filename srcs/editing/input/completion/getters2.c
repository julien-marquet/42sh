/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   getters2.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: legrivel <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/23 21:34:17 by legrivel     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/23 21:34:18 by legrivel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "editing/input/completion/completion.h"
#include "editing/input/input_action_handlers.h"

int			get_builtins(t_list **files, char *needle)
{
	size_t		i;
	size_t		len;
	t_list		*link;
	static char	*builtins[BUILTINS_NB] = {
		"set", "env", "setenv", "unsetenv", "unset", "exit", "echo", \
"export", "test", "[", "alias", "unalias", "jobs", "fg", "bg", "hash"
	};

	i = 0;
	len = ft_strlen(needle);
	while (i < BUILTINS_NB)
	{
		if (ft_strncmp(builtins[i], needle, len) == 0)
		{
			if ((link =
		ft_lstnew(builtins[i], ft_strlen(builtins[i]) + 1)) == NULL)
				return (free_exit(*files));
			if (*files == NULL)
				*files = link;
			else
				ft_lstadd(files, link);
		}
		i += 1;
	}
	return (0);
}
