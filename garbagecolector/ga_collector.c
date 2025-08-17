/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ga_collector.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmounji <zmounji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 18:38:30 by zmounji           #+#    #+#             */
/*   Updated: 2025/08/17 15:05:44 by zmounji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"



void	add_back(t_collecter *new_node)
{
	t_collecter	*tmp;
	t_collecter	**alloc_head;


    alloc_head = getter_garbage();
    
	if (!alloc_head || !*alloc_head)
	{
		*alloc_head = new_node;
		return ;
	}
	tmp = *alloc_head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_node;
}

void	*ft_malloc(size_t size)
{
	void		*mem;
	t_collecter	*new_node;

	mem = malloc(size);
	if (!mem)
	{
		perror("minishell: malloc");
		ft_free_all();
		exit(1);
	}
	new_node = malloc(sizeof(t_collecter));
	if (!new_node)
	{
		free(mem);
		perror("minishell: malloc");
		ft_free_all();
		exit(1);
	}
	new_node->single1 = mem;
	new_node->next = NULL;
	add_back(new_node);
	return (mem);
}

void	free_images(void)
{
	t_elements *element;
	int			i;

	element = getter();
	i = 0;
	while (i < 6)
	{
		if (element->textures[i].img_ptr)
			mlx_destroy_image(element->mlx, element->textures[i].img_ptr);
		element->textures[i].img_ptr = NULL;
		i++;
	}
	mlx_destroy_image(element->mlx, element->img);
	i = 0;
	while (i < 10)
	{
		if (element->enemy->textures[i].img_ptr)
			mlx_destroy_image(element->mlx, element->enemy->textures[i].img_ptr);
		element->textures[i].img_ptr = NULL;
		
		i++;
	}
	if (element->wind)
    	mlx_destroy_window(element->mlx, element->wind);
	mlx_destroy_display(element->mlx);
	free(element->mlx);
}

void	ft_free_all(void)
{
	t_collecter	*tmp;
	t_collecter	**alloc_head;

    alloc_head = getter_garbage();
	free_images();
	while (alloc_head && *alloc_head)
	{
		tmp = *alloc_head;
		*alloc_head = (*alloc_head)->next;
		free(tmp->single1);
		free(tmp);
	}
}

void	ft_free(void *pointer)
{
	t_collecter	*current;
	t_collecter	*prev;
	t_collecter	**alloc_head;

    alloc_head = getter_garbage();
	prev = NULL;
	current = *alloc_head;
	while (current)
	{
		if (current->single1 == pointer)
		{
			if (prev)
				prev->next = current->next;
			else
				*alloc_head = current->next;
			free(current->single1);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}
