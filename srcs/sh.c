/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   sh.c                                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mmoya <mmoya@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/28 22:59:25 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/04 17:49:30 by mmoya       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "sh.h"

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
	unsigned char	status;
	void (*del)(void *, size_t);

	status = sh_state->status;
	// TODO HISTORY SAVE `.42sh_history`
	del = free_lstnode;
	ft_lstdel(&sh_state->history, del);
	flush_all_jobs();
	set_term_state_backup(sh_state);
	free_sh_state(&sh_state);
	free_input_data(&input_data);
	set_search_mode(0);
	exit(status);
}
