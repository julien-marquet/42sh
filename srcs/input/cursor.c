/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   cursor.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/31 23:39:16 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/05 18:06:43 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "input/cursor.h"

int		get_window_size(struct winsize *ws)
{
	if (ioctl(0, TIOCGWINSZ, ws) != 0)
		return (1);
	return (0);
}

/*
**	Get Cursor position by parsing the string returned
**	after a certain termcaps is sent
*/

int		get_cursor_position(t_cur_abs_pos *pos)
{
	size_t			len;
	unsigned char	str[16];
	size_t			i;
	ssize_t			ret;

	len = 0;
	i = 0;
	write(0, "\033[6n", 4);
	while (len < sizeof(str) - 1 && (ret = read(0, str + len, 1)) == 1)
	{
		if (str[len++] == 'R')
			break ;
	}
	if (ret == -1)
		return (1);
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

/*
**	Move cursor
*/

int		move_cursor_left(t_input_data *input_data)
{
	if (input_data->rel_cur_pos > 0)
	{
		tputs(tgoto(tgetstr("le", NULL), 1, 1), 1, ft_putchar);
		input_data->rel_cur_pos -= 1;
	}
	return (0);
}

int		move_cursor_right(t_input_data *input_data)
{
	t_cur_abs_pos	pos;
	struct winsize	ws;

	if (input_data->rel_cur_pos < input_data->input_buf->len)
	{
		if (get_cursor_position(&pos) == 1 || get_window_size(&ws) == 1)
			return (1);
		if (input_data->input_buf->buf[input_data->rel_cur_pos + 1] == '\n' ||
	pos.col + 1 > (int)ws.ws_col)
			tputs(tgoto(tgetstr("cm", NULL), 0, pos.row + 1), 1, ft_putchar);
		else
			tputs(tgoto(tgetstr("nd", NULL), 1, 1), 1, ft_putchar);
		input_data->rel_cur_pos += 1;
	}
	return (0);
}
