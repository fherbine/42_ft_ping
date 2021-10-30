#include "libft.h"

uint8_t		ft_strinarray(char **haystack, char *needle)
{
	uint8_t	i;

	i = 0;
	while (haystack[i])
	{
		if (!ft_strcmp(haystack[i], needle))
			return (i);
		i++;
	}
	return (0);
}