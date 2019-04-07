/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   sh_state.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/28 22:56:52 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/07 23:16:35 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "sh_state.h"

t_sh_state	*init_sh_state(void)
{
	t_sh_state	*sh_state;

	if ((sh_state = malloc(sizeof(t_sh_state))) == NULL)
		return (NULL);
	sh_state->status = 0;
	sh_state->exit_sig = 0;
	sh_state->env = NULL;
	sh_state->internal_storage = NULL;
	return (sh_state);
}

void		free_sh_state(t_sh_state **state)
{
	void (*del)(void *, size_t);

	if (state == NULL || *state == NULL)
		return ;

	del = free_lstnode;
	ft_lstdel(&((*state)->env), del);
	free(*state);
}
