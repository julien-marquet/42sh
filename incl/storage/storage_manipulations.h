/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   storage_manipulations.h                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/05 17:33:14 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/28 06:17:03 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef STORAGE_MANIPULATIONS_H
# define STORAGE_MANIPULATIONS_H

# include "common.h"
# include "storage/storage_utils.h"
# include "hash/hash.h"

int		add_entry_storage(t_sh_state *state, const char *name,
		const char *value, int exported);
void	print_storage_content(t_list *storage, int fd);
int		remove_entry_storage(t_sh_state *sh_state, t_list **storage,
		const char *name);
int		update_exported_flag(t_list *storage, t_list **hash_table,
		const char *name, int exported);
int		is_valid_var_name(const char *name);

#endif
