/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   term_state.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/28 22:56:55 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/31 23:31:03 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "common.h"

int			init_term_state(t_sh_state *state)
{
	int		fd;

	fd = tgetent(NULL, getenv("TERM"));
	if (tcgetattr(fd, &(state->term_state)) != 0 ||
tcgetattr(fd, &(state->term_state_backup)) != 0)
		return (1);
	state->term_state.c_lflag &= ~(ICANON);
	state->term_state.c_lflag &= ~(ECHO);
	state->term_state.c_lflag &= ~(ISIG);
	if (tcsetattr(0, 0, &(state->term_state)) != 0)
		return (1);
	return (0);
}

int			reset_term_state(t_sh_state *sh_state)
{
	if (tcsetattr(0, 0, &(sh_state->term_state_backup)) != 0)
		return (1);
	return (0);
}
