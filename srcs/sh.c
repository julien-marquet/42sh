/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   sh.c                                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/28 22:59:25 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/02 21:45:17 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "sh.h"
#include "sh_state.h"
#include "term_state.h"
#include "win_data.h"
#include "input/input_data.h"

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

void		exit_sh(t_sh_state *sh_state, t_input_data *input_data)
{
	size_t	status;

	status = sh_state->status;
	reset_term_state(sh_state);
	free_sh_state(&sh_state);
	free_input_data(&input_data);
	exit(status);
}
