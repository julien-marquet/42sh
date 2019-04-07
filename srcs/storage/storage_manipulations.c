/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   storage_manipulations.c                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/05 14:28:01 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/08 01:21:25 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "storage/storage_manipulations.h"

int		add_entry_storage(t_list **storage, const char *name, const char *value, int exported)
{
	t_list	*node;
	size_t	len;
	t_internal_storage entry;

	len = 0;
	if (value)
		len = ft_strlen(value);
	len += ft_strlen(name) + 1;
	if (ft_strlen(name) == 0)
		return (0);
	if ((node = find_node_by_name(*storage, name)) != NULL)
	{
		free(node->content);
		node->content_size = sizeof(t_internal_storage);
		if ((node->content = merge_name_value(name, value,
	len)) == NULL)
			return (1);
	}
	else
	{
		if ((fill_entry(&entry, name, value, len)) == 1)
			return (1);
		entry.exported = exported;
		if ((node = ft_lstnew((const void *)&entry,
	sizeof(t_internal_storage))) == NULL)
			return (1);
		ft_lstprepend(storage, node);
	}
	return (0);
}

int		remove_entry_storage(t_list **storage, const char *name)
{
	t_list	*tmp;
	t_list	*prev;
	size_t	len;

	tmp = *storage;
	prev = NULL;
	len = ft_strlen(name);
	if (len == 0)
		return (0);
	while (tmp != NULL)
	{
		if (ft_strncmp(name, ((t_internal_storage *)tmp->content)->string, len) == 0 &&
		((t_internal_storage *)tmp->content)->string[len] == '=')
		{
			remove_node(storage, &tmp, prev);
			return (1);
		}
		prev = tmp;
		tmp = tmp->next;
	}
	return (0);
}

void	print_storage_content(t_list *storage, int fd_out)
{
	while (storage != NULL)
	{
		ft_putendl_fd(((t_internal_storage *)(storage->content))->string,
	fd_out);
		storage = storage->next;
	}
}
