/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   input_searched.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/05 19:00:00 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/05 19:14:08 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "editing/input/input_searched.h"

char		**searched_super_get(void)
{
	static char	*searched = NULL;

	return (&searched);
}

const char	*get_searched(void)
{
	return (*searched_super_get());
}

void		set_searched(char *setter)
{
	char	**searched;
	char	*tmp;

	searched = searched_super_get();
	tmp = *searched;
	ft_strdel(&tmp);
	*searched = setter;
}
