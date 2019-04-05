/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   storage_env.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/05 17:25:57 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/05 17:26:11 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "storage/storage_env.h"

t_list	*init_env(const char **env)
{
	t_list	*alst;
	t_list	*node;
	size_t	i;

	i = 0;
	alst = NULL;
	while (env[i] != NULL)
	{
		if ((node = ft_lstnew(env[i], ft_strlen(env[i]) + 1)) == NULL)
			return (NULL);
		ft_lstadd(&alst, node);
		i++;
	}
	return (alst);
}