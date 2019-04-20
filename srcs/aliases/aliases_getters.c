/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   aliases_getters.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/08 22:49:03 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/19 21:12:43 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "aliases/aliases_getters.h"

char	*get_alias(t_list *aliases, const char *var_name)
{
	t_list	*node;

	if (var_name == NULL)
		return (NULL);
	if ((node = find_alias_by_name(aliases, var_name)) == NULL)
		return (NULL);
	return (ft_strdup(&(((char *)node->content)[ft_strlen(var_name) + 1])));
}


t_list			*duplicate_aliases(t_list *aliases)
{
	t_list	*new;
	t_list	*node;

	new = NULL;
	while (aliases != NULL)
	{
		if ((node = ft_lstnew(aliases->content, aliases->content_size)) == NULL)
			return (new);
		ft_lstappend(&new, node);
		aliases = aliases->next;
	}
	return (new);
}
