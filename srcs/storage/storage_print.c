/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   storage_print.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mmoya <mmoya@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/06 06:11:43 by mmoya        #+#   ##    ##    #+#       */
/*   Updated: 2019/05/06 06:12:24 by mmoya       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "storage/storage_print.h"

void	print_storage_content(t_list *storage, int fd)
{
	while (storage != NULL)
	{
		ft_putendl_fd(((t_internal_storage *)(storage->content))->string,
		fd);
		storage = storage->next;
	}
}
