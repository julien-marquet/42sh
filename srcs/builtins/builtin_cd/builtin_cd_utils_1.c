/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtin_cd_utils_1.c                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/05 15:05:18 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/05 15:10:39 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "builtins/builtin_cd/builtin_cd.h" 

int		had_null_paths(char *cdpath, int i)
{
	int	j;
	int	separator;
	int entry;

	separator = 1;
	entry = -1;
	j = 0;
	while (cdpath[j] != '\0')
	{
		if (cdpath[j] != ':')
		{
			if (separator == 1)
			{
				entry++;
				separator = 0;
			}
		}
		separator |= cdpath[j] == ':';
		if (entry == i)
			return (check_for_cons_separator(cdpath, j));
		j++;
	}
	return (0);
}

char	*get_old_pwd(t_sh_state *sh_state, t_builtin_context *context)
{
	char	*res;

	if ((res = ft_strdup(get_env_value(sh_state->internal_storage,
"OLDPWD"))) == NULL)
		print_error(context->origin, "OLDPWD not set", 2);
	return (res);
}

int	is_symbolic_link(char *path)
{
	struct stat	stats;

	if (lstat(path, &stats) == -1)
		return (-1);
	return (S_ISLNK(stats.st_mode));
}

char	**get_dirs(char *base, char *path, char ***pointer)
{
	char	**dirs;

	if (base == NULL || path == NULL)
		return (NULL);
	if ((dirs = ft_strsplit(path, '/')) == NULL)
		return (NULL);
	*pointer = dirs;
	return (dirs);
}

int	verify_new(char **base, char *pointer, char **tmp, char ***dirs)
{
	int		res;

	if ((*tmp = ft_strjoin(*base, pointer)) == NULL)
	{
		ft_strdel(base);
		ft_freetab(dirs);
		return (-1);
	}
	ft_strdel(base);
	if ((res = is_symbolic_link(*tmp)) == -1)
		ft_freetab(dirs);
	return (res);
}
