/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   storage_manipulations.c                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mmoya <mmoya@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/05 14:28:01 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/06 06:23:09 by mmoya       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "storage/storage_manipulations.h"

int				is_valid_var_name(const char *name)
{
	if (!name || ft_strlen(name) == 0)
		return (0);
	while (*name != '\0')
	{
		if (!(ft_isalnum(*name) || *name == '_'))
			return (0);
		name++;
	}
	return (1);
}

static t_list	*storage_init_node(const char *name, const char *value,
size_t len, int exported)
{
	t_internal_storage	entry;

	if ((fill_entry(&entry, name, value, len)) == 1)
		return (NULL);
	if (exported != 1 && exported != 0)
		exported = 0;
	entry.exported = exported;
	entry.tmp = 0;
	return (ft_lstnew((const void *)&entry, sizeof(t_internal_storage)));
}

/*
**	Return 0 on success 1 on parse error and -1 on critical error
*/

int				add_entry_storage(t_sh_state *sh_state, const char *name,
const char *value, int exported)
{
	t_list				*node;
	size_t				len;

	len = 0;
	if (value)
		len = ft_strlen(value);
	len += ft_strlen(name) + 1;
	if (is_valid_var_name(name) == 0)
		return (1);
	if ((node = find_node_by_name(sh_state->internal_storage, name)) != NULL)
	{
		update_table(&(sh_state->hash_table), name);
		if (update_existing_node(node, name, value, len) == 1)
			return (-1);
		if (exported == 1 || exported == 0)
			((t_internal_storage *)node->content)->exported = exported;
	}
	else
	{
		if ((node = storage_init_node(name, value, len, exported)) == NULL)
			return (-1);
		ft_lstprepend(&(sh_state->internal_storage), node);
	}
	return (0);
}

int				remove_entry_storage(t_sh_state *sh_state, t_list **storage,
const char *name)
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
		if (ft_strncmp(name, ((t_internal_storage *)tmp->content)->string, len)
		== 0 && ((t_internal_storage *)tmp->content)->string[len] == '=')
		{
			if (ft_strcmp("PATH", name) == 0)
				delete_table(&sh_state->hash_table);
			remove_storage_node(storage, &tmp, prev);
			return (1);
		}
		prev = tmp;
		tmp = tmp->next;
	}
	return (0);
}

int				update_exported_flag(t_list *storage, t_list **hash_table,
const char *name, int exported)
{
	t_list	*node;

	if ((node = find_node_by_name(storage, name)) != NULL)
	{
		if (((t_internal_storage *)node->content)->exported != exported)
		{
			((t_internal_storage *)node->content)->exported = exported;
			if (ft_strcmp("PATH", name) == 0)
				delete_table(hash_table);
		}
		return (1);
	}
	return (0);
}
