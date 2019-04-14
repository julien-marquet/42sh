#include "builtins/builtin_hash/builtin_hash.h"
#include "storage/storage.h"

static int		test_bin(char *bin_path)
{
	if (bin_path == NULL)
		return (-1);
	if (access(bin_path, F_OK) == -1)
		return (1);
	if (access(bin_path, X_OK) == -1)
		return (2);
	return (0);
}

static char		*create_path(char *path, char *bin)
{
	char	*tmp;
	char	*tmp_path;

	if ((tmp = ft_strjoin(path, "/")) == NULL)
		return (NULL);
	if ((tmp_path = ft_strjoin(tmp, bin)) == NULL)
	{
		free(tmp);
		return (NULL);
	}
	free(tmp);
	return (tmp_path);
}

static char		*add_path(char *path, t_list **table, char *bin)
{
	t_list			*tmp;
	t_hash_table	content;
	t_list			*pointer;

	content.hits = 1;
	if ((content.bin = ft_strdup(bin)) == NULL)
		return (NULL);
	content.path = path;
	pointer = *table;
	while (pointer != NULL && pointer->next != NULL)
		pointer = pointer->next;
	if ((tmp = ft_lstnew(&content, sizeof(t_hash_table))) == NULL)
	{
		free(content.bin);
		return (NULL);
	}
	if (*table == NULL)
		*table = tmp;
	else
		ft_lstadd(table, tmp);
	return (content.path);
}

static char		*permission_denied(char *path)
{
	char	*error;

	error = ft_strjoin("-", NAME);
	if (error != NULL)
		error = ft_strjoin(error, ": ");
	if (error != NULL)
		error = ft_strjoin(error, path);
	if (error != NULL)
		error = ft_strjoin(error, ": Permission denied\n");
	return (error);
}

static char		*search_bin_path(char *bin, t_list **table, t_list *internal_storage, size_t *found)
{
	int		ret;
	char	*tmp;
	char	*error;
	char	**paths;
	char	**pointer;

	if ((tmp = get_env_value(internal_storage, "PATH")) == NULL)
		tmp = "";
	if ((paths = ft_strsplit(tmp, ':')) == NULL)
		return (NULL);
	error = NULL;
	pointer = paths;
	while (*pointer != NULL)
	{
		tmp = create_path(*pointer, bin);
		if ((ret = test_bin(tmp)) == -1)
		{
			ft_freetab(&paths);
			return (NULL);
		}
		if (ret == 0)
		{
			ft_freetab(&paths);
			return (add_path(tmp, table, bin));
		}
		if (ret == 2 && error == NULL)
			error = permission_denied(tmp);
		free(tmp);
		pointer += 1;
	}
	*found = 0;
	if (error != NULL)
		write(2, error, ft_strlen(error));
	ft_strdel(&error);
	ft_freetab(&paths);
	return (NULL);
}

char			*get_bin_path(char **av, t_list **table, t_list *internal_storage, size_t *error)
{
	char	*path;
	size_t	found;
	t_list	*pointer;

	*error = 0;
	pointer = *table;
	while (pointer != NULL && ft_strcmp(av[0], ((t_hash_table *)(pointer->content))->bin) != 0)
		pointer = pointer->next;
	found = 1;
	if (pointer == NULL)
	{
		if ((path = search_bin_path(av[0], table, internal_storage, &found)) == NULL)
		{
			if (found)
				return (path);
			else
				*error = 1;
		}
		return (NULL);
	}
	((t_hash_table *)pointer->content)->hits += 1;
	dprintf(2, "Hits for %s: %zu, path: %s\n", ((t_hash_table *)pointer->content)->bin, ((t_hash_table *)pointer->content)->hits,((t_hash_table *)pointer->content)->path);
	return (((t_hash_table *)pointer->content)->path);
}
