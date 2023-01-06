/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwkim <juwkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 00:19:19 by juwkim            #+#    #+#             */
/*   Updated: 2023/01/07 00:19:19 by juwkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ELEMENTS 10000000L
int list[MAX_ELEMENTS];
int count;	// Ž�� ����Ƚ��

#define INDEX_SIZE 256

typedef struct {
	int key;
	int index;
} itable;
itable index_list[INDEX_SIZE];


//
// ���� Ž��
//
int seqsearch(int list[], int n, int searchnum)
{
	int i;

	count = 0;
	for (i = 0; i < n; i++) {
		count++;
		if (list[i] == searchnum)
			return i;
	}
	return -1;		// �߰ߵ��� ���� 
}

//
// ������ ���� Ž��
//
int seqsearch2(int list[], int n, int searchnum)
{
	count = 0;
	while (count < n && list[count] != searchnum)
		count++;

	if (count == n)	return -1;		// �߰ߵ��� ����
	else return count; 		//Ž�� ����
}
//
// ���� Ž��
//
int seqsearch3(int low, int high, int searchnum)
{
	int i;

	count = 0;
	for (i = low; i < high; i++) {
		count++;
		if (list[i] == searchnum)
			return i;
	}
	return -1;		// �߰ߵ��� ���� 
}


//
// ���� Ž��(�ݺ�)
//
int binsearch(int list[], int n, int searchnum)
{
	int left = 0;
	int right = n - 1;
	int middle;

	count = 0;
	while (left <= right) {		// ���� ���ڵ��� ���� ������
		count++;
		middle = (left + right) / 2;
		if (list[middle] == searchnum)
			return middle;
		else if (list[middle] < searchnum)
			left = middle + 1;
		else
			right = middle - 1;
	}
	return -1;		// �߰ߵ��� ���� 
}

//
// ���� Ž��(��ȯ ȣ�� ����)
//
int binsearch2(int list[], int low, int high, int searchnum)
{
	if (low > high)
		return -1; // �߰ߵ��� ����

	int middle = (low + high) / 2;
	count++;
	if (list[middle] == searchnum)
		return middle;
	else if (list[middle] < searchnum)
		return binsearch2(list, middle + 1, high, searchnum);
	else
		return binsearch2(list, low, middle - 1, searchnum);
}

//�ε��� ���̺� ����
void makeIndexTable(int list[], int size) {
	int interval = (size + INDEX_SIZE - 1) / INDEX_SIZE;

	for (int i = 0; i < INDEX_SIZE; i++) {
		index_list[i].index = i * interval;
		index_list[i].key = list[i * interval];
	}
}

/* INDEX_SIZE�� �ε��� ���̺��� ũ��,n�� ��ü �������� �� */
int index_search(int list[], int key, int n)
{
	int i, low, high;
	// Ű ���� ����Ʈ ���� ���� ���� �ƴϸ� Ž�� ���� 
	if (key < list[0])
		return -1;

	makeIndexTable(list, n);  //�ε��� ���̺� ����

	// �ε��� ���̺��� �����Ͽ� �ش�Ű�� ���� ����
	for (i = 1; i <= INDEX_SIZE; i++)
	{
		if (key <= index_list[i].key) {
			low = index_list[i - 1].index;
			high = index_list[i].index;
			break;
		}
	}

	if (i == INDEX_SIZE) {  // �ε��� ���̺��� ���̸� 
		low = index_list[INDEX_SIZE - 1].index;
		high = n;
	}
	// ����Ǵ� ������ ���� Ž�� 
	return seqsearch3(low, high, key);

}

//����Ž��
int search_interpolation(int list[], int n, int key)
{
	int low, high, j;
	count = 0;
	low = 0;
	high = n - 1;

	while ((list[low] <= key) && (key <= list[high])) {		//key�� list�� ���� �ȿ� ������
		count++;
		j = low + (high - low) / (list[high] - list[low]) * (key - list[low]);
		if (list[j] == key)
			return j;
		else if (list[j] > key)
			high = j - 1;
		else
			low = j + 1;
	}
	if (list[low] == key) return low;  	//Ž�� ����
	else return -1;  			// �߰ߵ��� ���� 
}

int main()
{
	int i;
	int search_number;  // Ž���� ����
	int return_value;
	clock_t start, finish;
	clock_t  duration;

	for (i = 0; i < MAX_ELEMENTS; i++)
		list[i] = i;

	printf("Ž���� ���ڸ� �Է��ϼ���: ");
	if (scanf("%d", &search_number) == 0)
		return 0;

	//����Ž������ �˻� 
	start = clock();
	return_value = seqsearch(list, MAX_ELEMENTS, search_number);
	finish = clock();

	duration = finish - start;
	printf("���� Ž���ð� = %d milliseconds\n", duration);
	printf("����Ƚ�� = %d\n ", count);

	if (return_value == -1) {
		printf("���ڰ� �߰ߵ��� �ʾҽ��ϴ�.\n");
	}
	else {
		printf("���ڰ� ��ġ %d���� �߰ߵǾ����ϴ�.\n", return_value);
	}

	//������ ����Ž������ �˻� 
	start = clock();
	return_value = seqsearch2(list, MAX_ELEMENTS, search_number);
	finish = clock();

	duration = finish - start;
	printf("������ ���� Ž���ð� = %d milliseconds\n", duration);
	printf("����Ƚ�� = %d\n ", count);

	if (return_value == -1) {
		printf("���ڰ� �߰ߵ��� �ʾҽ��ϴ�.\n");
	}
	else {
		printf("���ڰ� ��ġ %d���� �߰ߵǾ����ϴ�.\n", return_value);
	}


	//���� Ž��(�ݺ�)���� �˻�
	start = clock();
	return_value = binsearch(list, MAX_ELEMENTS, search_number);
	finish = clock();

	duration = finish - start;
	printf("���� Ž��(�ݺ� ����) �ð� = %d milliseconds\n", duration);
	printf("����Ƚ��=%d\n ", count);

	if (return_value == -1) {
		printf("���ڰ� �߰ߵ��� �ʾҽ��ϴ�.\n");
	}
	else {
		printf("���ڰ� ��ġ %d���� �߰ߵǾ����ϴ�.\n", return_value);
	}


	//���� Ž��(��ȯ)���� �˻�
	count = 0;
	start = clock();
	return_value = binsearch2(list, 0, MAX_ELEMENTS - 1, search_number);
	finish = clock();

	duration = finish - start;
	printf("���� Ž��(��ȯ ����) �ð� = %d milliseconds\n", duration);
	printf("����Ƚ��=%d\n ", count);

	if (return_value == -1) {
		printf("���ڰ� �߰ߵ��� �ʾҽ��ϴ�.\n");
	}
	else {
		printf("���ڰ� ��ġ %d���� �߰ߵǾ����ϴ�.\n", return_value);
	}


	//���� ���� Ž������ �˻�
	start = clock();
	return_value = index_search(list, search_number, MAX_ELEMENTS);
	finish = clock();

	duration = finish - start;
	printf("���� ���� Ž���ð� = %d milliseconds\n", duration);
	printf("����Ƚ��=%d\n ", count);

	if (return_value == -1) {
		printf("���ڰ� �߰ߵ��� �ʾҽ��ϴ�.\n");
	}
	else {
		printf("���ڰ� ��ġ %d���� �߰ߵǾ����ϴ�.\n", return_value);
	}


	//����Ž������ �˻� 
	start = clock();
	return_value = search_interpolation(list, MAX_ELEMENTS, search_number);
	finish = clock();

	duration = finish - start;
	printf("���� Ž���ð� = %d milliseconds\n", duration);
	printf("����Ƚ�� = %d\n ", count);
	if (return_value == -1) {
		printf("���ڰ� �߰ߵ��� �ʾҽ��ϴ�.\n");
	}
	else {
		printf("���ڰ� ��ġ %d���� �߰ߵǾ����ϴ�.\n", return_value);
	}

	return 0;
}