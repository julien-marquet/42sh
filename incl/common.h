/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   common.h                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/24 18:35:08 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/30 16:08:20 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef SH_COMMON_H
# define SH_COMMON_H

# include <sys/ioctl.h>
# include <curses.h>
# include <term.h>
# include <unistd.h>
# include <termios.h>
# include "types.h"
# include "signal.h"
# include "../libs/Libft/libft.h"
# include <sys/stat.h>
# include "limits.h"
# include "stdio.h"

# define NAME "42sh"

# define QUOTE_NONE 0
# define QUOTE_SIMPLE 1
# define QUOTE_DOUBLE 2

#endif
