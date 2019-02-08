/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   input.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/29 00:52:24 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/08 18:12:53 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "input/input.h"
#include "input/input_control.h"
#include "input/prompt.h"
#include "input/cursor.h"


int		is_capability(char	c)
{
	int		is_cap;

	is_cap = 0;
	is_cap |= (c == '\033');
	is_cap |= (c == '\03');
	is_cap |= (c == '\010');
	is_cap |= (c == '\177');
	return (is_cap);
}

int		insertn_chars(t_input_data *input_data, size_t n)
{
	t_cur_abs_pos	pos;
	write(1, input_data->build_buf->buf, n);
	if (get_cursor_position(&pos) == 1 || get_win_col() == -1)
		return (1);
	input_data->rel_cur_pos += n;
	if (pos.col == get_win_col() - 1 && input_data->rel_cur_pos < input_data->input_buf->len)
	{
		tputs(tgoto(tgetstr("cm", NULL), 0, pos.row + 1), 1, ft_putchar);
	}
	if (input_data->rel_cur_pos < input_data->input_buf->len)
	 	return (update_vbuf(input_data->input_buf->buf, input_data->rel_cur_pos));
	return (0);
}

int		handle_insertion(t_input_data *input_data)
{
	size_t		i;

	i = 0;
	while (i < input_data->build_buf->len && !is_capability(input_data->build_buf->buf[i]))
	{
		i++;
		if (input_data->build_buf->buf[i - 1] == '\n')
			break ;
	}
	dprintf(2, "INSERTION OF %zu chars", i);
	input_data->processed_chars = i;
	insertn_dyn_buf(input_data->build_buf->buf, input_data->input_buf, input_data->rel_cur_pos, i);
	insertn_chars(input_data, i);
	return (0);
}

int		handle_capabilities(t_input_data *input_data, t_sh_state *sh_state)
{
	if (ft_strncmp(input_data->build_buf->buf, KEY_SIGINT, 1) == 0 && (input_data->processed_chars = 1))
	{
		sh_state->exit_sig = 1;
	}
	else if ((ft_strncmp(input_data->build_buf->buf, KEY_BS, 1) == 0 || ft_strncmp(input_data->build_buf->buf, KEY_BS2, 1) == 0) && (input_data->processed_chars = 1))
	{
		if (delete_prev_char(input_data) != 0)
			return (1);
	}
	else if (ft_strncmp(input_data->build_buf->buf, KEY_ARROW_LEFT, 3) == 0 && (input_data->processed_chars = 3))
	{
		move_cursor_left(input_data);
	}
	else if (ft_strncmp(input_data->build_buf->buf, KEY_ARROW_RIGHT, 3) == 0 && (input_data->processed_chars = 3))
	{
		move_cursor_right(input_data);
	}
	else if (ft_strncmp(input_data->build_buf->buf, KEY_ARROW_UP, 3) == 0 && (input_data->processed_chars = 3))
	{
		write(1, "[Up]", 4);
	}
	else if (ft_strncmp(input_data->build_buf->buf, KEY_ARROW_DOWN, 3) == 0 && (input_data->processed_chars = 3))
	{
		write(1, "[Down]", 6);
	}
	else if ((ft_strncmp(input_data->build_buf->buf, KEY_DEL, 4) == 0) && (input_data->processed_chars = 4))
	{
		delete_cur_char(input_data);
	}
	return (0);
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




int		handle_input(t_sh_state *sh_state, t_input_data *input_data)
{
	print_prompt();
	input_data->rel_cur_pos = 0;
	while (sh_state->exit_sig == 0 && (input_data->input_buf->len == 0 ||
input_data->input_buf->buf[input_data->input_buf->len - 1] != '\n'))
	{
		if (input_data->build_buf->len == 0)
		{
			if (get_buf(input_data->build_buf) != 0)
				return (1);
		}
		if (is_capability(input_data->build_buf->buf[0]) == 1)
		{
			if (handle_capabilities(input_data, sh_state) == 1)
				return (1);
		}
		else
		{
			if (handle_insertion(input_data) == -1)
				return (1);
		}
		shift_dyn_buf(input_data->build_buf, input_data->processed_chars);
		input_data->processed_chars = 0;
		ft_putendl_fd(input_data->input_buf->buf, 2);
	}
	return (0);
}
