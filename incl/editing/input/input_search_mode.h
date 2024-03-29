/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   input_search_mode.h                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/26 04:06:00 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/05 19:11:51 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef INPUT_SEARCH_MODE_H
# define INPUT_SEARCH_MODE_H

# include "common.h"
# include "editing/input/input_active_search.h"
# include "editing/input/input_searched.h"

int			get_search_mode(void);
void		set_search_mode(int	setter);

#endif
