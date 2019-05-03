/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   signal_handler.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/11 11:19:15 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/03 17:00:57 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "signal_handler.h"
#pragma GCC diagnostic ignored "-Wunused-parameter"

void	handle_sigwinch(int signo)
{
	update_win_data();
}

void	handle_sigchld(int signo)
{
	handle_process_update();
}
