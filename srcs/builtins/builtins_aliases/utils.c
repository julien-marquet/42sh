/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   utils.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: legrivel <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/05 05:04:45 by legrivel     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/05 05:04:46 by legrivel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "builtins/builtins_aliases/builtin_alias.h"

void	alias_error(char *origin, char *msg, int *res)
{
	print_error(origin, msg, 2);
	*res = 1;
}
