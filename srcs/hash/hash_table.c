/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   hash_table.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/15 22:42:12 by legrivel     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/21 22:30:54 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "hash/hash_table.h"

static char		*check_paths(char **paths, char *bin,
			t_list **table, size_t *error)
{
	int		ret;
	char	*tmp;
	char	**pointer;

	pointer = paths;
	while (*pointer != NULL)
	{
		tmp = create_path(*pointer, bin);
		if ((ret = test_bin(tmp)) == -1)
			return (NULL);
		if (ret == 0)
			return (add_path(tmp, table, bin, *error != 0));
		else if (ret == 2 && *error == 4)
			*error = 1;
		else if (ret == 3 && *error == 4)
			*error = 2;
		free(tmp);
		pointer += 1;
	}
	return ("");
}

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

void			delete_table(t_list **table)
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

char			*append_bin(char *bin, t_list **table,
			t_list *internal_storage, size_t *error)
{
	char	*tmp;
	char	**paths;

	if ((tmp = get_env_value(internal_storage, "PATH")) == NULL)
		tmp = "";
	if ((paths = ft_strsplit(tmp, ':')) == NULL)
		return (NULL);
	tmp = check_paths(paths, bin, table, error);
	if (*error != 4)
		return (NULL);
	ft_freetab(&paths);
	if (tmp == NULL)
		return (NULL);
	if (tmp[0] != '\0')
		return (tmp);
	*error = 0;
	return (NULL);
}

char			*get_bin_path(char **av, t_list **table,
			t_list *internal_storage, size_t *error)
{
	char	*path;
	t_list	*pointer;

	*error = 0;
	pointer = *table;
	while (pointer != NULL &&
	ft_strcmp(av[0], ((t_hash_table *)(pointer->content))->bin) != 0)
		pointer = pointer->next;
	*error = 4;
	if (pointer == NULL)
	{
		if ((path = append_bin(av[0], table, internal_storage, error)) != NULL)
		{
			if (*error == 4)
				return (path);
		}
		return (NULL);
	}

	((t_hash_table *)pointer->content)->hits += 1;
	return (((t_hash_table *)pointer->content)->path);
}
