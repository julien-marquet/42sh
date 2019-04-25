/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   handlers.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: legrivel <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/23 19:52:30 by legrivel     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/23 19:52:31 by legrivel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "parse/parse.h"
#include "editing/input/completion/completion.h"

static int		handle_completion_type(t_input_data *input,
t_sh_state *sh_state, char *word)
{
	char	*pointer;

	pointer = input->active_buf->buf + input->rel_cur_pos;
	while (pointer != input->active_buf->buf)
	{
		if (is_stopping(*pointer) && *(pointer - 1) != '\\')
		{
			if (*pointer == ' ')
				return (complete_arg(input, word, sh_state));
			else
				return (complete_bin(word, sh_state, input));
		}
		pointer -= 1;
	}
	return (complete_bin(word, sh_state, input));
}

static size_t	is_quoting(char **tmp, size_t *quoting, char *trimmed)
{
	if ((*tmp != trimmed && *((*tmp) - 1) != '\\') || *tmp == trimmed)
	{
		if (**tmp == '"' && (*quoting == 0 || *quoting == 1))
		{
			*quoting = *quoting == 1 ? 0 : 1;
			*tmp += 1;
			return (1);
		}
		if (**tmp == '\'' && (*quoting == 0 || *quoting == 2))
		{
			*quoting = *quoting == 2 ? 0 : 2;
			*tmp += 1;
			return (1);
		}
		if (**tmp == '`' && (*quoting == 0 || *quoting == 3))
		{
			*quoting = *quoting == 3 ? 0 : 3;
			*tmp += 1;
			return (1);
		}
	}
	return (0);
}

static char		*handle_quotes(char *word)
{
	char	*tmp;
	char	*final;
	size_t	quoting;
	char	*trimmed;
	char	*pointer;

	quoting = 0;
	trimmed = trim(word);
	tmp = trimmed;
	if ((final = malloc(ft_strlen(trimmed) + 1)) == NULL)
		return (NULL);
	pointer = final;
	while (*tmp)
	{
		if (is_quoting(&tmp, &quoting, trimmed))
			continue ;
		*pointer = *tmp;
		pointer += 1;
		tmp += 1;
	}
	*pointer = '\0';
	free(word);
	return (final);
}

char			*handle_expand(char *word, t_sh_state *sh_state)
{
	char	*pointer;
	char	*current_word;

	if (*word == '\0')
	{
		free(word);
		return (ft_strdup(""));
	}
	if ((current_word = get_expand_str(word, sh_state)) == NULL)
		return (NULL);
	pointer = current_word;
	while (*pointer == ' ')
		pointer += 1;
	if (*pointer == '\0')
	{
		free(current_word);
		current_word = word;
	}
	else
		free(word);
	return (handle_quotes(current_word));
}

int				handle_completion(t_input_data *input, t_sh_state *sh_state)
{
	char	*pointer;
	char	*current_word;

	pointer = input->active_buf->buf;
	while (*pointer == ' ')
		pointer += 1;
	if (*pointer == '\0')
		return (0);
	if ((current_word = get_current_word(input, sh_state)) == NULL)
		return (1);
	if (handle_completion_type(input, sh_state, current_word) == 1)
	{
		free(current_word);
		return (1);
	}
	free(current_word);
	return (0);
}