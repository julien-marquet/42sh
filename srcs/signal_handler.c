/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   signal_handler.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/11 11:19:15 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/11 02:21:38 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "signal_handler.h"

void	handle_all(int signo)
{
	if (signo == SIGWINCH)
		update_win_data();
	else if (signo == 20)
	{
		dprintf(2, "SIGNAL RECEIVED = %d\n", signo);
		update_jobs_list();
	}
	else
		dprintf(2, "SIGNAL RECEIVED = %d\n", signo);
}
