/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtins_env.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/05 22:37:30 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/07 18:30:08 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "builtins/builtins_storage/builtins_env.h"

int		builtins_env(void *env, int fd_out)
{
	t_list *casted_env;

	casted_env = (t_list *)env;
	print_storage_content(casted_env, fd_out);
	sleep(3);
	return (0);
}
