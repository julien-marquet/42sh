/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   utils.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: legrivel <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/05 03:54:31 by legrivel     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/05 03:54:31 by legrivel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "builtins/builtin_hash/builtin_hash.h"

int		check_not_found(t_hash_table *link, size_t found,
const char *av, size_t *i)
{
	int		ret;

	ret = 0;
	if (link != NULL)
		link->hits = 0;
	if (!found)
		ret = not_found((char *)av);
	*i += 1;
	return (ret);
}
