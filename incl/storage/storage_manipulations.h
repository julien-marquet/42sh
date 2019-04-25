/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   storage_manipulations.h                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/05 17:33:14 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/09 01:50:52 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef STORAGE_MANIPULATIONS_H
# define STORAGE_MANIPULATIONS_H

# include "common.h"
# include "storage/storage_utils.h"

int		add_entry_storage(t_sh_state *state, const char *name,
		const char *value, int exported);
void	print_storage_content(t_list *storage, int fd);
int		remove_entry_storage(t_list **storage, const char *name);
int		update_exported_flag(t_list *storage, t_list **hash_table,
		const char *name, int exported);
void	flush_new_entry_flag(t_list *storage);

#endif
