/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   cursor.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/31 23:39:16 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/31 23:40:48 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "input/cursor.h"

/*
**	Get Cursor position by parsing the string returned
**	after a certain termcaps is sent
*/

int		get_cursor_position(t_cur_abs_pos *pos)
{
	size_t			len;
	unsigned char	str[16];
	size_t			i;

	len = 0;
	i = 0;
	write(0, "\x1B[6n", 4);
	while (len < sizeof(str) - 1 && read(0, str + len, 1) == 1)
	{
		if (str[len++] == 'R')
			break ;
	}
	str[len] = '\0';
	while (++i < len)
	{
		if (!(str[i] < ' ' || '~' < str[i]))
		{
			if (str[i] == '[')
				pos->row = ft_atoi((char *)&(str[++i]));
			else if (str[i] == ';')
				pos->col = ft_atoi((char *)&(str[++i]));
		}
	}
	return (0);
}
