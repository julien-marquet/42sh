/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   aliases_utils.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/08 21:53:42 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/08 22:21:13 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "aliases/aliases_utils.h"

t_list	*find_alias_by_name(t_list *aliases, const char *var_name)
{
	t_list	*tmp;
	size_t	len;

	if (var_name == NULL)
		return (NULL);
	tmp = aliases;
	len = ft_strlen(var_name);
	while (tmp != NULL)
	{
		if (ft_strncmp(var_name,
	(char *)tmp->content, len) == 0 &&
	((char *)tmp->content)[len] == '=')
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

int		update_existing_alias(t_list *node, const char *name,
const char *value, size_t len)
{
	free(node->content);
	node->content_size = len + 1;
	if ((node->content = merge_name_value(name, value, len)) == NULL)
		return (1);
	return (0);
}
