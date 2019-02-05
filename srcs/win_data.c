/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   win_data.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/05 22:05:05 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/05 22:34:12 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "win_data.h"

int		init_win_data(void)
{
	if (ioctl(0, TIOCGWINSZ, (&g_win_data.ws)) != 0)
		return (g_win_data.err = 1);
	return (g_win_data.err = 0);
}

void	update_win_data(int signo)
{
	signo += 0;
	g_win_data.err = ioctl(0, TIOCGWINSZ, (&g_win_data.ws));
}

int		get_win_col(void)
{
	if (g_win_data.err != 0)
		return (-1);
	return ((int)g_win_data.ws.ws_col);
}
