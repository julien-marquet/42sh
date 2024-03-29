/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   storage_env.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mmoya <mmoya@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/05 17:25:57 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/05 19:28:15 by mmoya       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "storage/storage_env.h"

t_list		*init_env(const char **env)
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
		tmp.tmp = 0;
		if ((node = ft_lstnew(&tmp, sizeof(tmp))) == NULL)
			return (NULL);
		ft_lstprepend(&alst, node);
		i++;
	}
	return (alst);
}

void		print_env(t_list *internal_storage, int fd)
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

static int	fill_arr_env(char **arr_env, t_list *storage)
{
	t_list	*tmp;
	size_t	i;

	tmp = storage;
	i = 0;
	while (tmp != NULL)
	{
		if (((t_internal_storage *)tmp->content)->exported == 1)
		{
			if ((arr_env[i] = ft_strdup((const char *)(
		(t_internal_storage *)tmp->content)->string)) == NULL)
				return (1);
			i++;
		}
		tmp = tmp->next;
	}
	arr_env[i] = NULL;
	return (0);
}

char		**generate_env(t_list *storage)
{
	t_list	*tmp;
	size_t	len;
	char	**arr_env;

	tmp = storage;
	len = 0;
	while (tmp != NULL)
	{
		if (((t_internal_storage *)tmp->content)->exported == 1)
			len++;
		tmp = tmp->next;
	}
	if ((arr_env = (char **)ft_memalloc(sizeof(char *) * (len + 1))) == NULL)
		return (NULL);
	if (fill_arr_env(arr_env, storage) == 1)
		return (NULL);
	return (arr_env);
}
