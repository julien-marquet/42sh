/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   storage_getters.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/05 18:06:26 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/08 23:31:55 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "storage/storage_getters.h"

char	*get_stored(t_list *storage, const char *var_name)
{
	t_list	*node;

	if (var_name == NULL)
		return (NULL);
	if ((node = find_node_by_name(storage, var_name)) == NULL)
		return (NULL);
	return (ft_strdup(&((t_internal_storage *)(
node->content))->string[ft_strlen(var_name) + 1]));
}
