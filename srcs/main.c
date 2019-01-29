/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/24 18:24:42 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/29 22:52:47 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "common.h"
#include "sh.h"
#include "input.h"

int		main(void)
{
	t_sh_state	*sh_state;
	t_input_buf	*input_buf;

	sh_state = init_sh();
	input_buf = init_input_buf();
	while (sh_state->exit_sig == 0)
	{
		handle_input(sh_state, input_buf);
		sh_state->exit_sig = 1;
	}
	exit_sh(0, sh_state);
	return (0);
}
