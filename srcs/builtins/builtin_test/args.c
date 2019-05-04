/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   args.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: legrivel <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/11 21:51:49 by legrivel     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/11 21:51:50 by legrivel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "builtins/builtin_test/builtin_test.h"

int			is_unary_op(char *arg)
{
	return (ft_strlen(arg) == 2 &&
		arg[0] == '-' &&
		ft_strchr("bcdefgLprSsuwxz", arg[1]) != NULL);
}

int			is_binary_op(char *arg)
{
	return (ft_strcmp("-eq", arg) == 0 ||
		ft_strcmp("-ne", arg) == 0 ||
		ft_strcmp("-ge", arg) == 0 ||
		ft_strcmp("-lt", arg) == 0 ||
		ft_strcmp("-le", arg) == 0 ||
		ft_strcmp("=", arg) == 0 ||
		ft_strcmp("!=", arg) == 0);
}
