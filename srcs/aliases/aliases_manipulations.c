/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   aliases_manipulations.c                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/08 20:18:26 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/08 22:37:30 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "aliases/aliases_manipulations.h"

int		add_alias(t_list **aliases, const char *name, const char *value)
{
	t_list		*node;
	size_t		len;
	char		*entry;

	len = 0;
	if (value)
		len = ft_strlen(value);
	len += ft_strlen(name) + 1;
	if (ft_strlen(name) == 0)
		return (0);
	if ((node = find_alias_by_name(*aliases, name)) != NULL)
	{
		if (update_existing_alias(node, name, value, len) == 1)
			return (1);
	}
	else
	{
		if ((entry = merge_name_value(name, value, len)) == NULL)
			return (1);
		if ((node = ft_lstnew((const void *)entry, len + 1)) == NULL)
			return (1);
		free(entry);
		ft_lstprepend(aliases, node);
	}
	return (0);
}

void	print_aliases(t_list *aliases, int fd_out)
{
	t_list	*tmp;

	tmp = aliases;
	while (tmp != NULL)
	{
		write(fd_out, tmp->content, tmp->content_size);
		write(fd_out, "\n", 1);
		tmp = tmp->next;
	}
}
