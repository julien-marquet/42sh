/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   input_active_search.h                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/05 19:06:40 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/05 19:10:29 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef INPUT_ACTIVE_SEARCH_H
# define INPUT_ACTIVE_SEARCH_H

# include "common.h"

void		set_active_search_node(t_list *node);
t_list		*get_active_search_node(void);

#endif
