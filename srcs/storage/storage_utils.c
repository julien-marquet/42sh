/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   storage_utils.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/05 17:28:09 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/08 18:57:24 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "storage/storage_utils.h"

t_list	*find_node_by_name(t_list *env, const char *var_name)
{
	t_list	*tmp;
	size_t	len;

	tmp = env;
	len = ft_strlen(var_name);
	while (tmp != NULL)
	{
		if (ft_strncmp(var_name,
	((t_internal_storage *)tmp->content)->string, len) == 0 &&
	(((t_internal_storage *)tmp->content)->string)[len] == '=')
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

char	*merge_name_value(const char *name,
const char *value, const size_t size)
{
	size_t	name_len;
	char	*res;

	name_len = ft_strlen(name);
	if ((res = ft_memalloc(size + 1)) == NULL)
		return (NULL);
	ft_strcpy(res, name);
	res[name_len] = '=';
	if (value != NULL)
		ft_strcpy(&(res[name_len + 1]), value);
	return res;
}

int		fill_entry(t_internal_storage *entry, const char *name,
const char *value, const size_t size)
{
	entry->exported = 0;
	entry->string = merge_name_value(name, value, size);
	return (entry->string == NULL);
}

void	remove_node(t_list **alst, t_list **node, t_list *prev)
{
	if (prev != NULL)
		prev->next = (*node)->next;
	else
		*alst = (*node)->next;
	free((*node)->content);
	free(*node);
}

int		update_existing_node(t_list *node, const char *name,
const char *value, size_t len)
{
	free(((t_internal_storage *)node->content)->string);
	node->content_size = sizeof(t_internal_storage);
	if ((((t_internal_storage *)node->content)->string =
merge_name_value(name, value,
len)) == NULL)
		return (1);
	return (0);
}
