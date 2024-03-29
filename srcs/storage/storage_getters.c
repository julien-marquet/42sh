/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   storage_getters.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mmoya <mmoya@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/05 18:06:26 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/05 19:42:29 by mmoya       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "storage/storage_getters.h"

/*
**	Does not need to be freed
*/

char			*get_env_value(t_list *list, const char *key)
{
	t_internal_storage	*storage;
	size_t				key_length;

	key_length = ft_strlen((char *)key);
	while (list != NULL)
	{
		storage = list->content;
		if (storage->exported && ft_strncmp(storage->string, key,
			key_length) == 0 && *(storage->string + key_length) == '=')
			return (storage->string + key_length + 1);
		list = list->next;
	}
	return (NULL);
}

char			*get_var(t_list *list, const char *var)
{
	size_t				len;
	char				*value;
	t_internal_storage	*storage;

	if ((value = get_env_value(list, var)) != NULL)
		return (value);
	len = ft_strlen(var);
	while (list != NULL)
	{
		storage = list->content;
		if (ft_strncmp(storage->string, var, len) == 0 &&
			*(storage->string + len) == '=')
			return (storage->string + len + 1);
		list = list->next;
	}
	return (NULL);
}

/*
**	Need to be freed
*/

char			*get_stored(t_list *storage, const char *var_name)
{
	t_list	*node;

	if (var_name == NULL)
		return (NULL);
	if ((node = find_node_by_name(storage, var_name)) == NULL)
		return (NULL);
	return (ft_strdup(&((t_internal_storage *)(
node->content))->string[ft_strlen(var_name) + 1]));
}
