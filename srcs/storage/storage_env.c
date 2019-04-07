/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   storage_env.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/05 17:25:57 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/08 01:19:42 by jmarquet    ###    #+. /#+    ###.fr     */
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

int		remove_env(t_list **internal_storage, const char *name)
{
	t_list	*tmp;
	t_list	*prev;
	size_t	len;

	tmp = *internal_storage;
	prev = NULL;
	len = ft_strlen(name);
	if (len == 0)
		return (0);
	while (tmp != NULL)
	{
		if (ft_strncmp(name,
	((t_internal_storage *)tmp->content)->string, len) == 0 &&
	((t_internal_storage *)tmp->content)->string[len] == '=' &&
	((t_internal_storage *)tmp->content)->exported == 1)
		{
			remove_node(internal_storage, &tmp, prev);
			return (1);
		}
		prev = tmp;
		tmp = tmp->next;
	}
	return (0);
}
