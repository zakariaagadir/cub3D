/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing_mn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmounji <zmounji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 14:22:08 by zmounji           #+#    #+#             */
/*   Updated: 2025/07/25 15:43:13 by zmounji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../cube.h"

void	strlen_exit(void)
{
	write (2, "saving contre overflowing\n", 27);
	exit (1);
}

int ff_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str && str[i])
	{
		if(i >= 2147483647)
			strlen_exit();
		i++;
	}
	return (i);
}

char	*ft_strstr(const char *haystack, const char *needle)
{
	size_t	i;
	size_t	j;
	size_t	pt;
	pt = ff_strlen(needle);
	i = 0;
	if (!*needle)
		return ((char *)haystack);
	if (!*haystack)
		return (NULL);
	while (haystack[i])
	{
		j = 0;
		while (haystack[i + j] == needle[j] && haystack[i + j])
			j++;
		if ( needle[j] == '\0' && (i + pt))
			return ((char *)(haystack + i));
		i++;
	}
	return (NULL);
}

void	ft_error(const char *str)
{
	write(2, "Error\n", 7);
	write(2, str, ff_strlen(str));
	exit (1);
}

void parcing_mn(int ac, char **argv)
{
    if (ac != 2)
		ft_error("Number of parametter not correct\n");
	if (!ft_strstr(argv[1], ".cub"))
		ft_error("Name of the map not correct\n");
	map(argv);
}
