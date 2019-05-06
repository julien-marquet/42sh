/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   term_state.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/28 22:56:55 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/06 15:40:15 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "common.h"
#include "errno.h"

int			init_term_state(t_sh_state *state, char **env)
{
	int		fd;
	char	*term;

	if ((term = ft_getenv("TERM", env)) == NULL)
		return (1);
	if ((fd = tgetent(NULL, term)) <= 0)
	{
		ft_strdel(&term);
		return (1);
	}
	ft_strdel(&term);
	if (tcgetattr(fd, &(state->term_state)) != 0 ||
tcgetattr(fd, &(state->term_state_backup)) != 0)
		return (1);
	state->term_state.c_lflag &= ~(ICANON);
	state->term_state.c_lflag &= ~(ECHO);
	state->term_state.c_lflag &= ~(ISIG);
	if (tcsetattr(0, TCSANOW, &(state->term_state)) != 0)
		return (1);
	return (0);
}

int			set_term_state_backup(t_sh_state *sh_state)
{
	if (tcsetattr(0, TCSADRAIN, &(sh_state->term_state_backup)) != 0)
		return (1);
	return (0);
}

int			set_term_state(t_sh_state *sh_state)
{
	if (tcsetattr(0, TCSADRAIN, &(sh_state->term_state)) != 0)
		return (1);
	return (0);
}
