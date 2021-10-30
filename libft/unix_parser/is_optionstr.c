#include "../libft.h"

uint8_t		is_optionstr(const char *str)
{
	if (ft_strlen(str) < 2)
		return (FALSE);
	return ((str[0] == '-') ? TRUE : FALSE);
}