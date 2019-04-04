/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   cursor_vertical_moves.c                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/04 16:42:31 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/04 17:13:21 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "input/cursor_vertical_moves.h"

static int			search_for_prev_line(t_input_data *input_data, size_t *i)
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

static int			search_for_next_line(t_input_data *input_data, size_t *i)
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