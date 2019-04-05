/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   storage_utils.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/05 17:28:09 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/05 17:30:11 by jmarquet    ###    #+. /#+    ###.fr     */
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
		if (ft_strncmp(var_name, (char *)tmp->content, len) == 0 &&
		((char *)tmp->content)[len] == '=')
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

char	*create_entry(const char *name, const char *value, const size_t size)
{
	size_t	name_len;
	char	*res;

	name_len = ft_strlen(name);
	if ((res = ft_memalloc(size)) == NULL)
		return (NULL);
	ft_strcpy(res, name);
	res[name_len] = '=';
	ft_strcpy(&(res[name_len + 1]), value);
	return res;
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
