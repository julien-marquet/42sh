/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   storage_tmp.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: legrivel <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/29 08:48:27 by legrivel     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/29 08:48:28 by legrivel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "storage/storage_tmp.h"

static size_t	get_array_length(char **env)
{
	size_t	i;

	i = 0;
	while (env[i])
		i += 1;
	return (i);
}

static size_t	get_total_length(char **env, t_list *tmp)
{
	size_t				i;
	t_internal_storage	*entry;
	t_list				*pointer;
	size_t				name_len;

	i = get_array_length(env);
	pointer = tmp;
	while (pointer)
	{
		entry = pointer->content;
		name_len = ft_strlen(entry->string) - ft_strlen(ft_strchr(entry->string, '='));
		if (ft_strncmp(entry->string, *env, name_len + 1) == 0)
			break ;
		pointer = pointer->next;
		if (pointer == NULL && tmp != NULL)
			i += 1;
	}
	return (i);
}

char			**update_env(char **env, t_list *tmp)
{
	size_t				i;
	char				**new;
	t_internal_storage	*entry;
	size_t				name_len;
	t_list				*pointer;

	if ((new = malloc((get_total_length(env, tmp) + 1) * sizeof(char *))) == NULL)
		return (NULL);
	i = 0;
	while (*env)
	{
		pointer = tmp;
		while (pointer)
		{
			entry = pointer->content;
			name_len = ft_strlen(entry->string) - ft_strlen(ft_strchr(entry->string, '='));
			if (ft_strncmp(entry->string, *env, name_len + 1) == 0)
			{
				new[i] = entry->string;
				break ;
			}
			pointer = pointer->next;
		}
		if (pointer == NULL)
			new[i] = *env;
		i += 1;
		env += 1;
	}
	new[i] = NULL;
	return (new);
}

void			remove_tmp_env(t_list **storage)
{
	t_list	*pointer;
	t_list	*previous;

	previous = NULL;
	pointer = *storage;
	while (pointer != NULL)
	{
		if (((t_internal_storage *)(pointer->content))->tmp)
		{
			if (previous == NULL)
			{
				*storage = (*storage)->next;
				free(((t_internal_storage *)pointer->content)->string);
				free(pointer->content);
				pointer = *storage;
				continue ;
			}
			else
			{
				free(((t_internal_storage *)pointer->content)->string);
				free(pointer->content);
				previous->next = pointer->next;
				pointer = previous->next;
				continue ;
			}
		}
		previous = pointer;
		pointer = pointer->next;
	}
}

int				update_builtin_env(t_list **storage, t_list *vars)
{
	t_list				*tmp;
	t_internal_storage	new;
	t_list				*pointer;

	pointer = *storage;
	while (pointer != NULL && pointer->next != NULL)
		pointer = pointer->next;
	while (vars != NULL)
	{
		if ((new.string =
	ft_strdup(((t_internal_storage *)(vars->content))->string)) == NULL)
			return (-1);
		new.exported = 1;
		new.tmp = 1;
		if ((tmp = ft_lstnew(&new, sizeof(t_internal_storage))) == NULL)
			return (-1);
		if (pointer == NULL)
			*storage = tmp;
		else
		{
			pointer->next = tmp;
			pointer = pointer->next;
		}
		vars = vars->next;
	}
	return (0);
}
