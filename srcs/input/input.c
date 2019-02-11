/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   input.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/29 00:52:24 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/11 14:15:33 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "input/input.h"
#include "input/input_control.h"
#include "input/prompt.h"
#include "input/cursor.h"

int		is_capability(char *s)
{
	int		is_cap;

	is_cap = 0;
	if (*s == '\033')
	{
		is_cap |= (ft_strncmp(s, KEY_ARROW_LEFT, 3) != 0);
		is_cap |= (ft_strncmp(s, KEY_ARROW_RIGHT, 3) != 0);
		is_cap |= (ft_strncmp(s, KEY_ARROW_UP, 3) != 0);
		is_cap |= (ft_strncmp(s, KEY_ARROW_DOWN, 3) != 0);
		is_cap |= (ft_strncmp(s, KEY_DEL, 4) != 0);
	}
	is_cap |= (*s == '\03');
	is_cap |= (*s == '\010');
	is_cap |= (*s == '\177');
	return (is_cap);
}

int		handle_insertion(t_input_data *input_data)
{
	size_t		i;

	i = 0;
	while (i < input_data->build_buf->len &&
!is_capability(&(input_data->build_buf->buf[i])))
	{
		i++;
		if (input_data->build_buf->buf[i - 1] == '\n')
		{
			// send output
			break ;
		}
	}
	dprintf(2, "INSERTION OF %zu chars", i);
	input_data->processed_chars = i;
	insertn_dyn_buf(input_data->build_buf->buf, input_data->input_buf,
input_data->rel_cur_pos, i);
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
	ft_bzero(buf, READ_SIZE + 1);
	ret = read(0, &buf, READ_SIZE);
	if (ret == -1 || insert_dyn_buf(buf, build_buf, build_buf->len) != 0)
		return (1);
	else if (ret == 0)
		return (0);
	return (0);
}

#define NONE 0
#define SIMPLE 1
#define DOUBLE 2

int		are_quotes_closed(t_dyn_buf *dyn_buf)
{
	int		opened;
	size_t	i;
	int		quote_type;

	i = 0;
	opened = false;
	quote_type = NONE;
	while (i < dyn_buf->len)
	{
		if (dyn_buf->buf[i] == '\'' &&
	((quote_type == SIMPLE && opened == true) ||
	((quote_type == SIMPLE || quote_type == NONE) &&
	opened == false && (i == 0 || dyn_buf->buf[i - 1] != '\\'))))
		{
			if ((opened = !opened) == 0)
				quote_type = NONE;
			else
				quote_type = SIMPLE;
		}
		else if (dyn_buf->buf[i] == '\"' &&
	(i == 0 || dyn_buf->buf[i - 1] != '\\'))
		{
			if (quote_type == NONE || quote_type == DOUBLE)
			{
				if ((opened = !opened) == 0)
					quote_type = NONE;
				else
					quote_type = DOUBLE;
			}
		}
		i++;
	}
	return (opened == 0);
}

int		output_is_ready(t_dyn_buf *dyn_buf)
{
	int		ready_state;

	ready_state = true;
	ready_state &= (dyn_buf->len > 0 && dyn_buf->buf[dyn_buf->len - 1] == '\n');
	ready_state &= are_quotes_closed(dyn_buf);
	return (ready_state);
}

int		handle_input(t_sh_state *sh_state, t_input_data *input_data)
{
	while (input_data->input_buf->len == 0 || input_data->stored_buf->len > 0)
	{
		if (get_start_position(input_data->start_pos) == 1)
			return (1);
		print_prompt(input_data->stored_buf->len > 0);
		input_data->rel_cur_pos = 0;
		while (sh_state->exit_sig == 0 && (input_data->input_buf->len == 0 ||
	input_data->input_buf->buf[input_data->input_buf->len - 1] != '\n'))
		{
			if (input_data->build_buf->len == 0)
			{
				if (get_buf(input_data->build_buf) != 0)
					return (1);
			}
			if (is_capability(input_data->build_buf->buf) == 1)
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
		}
		if (input_data->stored_buf->len > 0)
		{
			insert_dyn_buf(input_data->stored_buf->buf, input_data->input_buf, 0);
			reset_dyn_buf(input_data->stored_buf);
		}
		if (output_is_ready(input_data->input_buf) == false)
		{
			dprintf(2, "store buf\n");
			ft_swap((void **)(&(input_data->input_buf)), (void **)(&(input_data->stored_buf)));
			dprintf(2, "Stored buf len = %zu\n, Input buf len = %zu", input_data->stored_buf->len, input_data->input_buf->len);
		}
	}
	return (0);
}
