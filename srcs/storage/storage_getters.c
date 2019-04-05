/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   storage_getters.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/05 18:06:26 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/05 18:08:01 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "storage/storage_getters.h"

char	*get_stored(t_list *storage, const char *var_name)
{
	char	*res;
	t_list	*node;

	if ((node = find_node_by_name(storage, var_name)) == NULL)
		return (NULL);
	res = ft_strdup(&((char *)node->content)[ft_strlen(var_name) + 1]);
	return (res);
}

char	*get_stored_multiple(t_list *storage_1, t_list *storage_2,
const char *var_name)
{
	char	*res;
	t_list	*node;

	res = NULL;
	if ((node = find_node_by_name(storage_1, var_name)) != NULL ||
(node = find_node_by_name(storage_2, var_name)) != NULL)
		res = ft_strdup(&((char *)node->content)[ft_strlen(var_name) + 1]);
	return (res);
}
