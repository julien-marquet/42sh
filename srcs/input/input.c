/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   input.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/29 00:52:24 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/05 22:34:03 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "input/input.h"
#include "input/input_control.h"
#include "input/prompt.h"
#include "input/cursor.h"
 

int		handle_capabilities(t_input_data *input_data,
t_sh_state *sh_state, int *send_input)
{
	int		res;
	input_data->input_buf->len += 0;
	sh_state->status += 0;
	res = 0;
	if (input_data->build_buf->len > 0 && input_data->build_buf->buf[input_data->build_buf->len - 1] == '\n' && (res = 1))
		*send_input = 1;
	if (ft_strcmp(input_data->build_buf->buf, KEY_ARROW_LEFT) == 0 && (res = 1))
		move_cursor_left(input_data);
	else if (ft_strcmp(input_data->build_buf->buf, KEY_ARROW_RIGHT) == 0 && (res = 1))
		move_cursor_right(input_data);
	if (ft_strcmp(input_data->build_buf->buf, KEY_ARROW_UP) == 0 && (res = 1))
		write(1, "[Up]", 4);
	else if (ft_strcmp(input_data->build_buf->buf, KEY_ARROW_DOWN) == 0 && (res = 1))
		write(1, "[Down]", 6);
	else if ((ft_strcmp(input_data->build_buf->buf, KEY_BS) == 0 ||
ft_strcmp(input_data->build_buf->buf, KEY_BS2) == 0) && (res = 1))
	{
		if (delete_prev_char(input_data) != 0)
			return (1);
	}
	else if ((ft_strcmp(input_data->build_buf->buf, KEY_DEL) == 0 && (res = 1)))
		delete_cur_char(input_data); // add cursor position
	else if (ft_strcmp(input_data->build_buf->buf, KEY_SIGINT) == 0 && (res = 1))
	{
		*send_input = 1;
		sh_state->exit_sig = 1;
		sh_state->status = 2;
	}
	return (res);
}

int		get_buf(t_dyn_buf *build_buf)
{
	char	buf[READ_SIZE + 1];
	ssize_t	ret;

	ret = READ_SIZE;
	while (ret >= READ_SIZE)
	{
		ft_bzero(buf, READ_SIZE + 1);
		ret = read(0, &buf, READ_SIZE);
		if (ret == -1 || insert_dyn_buf(buf, build_buf, build_buf->len) != 0)
			return (1);
	}
	return (0);
}

int		insert_chars(t_input_data *input_data)
{
	t_cur_abs_pos	pos;

	if (get_cursor_position(&pos) == 1 || get_win_col() == -1)
		return (1);
	if (input_data->rel_cur_pos < input_data->input_buf->len - 1 &&
pos.col >= get_win_col())
		tputs(tgoto(tgetstr("cm", NULL), 0, pos.row), 1, ft_putchar);
	input_data->rel_cur_pos += input_data->build_buf->len;
	ft_putstr(input_data->build_buf->buf);
	if (input_data->rel_cur_pos < input_data->input_buf->len)
		return (update_vbuf(input_data));
	return (0);
}

/*
	build buf as to be kept if there 's  a \n  and it's not finished
	- get new buf or stored buf 
	- parse buf till \n 
	- remove the part that has been copied
	- exec 
*/

int		handle_input(t_sh_state *sh_state, t_input_data *input_data)
{
	int		send_input;
	int		is_cap;


	send_input = 0;
	print_prompt();
	while (send_input == 0)
	{
		if (get_buf(input_data->build_buf) != 0)
			return (1);
		is_cap = handle_capabilities(input_data, sh_state, &send_input);
		if (is_cap == -1)
			return (1);
		else if (is_cap == 0)
		{
			insert_dyn_buf(input_data->build_buf->buf, input_data->input_buf,
		input_data->rel_cur_pos);
			insert_chars(input_data);
		}
		ft_putendl_fd(input_data->input_buf->buf, 2);
		reset_dyn_buf(input_data->build_buf);
	}
	return (0);
}
