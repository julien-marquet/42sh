/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   treate.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/23 20:19:25 by legrivel     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/05 17:42:54 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "editing/input/completion/completion.h"
#include "editing/input/input_action_handlers.h"

static void	write_file(char *file)
{
	write(1, file, ft_strlen(file));
	write(1, "\t", 1);
}

static char	*get_completion(t_list *files)
{
	size_t	i;
	char	*tmp;
	t_list	*pointer;

	tmp = NULL;
	pointer = files;
	while (pointer != NULL)
	{
		if (tmp == NULL && (tmp = ft_strdup(pointer->content)) == NULL)
			return (NULL);
		else if (tmp != NULL)
		{
			i = 0;
			while (((char *)pointer->content)[i] == tmp[i] &&
				((char *)pointer->content)[i] != '\0' && tmp[i] != '\0')
				i += 1;
			if (tmp[i] != '\0')
			{
				free(tmp);
				tmp = ft_strndup(pointer->content, i);
			}
		}
		pointer = pointer->next;
	}
	return (tmp);
}

static int	print_files(t_list *files, t_input_data *input)
{
	t_cur_abs_pos	pos;
	t_list			*pointer;

	pointer = files;
	if (pointer != NULL)
		write(1, "\n", 1);
	while (pointer != NULL)
	{
		write_file(pointer->content);
		pointer = pointer->next;
	}
	if (files != NULL)
	{
		write(1, "\n", 1);
		print_prompt(0);
		write(1, input->active_buf->buf, ft_strlen(input->active_buf->buf));
		if (get_cursor_position(&pos, input->active_buf,
			input->rel_cur_pos, input->start_pos) == 1)
			return (1);
		tputs(tgoto(tgetstr("cm", NULL), pos.col, pos.row), 1, ft_putchar);
	}
	return (0);
}

static int	half_complete(t_list *files, t_input_data *input,
char *needle, t_sh_state *state)
{
	char			*tmp;

	if ((tmp = get_completion(files)) == NULL)
		return (1);
	if (ft_strncmp(needle, "${", 2) == 0)
		needle += 2;
	else if (ft_strncmp(needle, "$", 1) == 0)
		needle += 1;
	if (ft_strcmp(needle, tmp) != 0)
	{
		if (complete_word(input, tmp, 0, state) == 1)
			return (1);
	}
	else
	{
		free(tmp);
		return (print_files(files, input));
	}
	return (0);
}

int			find_in_dir(t_list *files, t_input_data *input,
char *needle, t_sh_state *state)
{
	char	*path;
	int		res;

	res = 0;
	if (files == NULL)
	{
		if ((path = get_path(input, 1, state)) == NULL)
			res = 1;
		else if (is_dir(path) && path[ft_strlen(path) - 1] != '/' &&
(insert_dyn_buf("/", input->active_buf, input->rel_cur_pos) == 1 ||
insertn_chars(input, "/", 1, 0) == 1))
			res = 1;
		ft_strdel(&path);
		return (res);
	}
	if (files->next == NULL)
	{
		if (complete_word(input, ft_strdup(files->content), 1, state) == 1)
			res = 1;
	}
	else if (half_complete(files, input, needle, state) == -1)
		res = 1;
	lstfree(files);
	return (res);
}
