/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   chev.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mmoya <mmoya@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/18 20:14:58 by mmoya        #+#   ##    ##    #+#       */
/*   Updated: 2019/04/08 16:49:45 by mmoya       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "parse.h"

static int		*parse_chev_type(char *str, int i)
{
	int		*type;

	if (!(type = ft_memalloc(sizeof(int) * sizeof(t_ctype))))
		return (NULL);
	type[C_TYPE] = str[i];
	type[C_IN] = type[C_TYPE] == '>' ? 1 : 0;
	type[C_OUT] = -1;
	while (i > 0 && ft_isdigit(str[i - 1]))
		i--;
	if ((i > 0 && stresc(";|<>& \n", str, i - 1)) || i == 0)
		ft_isdigit(str[i]) ? type[C_IN] = ft_atoi(str + i) : 0;
	while (str[i] && ft_isdigit(str[i]))
		i++;
	while (str[i + type[C_LEN]] && str[i + type[C_LEN]] == type[C_TYPE])
		type[C_LEN]++;
	i += type[C_LEN];
	if (str[i] == '&' && str[i + 1])
		type[C_OUT] = ft_atoi(str + i + 1);
	return (type);
}

static int		parse_chev_skip(char *str, int i, char c_type)
{
	while (str[i] && ft_isdigit(str[i]))
		i++;
	while (str[i] && str[i] == c_type)
		i++;
	if (str[i] == '&')
		i++;
	while (str[i] && ft_isspace(str[i]))
		i++;
	return (i);
}

static int		parse_chev_handle(char *str, int i, t_cmd *cmd, t_sh_state *sh_state, t_input_data *input_data)
{
	char	*file;
	int		len;
	int		tmp;
	int		*type;

	if (!(type = parse_chev_type(str, i)))
		return (i);
	len = i;
	while (i > 0 && ft_isdigit(str[i - 1]))
		i--;
	if ((i > 0 && stresc(";|<>& \n", str, i - 1)) || i == 0)
		len = i;
	i = parse_chev_skip(str, i, type[C_TYPE]);
	tmp = i;
	while (str[i] && (!stresc(";|<>& \n", str, i) || is_quoted(str, i)))
		i++;
	if (!(file = strndup_qr(str + tmp, i - tmp)))
		return (0);
	parse_chevcreate(file, cmd, type, sh_state, input_data);
	ft_memset(str + len, ' ', i - len);
	return (i);
}

void			parse_chev(t_cmd *cmd, t_sh_state *sh_state, t_input_data *input_data)
{
	char	*str;
	int		i;

	str = cmd->str;
	i = 0;
	while (str[i])
	{
		while (str[i] && is_quoted(str, i))
			i++;
		if (str[i] && stresc("<>", str, i))
			i = parse_chev_handle(str, i, cmd, sh_state, input_data);
		else
			str[i] ? i++ : 0;
	}
}
