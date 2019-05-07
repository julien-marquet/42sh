/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   getters.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/23 20:46:24 by legrivel     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/05 17:26:26 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "editing/input/completion/completion.h"

static size_t	should_stop(t_input_data *input, char **pointer, size_t *i)
{
	if (is_stopping(**pointer) && *((*pointer) - 1) != '\\')
	{
		*i -= 1;
		return (1);
	}
	if ((**pointer == '\'' && !is_closed(*pointer, input->active_buf->buf)) ||
		(**pointer == '"' && !is_closed(*pointer, input->active_buf->buf)) ||
		(**pointer == '`' && !is_closed(*pointer, input->active_buf->buf)))
	{
		*i -= 1;
		*pointer += 1;
		return (1);
	}
	return (0);
}

size_t			get_var_name_length(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '=')
		i += 1;
	return (i);
}

char			*dup_path(t_input_data *input,
		char *pointer, char old, char old2)
{
	char	*tmp;

	if (*(pointer + 1) == '\0' ||
		(ft_strrchr(input->active_buf->buf, '/') ==
		input->active_buf->buf && old2 == 0))
		tmp = ft_strdup("/");
	else if (ft_strcmp(pointer, "./") == 0)
		tmp = ft_strdup("./");
	else
		tmp = ft_strdup(*pointer == '/' ? pointer : pointer + 1);
	input->active_buf->buf[input->rel_cur_pos] = old;
	while (old2 != 0)
	{
		if (*pointer == '\0')
		{
			*pointer = old2;
			break ;
		}
		pointer += 1;
	}
	return (tmp);
}

char			*get_path(t_input_data *input,
size_t get_all, t_sh_state *state)
{
	char	old;
	char	old2;
	char	*pointer;

	old2 = 0;
	old = input->active_buf->buf[input->rel_cur_pos];
	input->active_buf->buf[input->rel_cur_pos] = '\0';
	pointer = input->active_buf->buf + input->rel_cur_pos;
	while (pointer != input->active_buf->buf)
	{
		if (is_stopping(*pointer) && *(pointer - 1) != '\\')
			break ;
		if (*pointer == '/' && old2 == 0)
		{
			if (!get_all)
			{
				old2 = *pointer;
				*pointer = '\0';
			}
		}
		pointer -= 1;
	}
	if ((pointer = dup_path(input, pointer, old, old2)) == NULL)
		return (NULL);
	return (handle_expand(pointer, state));
}

char			*get_current_word(t_input_data *input, t_sh_state *sh_state)
{
	size_t	i;
	char	*word;
	char	*pointer;

	i = 0;
	pointer = input->active_buf->buf + input->rel_cur_pos;
	while (pointer != input->active_buf->buf)
	{
		if (should_stop(input, &pointer, &i))
			break ;
		i += 1;
		pointer -= 1;
	}
	if ((word = malloc(i + 1)) == NULL)
		return (NULL);
	ft_strncpy(word, input->active_buf->buf + input->rel_cur_pos - i, i);
	word[i] = '\0';
	if (vars_match(sh_state->internal_storage, word) > 1)
		return (handle_quotes(word));
	return (handle_expand(word, sh_state));
}
