#include "editing/input/completion/completion.h"
#include "editing/input/input_action_handlers.h"

// TODO free `completed` on error
int	complete_word(t_input_data *input, char *completed, size_t add_slash)
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
		{
			path = ft_strjoin(completed, "/");
			free(completed);
			return (complete_word(input, path, 0));
		}
		free(path);
	}
	free(completed);
	return (0);
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
			if ((ft_strcmp(entry->d_name, ".") == 0 ||
			ft_strcmp(entry->d_name, "..") == 0) && ft_strcmp(needle, ".") != 0)
				continue ;
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

// TODO Free files on error
int			complete_arg(t_input_data *input, char *word, t_sh_state *state)
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
		lstmerge(&files, get_files(*pointer, word, 0, 0, sh_state->internal_storage));
		pointer += 1;
	}
	lstmerge(&files, get_files(NULL, word, 1, word[0] == '$', sh_state->internal_storage));
	find_in_dir(files, input, word);
	ft_freetab(&paths);
	return (0);
}
