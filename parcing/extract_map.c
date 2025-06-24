/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmounji <zmounji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 17:43:48 by zmounji           #+#    #+#             */
/*   Updated: 2025/06/24 19:16:52 by zmounji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"




int start_map(char *line, int fd)
{
    int             i;
    int             ismap;
    t_elements      *element;

    element = getter();
    ismap = 0;
   while (line)
   {
        i = 0;
        while(line[i])
        {
            if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
            {
                ismap = 1;
                break;
            }
            i++;
        }
        if (ismap == 1)
            return (extruct_map(line, fd));
        free (line);
        line = NULL;
        line = get_next_line(fd);
   }
    return (1);
}

int extruct_map(char *line, int fd)
{
    int col;
    int i;
    t_elements      *element;
    
    element = getter();
    element->map->rows = 0;
    while(line)
    {
        i = 0;
        // printf(" ----------------------------%d: %s \n", element->map->rows, line);
        while(line && line[i])
        {
            if (line[i] != ' ' && line[i] != '1' && line[i] != '0' && line[i] != '\0' && line[i] != 'N' && line[i] != 'E' && line[i] != 'O' && line[i] != 'S')
            {
                ft_error_el("invalid character \n");
            }
            i++;
        }
        element->map->rows++;
        col = ft_strlen(line);
        if (element->map->colomns < col)
            element->map->colomns = col;
        free (line);
        line = NULL;
        line = get_next_line(fd);
    }

    close (fd);
    element->map->map = malloc(sizeof(char *) * (element->map->rows + 1));
    if (!element)
        ft_error_el("ellocation failed \n");
    i = 0;
    element->map->map[element->map->rows] = NULL;
    while(i < element->map->colomns)
    {
        element->map->map[i] = malloc(sizeof(char) * (element->map->colomns + 1));
        if (!element->map->map[i])
            ft_error_el("ellocation failed \n");
        element->map->map[i][element->map->colomns] = '\0';
        i++;
    }
    return (1);
}