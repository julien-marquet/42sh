/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   input_capabilities_dispatchers.c                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/04 17:46:43 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/04 21:12:25 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "editing/input/input_capabilities_dispatchers.h"

int		capabilities_dispatcher_1(t_input_data *input_data)
{
	if (ft_strncmp(input_data->build_buf->buf, KEY_TAB, 1) == 0 &&
	(input_data->processed_chars = 1))
	{
		if (handle_completion(input_data) == 1)
			return (-1);
	}
	else if (ft_strncmp(input_data->build_buf->buf, KEY_NL, 1) == 0 && (input_data->processed_chars = 1))
	{
		if (handle_enter(input_data) == 1)
			return (-1);
	}
	else if (ft_strncmp(input_data->build_buf->buf, KEY_GOHOME, 3) == 0 && (input_data->processed_chars = 3))
	{
		if (goto_home(input_data) == 1)
			return (-1);
	}
	else if (ft_strncmp(input_data->build_buf->buf, KEY_GOEND, 3) == 0 && (input_data->processed_chars = 3))
	{
		if (goto_end(input_data) == 1)
			return (-1);
	}
	return (input_data->processed_chars > 0);
}

int		capabilities_dispatcher_2(t_input_data *input_data)
{
	if (ft_strncmp(input_data->build_buf->buf, ALT_ARROW_RIGHT, 4) == 0 && (input_data->processed_chars = 4))
	{
		if (move_to_next_word(input_data) == 1)
			return (-1);
	}
	else if (ft_strncmp(input_data->build_buf->buf, ALT_ARROW_LEFT, 4) == 0&& (input_data->processed_chars = 4))
	{
		if (move_to_prev_word(input_data) == 1)
			return (-1);
	}
	else if (ft_strncmp(input_data->build_buf->buf, ALT_ARROW_UP, 4) == 0 && (input_data->processed_chars = 4))
	{
		if (move_up(input_data) == 1)
			return (-1);
	}
	else if (ft_strncmp(input_data->build_buf->buf, ALT_ARROW_DOWN, 4) == 0&& (input_data->processed_chars = 4))
	{
		if (move_down(input_data) == 1)
			return (-1);
	}
	return (input_data->processed_chars > 0);
}

int		capabilities_dispatcher_3(t_input_data *input_data)
{
	if ((ft_strncmp(input_data->build_buf->buf, KEY_BS, 1) == 0 || ft_strncmp(input_data->build_buf->buf, KEY_BS2, 1) == 0) && (input_data->processed_chars = 1))
	{
		if (delete_prev_char(input_data) != 0)
			return (-1);
	}
	else if (ft_strncmp(input_data->build_buf->buf, KEY_ARROW_LEFT, 3) == 0 && (input_data->processed_chars = 3))
	{
		if (move_cursor_left(input_data) == 1)
			return (-1);
	}
	else if (ft_strncmp(input_data->build_buf->buf, KEY_ARROW_RIGHT, 3) == 0 && (input_data->processed_chars = 3))
	{
		if (move_cursor_right(input_data) == 1)
			return (-1);
	}
	return (input_data->processed_chars > 0);
}

int		capabilities_dispatcher_4(t_input_data *input_data, t_list *hist_copy)
{
	if (ft_strncmp(input_data->build_buf->buf, KEY_ARROW_UP, 3) == 0 && (input_data->processed_chars = 3))
	{
		if (hist_move_up(input_data, hist_copy) == 1)
			return (-1);
	}
	else if (ft_strncmp(input_data->build_buf->buf, KEY_ARROW_DOWN, 3) == 0 && (input_data->processed_chars = 3))
	{
		if (hist_move_down(input_data, hist_copy) == 1)
			return (-1);
	}
	else if ((ft_strncmp(input_data->build_buf->buf, KEY_DEL, 4) == 0) && (input_data->processed_chars = 4))
	{
		if (delete_cur_char(input_data) == 1)
			return (-1);
	}
	else if ((ft_strncmp(input_data->build_buf->buf, KEY_NP, 1) == 0) && (input_data->processed_chars = 1))
	{
		if (clear_input(input_data) == 1)
			return (-1);
	}
	return (input_data->processed_chars > 0);
}
