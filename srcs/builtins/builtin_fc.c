/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtin_fc.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mmoya <mmoya@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/19 22:10:25 by mmoya        #+#   ##    ##    #+#       */
/*   Updated: 2019/04/22 18:44:50 by mmoya       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "builtins/builtin_fc.h"

int		flag_handler(const char *arg, int *flag)
{
	size_t i;
	size_t len;

	i = 0;
	len = ft_strlen(arg);
	while (i < len)
	{
		if (arg[i] == 'e')
			*flag |= F_E;
		if (arg[i] == 'l')
			*flag |= F_L;
		if (arg[i] == 'n')
			*flag |= F_N;
		if (arg[i] == 'r')
			*flag |= F_R;
		if (arg[i] == 's')
			*flag |= F_S;
		i++;
	}
	return (0);
}

int		builtin_fc(t_sh_state *sh_state, int ac,
const char **av, t_builtin_context *context)
{
	int		i;
	int		flag;
	char	*editor;

	flag = 0;
	editor = NULL;
	(void)sh_state;
	(void)context;
	i = 0;
	while (i < ac)
	{
		if (av[i][0] == '-' && !(flag & F_E))
			flag_handler(av[i], &flag);
		else if (flag & F_E)
		{
			editor = ft_strdup(av[i]);
			flag -= F_E;
		}
		i++;
	}
	dprintf(2, "EDIT= %s\n", editor);
	dprintf(2, "F_E = %i\n", flag & F_E);
	dprintf(2, "F_L = %i\n", flag & F_L);
	dprintf(2, "F_N = %i\n", flag & F_N);
	dprintf(2, "F_R = %i\n", flag & F_R);
	dprintf(2, "F_S = %i\n", flag & F_S);
	return (0);
}
