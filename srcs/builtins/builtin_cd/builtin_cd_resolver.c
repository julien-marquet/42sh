/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtin_cd_resolver.c                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/05 15:19:03 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/05 15:23:49 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "builtins/builtin_cd/builtin_cd.h"

static char	*resolve(t_sh_state *state, char *path)
{
	ssize_t	len;
	char	*tmp;
	char	buf[_POSIX_PATH_MAX];

	if (path == NULL)
		return (NULL);
	if ((len = readlink(path, buf, _POSIX_PATH_MAX - 1)) == -1)
	{
		ft_strdel(&path);
		return (NULL);
	}
	tmp = ft_strrchr(path, '/');
	tmp[1] = '\0';
	tmp = path;
	buf[len] = '\0';
	if ((path = ft_construct_str(3, path, buf, "/")) == NULL)
		return (NULL);
	free(tmp);
	if (make_path_absolute(state, &path) != 0)
		return (NULL);
	return (path);
}

static char	*rejoin_path(char **arr)
{
	char	*tmp;
	char	*path;

	path = NULL;
	while (*arr && *(arr + 1))
	{
		if (path == NULL && (path = ft_strjoin(*arr, *(arr + 1))) == NULL)
			return (NULL);
		else if (path != NULL)
		{
			tmp = path;
			if ((path = ft_strjoin(*arr, *(arr + 1))) == NULL)
				return (NULL);
			free(tmp);
		}
		arr += 1;
	}
	if (path == NULL)
		return (*arr == NULL ? ft_strdup("") : ft_strdup(*arr));
	tmp = path;
	path = ft_strjoin(path, *arr);
	free(tmp);
	return (path);
}

char		*resolve_links(t_sh_state *state, char *base, char **path)
{
	char	*tmp;
	char	**dirs;
	char	**pointer;

	if ((dirs = get_dirs(base, *path, &pointer)) == NULL)
		return (NULL);
	while (*pointer)
	{
		if (verify_new(&base, *pointer, &tmp, &dirs) == 1)
		{
			ft_strdel(path);
			*path = rejoin_path(pointer + 1);
			ft_freetab(&dirs);
			return (resolve_links(state, resolve(state, tmp), path));
		}
		if ((base = ft_strjoin(tmp, "/")) == NULL)
			return (NULL);
		ft_strdel(&tmp);
		pointer += 1;
	}
	return (resolve_free(base, dirs));
}
