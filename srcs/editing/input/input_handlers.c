/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   input_handlers.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/04 17:51:47 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/05 18:47:29 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "editing/input/input_handlers.h"

int		handle_capabilities(t_input_data *input_data,
		t_list *hist_copy, t_sh_state *sh_state)
{
	int	res;

	if ((res = capabilities_dispatcher_selection(input_data)) != 0)
		return (res == -1);
	else
	{
		reset_selection(input_data->start_pos, input_data->active_buf,
	&input_data->rel_cur_pos);
		if ((res = capabilities_dispatcher_1(input_data, sh_state)) != 0)
			return (res == -1);
		else if ((res = capabilities_dispatcher_2(input_data)) != 0)
			return (res == -1);
		else if ((res = capabilities_dispatcher_3(input_data)) != 0)
			return (res == -1);
		else if ((res = capabilities_dispatcher_4(input_data, hist_copy)) != 0)
			return (res == -1);
		else
			input_data->processed_chars = count_escape_chars(
		input_data->build_buf->buf);
	}
	return (0);
}

int		handle_sig(t_input_data *input_data, t_sh_state *sh_state)
{
	if ((ft_strncmp(input_data->build_buf->buf, CTRL_C, 1) == 0) &&
(input_data->processed_chars = 1))
	{
		if (ctrl_c_handler(input_data) == 1)
			return (1);
	}
	else if ((ft_strncmp(input_data->build_buf->buf, CTRL_D, 1) == 0) &&
(input_data->processed_chars = 1))
	{
		if (ctrl_d_handler(sh_state, input_data) == 1)
			return (1);
	}
	else if ((ft_strncmp(input_data->build_buf->buf, CTRL_R, 1) == 0) &&
(input_data->processed_chars = 1))
	{
		if (ctrl_r_handler(sh_state, input_data) == 1)
			return (1);
	}
	return (0);
}

int		handle_insertion(t_input_data *input_data)
{
	size_t		i;
	char		*str;

	i = 0;
	while (i < input_data->build_buf->len &&
!is_capability(&(input_data->build_buf->buf[i])))
		i++;
	input_data->processed_chars = i;
	if ((str = ft_strndup(input_data->build_buf->buf, i)) == NULL)
		return (1);
	if (insert_dyn_buf(str, input_data->active_buf,
input_data->rel_cur_pos) == 1)
	{
		ft_strdel(&str);
		return (1);
	}
	ft_strdel(&str);
	return (insertn_chars(input_data, input_data->build_buf->buf, i, 0));
}
