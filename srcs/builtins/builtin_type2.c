/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtin_type2.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: legrivel <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/06 06:25:19 by legrivel     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/06 06:25:20 by legrivel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "builtins/builtin_type.h"

int			check_file_exec(const char *path)
{
	struct stat	f_stat;

	if (path == NULL)
		return (-1);
	if (access(path, F_OK) == -1)
		return (1);
	if (access(path, X_OK) == -1)
		return (2);
	if (stat(path, &f_stat) == -1)
		return (-1);
	if (S_ISREG(f_stat.st_mode) == 0)
		return (3);
	return (0);
}
