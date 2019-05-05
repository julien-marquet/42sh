/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   data_utils_arr.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/19 21:41:09 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/05 15:45:20 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "data/data_utils/data_utils_arr.h"

char	**duplicate_array(char **array)
{
	char	**new_arr;
	int		i;
	int		arr_len;

	new_arr = NULL;
	if (array != NULL)
	{
		arr_len = ft_arraylen((const void **)array);
		if ((new_arr = (char **)ft_memalloc(
	sizeof(char *) * (arr_len + 1))) == NULL)
			return (NULL);
		i = 0;
		while (array[i] != NULL)
		{
			if ((new_arr[i] = ft_strdup(array[i])) == NULL)
				return (new_arr);
			i++;
		}
	}
	return (new_arr);
}

void	free_arr(char **array)
{
	int		i;

	if (array)
	{
		i = 0;
		while (array[i] != NULL)
		{
			ft_strdel(&(array[i]));
			i++;
		}
		free(array);
		array = NULL;
	}
}
