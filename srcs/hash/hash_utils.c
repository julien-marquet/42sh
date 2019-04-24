/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   hash_utils.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/15 22:15:24 by legrivel     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/21 22:32:40 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "hash/hash_utils.h"
#include "builtins/builtins_utils.h"

int			test_bin(char *bin_path)
{
	struct stat	f_stat;

	if (bin_path == NULL)
		return (-1);
	if (access(bin_path, F_OK) == -1)
		return (1);
	if (stat(bin_path, &f_stat) == -1)
		return (-1);
	if (!S_ISREG(f_stat.st_mode))
		return (3);
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
		free(content.path);
		return (NULL);
	}
	if (*table == NULL)
		*table = tmp;
	else
		ft_lstadd(table, tmp);
	return (content.path);
}

int			not_found(char *bin)
{
	write(2, "-", 1);
	write(2, NAME, ft_strlen(NAME));
	write(2, ": hash: ", 8);
	write(2, bin, ft_strlen(bin));
	write(2, ": not found\n", 12);
	return (1);
}

void		handle_bin_error(int error, char *path)
{
	char	*str;
	char	*origin;

	str = NULL;
	origin = NULL;
	if (add_origin(&origin, NAME) == 1)
		return ;
	if (error == 0)
		str = ft_construct_str(2, path, ": command not found\n");
	else if (error == 1)
		str = ft_construct_str(2, path, ": permission denied\n");
	else if (error == 2)
		str = ft_construct_str(2, path, ": is not a regular file\n");
	if (str != NULL)
	{
		print_error(origin, str, 2);
		free(str);
	}
	free(origin);
}
