/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   cursor.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/31 23:39:16 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/12 10:12:08 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "input/cursor.h"
#include "input/prompt.h"

int		get_cursor_position(t_cur_abs_pos *pos, t_dyn_buf *input_buf,
size_t rel_cur_pos, t_cur_abs_pos *start_pos)
{
	int				win_col;
	size_t			i;

	if ((win_col = get_win_col()) == -1)
		return (1);
	pos->row = get_prompt_len() / win_col + start_pos->row; 
	pos->col = get_prompt_len()  % win_col + start_pos->col;
	i = 0;
	while (i < rel_cur_pos)
	{
		if (pos->col >= win_col)
		{
			pos->row += 1;
			pos->col = 1;
		}
		else if (input_buf->buf[i] == '\n')
		{
			pos->row += 1;
			pos->col = 0;
		}
		else
			pos->col++;
		i++;
	}
	return (0);
}

/*
**	Get Cursor position by parsing the string returned
**	after a certain termcaps is sent
**	artificially converted to origin 0
*/

int		get_start_position(t_cur_abs_pos *pos)
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

int		move_cursor_left(t_input_data *input_data)
{
	t_cur_abs_pos	pos;

	if (input_data->rel_cur_pos > 0)
	{
		input_data->rel_cur_pos -= 1;
		get_cursor_position(&pos, input_data->input_buf, input_data->rel_cur_pos, input_data->start_pos);
		tputs(tgoto(tgetstr("cm", NULL), pos.col, pos.row), 1, ft_putchar);
	}
	return (0);
}

int		move_cursor_right(t_input_data *input_data)
{
	t_cur_abs_pos	pos;

	if (input_data->rel_cur_pos < input_data->input_buf->len)
	{
		input_data->rel_cur_pos += 1;
		get_cursor_position(&pos, input_data->input_buf, input_data->rel_cur_pos, input_data->start_pos);
		tputs(tgoto(tgetstr("cm", NULL), pos.col, pos.row), 1, ft_putchar);
	}
	return (0);
}
