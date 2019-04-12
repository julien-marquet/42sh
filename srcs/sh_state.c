/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   sh_state.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/28 22:56:52 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/12 00:48:24 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "sh_state.h"

t_sh_state	*init_sh_state(void)
{
	t_sh_state	*sh_state;

	if ((sh_state = ft_memalloc(sizeof(t_sh_state))) == NULL)
		return (NULL);
	return (sh_state);
}

void		free_sh_state(t_sh_state **state)
{
	void (*del)(void *, size_t);

	if (state == NULL || *state == NULL)
		return ;

	del = free_lstnode;
	ft_lstdel(&((*state)->internal_storage), del);
	free(*state);
}
