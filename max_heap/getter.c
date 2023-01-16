/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwkim <juwkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 16:15:12 by juwkim            #+#    #+#             */
/*   Updated: 2023/01/16 14:06:07 by juwkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "max_heap.h"

int	heap_get_parent(int idx)
{
	return (idx >> 1);
}

int	heap_get_left_child(int idx)
{
	return (idx << 1);
}

int	heap_get_right_child(int idx)
{
	return ((idx << 1) + 1);
}

int	heap_get_higher_prioity_child(t_heap *heap, int idx)
{
	const int	left = heap_get_left_child(idx);
	const int	right = heap_get_right_child(idx);

	if (left > heap->size)
		return (0);
	else if (left == heap->size)
		return (left);
	else
	{
		if (heap->items[left].priority > heap->items[right].priority)
			return (left);
		else
			return (right);
	}
}
