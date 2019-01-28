/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   sh_state.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/28 22:56:52 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/28 23:28:17 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "common.h"

t_sh_state	*init_sh_state(void)
{
	t_sh_state	*sh_state;

	sh_state = malloc(sizeof(t_sh_state));
	return (sh_state);
}

void		free_sh_state(t_sh_state **state)
{
	if (state == NULL || *state == NULL)
		return ;
	free(*state);
}
