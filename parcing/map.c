/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmounji <zmounji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 16:13:34 by zmounji           #+#    #+#             */
/*   Updated: 2025/08/15 19:39:42 by zmounji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../cube.h"

void	ft_error_el(const char *str)
{
	write(2, "Error\n", 7);
	write(2, str, ff_strlen(str));
    // leack truck
	exit (1);
}

void	ft_esc(const char *str)
{
	write(2, str, ff_strlen(str));
    // leack truck
	exit (42);
}

char	*ft_strnext( char *haystack, const char *needle)
{
    int i;
    int j;
    
    i = 0;
    while (haystack && haystack[i])
    {
        j = 0;
        while (needle && needle[j] && (haystack[i + j] == needle[j]))
            j++;
        if (needle[j] == '\0')
        {
            while (haystack && (haystack [i + j] == '\t' || haystack[i + j] == ' '))
                j++;
            return (haystack + i +j );
        }
        i++;
    }
	return (NULL);
}


char *get_c(t_elements *element, char *line, char *str)
{
    char    **s_ar;
    int     col;

    str = ft_strnext(line, "C");
    if (str && element->c)
        ft_error_el ("elements was duplicated  -------\n");
    if (str)
    {
        element->c = malloc(sizeof(t_color));
        if (!element->c)
            ft_error_el("can not allocat");
        ft_bzero(element->c, sizeof(t_color));
        s_ar = ft_split(str, ',');
        col = 0;
        while (s_ar[col])
            col++;
        if(col != 3)
            ft_error_el("argument of coloro argb not correct\n");
        element->c->a = ft_atoi(s_ar[0]);
        element->c->b = ft_atoi(s_ar[1]);
        element->c->c = ft_atoi(s_ar[2]);
    }
    return (str);
}

char *get_f(t_elements *element, char *line, char *str)
{
    char    **s_ar;
    int     col;

    str = ft_strnext(line, "F");
    if (str && element->f)
    {
        printf("--> %s :---> %zu", str, ft_strlen(str));
        ft_error_el ("elements was duplicated ************\n");
    }
    if (str)
    {
        element->f = malloc(sizeof(t_color));
        if (!element->f)
            ft_error_el("can not allocat");
        ft_bzero(element->f, sizeof(t_color));
        s_ar = ft_split(str, ',');
        col = 0;
        while (s_ar[col])
            col++;
        if(col != 3)
            ft_error_el("argument of coloro argb not correct\n");
        element->f->a = ft_atoi(s_ar[0]);
        element->f->b = ft_atoi(s_ar[1]);
        element->f->c = ft_atoi(s_ar[2]);
    }
    return (str);
}

char    *get_no(t_elements *element, char *line, char *str)
{
    str = ft_strnext(line, "NO");
    if (str && element->no)
        ft_error_el ("elements was duplicated");
    if (str)
    {
        element->no = extruct_link(str);
    }
    return (str);
}

char    *get_so(t_elements *element, char *line, char *str)
{
    if (!str)
    {
        str = ft_strnext(line, "SO");
        if (str && element->so)
            ft_error_el ("elements was duplicated");
        if (str)
            element->so = extruct_link(str);
    }
    return (str);
}
char    *get_we(t_elements *element, char *line, char *str)
{
    if (!str)
    {
        str = ft_strnext(line, "WE");
        if (str && element->we)
            ft_error_el ("elements was duplicated");
        if (str)
            element->we = extruct_link(str);
    }
    return (str);
}
char    *get_ea(t_elements *element, char *line, char *str)
{
    if (!str)
    {
        str = ft_strnext(line, "EA");
        if (str && element->ea)
            ft_error_el ("elements was duplicated");
        if (str)
            element->ea = extruct_link(str);
    }
    return (str);
}

int extruct_elements(char *line)
{
    int             i;
    char            *str;
    t_elements      *element;
    
    i = 0;
    str = NULL;
    element = getter();
    str = get_no(element, line, str);
    str = get_so(element, line, str);
    str = get_we(element, line, str);
    str = get_ea(element, line, str);



    if (!str)
        str = get_f(element, line, str);
    if (!str)
        str = get_c(element, line, str);
    while (!str && line && line[i])
    {
        if (line[i] != ' ')
            ft_error_el("invalide character\n");
        i++;   
    }
    return (str != NULL);
}

char    *extruct_link(char *str)
{
    int i;
    int l;
    int j;
    char *link;

    i = 0;
    l = 0;
    if (!str || !*str)
        return (NULL);
    while (str[i] == ' ' || str[i] == '\t')
        i++;
    j = i;
    while (str[i] && str[i] != ' ' && str[i] != '\t')
        i++;
    link = malloc (i - j + 1);
    if (!link)
        return (NULL);
    link[i - j] = '\0';
    while((l+j) < i)
    {
        link[l] = str[l+j];
        l++;
    }
    return (link);
}

int extruct_them(char *line)
{
    int             i;
    char            *str;
    
    i = 0;
    str = NULL;
    // element = getter();
    str = ft_strnext(line, "NO");
    if (!str)
    {
        str = ft_strnext(line, "SO");
    }
    if (!str)
    {
        str = ft_strnext(line, "WE");

    }
    if (!str)
    {
        str = ft_strnext(line, "EA");
    }
    if (!str)
    {
        str = ft_strnext(line, "F");
    }
    if (!str)
    {
        str = ft_strnext(line, "C");
    }
    while (!str && line && line[i])
    {
        if (line[i] != ' ')
            ft_error_el("invalide character\n");
        i++;   
    }
    // printf("end \n");
    return (str != NULL);
}




void    map(char **argv)
{
    int     fd;
    int     number;
    char    *line;

    fd = open (argv[1], O_RDONLY,0644);
    line = NULL;
    line = get_next_line(fd);
    number = 0;
    while (line && (number < 6))
    {
        number += extruct_elements(line);
        free (line);
        line = NULL;
        line = get_next_line(fd);
    }
    if (number < 6)
        ft_error_el("element or more are absents");
    start_map(line, fd);
    upload_map(argv);
    cheack_map();
}
