/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   input_active_search.c                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/05 19:02:52 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/05 19:14:15 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "editing/input/input_active_search.h"

t_list	**active_search_node_super_get(void)
{
	static t_list	*active_search_node = NULL;

	return (&active_search_node);
}

void	set_active_search_node(t_list *node)
{
	t_list	**active_node;
	t_list	*tmp;

	active_node = active_search_node_super_get();
	tmp = *active_node;
	*active_node = node;
}

t_list	*get_active_search_node(void)
{
	return (*active_search_node_super_get());
}
