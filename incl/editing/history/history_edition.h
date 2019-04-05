/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   history_edition.h                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/04 17:27:30 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/05 18:13:22 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef HISTORY_EDITION_H
# define HISTORY_EDITION_H

# include "common.h"
# include "history.h"

t_list		*add_to_history_list(t_list **history, const char *buf, size_t len);
t_list		*edit_history_index(t_list *history, size_t index, const char *buf);

#endif
