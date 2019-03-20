/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   cursor.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/31 23:39:16 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/20 18:56:31 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

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

int		update_scroll(int new_scroll)
{
	static int	scroll = 0;

	if (new_scroll == SCROLL_RESET)
		scroll = 0;
	else if (new_scroll > scroll)
		scroll = new_scroll;
	return (scroll);
}

int		get_cursor_position(t_cur_abs_pos *pos, t_dyn_buf *active_buf,
size_t rel_cur_pos, t_cur_abs_pos *start_pos)
{
	int				win_col;
	t_cur_abs_pos	last_pos;

	if ((win_col = get_win_col()) == -1)
		return (1);
	pos->row = get_prompt_len() / win_col + start_pos->row;
	pos->col = get_prompt_len() % win_col + start_pos->col;
	last_pos.row = get_prompt_len() / win_col;
	last_pos.col = pos->col;
	sim_cursor_movements(pos, &last_pos, active_buf, rel_cur_pos);
	last_pos.row = update_scroll(last_pos.row);
	if (last_pos.row + start_pos->row >= get_win_row())
		pos->row -= last_pos.row;
	return (0);
}

int		get_start_position(t_cur_abs_pos *pos, t_dyn_buf *active_buf,
t_cur_abs_pos *start_pos)
{
	int				win_col;
	t_cur_abs_pos	last_pos;

	if ((win_col = get_win_col()) == -1)
		return (1);
	pos->row = start_pos->row;
	pos->col = start_pos->col;
	last_pos.row = get_prompt_len() / win_col;
	last_pos.col = get_prompt_len() % win_col + start_pos->col;
	sim_cursor_movements(pos, &last_pos, active_buf, 0);
	last_pos.row = update_scroll(last_pos.row);
	if (last_pos.row + start_pos->row >= get_win_row())
		pos->row -= last_pos.row;
	if (pos->row < 0)
		pos->row = 0;
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
