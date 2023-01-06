/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwkim <juwkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 00:19:14 by juwkim            #+#    #+#             */
/*   Updated: 2023/01/07 00:19:14 by juwkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define SWAP(x,y,t)	((t)=(x),(x)=(y),(y)=(t))
#define MAX_SIZE	1024

int list[] = { 5, 3, 8, 4, 9, 1, 6, 2, 7 };
int size = sizeof(list) / sizeof(list[0]);

void printArray(int arr[], int n, char* str)
{
	int i;
	printf("%s = ", str);
	for (i = 0; i < n; i++) printf("%3d", arr[i]);
	printf("\n");
}

void printStep(int arr[], int n, int val)
{
	int i;
	printf("  Step %2d = ", val);
	for (i = 0; i < n; i++) printf("%3d", arr[i]);
	printf("\n");
}

// ���� ���� �Լ� 
void selection_sort(int list[], int n)
{
	int i, j, least, tmp;
	for (i = 0; i < n - 1; i++) {
		least = i;
		for (j = i + 1; j < n; j++)				// �ּҰ� Ž�� 
			if (list[j] < list[least])
				least = j;
		SWAP(list[i], list[least], tmp);
		printStep(list, n, i + 1);		// �߰� ���� ��¿� ����
	}
}

void insertion_sort(int list[], int n)
{
	int i, j, key;
	for (i = 1; i < n; i++) {
		key = list[i];
		for (j = i - 1; j >= 0 && list[j] > key; j--) {
			list[j+1] = list[j];
			// ���ڵ��� ������ �̵�
		}
		list[j + 1] = key;
		// �߰��� ��ġ�� key�� ����
		printStep(list, n, i);			// �߰� ���� ��¿� ����
	}
}

// ������ ���� ���� �Լ�
void bubble_sort(int list[], int n)
{
	int i, j, flag = 1, tmp;
	for (i = n - 1; i > 0; i--) {
		flag = 0;
		for (j = 0; j < i; j++)
			if (list[j] > list[j+1]) {
				SWAP(list[j], list[j+1], tmp);
				flag = 1;			// ��ȯ �߻�
			}
		if (flag == 0)					// ��ȯ�� ������ ����
			break;
		printStep(list, n, n - i);			// �߰� ���� ��¿� ����
	}
}

int ascend(int x, int y) { return y - x; }	// �������� ���Լ�
int descend(int x, int y) { return x - y; }	// �������� ���Լ�

// �Լ� �����͸� �Ű������� �޴� �������� �Լ�
void insertion_sort_fn(int list[], int n, int(*f)(int, int))
{
	int i, j, key;
	for (i = 1; i < n; i++) {
		key = list[i];
		for (j = i - 1; j >= 0 && f(list[j], key) < 0; j--)
			list[j + 1] = list[j];		// ���ڵ��� ������ �̵�
		list[j + 1] = key;
		printStep(list, n, i);			// �߰� ���� ��¿� ����
	}
}



// gap ��ŭ ������ ��ҵ��� ���� ����. ������ ������ first���� last 
static void sortGapInsertion(int list[], int first, int last, int gap)
{
	int i, j, key;
	for (i = first + gap; i <= last; i = i + gap) {
		key = list[i];
		for (j = i - gap; j >= first && key < list[j]; j -= gap)
			list[j + gap] = list[j];
			//���ڵ��� gap��ŭ ������ �̵�
		list[j + gap] = key;
//�߰��� ��ġ�� key�� ����
	}
}
// �� ���� �˰����� �̿��� int �迭�� ������������ �����ϴ� �Լ� 
void shell_sort(int list[], int n)
{
	int i, gap, count = 0;
	for (gap = n / 2; gap > 0; gap = gap / 2) {
		for (i = 0; i < gap; i++) 
			sortGapInsertion(list, i, n - 1, gap);
		printStep(list, n, ++count);		// �߰� ���� ��¿� ���� 
	}
}

int mi = 1;
static void merge(int list[], int left, int mid, int right)
{
	int i, j, k = left, l;				// k�� ���ĵ� ����Ʈ�� ���� �ε���
	static int sorted[MAX_SIZE];		// ���յ� ����Ʈ ������ ���� �ӽù迭

	// ���� ���ĵ� list�� ����
	for (i = left, j = mid + 1; i <= mid && j <= right; )
	{
		if (list[i] <= list[j])
			sorted[k++] = list[i++];
		else
			sorted[k++] = list[j++];
	}

	// ���ʿ� ���� �ִ� ���ڵ��� �ϰ� ����
	if (i > mid)
	{
		for (l = j; l <= right; l++)
			sorted[k++] = list[l];
	}
	else
	{
		for (l = i; l <= mid; l++)
			sorted[k++] = list[l];
	}

	// �迭 sorted[]�� ����Ʈ�� �迭 list[]�� �ٽ� ����
	for (l = left; l <= right; l++) {
		list[l] = sorted[l];
	}

	printStep(list, size, mi++);			// �߰� ���� ��¿� ����
}

// ���� ���� �˰����� �̿��� int �迭�� ������������ �����ϴ� �Լ�
void merge_sort(int list[], int left, int right) {

	if (left < right) {
		int mid = (left + right) / 2;		// ����Ʈ�� �յ� ����
		merge_sort(list, left, mid);		// �κ� ����Ʈ ����
		merge_sort(list, mid + 1, right);	// �κ� ����Ʈ ����
		merge(list, left, mid, right);		// ����
	}
}

int qi = 1;
int partition(int list[], int left, int right)
{
	int tmp;
	int low = left + 1;
	int high = right;
	int pivot = list[left]; 		// �ǹ� ���� 
	while (low < high) {			// low�� high�� �������� �ʴ� �� �ݺ� 

		while (low <= high && list[low] < pivot)
			low++;
		while (high >= low && list[high] > pivot)
			high--;

		if (low < high)				// ���õ� �� ���ڵ� ��ȯ 
			SWAP(list[low], list[high], tmp);
	}
	SWAP(list[left], list[high], tmp);	// high�� �ǹ� �׸� ��ȯ
	printStep(list, size, qi++);
	return high;
}

// �� ���� �˰����� �̿��� �迭�� left ~ right �׸���� ������������ �����ϴ� �Լ�
void quick_sort(int list[], int left, int right)
{
	int q;
	if (left < right) { // ���� ������ 2�� �̻��� ���
		q = partition(list, left, right);	// �¿�� ���� 
		quick_sort(list, left, q - 1);		// ���� �κи���Ʈ�� �� ����
		quick_sort(list, q + 1, right);		// ������ �κи���Ʈ�� �� ����
	}
}

int compare(const void* e1, const void* e2)
{
	int* p1 = (int*)e1;
	int* p2 = (int*)e2;
	return (*p1 - *p2); // �������� ����
	//return -(*p1 - *p2); // �������� ����

}

void main()
{
	int sort_method = 0;
	char end[5] = "n";

	printArray(list, size, "Original ");	// ���� �� �迭 ��� 
	do {

		list[0] = 5, list[1] = 3, list[2] = 8, list[3] = 4, list[4] = 9, list[5] = 1, list[6] = 6, list[7] = 2, list[8] = 7;

		printf("\n\n");
		printArray(list, size, "Original ");	// ���� �� �迭 ��� 
		printf("(1��: ��������, 2��: ��������, 3��: ��������, 4��: �������� ��������, 5��: �� ����, 6��: �պ� ����, 7��: �� ����, (1-7)�̿��� ���� ��ȣ: ����)\n ���� ����� �����ϼ���: ");
		if (scanf("%d", &sort_method) == 0)
			return;
		switch (sort_method) {
		case 1:
			selection_sort(list, size);		// ���� ���� ���� 
			printArray(list, size, "Selection");	// ���� �� �迭 ��� 
			break;
		case 2:
			insertion_sort(list, size); 		// ���� ���� ���� 
			printArray(list, size, "Insertion");		// ���� �� �迭 ��� 
			break;
		case 3:
			bubble_sort(list, size); 		// ���� ���� ���� 
			printArray(list, size, "Bubble   ");	// ���� �� �迭 ��� 
			break;
		case 4:
			insertion_sort_fn(list, size, descend); 	// �������� �������� �˰���
			printArray(list, size, "Insert-De");	// ���� �� �迭 ��� 
			break;
		case 5:
			shell_sort(list, size); 			// ������ �˰���
			printArray(list, size, "ShellSort");		// ���� �� �迭 ��� 
			break;
		case 6:
			merge_sort(list, 0, size - 1); 		// �պ����� �˰���
			printArray(list, size, "MergeSort");	// ���� �� �迭 ��� 
			break;
		case 7:
			quick_sort(list, 0, size - 1); 		// ������ �˰���
			//qsort((void *)list, size, sizeof(int), compare);  // ������ ���̺귯�� �Լ� ȣ��
			printArray(list, size, "QuickSort");	// ���� �� �迭 ��� 
			break;
		default:
			printf("������ �����ðڽ��ϱ�?(y/n) :");
			if (scanf("%s", end) == 0)
				return;
			break;
		}
	} while (strcmp(end, "n") == 0);
}