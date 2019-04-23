#ifndef COMPLETION_H
# define COMPLETION_H

# include <dirent.h>
# include "common.h"

char	*trim(char *str);
size_t	is_dir(char *path);
size_t	is_stopping(char str);
size_t	is_closed(char *str, char *base);

int		lstfree(t_list *files);
void	lstmerge(t_list **list1, t_list *list2);

int		handle_completion(t_input_data *input, t_sh_state *sh_state);
#endif
