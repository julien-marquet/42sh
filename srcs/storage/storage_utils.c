/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   storage_utils.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/05 17:28:09 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/08 22:43:42 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "hash/hash.h"
#include "storage/storage_utils.h"

t_list	*find_node_by_name(t_list *env, const char *var_name)
{
	t_list	*tmp;
	size_t	len;

	if (var_name == NULL)
		return (NULL);
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

int		fill_entry(t_internal_storage *entry, const char *name,
const char *value, const size_t size)
{
	entry->exported = 0;
	entry->string = merge_name_value(name, value, size);
	return (entry->string == NULL);
}

void	remove_storage_node(t_list **alst, t_list **node, t_list *prev)
{
	if (prev != NULL)
		prev->next = (*node)->next;
	else
		*alst = (*node)->next;
	free(((t_internal_storage *)(*node)->content)->string);
	free((*node)->content);
	free(*node);
}

int		update_existing_node(t_list **hash_table, t_list *node, const char *name,
const char *value, size_t len)
{
	if (ft_strcmp("PATH", name) == 0)
		delete_table(hash_table);
	free(((t_internal_storage *)node->content)->string);
	((t_internal_storage *)(node->content))->tmp = 0;
	node->content_size = sizeof(t_internal_storage);
	if ((((t_internal_storage *)node->content)->string =
merge_name_value(name, value,
len)) == NULL)
		return (1);
	return (0);
}
