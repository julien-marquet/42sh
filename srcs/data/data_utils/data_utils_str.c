/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   data_utils_str.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/08 22:02:10 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/09 02:55:56 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "data/data_utils/data_utils_str.h"

char	*merge_name_value(const char *name,
const char *value, const size_t size)
{
	size_t	name_len;
	char	*res;

	name_len = ft_strlen(name);
	if ((res = ft_memalloc(size + 1)) == NULL)
		return (NULL);
	ft_strcpy(res, name);
	res[name_len] = '=';
	if (value != NULL)
		ft_strcpy(&(res[name_len + 1]), value);
	return res;
}
