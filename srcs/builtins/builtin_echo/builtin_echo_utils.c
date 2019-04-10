/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtin_echo_utils.c                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/10 02:51:24 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/10 02:56:00 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "builtins/builtin_echo/builtin_echo_utils.h"

int	get_octal_chars_nb(const char *str)
{
	int		i;

	i = 0;
	while (str[i] >= '0' && str[i] <= '7')
		i++;
	return (i);
}

int	convert_to_decimal(int octal)
{
	int decimal;
	int i;

	decimal = 0;
	i = 0;
	while (octal != 0)
	{
		decimal = decimal + (octal % 10) * ft_pow(8, i++);
		octal = octal / 10;
	}
	return (decimal);
}
