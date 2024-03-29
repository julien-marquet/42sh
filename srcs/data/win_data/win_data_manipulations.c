/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   win_data_manipulations.c                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/05 22:05:05 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/05 15:47:46 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "data/win_data/win_data_manipulations.h"

int		init_win_data(void)
{
	g_win_data.resized = 0;
	if (ioctl(0, TIOCGWINSZ, (&g_win_data.ws)) != 0)
		return (g_win_data.err = 1);
	return (g_win_data.err = 0);
}

void	update_win_data(void)
{
	struct winsize	old_size;

	old_size.ws_col = g_win_data.ws.ws_col;
	old_size.ws_row = g_win_data.ws.ws_row;
	g_win_data.err = ioctl(0, TIOCGWINSZ, (&g_win_data.ws));
	if (old_size.ws_col != g_win_data.ws.ws_col ||
old_size.ws_row != g_win_data.ws.ws_row)
		g_win_data.resized = 1;
}

void	reset_win_resized_value(void)
{
	g_win_data.resized = 0;
}

int		win_has_been_resized(void)
{
	return (g_win_data.resized);
}
