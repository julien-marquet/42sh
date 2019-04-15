/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parse_alias.h                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mmoya <mmoya@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/10 15:05:12 by mmoya        #+#   ##    ##    #+#       */
/*   Updated: 2019/04/12 23:56:22 by mmoya       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef PARSE_ALIAS_H
# define PARSE_ALIAS_H

# include "parse/parse.h"
# include "aliases/aliases.h"

int		skiplst_check(char *tmp, t_list *skip);
t_list	*skiplst_handle(char *tmp, t_list **skip);
t_list	*skiplst_last(t_list *skip);

#endif
