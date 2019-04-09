/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   aliases_manipulations.c                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/08 20:18:26 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/09 01:51:10 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "aliases/aliases_manipulations.h"

int		add_alias(t_list **aliases, const char *name, const char *value)
{
	t_list		*node;
	size_t		len;
	char		*entry;
	char		*new_value;

	len = 0;
	if (name == NULL)
		return (1);
	if (value)
	{
		len = ft_strlen(value) + 2;
		if ((new_value = ft_memalloc(len + 1)) == NULL)
			return (1);
		new_value[0] = '\'';
		ft_strcpy(&new_value[1], value);
		new_value[len - 1] = '\'';
	}
	len += ft_strlen(name) + 1;
	if (ft_strlen(name) == 0)
		return (0);
	if ((node = find_alias_by_name(*aliases, name)) != NULL)
	{
		if (update_existing_alias(node, name, new_value, len) == 1)
			return (1);
	}
	else
	{
		if ((entry = merge_name_value(name, new_value, len)) == NULL)
			return (1);
		if ((node = ft_lstnew((const void *)entry, len + 1)) == NULL)
			return (1);
		free(entry);
		ft_lstprepend(aliases, node);
	}
	free(new_value);
	return (0);
}

int		remove_alias(t_list **aliases, const char *name)
{
	t_list	*tmp;
	t_list	*prev;
	size_t	len;

	tmp = *aliases;
	prev = NULL;
	if (name == NULL)
		return (0);
	len = ft_strlen(name);
	if (len == 0)
		return (0);
	while (tmp != NULL)
	{
		if (ft_strncmp(name, (char *)tmp->content, len) == 0 &&
		((char *)tmp->content)[len] == '=')
		{
			remove_alias_node(aliases, &tmp, prev);
			return (1);
		}
		prev = tmp;
		tmp = tmp->next;
	}
	return (0);
}

void	print_aliases(t_list *aliases, int fd)
{
	t_list	*tmp;

	tmp = aliases;
	while (tmp != NULL)
	{
		write(fd, tmp->content, tmp->content_size);
		write(fd, "\n", 1);
		tmp = tmp->next;
	}
}
