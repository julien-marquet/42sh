/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   input_search_mode.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/26 04:03:30 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/26 05:33:37 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "editing/input/input_search_mode.h"

int		*search_mode_super_get(void)
{
	static int search_mode = 0;

	return (&search_mode);
}
char	**searched_super_get(void)
{
	static char	*searched = NULL;

	return (&searched);
}

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

int		get_search_mode(void)
{
	return (*search_mode_super_get());
}
void	set_search_mode(int	setter)
{
	int		*tmp;

	tmp = search_mode_super_get();
	if (setter == 0)
	{
		set_searched(NULL);
		set_active_search_node(NULL);
	}
	*tmp = setter;
}
const char	*get_searched(void)
{
	return (*searched_super_get());
}
void	set_searched(char *setter)
{
	char	**searched;
	char	*tmp;

	searched = searched_super_get();
	tmp = *searched;
	ft_strdel(&tmp);
	*searched = setter;
}
