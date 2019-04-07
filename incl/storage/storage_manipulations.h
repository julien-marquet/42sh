/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   storage_manipulations.h                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/05 17:33:14 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/07 21:11:06 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef STORAGE_MANIPULATIONS_H
# define STORAGE_MANIPULATIONS_H

# include "common.h"
# include "storage/storage_utils.h"

int		add_entry_storage(t_list **storage, const char *name,
		const char *value);
void	print_storage_content(t_list *storage, int fd_out);
int		remove_entry_storage(t_list **storage, const char *name);

#endif
