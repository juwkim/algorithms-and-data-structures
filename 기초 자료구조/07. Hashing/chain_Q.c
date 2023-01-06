/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chain_Q.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwkim <juwkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 00:19:25 by juwkim            #+#    #+#             */
/*   Updated: 2023/01/07 00:19:25 by juwkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SIZE 5
#define TABLE_SIZE	7	// �ؽ� ���̺��� ũ��=�Ҽ� 

int collision_count; //�浹 Ƚ��


typedef struct {
	int key;
} element;

struct list
{
	element item;
	struct list* link;
};

struct list* hash_table[TABLE_SIZE];

// ���� �Լ��� ����� �ؽ� �Լ�
int hash_function(int key)
{
	return key % TABLE_SIZE;
}

// ü�ι��� �̿��Ͽ� ���̺� Ű�� ����
void hash_chain_add(element item, struct list* ht[])
{
	int hash_value = hash_function(item.key);
	struct list* ptr;
	struct list* node = ht[hash_value];

	if (node == NULL)
	{
		ht[hash_value] = malloc(sizeof(struct list));
		if (ht[hash_value] == NULL)
			return;
		ht[hash_value]->item = item;
		ht[hash_value]->link = NULL;
		return;
	}
	while (1)
	{
		printf("�ε��� %d���� �浹 �߻�. �浹 Ƚ�� = %d\n", hash_value, ++collision_count);
		if (node->item.key == item.key)
		{
			printf("�ε��� %d���� Ž��Ű�� �ߺ��Ǿ����ϴ�.\n", hash_value);
			return;
		}
		if (node->link == NULL)
		{
			struct list* new = malloc(sizeof(struct list));
			if (new == NULL)
				return;
			new->item = item;
			new->link = NULL;
			node->link = new;
			return;
		}
		node = node->link;
	}
}

// ü�ι��� �̿��Ͽ� ���̺� ����� Ű�� Ž��
void hash_chain_search(element item, struct list* ht[])
{
	int search_count = 1; // Ž�� Ƚ��
	int hash_value = hash_function(item.key);
	struct list* node = ht[hash_value];

	while (node && node->item.key != item.key)
	{
		node = node->link;
		++search_count;
	}

	if (node == NULL)
		printf("Ű�� ã�� ������\n");
	else
		printf("Ž�� %d ���� Ž�� Ƚ��: %d ��\n", item.key, search_count);
}

// �ؽ� ���̺��� ������ ���
void hash_chain_print(struct list* ht[])
{
	struct list* node;
	int i;
	printf("\n===============================\n");
	for (i = 0; i < TABLE_SIZE; i++) {
		printf("[%d]->", i);
		for (node = ht[i]; node; node = node->link) {
			printf("%d->", node->item.key);
		}
		printf("\n");
	}
	printf("===============================\n\n");
}


// �ؽ� ���̺��� ����� ���� 
int main(void)
{
	int data[SIZE] = { 8, 1, 9, 6, 13 };
	element e;

	for (int i = 0; i < SIZE; i++) {
		e.key = data[i];
		hash_chain_add(e, hash_table);
		hash_chain_print(hash_table);
	}
	for (int i = 0; i < SIZE; i++) {
		e.key = data[i];
		hash_chain_search(e, hash_table);
	}
	return 0;
}