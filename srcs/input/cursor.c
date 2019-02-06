/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   cursor.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/31 23:39:16 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/06 23:59:40 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "input/cursor.h"

/*
**	Get Cursor position by parsing the string returned
**	after a certain termcaps is sent 
**	artificially converted to origin 0
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
				pos->row = ft_atoi((char *)&(str[++i])) - 1;
			else if (str[i] == ';')
				pos->col = ft_atoi((char *)&(str[++i])) - 1;
		}
	}
	return (0);
}

int		get_line_length(size_t pos, char *buf)
{
	size_t			len;
	size_t			nl;

	len = 0;
	nl = 0;
	if (get_win_col() == 1)
		return (-1);
	while (pos > 0 && nl < 2)
	{
		if (buf[pos] == '\n')
			nl++;
		len++;
		pos--;
	}
	return (len);
}

/*
**	Move cursor
*/

int		move_cursor_left(t_input_data *input_data)
{
	t_cur_abs_pos	pos;

	if (input_data->rel_cur_pos > 0)
	{
		if (get_cursor_position(&pos) == 1)
			return (1);
		if (pos.col == 0)
			dprintf(2, "line length = %d\n", get_line_length(input_data->rel_cur_pos - 2, input_data->input_buf->buf));
		tputs(tgoto(tgetstr("le", NULL), 1, 1), 1, ft_putchar);
		input_data->rel_cur_pos -= 1;
	}
	return (0);
}

int		move_cursor_right(t_input_data *input_data)
{
	t_cur_abs_pos	pos;

	if (input_data->rel_cur_pos < input_data->input_buf->len)
	{
		if (get_cursor_position(&pos) == 1 || get_win_col() == -1)
			return (1);
		if (input_data->input_buf->buf[input_data->rel_cur_pos + 1] == '\n' ||
	pos.col + 1 >= get_win_col())
			tputs(tgoto(tgetstr("cm", NULL), 0, pos.row + 1), 1, ft_putchar);
		else
			tputs(tgoto(tgetstr("nd", NULL), 1, 1), 1, ft_putchar);
		input_data->rel_cur_pos += 1;
	}
	return (0);
}
