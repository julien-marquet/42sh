/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtin_hash.h                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/15 22:14:29 by legrivel     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/21 22:26:33 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef BUILTIN_HASH_H
# define BUILTIN_HASH_H

# include "common.h"
# include "hash/hash.h"

int				check_not_found(t_hash_table *link, size_t found,
const char *av, size_t *i);
int				builtin_hash(t_sh_state *sh_state, int ac,
			const char **av, t_builtin_context *context);

#endif
