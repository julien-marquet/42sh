/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   cursor_utils.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/04 16:50:18 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/05 15:56:32 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "editing/cursor/cursor_utils.h"

static int	get_line_length(t_dyn_buf *active_buf, size_t start)
{
	size_t	i;

	i = 0;
	while (start + i < active_buf->len && active_buf->buf[start + i] != '\n')
		i++;
	return (i);
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
	in_word = !ft_isspace(
input_data->active_buf->buf[input_data->rel_cur_pos - 1]);
	while (input_data->rel_cur_pos - (i + 1) != 0)
	{
		if (ft_isspace(
	input_data->active_buf->buf[input_data->rel_cur_pos - (i + 1)]) == in_word)
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
	while (i + input_data->rel_cur_pos < input_data->active_buf->len)
	{
		if (ft_isspace(
	input_data->active_buf->buf[input_data->rel_cur_pos + i]) == in_word)
			break ;
		i++;
	}
	return (i);
}

int			get_prev_position(t_input_data *input_data,
t_cur_abs_pos *pos_prev, size_t i)
{
	t_cur_abs_pos pos_curr;

	if ((get_cursor_position(pos_prev, input_data->active_buf,
input_data->rel_cur_pos - i, input_data->start_pos)) == 1 ||
(get_cursor_position(&pos_curr, input_data->active_buf,
input_data->rel_cur_pos, input_data->start_pos)) == 1)
		return (1);
	if (pos_curr.col < pos_prev->col)
	{
		i += (size_t)pos_prev->col - (size_t)pos_curr.col;
		if (i > input_data->rel_cur_pos && !(input_data->rel_cur_pos = 0))
		{
			if ((get_cursor_position(pos_prev, input_data->active_buf,
		0, input_data->start_pos)) == 1)
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

int			get_next_position(t_input_data *input_data,
t_cur_abs_pos *pos_next, size_t i)
{
	int				line_len;
	t_cur_abs_pos	pos_curr;

	if ((get_cursor_position(pos_next, input_data->active_buf,
input_data->rel_cur_pos + i, input_data->start_pos)) == 1)
		return (1);
	if ((get_cursor_position(&pos_curr, input_data->active_buf,
input_data->rel_cur_pos, input_data->start_pos)) == 1)
		return (1);
	line_len = get_line_length(input_data->active_buf,
input_data->rel_cur_pos + i);
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
