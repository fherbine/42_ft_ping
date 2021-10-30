#ifndef UNIX_PARSING_H
# define UNIX_PARSING_H

typedef struct      s_args {
	char			*name;
	void			*value;
    struct s_args   *next;
}               	t_args;

typedef struct		s_expect_args {
	char			*name;
	int				argc;
}					t_eargs;

uint8_t		is_optionstr(const char *str);

void		*get_option(const char *option_name, t_args **optn_lst);
void		new_option(t_args **optn_lst, const char *option_name, void *value);
void		del_option_by_name(t_args **optn_lst, const char *option_name);
void		del_args(t_args **optn_lst);

#endif