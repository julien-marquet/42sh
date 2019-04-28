/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   expand_error.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mmoya <mmoya@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/14 21:12:10 by mmoya        #+#   ##    ##    #+#       */
/*   Updated: 2019/04/28 17:58:46 by mmoya       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "parse/expand.h"

static int	expand_error_eof(void)
{
	ft_putstr_fd(NAME, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(ERR_EOF1, 2);
	return (-1);
}

static int	expand_error_sub(char *str)
{
	ft_putstr_fd(NAME, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd(": bad substitution", 2);
	ft_strdel(&str);
	return (-1);
}

int			param_check_isspecial(char *str)
{
	if (str[0] && str[1] == 0)
		return (str[0] == '?' ||
		str[0] == '$' ||
		str[0] == '-' ||
		str[0] == '!' ||
		str[0] == '0');
	return (0);
}

static int	expand_check_sub(char *str)
{
	int i;

	i = 0;
	if (ft_strlen(str) == 0)
		return (expand_error_sub(str));
	while (str[i])
	{
		if (!param_check_isspecial(str) && !ft_isalnum(str[i]) && str[i] != '_')
			return (expand_error_sub(str));
		i++;
	}
	return (0);
}

int			expand_error_handler(int type, char *str)
{
	if (type == 0)
		return (expand_error_eof());
	if (type == 1)
		return (expand_check_sub(str));
	return (0);
}
