/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   input.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/29 00:52:24 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/29 19:06:49 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "input/input.h"
#include "input/input_control.h"
#include "input/prompt.h"
#include "input/cursor.h"
#include "input/history.h"
#include "sh.h"

int		count_escape_chars(char *str)
{
	int		i;

	i = 0;
	while (str[i] != '\0' && !(str[i] >= '\010' && str[i] <= '\011') && str[i] <= '\037')
		i++;
	return (i);
}

int		is_capability(char *s)
{
	int		is_cap;

	is_cap = *s > '\0' && *s <= '\037';
	is_cap |= *s == '\177';
	return (is_cap);
}

int		is_sig(char *s)
{
	return (*s == '\04' || *s == '\03' || *s == '\032');
}

int		reset_input(t_input_data *input_data)
{
	reset_dyn_buf(input_data->stored_buf);
	reset_dyn_buf(input_data->active_buf);
	input_data->rel_cur_pos = 0;
	return (0);
}

int		handle_sig(t_input_data *input_data, t_sh_state *sh_state)
{
	t_cur_abs_pos pos;

	sh_state->exit_sig = sh_state->exit_sig;
	if ((ft_strncmp(input_data->build_buf->buf, CTRL_C, 1) == 0) && (input_data->processed_chars = 1))
	{
		input_data->sig_call = 1;
		get_cursor_position(&pos, input_data->active_buf, input_data->active_buf->len ,input_data->start_pos);
		if (tputs(tgoto(tgetstr("cm", NULL), pos.col, pos.row), 1, ft_putchar) != 0)
			return (1);
		write(1, "\n", 1);
	}
	else if ((ft_strncmp(input_data->build_buf->buf, CTRL_D, 1) == 0) && (input_data->processed_chars = 1))
		exit_sh(sh_state);
	else if ((ft_strncmp(input_data->build_buf->buf, CTRL_Z, 1) == 0) && (input_data->processed_chars = 1))
		dprintf(2, "SUSPEND SIG\n");
	return (0);
}

int		handle_insertion(t_input_data *input_data)
{
	size_t		i;

	i = 0;
	while (i < input_data->build_buf->len && !is_capability(&(input_data->build_buf->buf[i])))
		i++;
	dprintf(2, "BUF = %s\n", input_data->build_buf->buf);
	input_data->processed_chars = i;
	insertn_dyn_buf(input_data->build_buf->buf, input_data->active_buf,
input_data->rel_cur_pos, i);
	insertn_chars(input_data, input_data->build_buf->buf, i, 0);
	return (0);
}

int		handle_capabilities(t_input_data *input_data, t_list *hist_copy)
{
	t_cur_abs_pos copy_pos;
	if (ft_strncmp(input_data->build_buf->buf, KEY_NL, 1) == 0 && (input_data->processed_chars = 1))
	{
		get_cursor_position(&copy_pos, input_data->active_buf, input_data->active_buf->len ,input_data->start_pos);
		if (tputs(tgoto(tgetstr("cm", NULL), copy_pos.col, copy_pos.row), 1, ft_putchar) != 0)
			return (1);
		insert_dyn_buf("\n", input_data->active_buf, input_data->active_buf->len);
		write(1, "\n", 1);
		input_data->rel_cur_pos = input_data->active_buf->len;
		input_data->enter = 1;
	}
	else if (ft_strncmp(input_data->build_buf->buf, ALT_ARROW_RIGHT, 4) == 0 && (input_data->processed_chars = 4))
	{
		move_to_next_word(input_data);
	}
	else if (ft_strncmp(input_data->build_buf->buf, ALT_ARROW_LEFT, 4) == 0&& (input_data->processed_chars = 4))
	{
		move_to_prev_word(input_data);
	}
	else if (ft_strncmp(input_data->build_buf->buf, ALT_ARROW_UP, 4) == 0 && (input_data->processed_chars = 4))
	{
		move_up(input_data);
	}
	else if (ft_strncmp(input_data->build_buf->buf, ALT_ARROW_DOWN, 4) == 0&& (input_data->processed_chars = 4))
	{
		move_down(input_data);
	}
	else if ((ft_strncmp(input_data->build_buf->buf, KEY_BS, 1) == 0 || ft_strncmp(input_data->build_buf->buf, KEY_BS2, 1) == 0) && (input_data->processed_chars = 1))
	{
		if (delete_prev_char(input_data) != 0)
			return (1);
	}
	else if (ft_strncmp(input_data->build_buf->buf, KEY_TAB, 1) == 0 && (input_data->processed_chars = 1))
	{
		insert_dyn_buf(" ", input_data->active_buf, input_data->rel_cur_pos);
		insertn_chars(input_data, " ", 1, 0);
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
		history_navigate(input_data, hist_copy, HIST_NEXT);
		print_anew(input_data, &copy_pos);
		update_start_position(input_data->active_buf, input_data->start_pos);
	}
	else if (ft_strncmp(input_data->build_buf->buf, KEY_ARROW_DOWN, 3) == 0 && (input_data->processed_chars = 3))
	{
		history_navigate(input_data, hist_copy, HIST_PREV);
		print_anew(input_data, &copy_pos);
		update_start_position(input_data->active_buf, input_data->start_pos);
	}
	else if ((ft_strncmp(input_data->build_buf->buf, KEY_DEL, 4) == 0) && (input_data->processed_chars = 4))
		delete_cur_char(input_data);
	else if ((ft_strncmp(input_data->build_buf->buf, KEY_NP, 1) == 0) && (input_data->processed_chars = 1))
	{
		input_data->start_pos->row = 0;
		print_anew(input_data, &copy_pos);
	}
	else
		input_data->processed_chars = count_escape_chars(input_data->build_buf->buf);
	return (0);
}


int		get_buf(t_dyn_buf *build_buf)
{
	char	buf[READ_SIZE + 1];
	ssize_t	ret;

	ret = READ_SIZE;
	ft_bzero(buf, READ_SIZE + 1);
	ret = read(0, &buf, READ_SIZE);
	dprintf(2, "LEN = %zu, char = %hho\n", ft_strlen(buf), buf[0]);
	if (ret == -1 || insert_dyn_buf(buf, build_buf, build_buf->len) != 0)
		return (1);
	else if (ret == 0)
		return (0);
	return (0);
}

#define NONE 0
#define SIMPLE 1
#define DOUBLE 2

int		are_quotes_closed(t_dyn_buf *dyn_buf, char *here_doc)
{
	int		opened;
	size_t	i;
	int		quote_type;

	if (here_doc != NULL)
		return (ft_strstr(dyn_buf->buf, here_doc) != NULL);
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

int		output_is_ready(t_dyn_buf *dyn_buf, char *here_doc)
{
	int		ready_state;

	ready_state = true;
	ready_state &= (dyn_buf->len > 0 && dyn_buf->buf[dyn_buf->len - 1] == '\n');
	ready_state &= are_quotes_closed(dyn_buf, here_doc);
	return (ready_state);
}

int		handle_input(t_sh_state *sh_state, t_input_data *input_data, char *here_doc)
{
	t_list	*hist_copy;

	hist_copy = ft_lstdup(input_data->history_list);
	while (input_data->sig_call == 0 && (input_data->active_buf->len == 0 || input_data->stored_buf->len > 0))
	{
		if (ask_start_position(input_data->start_pos) == 1)
			return (1);
		print_prompt(input_data->stored_buf->len > 0 ? PROMPT_MULTI : PROMPT_SIMPLE);
		input_data->rel_cur_pos = 0;
		while (input_data->sig_call == 0 && sh_state->exit_sig == 0 && (input_data->active_buf->len == 0 ||
	input_data->enter == 0))
		{
			if (input_data->build_buf->len == 0)
			{
				if (get_buf(input_data->build_buf) == 1)
					return (1);
			}
			if (is_sig(input_data->build_buf->buf) == 1)
			{
				if (handle_sig(input_data, sh_state) == 1)
					return (1);
			}
			else if (is_capability(input_data->build_buf->buf) == 1)
			{
				if (handle_capabilities(input_data, hist_copy) == 1)
					return (1);
			}
			else
			{
				if (handle_insertion(input_data) == -1)
					return (1);
			}
			if (input_data->processed_chars > 0)
			{
				shift_dyn_buf(input_data->build_buf, input_data->processed_chars);
				input_data->processed_chars = 0;
			}
		}
		input_data->enter = 0;
		dprintf(2, "OUT sigcall = %zu\n", input_data->sig_call);
		if (input_data->stored_buf->len > 0)
		{
			insert_dyn_buf(input_data->stored_buf->buf, input_data->active_buf, 0);
			reset_dyn_buf(input_data->stored_buf);
		}
		if (output_is_ready(input_data->active_buf, here_doc) == false)
			ft_swap((void **)(&(input_data->active_buf)), (void **)(&(input_data->stored_buf)));
	}
	if (input_data->active_buf->len > 0 && input_data->active_buf->buf[0] != '\n')
		add_to_history_list(&(input_data->history_list), input_data->active_buf->buf, input_data->active_buf->len);
	if (input_data->sig_call == 1)
	{
		if (input_data->active_buf->len > 0 && input_data->active_buf->buf[0] != '\n')
			add_to_history_list(&(input_data->history_list), input_data->active_buf->buf, input_data->active_buf->len + 1);
		else if (input_data->stored_buf->len > 0 && input_data->stored_buf->buf[0] != '\n')
			add_to_history_list(&(input_data->history_list), input_data->stored_buf->buf, input_data->stored_buf->len + 1);
		reset_input(input_data);
		input_data->sig_call = 0;
	}
	history_navigate(input_data, hist_copy, HIST_RESET);
	return (0);
}
