/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   aliases_manipulations.c                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/08 20:18:26 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/30 15:13:23 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "aliases/aliases_manipulations.h"

int		add_alias(t_list **aliases, const char *name, const char *value)
{
	t_list		*node;
	size_t		len;
	size_t		name_len;
	char		*entry;

	if (name == NULL || ft_strcspn(name, "/=") != (name_len = ft_strlen(name)))
		return (1);
	if (name_len == 0)
		return (0);
	len = value ? ft_strlen(value) : 0;
	len += name_len + 1;
	if ((node = find_alias_by_name(*aliases, name)) != NULL)
	{
		if (update_existing_alias(node, name, value, len) == 1)
			return (1);
	}
	else
	{
		if ((entry = merge_name_value(name, value, len)) == NULL ||
			(node = ft_lstnew((const void *)entry, len + 1)) == NULL)
			return (1);
		free(entry);
		ft_lstprepend(aliases, node);
	}
	return (0);
}

int		remove_alias(t_list **aliases, const char *name)
{
	t_list	*tmp;
	t_list	*prev;
	size_t	len;

	tmp = *aliases;
	prev = NULL;
	if (name == NULL)
		return (0);
	len = ft_strlen(name);
	if (len == 0)
		return (0);
	while (tmp != NULL)
	{
		if (ft_strncmp(name, (char *)tmp->content, len) == 0 &&
		((char *)tmp->content)[len] == '=')
		{
			remove_alias_node(aliases, &tmp, prev);
			return (1);
		}
		prev = tmp;
		tmp = tmp->next;
	}
	return (0);
}

void	print_aliases(t_list *aliases, int fd)
{
	t_list	*tmp;
	char	*str;
	char	*value;
	size_t	len;

	tmp = aliases;
	while (tmp != NULL)
	{
		ft_putstr_fd("alias ", fd);
		str = (char *)(tmp->content);
		value = ft_strchr(str, '=') + 1;
		len = ft_strlen(value);
		write(fd, str, ft_strlen(str) - len);
		if (value[0] != '\'')
			write(fd, "\'", 1);
		write(fd, value, len);
		if (value[len - 1] != '\'')
			write(fd, "\'", 1);
		write(fd, "\n", 1);
		tmp = tmp->next;
	}
}

void	remove_all_aliases(t_list **aliases)
{
	void (*del)(void *, size_t);

	del = free_lstnode;
	ft_lstdel(aliases, del);
	*aliases = NULL;
}
