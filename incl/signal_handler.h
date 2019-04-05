/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   signal_handler.h                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/11 11:19:58 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/21 16:09:41 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef SIGNAL_HANDLER_H
# define SIGNAL_HANDLER_H

# include "common.h"

void	handle_sigwinch(int signo);

#endif