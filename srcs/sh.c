/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   sh.c                                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/28 22:59:25 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/05 22:26:49 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "sh.h"
#include "sh_state.h"
#include "term_state.h"
#include "win_data.h"

t_sh_state	*init_sh(void)
{
	t_sh_state	*sh_state;

	if ((sh_state = init_sh_state()) == NULL)
		return (NULL);
	if (init_term_state(sh_state) != 0)
		return (NULL);
	if (init_win_data() != 0)
		return (NULL);
	return (sh_state);
}

int			exit_sh(t_sh_state *sh_state)
{
	size_t	status;

	status = sh_state->status;
	reset_term_state(sh_state);
	free_sh_state(&sh_state);
	exit(status);
}
