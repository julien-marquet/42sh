#include "builtins/builtin_hash/builtin_hash.h"
#include "storage/storage.h"

t_hash_table	*get_link(t_list **table, char *bin)
{
	t_list	*pointer;

	pointer = *table;
	while (pointer != NULL)
	{
		if (ft_strcmp(((t_hash_table *)(pointer->content))->bin, bin) == 0)
			return (pointer->content);
		pointer = pointer->next;
	}
	return (NULL);
}

void	delete_table(t_list **table)
{
	t_list	*pointer;
	void	*previous;

	pointer = *table;
	while (pointer != NULL)
	{
		free(((t_hash_table *)(pointer->content))->bin);
		free(((t_hash_table *)(pointer->content))->path);
		free(pointer->content);
		previous = pointer;
		pointer = pointer->next;
		free(previous);
	}
	*table = NULL;
}

char			*append_bin(char *bin, t_list **table, t_list *internal_storage, size_t *found)
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
			return (add_path(tmp, table, bin, *found == 2));
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
	found = 2;
	if (pointer == NULL)
	{
		if ((path = append_bin(av[0], table, internal_storage, &found)) == NULL)
		{
			if (found)
				return (path);
			else
				*error = 1;
		}
		return (NULL);
	}
	((t_hash_table *)pointer->content)->hits += 1;
	return (((t_hash_table *)pointer->content)->path);
}
