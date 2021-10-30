#include "../libft.h"

static t_args	*del_option(t_args *optn)
{
	t_args		*new_ptr;

	new_ptr = optn->next;
	free(optn->name);
	free(optn);
	return new_ptr;
}

void			del_option_by_name(t_args **optn_lst, const char *option_name)
{
	while ((*optn_lst)->next)
	{
		if (!ft_strcmp((*optn_lst)->name, option_name))
			*optn_lst = del_option(*optn_lst);
		optn_lst = &((*optn_lst)->next);
	}
}

void			del_args(t_args **optn_lst)
{
	t_args		*del_ptr;

	del_ptr = *optn_lst;

	while (del_ptr)
		del_ptr = del_option(del_ptr);
	
}