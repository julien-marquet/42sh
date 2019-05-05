/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   buitlin_cd_utils_2.c                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/05 15:05:16 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/05 15:10:37 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "builtins/builtin_cd/builtin_cd.h"

int		check_for_cons_separator(char *cdpath, int j)
{
	int		separator;

	separator = 0;
	j--;
	while (j >= 0 && cdpath[j] == ':')
	{
		separator++;
		j--;
	}
	return (separator > 1 || (separator == 1 && j == -1));
}

int		check_dir_path(const char *path)
{
	struct stat	f_stat;

	if (path == NULL)
		return (-1);
	if (access(path, F_OK) == -1)
		return (1);
	if (stat(path, &f_stat) == -1)
		return (-1);
	if (S_ISDIR(f_stat.st_mode) == 0)
		return (3);
	if (access(path, X_OK) == -1)
		return (2);
	return (0);
}

char	*resolve_free(char *base, char **dirs)
{
	ft_freetab(&dirs);
	return (base);
}

char	*format_and_verify(t_sh_state *sh_state,
char *curpath, char *origin, int check)
{
	char	*formatted;

	formatted = format_path(sh_state, curpath, check);
	if (verify_path(origin, curpath, formatted) != 0)
	{
		free(formatted);
		return (NULL);
	}
	return (formatted);
}

int		check_links(const char **av, size_t opts)
{
	size_t	i;
	size_t	res_links;

	i = 0;
	res_links = 0;
	while (i < opts)
	{
		if (ft_strcmp(av[i + 1], "-L") == 0)
			res_links = 0;
		else if (ft_strcmp(av[i + 1], "-P") == 0)
			res_links = 1;
		i += 1;
	}
	return (res_links);
}
