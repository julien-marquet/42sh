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

// TODO free `completed` on error
static int	complete_word(t_input_data *input, char *completed)
{
	char	*pointer;

	if (completed == NULL)
		return (1);
	pointer = input->active_buf->buf + input->rel_cur_pos - 1;
	while (pointer != input->active_buf->buf)
	{
		if (*pointer == '/' || (*pointer == ' ' && *(pointer - 1) != '\\'))
			break ;
		if (delete_prev_char(input) == 1)
			return (1);
		pointer -= 1;
	}
	if (insertn_dyn_buf(completed, input->active_buf, input->rel_cur_pos, ft_strlen(completed)) == 1)
		return (1);
	if (insertn_chars(input, completed, ft_strlen(completed), 0) == 1)
		return (1);
	// TODO If completed is a dir, add a /
	free(completed);
	return (0);
}

static int	find_in_dir(t_input_data *input, char *path,
		char *needle, size_t action)
{
	size_t			len;
	char			*tmp;
	DIR				*dir;
	size_t			match;
	struct dirent	*entry;

	if ((dir = opendir(path)) == NULL)
		return (0);
	match = 0;
	len = ft_strlen(needle);
	while ((entry = readdir(dir)) != NULL)
	{
		if (ft_strncmp(entry->d_name, needle, len) == 0)
		{
			if (action == 0)
				match += 1;
			else if (action == 1)
			{
				tmp = ft_strdup(entry->d_name);
				closedir(dir);
				return (complete_word(input, tmp));
			}
			else if (action == 2)
				dprintf(2, "%s\n", entry->d_name);
		}
	}
	closedir(dir);
	if (action == 0 && match > 0)
		return (find_in_dir(input, path, needle, match > 1 ? 2 : 1));
	return (0);
	/* free(path); */
	/* free(needle); */
}

static int	complete_arg(t_input_data *input, char *word)
{
	size_t	i;
	size_t	len;

	len = ft_strlen(word);
	if (word[len - 1] == '/')
		return (find_in_dir(input, word, "", 2));
	else
	{
		// TODO If word length is 0
		i = len;
		word += len - 1;
		while (!is_stopping(*word))
		{
			if (*word == '/' || (*word == '\\' && *(word - 1) != '\\'))
				return (find_in_dir(input, ft_strndup(word - (i - 1), i), word + 1, 0));
			i -= 1;
			word -= 1;
		}
	}
	return (0);
}

static int	complete_bin(t_input_data *input, char *word)
{
	(void)input;
	(void)word;
	return (0);
}

static int	handle_completion_type(t_input_data *input, char *word)
{
	char	*pointer;

	pointer = input->active_buf->buf + input->rel_cur_pos;
	while (pointer != input->active_buf->buf)
	{
		if (is_stopping(*pointer) && *(pointer - 1) != '\\')
			return (complete_arg(input, word));
		pointer -= 1;
	}
	return (complete_bin(input, word));
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
	return (handle_completion_type(input, currentWord));
}
