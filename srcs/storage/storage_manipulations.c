/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   storage_manipulations.c                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/05 14:28:01 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/28 02:48:08 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "storage/storage_manipulations.h"

int	is_valid_var_name(const char *name)
{
	if (!name)
		return (0);
	while (*name != '\0')
	{
		if (!(ft_isalnum(*name) || *name == '_'))
			return (0);
		name++;
	}
	return (1);
}

/*
**	Return 0 on success 1 on parse error and -1 on critical error
*/

int		add_entry_storage(t_sh_state *sh_state, const char *name, const char *value, int exported)
{
	t_list				*node;
	size_t				len;
	t_internal_storage	entry;

	len = 0;
	if (value)
		len = ft_strlen(value);
	len += ft_strlen(name) + 1;
	if (is_valid_var_name(name) == 0)
		return (1);
	if ((node = find_node_by_name(sh_state->internal_storage, name)) != NULL)
	{
		if (update_existing_node(&(sh_state->hash_table), node, name, value, len) == 1)
			return (-1);
		if (exported == 1 || exported == 0)
			((t_internal_storage *)node->content)->exported = exported;
		((t_internal_storage *)node->content)->new_entry = 1;
	}
	else
	{
		if ((fill_entry(&entry, name, value, len)) == 1)
			return (-1);
		if (exported != 1 && exported != 0)
			exported = 0;
		entry.exported = exported;
		entry.new_entry = 1;
		if ((node = ft_lstnew((const void *)&entry,
	sizeof(t_internal_storage))) == NULL)
			return (-1);
		ft_lstprepend(&(sh_state->internal_storage), node);
	}
	return (0);
}

int		remove_entry_storage(t_sh_state *sh_state, t_list **storage, const char *name)
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

void	print_storage_content(t_list *storage, int fd)
{
	while (storage != NULL)
	{
		ft_putendl_fd(((t_internal_storage *)(storage->content))->string,
	fd);
		storage = storage->next;
	}
}

int		update_exported_flag(t_list *storage, t_list **hash_table,
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
