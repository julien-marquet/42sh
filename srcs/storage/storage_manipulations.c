/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   storage_manipulations.c                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/05 14:28:01 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/09 00:36:07 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "storage/storage_manipulations.h"

int		add_entry_storage(t_list **storage, const char *name, const char *value, int exported)
{
	t_list				*node;
	size_t				len;
	t_internal_storage	entry;

	len = 0;
	if (value)
		len = ft_strlen(value);
	len += ft_strlen(name) + 1;
	if (ft_strlen(name) == 0)
		return (0);
	if ((node = find_node_by_name(*storage, name)) != NULL)
	{
		if (update_existing_node(node, name, value, len) == 1)
			return (1);
	}
	else
	{
		if ((fill_entry(&entry, name, value, len)) == 1)
			return (1);
		if ((node = ft_lstnew((const void *)&entry, sizeof(t_internal_storage))) == NULL)
			return (1);
		ft_lstprepend(storage, node);
	}
	entry.exported = exported;
	entry.new_entry = 1;
	return (0);
}

int		remove_entry_storage(t_list **storage, const char *name)
{
	t_list	*tmp;
	t_list	*prev;
	size_t	len;

	if (name == NULL)
		return (1);
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
			remove_storage_node(storage, &tmp, prev);
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

int		update_exported_flag(t_list *storage, const char *name, int exported)
{
	t_list	*node;

	if ((node = find_node_by_name(storage, name)) != NULL)
	{
		((t_internal_storage *)node->content)->exported = exported;
		return (1);
	}
	return (0);
}

void	flush_new_entry_flag(t_list *storage)
{
	t_list	*tmp;

	tmp = storage;
	while (tmp != NULL)
	{
		((t_internal_storage *)tmp->content)->new_entry = 0;
		tmp = tmp->next;
	}
}
