/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   sh_state.h                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/28 23:05:43 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/19 21:21:04 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef SH_STATE_H
# define SH_STATE_H

# include "common.h"
# include "data/data_utils/data_utils_lst.h"
# include "aliases/aliases.h"
# include "storage/storage.h"

t_sh_state	*init_sh_state(void);
void		free_sh_state(t_sh_state **state);
t_sh_state	*duplicate_sh_state(t_sh_state *sh_state);

#endif
