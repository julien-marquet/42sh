/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtin_hash.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: legrivel <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/15 22:17:59 by legrivel     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/15 22:17:59 by legrivel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "builtins/builtin_hash/builtin_hash.h"
#pragma GCC diagnostic ignored "-Wunused-parameter"

static void	print_table(t_list *table)
{
	if (table == NULL)
	{
		write(1, "hash: hash table empty\n", 23);
		return ;
	}
	write(1, "hits\t\t", 6);
	write(1, "command\n", 8);
	while (table != NULL)
	{
		ft_putnbr(((t_hash_table *)(table->content))->hits);
		write(1, "\t\t", 2);
		write(1, ((t_hash_table *)(table->content))->path,
			ft_strlen(((t_hash_table *)(table->content))->path));
		write(1, "\n", 1);
		table = table->next;
	}
}

static int	invalid_option(char opt)
{
	write(2, "-", 1);
	write(2, NAME, ft_strlen(NAME));
	write(2, ": hash: -", 9);
	write(2, &opt, 1);
	write(2, ": invalid option\n", 17);
	write(2, "hash: usage: hash [-r] [name ...]\n", 34);
	return (2);
}

static int	handle_options(const char **av, t_list **table)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (av[i] != NULL)
	{
		if (av[i][0] == '-')
		{
			j = 1;
			while (av[i][j])
			{
				if (av[i][j] == 'r')
					delete_table(table);
				else
					return (invalid_option(av[i][j]));
				j += 1;
			}
		}
		i += 1;
	}
	return (0);
}

static int	handle_args(const char **av,
		t_list **table, t_list *internal_storage)
{
	size_t			i;
	int				ret;
	size_t			found;
	t_hash_table	*link;
	int				error;

	i = 1;
	ret = 0;
	while (av[i] != NULL && av[i][0] == '-')
		i += 1;
	while (av[i] != NULL)
	{
		found = 1;
		link = get_link(table, (char *)(av[i]));
		if (link == NULL)
			if (append_bin((char *)(av[i]),
		table, internal_storage, &error) == NULL)
			{
				found = error == 0 ? 0 : 1;
				if (error == -1)
					return (-1);
			}
		ret = check_not_found(link, found, av[i], &i);
	}
	return (ret);
}

int			builtin_hash(t_sh_state *sh_state, int ac,
			const char **av, t_builtin_context *context)
{
	int		ret;

	ret = 0;
	if (ac == 1)
		print_table(sh_state->hash_table);
	else if (ac > 1 && av[1][0] == '-')
		ret = handle_options(av, &(sh_state->hash_table));
	if (ret == 2)
		return (2);
	if ((ret = handle_args(av,
		&(sh_state->hash_table), sh_state->internal_storage)) > 2)
		return (-1);
	return (ret);
}
