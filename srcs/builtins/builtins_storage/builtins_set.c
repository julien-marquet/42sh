/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtins_set.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/05 18:47:16 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/05 22:57:26 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "builtins/builtins_storage/builtins_set.h"

int		builtins_set(void *i_storage, int fd_out)
{
	t_list *casted_i_storage;

	casted_i_storage = (t_list *)i_storage;
	print_storage_content(casted_i_storage, fd_out);
	return (0);
}
