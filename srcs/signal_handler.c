/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   signal_handler.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/11 11:19:15 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/04 20:54:37 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "signal_handler.h"
#include "data/input_data.h"
#include "sh.h"

void	handle_sigwinch(int signo)
{
	signo += 0;
	dprintf(2, "SIGWINCH RECEIVED, %d\n", signo);
	update_win_data();
}