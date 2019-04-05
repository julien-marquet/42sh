/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   storage_manipulation.c                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/05 14:28:01 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/05 17:33:10 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "storage/storage_manipulation.h"

char	*get_stored(t_list *storage, const char *var_name)
{
	char	*res;
	t_list	*node;

	if ((node = find_node_by_name(storage, var_name)) == NULL)
		return (NULL);
	res = ft_strdup(&((char *)node->content)[ft_strlen(var_name) + 1]);
	return (res);
}

int		add_entry_storage(t_list **storage, const char *name, const char *value)
{
	t_list	*node;
	char	*tmp;
	size_t	len;

	len = ft_strlen(name) + ft_strlen(value) + 1;
	if (ft_strlen(name) == 0)
		return (0);
	if ((node = find_node_by_name(*storage, name)) != NULL)
	{
		free(node->content);
		node->content_size = len + 1;
		if ((node->content = create_entry(name, value,
	node->content_size)) == NULL)
			return (1);
	}
	else
	{
		if ((tmp = create_entry(name, value, len + 1)) == NULL)
			return (1);
		if ((node = ft_lstnew(tmp, len + 1)) == NULL)
			return (1);
		ft_lstadd(storage, node);
	}
	return (0);
}

int		remove_entry_storage(t_list **storage, char *name)
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

void	debug_dump_storage(t_list *storage)
{
	while (storage != NULL)
	{
		dprintf(2, "%s\n", (char *)storage->content);
		storage = storage->next;
	}
}
