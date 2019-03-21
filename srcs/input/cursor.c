/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   cursor.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/31 23:39:16 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/21 21:43:49 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

/*
	TODO = Calc start
	Store old if neccessary
	Calc cursor without touching  start
*/

#include "input/cursor.h"
#include "input/prompt.h"

static void	sim_wrap(t_cur_abs_pos *pos)
{
	pos->row += 1;
	pos->col = 1;
}

static void	sim_break(t_cur_abs_pos *pos)
{
	pos->row += 1;
	pos->col = 0;
}

/*
**	Simulate cursor movement updating pos to rel_cur_pos
**	And last pos to position of last char
*/

static void	sim_cursor_movements(t_cur_abs_pos *pos, t_cur_abs_pos *last_pos,
t_dyn_buf *active_buf, size_t rel_cur_pos)
{
	size_t			i;

	i = 0;
	while (i < active_buf->len)
	{
		if (last_pos->col >= get_win_col())
			sim_wrap(last_pos);
		else if (active_buf->buf[i] == '\n')
			sim_break(last_pos);
		else
			last_pos->col++;
		if (i < rel_cur_pos)
		{
			if (pos->col >= get_win_col())
				sim_wrap(pos);
			else if (active_buf->buf[i] == '\n')
				sim_break(pos);
			else
			{
				if (i < rel_cur_pos)
					pos->col++;
			}
		}
		i++;
	}
}

/*
**	Return absolute cursor position
*/

int		get_cursor_position(t_cur_abs_pos *pos, t_dyn_buf *active_buf,
size_t rel_cur_pos, t_cur_abs_pos *start_pos)
{
	int				win_col;
	size_t			i;

	win_col = get_win_col();
	pos->col = get_prompt_len() % win_col + start_pos->col;
	pos->row = get_prompt_len() / win_col + start_pos->row;
	i = 0;
	while (i < active_buf->len && i < rel_cur_pos)
	{
		if (pos->col >= get_win_col())
			sim_wrap(pos);
		else if (active_buf->buf[i] == '\n')
			sim_break(pos);
		else
		{
			if (i < rel_cur_pos)
				pos->col++;
		}
		i++;
	}
	return (0);
}

/*
**	return start position (without prompt len)
**	update start position if scroll detected
*/

int		update_start_position(t_dyn_buf *active_buf,
t_cur_abs_pos *start_pos)
{
	int				win_col;
	t_cur_abs_pos	last_pos;

	if ((win_col = get_win_col()) == -1)
		return (1);
	last_pos.row = get_prompt_len() / win_col;
	last_pos.col = get_prompt_len() % win_col + start_pos->col;
	sim_cursor_movements(start_pos, &last_pos, active_buf, 0);
	if (last_pos.row + start_pos->row >= get_win_row())
		start_pos->row -= (last_pos.row + 1 + start_pos->row) % (get_win_row());
	if (start_pos->row < 0)
		start_pos->row = 0;
	return (0);
}

/*
**	Get Cursor position by parsing the string returned
**	after a certain termcaps is sent
**	artificially converted to origin 0
*/

int		ask_start_position(t_cur_abs_pos *pos)
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
		get_cursor_position(&pos, input_data->active_buf,
	input_data->rel_cur_pos, input_data->start_pos);
		tputs(tgoto(tgetstr("cm", NULL), pos.col, pos.row), 1, ft_putchar);
	}
	return (0);
}

int		move_cursor_right(t_input_data *input_data)
{
	t_cur_abs_pos	pos;

	if (input_data->rel_cur_pos < input_data->active_buf->len)
	{
		input_data->rel_cur_pos += 1;
		get_cursor_position(&pos, input_data->active_buf,
	input_data->rel_cur_pos, input_data->start_pos);
		tputs(tgoto(tgetstr("cm", NULL), pos.col, pos.row), 1, ft_putchar);
	}
	return (0);
}
