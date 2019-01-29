/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   input_buf.h                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/29 22:40:19 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/29 22:52:20 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef INPUT_BUF_H
# define INPUT_BUF_H
# define DEFAULT_INPUT_BUF_SIZE 128

int			append_input_buf(char *str, t_input_buf *input_buf);
t_input_buf	*init_input_buf(void);

#endif
