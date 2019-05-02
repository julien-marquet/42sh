/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   getters2.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/23 21:34:17 by legrivel     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/25 05:51:06 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "editing/input/completion/completion.h"
#include "editing/input/input_action_handlers.h"

int			get_builtins(t_list **files, char *needle)
{
	size_t		i;
	size_t		len;
	t_list		*link;
	const char	**builtins;

	i = 0;
	builtins = get_builtins_names();
	len = ft_strlen(needle);
	while (i < BUILTINS_NB)
	{
		if (ft_strncmp(builtins[i], needle, len) == 0)
		{
			if ((link =
		ft_lstnew(builtins[i], ft_strlen(builtins[i]) + 1)) == NULL)
				return (free_exit(*files, NULL));
			if (*files == NULL)
				*files = link;
			else
				ft_lstadd(files, link);
		}
		i += 1;
	}
	return (0);
}

int			get_vars(t_list **files, t_list *storage, char *needle)
{
	size_t	len;
	char	*tmp;
	char	*name;
	t_list	*link;

	needle = ft_strncmp(needle, "${", 2) == 0 ? needle + 2 : needle + 1;
	while (storage != NULL)
	{
		name = ((t_internal_storage *)(storage->content))->string;
		len = get_var_name_length(name);
		if (ft_strncmp(name, needle, ft_strlen(needle)) == 0)
		{
			if ((tmp = malloc(len + 1)) == NULL)
				return (free_exit(*files, NULL));
			ft_strncpy(tmp, name, len);
			tmp[len] = '\0';
			if ((link = ft_lstnew(tmp, len + 1)) == NULL)
				return (free_exit(*files, tmp));
			free(tmp);
			if (*files == NULL)
				*files = link;
			else
				ft_lstadd(files, link);
		}
		storage = storage->next;
	}
	return (0);
}

static int	fill_list(t_list **files, DIR *dir, char *needle)
{
	size_t			len;
	t_list			*link;
	struct dirent	*entry;

	len = ft_strlen(needle);
	while ((entry = readdir(dir)) != NULL)
	{
		if (ft_strncmp(entry->d_name, needle, len) == 0)
		{
			if ((ft_strcmp(entry->d_name, ".") == 0 ||
			ft_strcmp(entry->d_name, "..") == 0) && ft_strcmp(needle, ".") != 0)
				continue ;
			if ((link =
				ft_lstnew(entry->d_name, ft_strlen(entry->d_name) + 1)) == NULL)
				return (free_exit(*files, NULL));
			if (*files == NULL)
				*files = link;
			else
				ft_lstadd(files, link);
		}
	}
	return (0);
}

t_list		*get_files(char *path, char *needle,
	int flags, t_list *internal_storage)
{
	DIR		*dir;
	t_list	*files;

	files = NULL;
	if (flags & CHK_BUILTINS && get_builtins(&files, needle) == 1)
		return (NULL);
	if (flags & CHK_VARS && get_vars(&files, internal_storage, needle) == 1)
		return (NULL);
	if (path == NULL)
		return (files);
	if ((dir = opendir(path)) == NULL)
		return (NULL);
	if (fill_list(&files, dir, needle) == 1)
		return (NULL);
	closedir(dir);
	return (files);
}
