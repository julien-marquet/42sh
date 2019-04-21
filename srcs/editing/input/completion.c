#include "editing/input/input_completion.h"
#include "editing/input/input_action_handlers.h"
#include "parse/parse.h"

static char	*trim(char *str)
{
	char	*trimmed;

	while (*str == ' ')
		str += 1;
	trimmed = str;
	while (*str != ' ' && *str != '\0')
		str += 1;
	*str = '\0';
	return (trimmed);
}

static int	is_reversed_closed(char *str, char *base)
{
	char	c;
	size_t	closed;

	c = *str;
	closed = 0;
	str -= 1;
	while (str != base)
	{
		if (*str == c && *(str - 1) != '\\')
			closed = !closed;
		str -= 1;
	}
	return (closed);
}

static int	is_closed(char *str, char *base)
{
	size_t	quoting;

	if (is_reversed_closed(str, base))
		return (1);
	if (*str == '\'')
		quoting = 1;
	else if (*str == '"')
		quoting = 2;
	else
		quoting = 3;
	str += 1;
	while (*str)
	{
		if (quoting == 1 && *str == '\'' && *(str - 1) != '\\')
			return (1);
		if (quoting == 2 && *str == '"' && *(str - 1) != '\\')
			return (1);
		if (quoting == 3 && *str == '`' && *(str - 1) != '\\')
			return (1);
		str += 1;
	}
	return (0);
}

static char	*handle_quotes(char *word)
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
		if ((tmp != trimmed && *(tmp - 1) != '\\') || tmp == trimmed)
		{
			if (*tmp == '"' && (quoting == 0 || quoting == 1))
			{
				quoting = quoting == 1 ? 0 : 1;
				tmp += 1;
				continue ;
			}
			if (*tmp == '\'' && (quoting == 0 || quoting == 2))
			{
				quoting = quoting == 2 ? 0 : 2;
				tmp += 1;
				continue ;
			}
			if (*tmp == '`' && (quoting == 0 || quoting == 3))
			{
				quoting = quoting == 3 ? 0 : 3;
				tmp += 1;
				continue ;
			}
		}
		*pointer = *tmp;
		pointer += 1;
		tmp += 1;
	}
	*pointer = '\0';
	free(word);
	return (final);
}

static char	*handle_expand(char *word, t_sh_state *sh_state)
{
	char	*pointer;
	char	*currentWord;

	if (*word == '\0')
		return ("");
	if ((currentWord = get_expand_str(word, sh_state)) == NULL)
		return (NULL);
	pointer = currentWord;
	while (*pointer == ' ')
		pointer += 1;
	if (*pointer == '\0')
	{
		free(currentWord);
		currentWord = word;
	}
	else
		free(word);
	return (handle_quotes(currentWord));
}

static int	is_stopping(char str)
{
	return (str == ' ' ||
		str == ';' ||
		str == '|' ||
		str == '&' ||
		str == '>' ||
		str == '<' ||
		str == ':' ||
		str == '+');
}

static char	*get_current_word(t_input_data *input, t_sh_state *sh_state)
{
	size_t	i;
	char	*word;
	char	*pointer;

	i = 0;
	pointer = input->active_buf->buf + input->rel_cur_pos;
	while (pointer != input->active_buf->buf)
	{
		if (is_stopping(*pointer) && *(pointer - 1) != '\\')
		{
			i -= 1;
			break ;
		}
		if ((*pointer == '\'' && !is_closed(pointer, input->active_buf->buf)) ||
			(*pointer == '"' && !is_closed(pointer, input->active_buf->buf)) ||
			(*pointer == '`' && !is_closed(pointer, input->active_buf->buf)))
		{
			i -= 1;
			pointer += 1;
			break ;
		}
		i += 1;
		pointer -= 1;
	}
	if ((word = malloc(i + 1)) == NULL)
		return (NULL);
	ft_strncpy(word, input->active_buf->buf + input->rel_cur_pos - i, i);
	word[i] = '\0';
	return (handle_expand(word, sh_state));
}

static int	delete_completed(t_input_data *input)
{
	char *pointer;

	pointer = input->active_buf->buf + input->rel_cur_pos - 1;
	while (pointer != input->active_buf->buf)
	{
		// TODO ' ' to is_stopping
		if (*pointer == '/' || (*pointer == ' ' && *(pointer - 1) != '\\'))
			break ;
		if ((*pointer == '$' && (*(pointer - 1) == ' ' && *(pointer - 2) != '\\')))
			break ;
		if (delete_prev_char(input) == 1)
			return (1);
		if (*(pointer - 1) == '$' && pointer - 1 == input->active_buf->buf)
			break ;
		pointer -= 1;
	}
	if (pointer == input->active_buf->buf)
		return (delete_prev_char(input));
	return (0);
}

static char	*get_path(t_input_data *input, size_t get_all)
{
	char	old;
	char	old2;
	char	*tmp;
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
	if (*(pointer + 1) == '\0')
		tmp = ft_strdup("/");
	else
		tmp = ft_strdup(pointer + 1);
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

static size_t	is_dir(char *path)
{
	struct stat	stats;

	if (stat(path, &stats) == -1)
		return (0);
	return (S_ISDIR(stats.st_mode));
}

// TODO free `completed` on error
static int	complete_word(t_input_data *input, char *completed, size_t add_slash)
{
	char	*path;

	if (completed == NULL)
		return (1);
	if (delete_completed(input) == 1)
		return (1);
	if (insertn_dyn_buf(completed, input->active_buf, input->rel_cur_pos, ft_strlen(completed)) == 1)
		return (1);
	if (insertn_chars(input, completed, ft_strlen(completed), 0) == 1)
		return (1);
	if (add_slash)
	{
		if ((path = get_path(input, 1)) == NULL)
			return (1);
		if (is_dir(path))
			return (complete_word(input, ft_strjoin(completed, "/"), 0));
		free(path);
	}
	free(completed);
	return (0);
}

static int		lstfree(t_list *list)
{
	t_list	*previous;

	while (list != NULL)
	{
		previous = list;
		list = list->next;
		free(previous->content);
		free(previous);
	}
	return (1);
}

static int		get_builtins(t_list **files, char *needle)
{
	size_t	i;
	size_t	len;
	t_list	*link;
	char	*builtins[BUILTINS_NB] = {
		"set", "env", "setenv", "unsetenv", "unset", "exit", "echo", "export", "test", "[", "alias", "unalias", "jobs", "fg", "hash"
	};
	
	i = 0;
	len = ft_strlen(needle);
	while (i < BUILTINS_NB) {
		if (ft_strncmp(builtins[i], needle, len) == 0)
		{
			if ((link = ft_lstnew(builtins[i], ft_strlen(builtins[i]) + 1)) == NULL)
			{
				lstfree(*files);
				return (1);
			}
			if (*files == NULL)
				*files = link;
			else
				ft_lstadd(files, link);
		}
		i += 1;
	}
	return (0);
}

static size_t	get_var_name_length(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '=')
		i += 1;
	return (i);
}

static int		get_vars(t_list **files, t_list *storage, char *needle)
{
	size_t	len;
	char	*tmp;
	char	*name;
	t_list	*link;

	while (storage != NULL)
	{
		name = ((t_internal_storage *)(storage->content))->string;
		len = get_var_name_length(name);
		if (ft_strncmp(name, needle + 1, ft_strlen(needle + 1)) == 0)
		{
			if ((tmp = malloc(len + 1)) == NULL)
			{
				lstfree(*files);
				return (1);
			}
			ft_strncpy(tmp, name, len);
			tmp[len] = '\0';
			if ((link = ft_lstnew(tmp, len + 1)) == NULL)
			{
				free(tmp);
				lstfree(*files);
				return (1);
			}
			if (*files == NULL)
				*files = link;
			else
				ft_lstadd(files, link);
		}
		storage = storage->next;
	}
	return (0);
}

static t_list	*get_files(char *path, char *needle,
			size_t builtins, size_t vars, t_list *internal_storage)
{
	size_t	len;
	DIR		*dir;
	t_list	*link;
	t_list	*files;
	struct dirent	*entry;

	files = NULL;
	if (builtins && get_builtins(&files, needle) == 1)
		return (NULL);
	if (vars && get_vars(&files, internal_storage, needle) == 1)
		return (NULL);
	if (path == NULL)
		return (files);
	if ((dir = opendir(path)) == NULL)
		return (NULL);
	len = ft_strlen(needle);
	while ((entry = readdir(dir)) != NULL)
	{
		if (ft_strncmp(entry->d_name, needle, len) == 0)
		{
			if ((link = ft_lstnew(entry->d_name, ft_strlen(entry->d_name) + 1)) == NULL)
			{
				lstfree(files);
				return (NULL);
			}
			if (files == NULL)
				files = link;
			else
				ft_lstadd(&files, link);
		}
	}
	closedir(dir);
	return (files);
}

static void	write_file(char *file)
{
	write(1, file, ft_strlen(file));
	write(1, "\t", 1);
}

// TODO Free files on error
static int	find_in_dir(t_list *files, t_input_data *input, char *needle)
{
	size_t	i;
	char	*tmp;
	t_list	*pointer;

	if (files == NULL)
		return (0);
	if (files->next == NULL)
	{
		if (complete_word(input, ft_strdup(files->content), 1) == 1)
			return (1);
	}
	else
	{
		tmp = NULL;
		pointer = files;
		while (pointer != NULL)
		{
			if (tmp == NULL && (tmp = ft_strdup(pointer->content)) == NULL)
				return (1);
			else if (tmp != NULL)
			{
				i = 0;
				while (((char *)pointer->content)[i] == tmp[i] && ((char *)pointer->content)[i] != '\0' && tmp[i] != '\0')
					i += 1;
				if (tmp[i] != '\0')
				{
					free(tmp);
					if ((tmp = ft_strndup(pointer->content, i)) == NULL)
						return (1);
				}
			}
			pointer = pointer->next;
		}
		if (ft_strcmp(needle[0] == '$' ? needle + 1 : needle, tmp) != 0)
		{
			if (complete_word(input, tmp, 0) == 1)
				return (1);
		}
		else
		{
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
			}
		}
	}
	lstfree(files);
	return (0);
	/* free(path); */
	/* free(needle); */
}

static int	complete_arg(t_input_data *input, char *word, t_sh_state *state)
{
	size_t	i;
	size_t	len;
	char	*tmp;

	len = ft_strlen(word);
	if (len == 0)
		return (find_in_dir(get_files(".", "", 0, 0, state->internal_storage), input, ""));
	else if (word[len - 1] == '/')
	{
		if ((tmp = get_path(input, 0)) == NULL)
			return (1);
		dprintf(2, "Tmp: %s\n", tmp);
		if (find_in_dir(get_files(tmp, "", 0, 0, state->internal_storage), input, "") == 1)
			return (1);
		free(tmp);
	}
	else
	{
		i = len;
		word += len - 1;
		while (i > 0)
		{
			if (*word == '/' || (*word == '\\' && *(word - 1) != '\\'))
			{
				if ((tmp = get_path(input, 0)) == NULL)
					return (1);
				if (find_in_dir(get_files(tmp, word + 1, 0, 0, state->internal_storage), input, word + 1) == 1)
					return (1);
				free(tmp);
				return (0);
			}
			i -= 1;
			if (i > 0)
				word -= 1;
		}
		return (find_in_dir(get_files(".", word, 0, word[0] == '$', state->internal_storage), input, word));
	}
	return (0);
}

static void	lstmerge(t_list **list1, t_list *list2)
{
	t_list	*pointer;

	pointer = *list1;
	if (pointer == NULL)
	{
		*list1 = list2;
		return ;
	}
	while (pointer->next != NULL)
		pointer = pointer->next;
	pointer->next = list2;
}

static int	complete_bin(char *word, t_sh_state *sh_state, t_input_data *input)
{
	char	*tmp;
	t_list	*files;
	char	**paths;
	char	**pointer;

	if ((tmp = get_env_value(sh_state->internal_storage, "PATH")) == NULL)
		tmp = "";
	if ((paths = ft_strsplit(tmp, ':')) == NULL)
		return (1);
	files = NULL;
	pointer = paths;
	while (*pointer != NULL)
	{
		lstmerge(&files, get_files(*pointer, word, 0, 0, sh_state->internal_storage));
		pointer += 1;
	}
	lstmerge(&files, get_files(NULL, word, 1, word[0] == '$', sh_state->internal_storage));
	find_in_dir(files, input, word);
	ft_freetab(&paths);
	return (0);
}

static int	handle_completion_type(t_input_data *input, t_sh_state *sh_state, char *word)
{
	char	*pointer;

	pointer = input->active_buf->buf + input->rel_cur_pos;
	while (pointer != input->active_buf->buf)
	{
		if (is_stopping(*pointer) && *(pointer - 1) != '\\')
			return (complete_arg(input, word, sh_state));
		pointer -= 1;
	}
	return (complete_bin(word, sh_state, input));
}

int		handle_completion(t_input_data *input, t_sh_state *sh_state)
{ 
	char	*pointer;
	char	*currentWord;

	pointer = input->active_buf->buf;
	while (*pointer == ' ')
		pointer += 1;
	if (*pointer == '\0')
		return (0);
	if ((currentWord = get_current_word(input, sh_state)) == NULL)
		return (1);
	return (handle_completion_type(input, sh_state, currentWord));
}
