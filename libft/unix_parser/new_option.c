#include "../libft.h"

void		new_option(t_args **optn_lst, const char *option_name, void *value)
{
	t_args	*new_option;

	if (!(new_option = (t_args *)malloc(sizeof(t_args))))
		return ;

	new_option->name = ft_strdup(option_name);
	new_option->value = value;
	new_option->next = NULL;

	while ((*optn_lst)->next)
		optn_lst = &((*optn_lst)->next);

	(*optn_lst)->next = new_option;
}