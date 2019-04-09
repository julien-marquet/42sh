/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parse.h                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mmoya <mmoya@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/02/23 17:46:26 by mmoya        #+#   ##    ##    #+#       */
/*   Updated: 2019/04/09 16:31:23 by mmoya       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "common.h"
# include <pwd.h>

# define SH_NAME "42sh"

# define CHEV_PERM 420

# define READ_END 0
# define WRITE_END 1

typedef enum		e_ctype {
	C_IN = 0,
	C_LEN,
	C_OUT,
	C_TYPE
}					t_ctype;

/*
** TEMP ENV FUNCT
*/

typedef struct		s_term {
	char			*str;
	size_t			cpos;
	char			**env;
	int				fd;
	int				flag;
}					t_term;

typedef struct		s_file {
	char			*file;
	char			*here;
	int				*type;
	struct s_file	*next;
}					t_file;

typedef struct		s_arg {
	char			*arg;
	int				type;
	struct s_arg	*next;
}					t_arg;

typedef struct		s_cmd {
	char			*str;
	char			**arg;
	char			type;
	char			*red;
	t_file			*in;
	t_file			*out;
	struct s_cmd	*next;
}					t_cmd;

/*
** CHECK
*/

int				parse_error(char *str, int i);
int				parse_check(char *str);

/*
** PARSE
*/

int				parse(char *str, t_term *term, t_sh_state *sh_state, t_input_data *input_data);
void			parse_chev(t_cmd *cmd, t_sh_state *sh_state, t_input_data *input_data);
t_cmd			*parse_chevcreate(char *file, t_cmd *cmd, int *type, t_sh_state *sh_state, t_input_data *input_data);
int				parse_tokenize(char *str, t_cmd **cmd);
void			parse_expansion(t_cmd *cmd, t_sh_state *sh_state);
char			**parse_strsplit(char *str, int len);

/*
** UTILS
*/

char			*stresc(char *find, char *str, int i);
char			*strndup_qr(char *str, size_t len);
char			*strinsert(char *dst, char *new, size_t i, size_t end);
int				is_quoted(char *str, int i);

t_cmd			*parse_nextfree(t_cmd *cmd);

/*
** EXEC
*/

int				exec_chevout(t_cmd *cmd);
int				exec_chevin(t_cmd *cmd);

#endif
