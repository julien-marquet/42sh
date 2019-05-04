/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   completion.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/23 22:11:38 by legrivel     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/29 16:48:31 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "editing/input/completion/completion.h"
#include "editing/input/input_action_handlers.h"

static int	add_brace(char **completed)
{
	size_t	len;
	char	*tmp;

	tmp = *completed;
	len = ft_strlen(tmp);
	if ((*completed = malloc(len + 2)) == NULL)
		return (-1);
	ft_strncpy(*completed, tmp, len);
	free(tmp);
	(*completed)[len] = '}';
	(*completed)[len + 1] = '\0';
	return (0);
}

// TODO free `completed` on error
int			complete_word(t_input_data *input,
char *completed, size_t add_slash, t_sh_state *state)
{
	int		ret;
	char	*path;

	if (completed == NULL)
		return (1);
	if ((ret = delete_completed(input)) == 1)
		return (1);
	if (ret == 2)
		if (add_brace(&completed) == -1)
			return (1);
	if (insert_dyn_buf(completed, input->active_buf,
		input->rel_cur_pos) == 1)
		return (1);
	if (insertn_chars(input, completed, ft_strlen(completed), 0) == 1)
		return (1);
	if (add_slash)
	{
		if ((path = get_path(input, 1, state)) == NULL)
			return (1);
		if (is_dir(path))
		{
			free(path);
			path = ft_strjoin(completed, "/");
			free(completed);
			return (complete_word(input, path, 0, state));
		}
		free(path);
	}
	free(completed);
	return (0);
}

static int	complete_arg_word(t_input_data *input,
t_sh_state *state, char *word, size_t len)
{
	size_t	i;
	char	*tmp;

	i = len;
	word += len - 1;
	while (i > 0)
	{
		if (*word == '/' || (*word == '\\' && *(word - 1) != '\\'))
		{
			if ((tmp = get_path(input, 0, state)) == NULL)
				return (1);
			if (find_in_dir(get_files(tmp, word + 1,
				CHK_NONE, state->internal_storage, NULL), input, word + 1, state) == 1)
				return (1);
			free(tmp);
			return (0);
		}
		i -= 1;
		if (i > 0)
			word -= 1;
	}
	return (find_in_dir(get_files(".", word,
*word == '$' ? CHK_VARS : CHK_NONE, state->internal_storage, NULL), input, word, state));
}

// TODO Free files on error
int			complete_arg(t_input_data *input, char *word, t_sh_state *state)
{
	size_t	len;
	char	*tmp;

	len = ft_strlen(word);
	if (len == 0)
		return (find_in_dir(get_files(".", "",
		CHK_NONE, state->internal_storage, NULL), input, "", state));
	else if (word[len - 1] == '/')
	{
		if ((tmp = get_path(input, 0, state)) == NULL)
			return (1);
		if (find_in_dir(get_files(tmp, "",
			CHK_NONE, state->internal_storage, NULL), input, "", state) == 1)
			return (1);
		free(tmp);
	}
	else
		return (complete_arg_word(input, state, word, len));
	return (0);
}

int			complete_bin(char *word, t_sh_state *sh_state, t_input_data *input)
{
	char	*tmp;
	t_list	*files;
	char	**paths;
	char	**pointer;

	if (is_path(word))
		return (complete_arg(input, word, sh_state));
	if ((tmp = get_env_value(sh_state->internal_storage, "PATH")) == NULL)
		tmp = "";
	if ((paths = ft_strsplit(tmp, ':')) == NULL)
		return (1);
	files = NULL;
	pointer = paths;
	while (*pointer != NULL)
	{
		lstmerge(&files, get_files(*pointer, word,
		CHK_NONE, sh_state->internal_storage, files));
		pointer += 1;
	}
	lstmerge(&files, get_files(NULL, word, *word == '$' ?
	CHK_BUILTINS | CHK_VARS : CHK_BUILTINS, sh_state->internal_storage, files));
	find_in_dir(files, input, word, sh_state);
	ft_freetab(&paths);
	return (0);
}
