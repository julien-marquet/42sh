/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   storage_manipulations.c                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/05 14:28:01 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/07 21:10:35 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "storage/storage_manipulations.h"

int		add_entry_storage(t_list **storage, const char *name, const char *value)
{
	t_list	*node;
	char	*tmp;
	size_t	len;

	len = 0;
	if (value)
		len = ft_strlen(value);
	len += ft_strlen(name) + 1;
	if (ft_strlen(name) == 0)
		return (0);
	if ((node = find_node_by_name(*storage, name)) != NULL)
	{
		free(node->content);
		node->content_size = len + 1;
		if ((node->content = create_entry(name, value,
	len)) == NULL)
			return (1);
	}
	else
	{
		if ((tmp = create_entry(name, value, len)) == NULL)
			return (1);
		if ((node = ft_lstnew(tmp, len + 1)) == NULL)
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
		if (ft_strncmp(name, (char *)tmp->content, len) == 0 &&
		((char *)tmp->content)[len] == '=')
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
		write(fd_out, storage->content, storage->content_size - 1);
		write(fd_out, "\n", 1);
		storage = storage->next;
	}
}
