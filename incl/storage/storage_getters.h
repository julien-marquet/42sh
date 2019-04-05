/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   storage_getters.h                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/05 18:04:34 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/05 18:07:38 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef STORAGE_GETTERS_H
# define STORAGE_GETTERS_H

# include "common.h"
# include "storage/storage_utils.h"

char	*get_stored_multiple(t_list *storage_1, t_list *storage_2,
		const char *var_name);
char	*get_stored(t_list *storage, const char *var_name);

#endif
