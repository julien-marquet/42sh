/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   cursor.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/31 23:39:16 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/03 18:46:16 by jmarquet    ###    #+. /#+    ###.fr     */
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
#include "input/input_data.h"
#include "input/input_control.h"

int			goto_end(t_input_data *input_data)
{
	t_cur_abs_pos pos;
	input_data->rel_cur_pos = input_data->active_buf->len;
	if ((get_cursor_position(&pos, input_data->active_buf, input_data->rel_cur_pos, input_data->start_pos)) == 1)
		return (1);
	if (tputs(tgoto(tgetstr("cm", NULL), pos.col, pos.row), 1, ft_putchar) != 0)
		return (1);
	return (0);
}

int			goto_home(t_input_data *input_data)
{
	t_cur_abs_pos pos;
	input_data->rel_cur_pos = 0;
	if ((get_cursor_position(&pos, input_data->active_buf, input_data->rel_cur_pos, input_data->start_pos)) == 1)
		return (1);
	if (tputs(tgoto(tgetstr("cm", NULL), pos.col, pos.row), 1, ft_putchar) != 0)
		return (1);
	return (0);
}

int			get_prev_move_num(t_input_data *input_data)
{
	size_t	i;
	int		in_word;

	if (input_data->rel_cur_pos == 0)
		return (0);
	else if (input_data->rel_cur_pos == 1)
		return (1);
	i = 1;
	in_word = !ft_isspace(input_data->active_buf->buf[input_data->rel_cur_pos - 1]);
	while (input_data->rel_cur_pos - (i + 1) != 0)
	{
		if (ft_isspace(input_data->active_buf->buf[input_data->rel_cur_pos - (i + 1)]) == in_word)
			break ;
		i++;
	}
	if (input_data->rel_cur_pos - (i + 1) == 0)
		return (i + 1);
	return (i);
}

int			get_next_move_num(t_input_data *input_data)
{
	size_t	i;
	int		in_word;

	if (input_data->rel_cur_pos == input_data->active_buf->len)
		return (0);
	i = 1;
	in_word = !ft_isspace(input_data->active_buf->buf[input_data->rel_cur_pos]);
	while (i  + input_data->rel_cur_pos < input_data->active_buf->len)
	{
		if (ft_isspace(input_data->active_buf->buf[input_data->rel_cur_pos + i]) == in_word)
			break ;
		i++;
	}
	return (i);
}

int			search_for_prev_line(t_input_data *input_data, size_t *i)
{
	int		found;

	found = 0;
	while (input_data->rel_cur_pos - *i != 0)
	{
		if (input_data->active_buf->buf[input_data->rel_cur_pos - *i] == '\n')
		{
			found = 1;
			break ;
		}
		*i += 1;
	}
	return (found);
}

int			get_prev_position(t_input_data *input_data, t_cur_abs_pos *pos_prev, size_t i)
{
	t_cur_abs_pos pos_curr;

	if ((get_cursor_position(pos_prev, input_data->active_buf, input_data->rel_cur_pos - i, input_data->start_pos)) == 1)
		return (1);
	if ((get_cursor_position(&pos_curr, input_data->active_buf, input_data->rel_cur_pos, input_data->start_pos)) == 1)
		return (1);
	if (pos_curr.col < pos_prev->col)
	{
		i += (size_t)pos_prev->col - (size_t)pos_curr.col;
		if (i > input_data->rel_cur_pos)
		{
			input_data->rel_cur_pos = 0;
			if ((get_cursor_position(pos_prev, input_data->active_buf, 0, input_data->start_pos)) == 1)
				return (1);
		}
		else
		{
			input_data->rel_cur_pos -= i;
			pos_prev->col = pos_curr.col;
		}
	}
	else
		input_data->rel_cur_pos -= i;
	return (0);
}

int			move_up(t_input_data *input_data)
{
	size_t	i;
	int		found;
	t_cur_abs_pos pos_prev;

	i = 1;
	if (input_data->rel_cur_pos == 0)
		return (0);
	found = search_for_prev_line(input_data, &i);
	if (found == 1)
	{
		if (get_prev_position(input_data, &pos_prev, i) == 1)
			return (1);
		if (tputs(tgoto(tgetstr("cm", NULL), pos_prev.col, pos_prev.row), 1, ft_putchar) != 0)
			return (1);
	}
	return (0);
}

int			get_line_length(t_dyn_buf *active_buf, size_t start)
{
	size_t	i;

	i = 0;
	while (start + i < active_buf->len && active_buf->buf[start + i] != '\n')
		i++;
	return (i);
}

int			search_for_next_line(t_input_data *input_data, size_t *i)
{
	int		found;

	found = 0;
	while (input_data->rel_cur_pos + *i < input_data->active_buf->len)
	{
		if (input_data->active_buf->buf[input_data->rel_cur_pos + *i] == '\n'
	&& input_data->rel_cur_pos + *i + 1 <= input_data->active_buf->len)
		{
			*i += 1;
			found = 1;
			break ;
		}
		*i += 1;
	}
	return (found);
}
int			get_next_position(t_input_data *input_data, t_cur_abs_pos *pos_next, size_t i)
{
	int	line_len;
	t_cur_abs_pos pos_curr;

	if ((get_cursor_position(pos_next, input_data->active_buf, input_data->rel_cur_pos + i, input_data->start_pos)) == 1)
		return (1);
	if ((get_cursor_position(&pos_curr, input_data->active_buf, input_data->rel_cur_pos, input_data->start_pos)) == 1)
		return (1);
	line_len = get_line_length(input_data->active_buf, input_data->rel_cur_pos + i);
	if (pos_curr.col > line_len)
	{
		i += line_len;
		pos_next->col = line_len;
	}
	else
	{
		i += pos_curr.col;
		pos_next->col += pos_curr.col;
	}
	input_data->rel_cur_pos += i;
	return (0);
}

int			move_down(t_input_data *input_data)
{
	size_t	i;
	t_cur_abs_pos pos_next;
	int		found;

	i = 0;
	found = search_for_next_line(input_data, &i);
	if (found == 1)
	{
		if (get_next_position(input_data, &pos_next, i) == 1)
			return (1);
		if (tputs(tgoto(tgetstr("cm", NULL), pos_next.col, pos_next.row), 1, ft_putchar) != 0)
			return (1);
	}
	return (0);
}

int			move_to_next_word(t_input_data *input_data)
{
	t_cur_abs_pos	pos;
	input_data->rel_cur_pos += get_next_move_num(input_data);
	if ((get_cursor_position(&pos, input_data->active_buf, input_data->rel_cur_pos ,input_data->start_pos)) == 1)
		return (1);
	if (tputs(tgoto(tgetstr("cm", NULL), pos.col, pos.row), 1, ft_putchar) != 0)
		return (1);
	return (0);
}

int			move_to_prev_word(t_input_data *input_data)
{
	t_cur_abs_pos	pos;
	input_data->rel_cur_pos -= get_prev_move_num(input_data);
	if ((get_cursor_position(&pos, input_data->active_buf, input_data->rel_cur_pos ,input_data->start_pos)) == 1)
		return (1);
	if (tputs(tgoto(tgetstr("cm", NULL), pos.col, pos.row), 1, ft_putchar) != 0)
		return (1);
	return (0);
}

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

int			update_wanted_pos(t_cur_abs_pos *pos, t_dyn_buf *active_buf, size_t i, size_t rel_cur_pos)
{
	int				win_col;

	if ((win_col = get_win_col()) == -1)
		return (1);
	if (pos->col >= win_col)
		sim_wrap(pos);
	else if (active_buf->buf[i] == '\n')
		sim_break(pos);
	else
	{
		if (i < rel_cur_pos)
			pos->col++;
	}
	return (0);
}

/*
**	Simulate cursor movement updating pos to wanted pos
**	And last pos to position of last char
*/

static int	sim_cursor_movements(t_cur_abs_pos *pos, t_cur_abs_pos *last_pos,
t_dyn_buf *active_buf, size_t rel_cur_pos)
{
	int				win_col;
	size_t			i;

	i = 0;
	if ((win_col = get_win_col()) == -1)
		return (1);
	while (i < active_buf->len)
	{
		if (last_pos->col >= win_col)
			sim_wrap(last_pos);
		else if (active_buf->buf[i] == '\n')
			sim_break(last_pos);
		else
			last_pos->col++;
		if (i < rel_cur_pos)
		{
			if (update_wanted_pos(pos, active_buf, i, rel_cur_pos) == 1)
				return (1);
		}
		i++;
	}
	return (0);
}

int		sim_cursor_movement_light(t_dyn_buf *active_buf, size_t rel_cur_pos, t_cur_abs_pos *pos, int win_col)
{
	size_t	i;

	i = 0;
	while (i < active_buf->len && i < rel_cur_pos)
	{
		if (pos->col >= win_col)
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
	return (i);
}

/*
**	Return absolute cursor position
*/

int		get_cursor_position(t_cur_abs_pos *pos, t_dyn_buf *active_buf,
size_t rel_cur_pos, t_cur_abs_pos *start_pos)
{
	int				win_col;
	size_t			i;
	int	 			resize;

	if ((resize = win_has_been_resized()))
	{
		if (update_start_position(active_buf, start_pos) == 1)
			return (1);
	}
	if ((win_col = get_win_col()) == -1)
		return (1);
	pos->col = get_prompt_len() % win_col + start_pos->col;
	pos->row = get_prompt_len() / win_col + start_pos->row;
	i = sim_cursor_movement_light(active_buf, rel_cur_pos, pos, win_col);
	if (resize)
		print_anew(start_pos, active_buf, rel_cur_pos);
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
	int				win_row;
	t_cur_abs_pos	last_pos;

	if ((win_col = get_win_col()) == -1 || (win_row = get_win_row()) == -1)
		return (1);
	last_pos.row = get_prompt_len() / win_col;
	last_pos.col = get_prompt_len() % win_col + start_pos->col;
	if (sim_cursor_movements(start_pos, &last_pos, active_buf, 0) == 1)
		return (1);
	if (last_pos.row + start_pos->row >= win_row)
		start_pos->row -= (last_pos.row + 1 + start_pos->row) % win_row;
	if (start_pos->row < 0)
		start_pos->row = 0;
	reset_win_resized_value();
	return (0);
}

void	process_location_termcaps(size_t i, size_t len, unsigned char str[16], t_cur_abs_pos *pos)
{
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
	process_location_termcaps(i, len, str, pos);
	return (0);
}

int		move_cursor_left(t_input_data *input_data)
{
	t_cur_abs_pos	pos;

	if (input_data->rel_cur_pos > 0)
	{
		input_data->rel_cur_pos -= 1;
		if ((get_cursor_position(&pos, input_data->active_buf, input_data->rel_cur_pos, input_data->start_pos)) == 1)
			return (1);
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
		if ((get_cursor_position(&pos, input_data->active_buf, input_data->rel_cur_pos, input_data->start_pos)) == 1)
			return (1);
		tputs(tgoto(tgetstr("cm", NULL), pos.col, pos.row), 1, ft_putchar);
	}
	return (0);
}
