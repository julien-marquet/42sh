/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   utils2.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/23 21:34:51 by legrivel     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/05 17:43:19 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "editing/input/completion/completion.h"
#include "editing/input/input_action_handlers.h"

int			delete_completed(t_input_data *input)
{
	char *pointer;

	pointer = input->active_buf->buf + input->rel_cur_pos - 1;
	while (pointer != input->active_buf->buf)
	{
		if ((*pointer == '/') ||
			(is_stopping(*pointer) && *(pointer - 1) != '\\'))
			break ;
		if (((*pointer == '{' && *(pointer - 1) == '$' &&
			(is_stopping(*(pointer - 2)) && *(pointer - 3) != '\\'))) ||
(*pointer == '$' && (is_stopping(*(pointer - 1)) && *(pointer - 2) != '\\')))
			break ;
		if (delete_prev_char(input) == 1)
			return (1);
		if (*(pointer - 1) == '$' && pointer - 1 == input->active_buf->buf)
			break ;
		pointer -= 1;
	}
	if (pointer == input->active_buf->buf && *pointer != '/')
		return (delete_prev_char(input));
	if (*pointer == '{' && *(pointer - 1) == '$')
		return (2);
	return (0);
}

size_t		is_path(const char *word)
{
	char	*pointer;

	pointer = (char *)word;
	while (*pointer)
	{
		if (*pointer == '/' &&
			(pointer == word || *(pointer - 1) != '\\'))
			return (1);
		pointer += 1;
	}
	return (0);
}

size_t		vars_match(t_list *storage, char *needle)
{
	size_t	i;

	i = 0;
	if (ft_strlen(needle) == 0)
		return (0);
	needle = ft_strncmp(needle, "${", 2) == 0 ? needle + 2 : needle + 1;
	while (storage != NULL)
	{
		if (ft_strncmp(((t_internal_storage *)(storage->content))->string,
			needle, ft_strlen(needle)) == 0)
			i += 1;
		storage = storage->next;
	}
	return (i);
}

int			f_add_slash(char **path, t_input_data *input,
char **completed, t_sh_state *state)
{
	if ((*path = get_path(input, 1, state)) == NULL)
	{
		ft_strdel(completed);
		return (1);
	}
	if (is_dir(*path))
	{
		ft_strdel(path);
		*path = ft_strjoin(*completed, "/");
		ft_strdel(completed);
		return (complete_word(input, *path, 0, state));
	}
	ft_strdel(path);
	ft_strdel(completed);
	return (0);
}

t_gf_data	build_gf(char *path, char *needle)
{
	t_gf_data	gf_data;

	gf_data.needle = needle;
	gf_data.path = path;
	return (gf_data);
}
