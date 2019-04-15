#include "builtins/builtin_hash/builtin_hash.h"

int		test_bin(char *bin_path)
{
	if (bin_path == NULL)
		return (-1);
	if (access(bin_path, F_OK) == -1)
		return (1);
	if (access(bin_path, X_OK) == -1)
		return (2);
	return (0);
}

char		*create_path(char *path, char *bin)
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

char		*add_path(char *path, t_list **table, char *bin, size_t inc_hits)
{
	t_list			*tmp;
	t_hash_table	content;
	t_list			*pointer;

	content.hits = inc_hits;
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

char		*permission_denied(char *path)
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
