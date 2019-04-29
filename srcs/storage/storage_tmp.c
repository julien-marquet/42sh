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
