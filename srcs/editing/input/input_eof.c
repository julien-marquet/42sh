/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   input_eof.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/28 06:51:37 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/28 07:17:29 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "editing/input/input_eof.h"

/*
** 0 no eof
** 1 waiting for eof
** 2 eof sent
*/

int		*super_get_eof(void)
{
	static int eof = 0;

	return (&eof);
}

int		get_eof(void)
{
	return (*super_get_eof());
}

void	set_eof(int new_eof)
{
	*super_get_eof() = new_eof;
}
