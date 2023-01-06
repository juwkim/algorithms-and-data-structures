/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linear_probing_Q.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwkim <juwkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 00:19:31 by juwkim            #+#    #+#             */
/*   Updated: 2023/01/07 00:19:31 by juwkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SIZE 5			// �迭�� �ִ����  
#define TABLE_SIZE	7	// �ؽ� ���̺��� ũ��=�Ҽ� 
#define INIT -1			// �ؽ� ���̺��� �ʱⰪ -1

int count; //�浹 Ƚ��

typedef struct {
	int key;
} element;

element hash_table[TABLE_SIZE];		// �ؽ� ���̺� 

void init_table(element ht[])
{
	int i;
	for (i = 0; i < TABLE_SIZE; i++) {
		ht[i].key = INIT;
	}
}
// ���� �Լ��� ����� �ؽ� �Լ�
int hash_function(int key)
{
	// Ű�� ���� ���̺��� ũ��� ������ �������� ��ȯ
	return key % TABLE_SIZE;
}

// ���� ������� �̿��Ͽ� ���̺� Ű�� �����ϰ�, 
// ���̺��� ���� �� ���� ����     
void hash_lp_add(element item, element ht[])
{
	int i, hash_value;
	hash_value = i = hash_function(item.key);
	
	printf("hash_address = %d\n", i);
	do
	{
		if (ht[i].key == INIT)
		{
			ht[i] = item;
			printf("�ε��� %d�� insert item %d\n", i, item.key);
			return;
		}
		printf("�ε��� %d���� �浹 �߻�. �浹 Ƚ�� = %d\n", i, ++count);
		i++;
		if (i == TABLE_SIZE)
			i = 0;
	} while (i != hash_value);
	printf("���̺��� ����á���ϴ�.\n");
}

// ����������� �̿��Ͽ� ���̺� ����� Ű�� Ž��
void hash_lp_search(element item, element ht[])
{
	int i, hash_value;
	hash_value = i = hash_function(item.key);
	do
	{
		if (ht[i].key == item.key)
		{
			printf("Ž�� %d: ��ġ = %d\n", item.key, i);
			return;
		}
		i++;
		if (i == TABLE_SIZE)
			i = 0;
	} while (i != hash_value);
}

// �ؽ� ���̺��� ������ ���
void hash_lp_print(element ht[])
{
	int i;
	printf("\n===============================\n");
	for (i = 0; i < TABLE_SIZE; i++)
		printf("[%d]	%d\n", i, ht[i].key);
	printf("===============================\n\n");
}


// �ؽ� ���̺��� ����� ���� 
int main(void)
{
	int data[SIZE] = { 8, 1, 9, 6, 13 };
	element e;
	init_table(hash_table);   //�ؽ� ���̺� �ʱ�ȭ

	for (int i = 0; i < SIZE; i++) {
		e.key = data[i];
		hash_lp_add(e, hash_table);
		hash_lp_print(hash_table);
	}
	for (int i = 0; i < SIZE; i++) {
		e.key = data[i];
		hash_lp_search(e, hash_table);
	}
	return 0;
}