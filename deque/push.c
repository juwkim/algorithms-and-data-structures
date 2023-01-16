/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwkim <juwkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 11:50:11 by juwkim            #+#    #+#             */
/*   Updated: 2023/01/16 14:38:44 by juwkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "deque.h"

void	dq_push_front(t_deque *dq, t_dq_data item)
{
	dq->head = (dq->head - 1) % QUEUE_SIZE;
	dq->nodes[dq->head].item = item;
}

void	dq_push_back(t_deque *dq, t_dq_data item)
{
	dq->nodes[dq->tail].item = item;
	dq->tail = (dq->tail + 1) % QUEUE_SIZE;
}
