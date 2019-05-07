/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   utils.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mmoya <mmoya@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/07 22:55:15 by mmoya        #+#   ##    ##    #+#       */
/*   Updated: 2019/05/07 23:36:03 by mmoya       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "parse/parse_alias.h"

int			alias_endspace(char *str)
{
	size_t	i;

	i = 0;
	if (str == NULL || str[0] == 0)
		return (1);
	while (str[i] && str[i + 1])
		i++;
	if (str[i] == ' ')
		return (1);
	return (0);
}
