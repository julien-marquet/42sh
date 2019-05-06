/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   input_search_mode.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/26 04:03:30 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/05 19:08:10 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "editing/input/input_search_mode.h"

int		*search_mode_super_get(void)
{
	static int search_mode = 0;

	return (&search_mode);
}

int		get_search_mode(void)
{
	return (*search_mode_super_get());
}

void	set_search_mode(int setter)
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
