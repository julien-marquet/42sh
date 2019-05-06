/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   history_file.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mmoya <mmoya@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/02 15:52:11 by mmoya        #+#   ##    ##    #+#       */
/*   Updated: 2019/05/05 05:31:56 by mmoya       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "editing/history/history_file.h"

t_list		*hist_list_add(t_list *args, char *str, size_t len)
{
	char	*tmp;
	t_list	*new;

	if (!(tmp = ft_strndup(str, len)))
		return (NULL);
	if (!(new = ft_lstnew(tmp, ft_strlen(tmp) + 1)))
		return (NULL);
	ft_strdel(&tmp);
	if (args == NULL)
		return (new);
	args = ft_lstappend(&args, new);
	return (args);
}

static int	hist_splitchar(char *str, int i, char *split)
{
	while (i > 0 && ft_isspace(str[i]))
		i--;
	return (stresc(split, str, i) != NULL);
}

t_list		*hist_str2list(char *str)
{
	t_list	*args;
	size_t	start;
	size_t	i;

	i = 0;
	args = NULL;
	while (str[i])
	{
		start = i;
		while (str[i] && (hist_splitchar(str, i, "|&\\") || str[i] != '\n' ||
		is_quoted(str, i)))
			str[i] ? i++ : 0;
		if (str[i] == '\n' || str[i] == 0)
			if (!(args = hist_list_add(args, str + start, i - start)))
				return (NULL);
		str[i] ? i++ : 0;
	}
	return (args);
}
