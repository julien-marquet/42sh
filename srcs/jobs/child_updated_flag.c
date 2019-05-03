/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   child_updated_flag.c                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/03 14:58:45 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/03 15:17:02 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "jobs/child_updated_flag.h"

int		*super_get_sigchld_flag(void)
{
	static int	child_updated = 0;

	return (&child_updated);
}
