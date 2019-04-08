/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   storage_env.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/05 17:25:57 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/08 01:58:04 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "storage/storage_env.h"

t_list	*init_env(const char **env)
{
	t_list				*alst;
	t_list				*node;
	t_internal_storage	tmp;
	size_t				i;

	i = 0;
	alst = NULL;
	while (env[i] != NULL)
	{
		tmp.string = ft_strdup(env[i]);
		tmp.exported = 1;
		if ((node = ft_lstnew(&tmp, sizeof(tmp))) == NULL)
			return (NULL);
		ft_lstprepend(&alst, node);
		i++;
	}
	return (alst);
}

void	print_env(t_list *internal_storage, int fd)
{
	t_list	*tmp;

	tmp = internal_storage;
	while (tmp != NULL)
	{
		if (((t_internal_storage *)(tmp->content))->exported == 1)
			ft_putendl_fd(((t_internal_storage *)(tmp->content))->string, fd);
		tmp = tmp->next;
	}
}
