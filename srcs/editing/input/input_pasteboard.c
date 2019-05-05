/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   input_pasteboard.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/05 18:15:16 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/05 18:58:48 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "editing/input/input_pasteboard.h"

static void		input_copy(t_input_data *input_data)
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

static int		input_paste(t_input_data *input_data)
{
	size_t	len;

	if (input_data->clipboard != NULL)
	{
		len = ft_strlen(input_data->clipboard);
		if (insert_dyn_buf(input_data->clipboard, input_data->active_buf,
	input_data->rel_cur_pos) == 1)
			return (1);
		if (insertn_chars(input_data, input_data->clipboard, len, 0) == 1)
			return (1);
	}
	return (reset_selection(input_data->start_pos, input_data->active_buf,
&input_data->rel_cur_pos));
}

static int		input_cut(t_input_data *input_data)
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
		if (print_anew(input_data->start_pos, input_data->active_buf,
	input_data->rel_cur_pos) == 1)
			return (1);
	}
	return (reset_selection(input_data->start_pos, input_data->active_buf,
&input_data->rel_cur_pos));
}

int				pasteboard_handle_capabilities(t_input_data *input_data)
{
	if ((ft_strncmp(input_data->build_buf->buf, ALT_C, 2) == 0) &&
(input_data->processed_chars = 2))
		input_copy(input_data);
	else if ((ft_strncmp(input_data->build_buf->buf, ALT_V, 3) == 0) &&
(input_data->processed_chars = 3))
	{
		if (input_paste(input_data) == 1)
			return (-1);
	}
	else if ((ft_strncmp(input_data->build_buf->buf, ALT_X, 3) == 0) &&
(input_data->processed_chars = 3))
	{
		if (input_cut(input_data) == 1)
			return (-1);
	}
	return (0);
}
