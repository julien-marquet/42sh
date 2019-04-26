/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   input_capabilities_dispatchers.c                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/04 17:46:43 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/26 02:10:49 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "editing/input/input_capabilities_dispatchers.h"

int		capabilities_dispatcher_1(t_input_data *input_data,
t_sh_state *sh_state)
{
	if (ft_strncmp(input_data->build_buf->buf, KEY_TAB, 1) == 0 &&
	(input_data->processed_chars = 1))
	{
		if (handle_completion(input_data, sh_state) == 1)
			return (-1);
	}
	else if (ft_strncmp(input_data->build_buf->buf, KEY_NL, 1) == 0 &&
(input_data->processed_chars = 1))
	{
		if (handle_enter(input_data) == 1)
			return (-1);
	}
	else if (ft_strncmp(input_data->build_buf->buf, KEY_GOHOME, 3) == 0 &&
(input_data->processed_chars = 3))
	{
		if (goto_home(input_data) == 1)
			return (-1);
	}
	else if (ft_strncmp(input_data->build_buf->buf, KEY_GOEND, 3) == 0 &&
(input_data->processed_chars = 3))
	{
		if (goto_end(input_data) == 1)
			return (-1);
	}
	return (input_data->processed_chars > 0);
}

int		capabilities_dispatcher_2(t_input_data *input_data)
{
	if (ft_strncmp(input_data->build_buf->buf, ALT_ARROW_RIGHT, 4) == 0 &&
(input_data->processed_chars = 4))
	{
		if (move_to_next_word(input_data) == 1)
			return (-1);
	}
	else if (ft_strncmp(input_data->build_buf->buf, ALT_ARROW_LEFT, 4) == 0 &&
(input_data->processed_chars = 4))
	{
		if (move_to_prev_word(input_data) == 1)
			return (-1);
	}
	else if (ft_strncmp(input_data->build_buf->buf, ALT_ARROW_UP, 4) == 0 &&
(input_data->processed_chars = 4))
	{
		if (move_up(input_data) == 1)
			return (-1);
	}
	else if (ft_strncmp(input_data->build_buf->buf, ALT_ARROW_DOWN, 4) == 0 &&
(input_data->processed_chars = 4))
	{
		if (move_down(input_data) == 1)
			return (-1);
	}
	return (input_data->processed_chars > 0);
}

int		capabilities_dispatcher_3(t_input_data *input_data)
{
	if ((ft_strncmp(input_data->build_buf->buf, KEY_BS, 1) == 0 ||
ft_strncmp(input_data->build_buf->buf, KEY_BS2, 1) == 0) &&
(input_data->processed_chars = 1))
	{
		if (delete_prev_char(input_data) != 0)
			return (-1);
	}
	else if (ft_strncmp(input_data->build_buf->buf, KEY_ARROW_LEFT, 3) == 0 &&
(input_data->processed_chars = 3))
	{
		if (move_cursor_left(input_data->start_pos, input_data->active_buf,
	&input_data->rel_cur_pos) == 1)
			return (-1);
	}
	else if (ft_strncmp(input_data->build_buf->buf, KEY_ARROW_RIGHT, 3) == 0 &&
(input_data->processed_chars = 3))
	{
		if (move_cursor_right(input_data->start_pos, input_data->active_buf,
	&input_data->rel_cur_pos) == 1)
			return (-1);
	}
	return (input_data->processed_chars > 0);
}

int		capabilities_dispatcher_4(t_input_data *input_data, t_list *hist_copy)
{
	if (ft_strncmp(input_data->build_buf->buf, KEY_ARROW_UP, 3) == 0 &&
(input_data->processed_chars = 3))
	{
		if (hist_move_up(input_data, hist_copy) == 1)
			return (-1);
	}
	else if (ft_strncmp(input_data->build_buf->buf, KEY_ARROW_DOWN, 3) == 0 &&
(input_data->processed_chars = 3))
	{
		if (hist_move_down(input_data, hist_copy) == 1)
			return (-1);
	}
	else if ((ft_strncmp(input_data->build_buf->buf, KEY_DEL, 4) == 0) &&
(input_data->processed_chars = 4))
	{
		if (delete_cur_char(input_data) == 1)
			return (-1);
	}
	else if ((ft_strncmp(input_data->build_buf->buf, KEY_NP, 1) == 0) &&
(input_data->processed_chars = 1))
	{
		if (clear_input(input_data) == 1)
			return (-1);
	}
	return (input_data->processed_chars > 0);
}

int		capabilities_dispatcher_selection(t_input_data *input_data)
{
	if ((ft_strncmp(input_data->build_buf->buf, KEY_SHIFT_LEFT, 6) == 0) &&
(input_data->processed_chars = 6))
	{
		if (expand_selection_left(input_data->start_pos, input_data->active_buf,
	&input_data->rel_cur_pos) == 1)
			return (-1);
	}
	else if ((ft_strncmp(input_data->build_buf->buf, KEY_SHIFT_RIGHT,
6) == 0) && (input_data->processed_chars = 6))
	{
		if (expand_selection_right(input_data->start_pos,
	input_data->active_buf, &input_data->rel_cur_pos) == 1)
			return (-1);
	}
	else if ((ft_strncmp(input_data->build_buf->buf, ALT_C, 2) == 0) &&
(input_data->processed_chars = 2))
	{
		int		start;

		if ((start = get_first_selected_char(input_data->active_buf)) != -1 &&
	input_data->active_buf->sel_len != 0)
		{
			ft_strdel(&input_data->clipboard);
			input_data->clipboard = ft_strndup(
		&(input_data->active_buf->buf[start]),
		ft_abs(input_data->active_buf->sel_len));
		}
		reset_selection(input_data->start_pos, input_data->active_buf,
	&input_data->rel_cur_pos);
	}
	else if ((ft_strncmp(input_data->build_buf->buf, ALT_V, 3) == 0) &&
(input_data->processed_chars = 3))
	{
		size_t	len;

		if (input_data->clipboard != NULL)
		{
			len = ft_strlen(input_data->clipboard);
			insertn_dyn_buf(input_data->clipboard, input_data->active_buf,
		input_data->rel_cur_pos, len);
			insertn_chars(input_data, input_data->clipboard, len, 0);
		}
		reset_selection(input_data->start_pos, input_data->active_buf,
	&input_data->rel_cur_pos);
	}
	else if ((ft_strncmp(input_data->build_buf->buf, ALT_X, 3) == 0) &&
(input_data->processed_chars = 3))
	{
		int		start;

		if ((start = get_first_selected_char(input_data->active_buf)) != -1 &&
		input_data->active_buf->sel_len != 0)
		{
			ft_strdel(&input_data->clipboard);
			input_data->clipboard = ft_strndup(
		&(input_data->active_buf->buf[start]),
		ft_abs(input_data->active_buf->sel_len));
			del_n_at_dyn_buf(input_data->active_buf, start,
		ft_abs(input_data->active_buf->sel_len));
			print_anew(input_data->start_pos, input_data->active_buf,
		input_data->rel_cur_pos);
		}
		reset_selection(input_data->start_pos, input_data->active_buf,
	&input_data->rel_cur_pos);
	}
	return (input_data->processed_chars > 0);
}
