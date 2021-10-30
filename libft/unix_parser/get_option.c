#include "../libft.h"

void	*get_option(const char *option_name, t_args **optn_lst)
{
	while ((*optn_lst)->next)
	{
		if (!ft_strcmp((*optn_lst)->name, option_name))
			return ((*optn_lst)->value);
		optn_lst = &((*optn_lst)->next);
	}
	return (NULL);
}