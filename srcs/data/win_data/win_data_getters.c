/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   win_data_getters.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/05 18:18:41 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/05 18:25:09 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "data/win_data/win_data_getters.h"

int		get_win_col(void)
{
	if (g_win_data.err != 0)
		return (-1);
	return ((int)g_win_data.ws.ws_col);
}

int		get_win_row(void)
{
	if (g_win_data.err != 0)
		return (-1);
	return ((int)g_win_data.ws.ws_row);
}
