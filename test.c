#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define ALLOC 20	/*Ԥ��������ռ��С*/
typedef int data_t;

typedef struct SigleList_Node {
	data_t data;
	struct SigleList_Node* next;
}SigleList_Node;

typedef SigleList_Node* SigleList;//��������Ϊ���ָ��
//����ֱ��void���Ǻܺã�����0�����ʼ���ɹ���-1�����ʼ��ʧ��
//��������һ��ָ��
size_t SigleList_init(SigleList* List) {
	(*List) = (SigleList)malloc(sizeof(SigleList_Node));
	if ((*List) == NULL) {
		return -1;
	}
	//����ͷ�ڵ�����ݽ��г�ʼ���������������ñ����������ֹ��ͷ�ڵ����ݵķ���
	//(*List)->data = 0;
	(*List)->next = 0;//β���ı�ʾ��ʽ��nextָ��Ϊnullptr
	return 0;
}
//��������
void SigleList_destory(SigleList* List) {
	if (List == NULL) {
		return;//����ǿ�ָ�룬��ôʲô��������
	}
	while ((*List) != NULL) {
		SigleList_Node* tmp = (*List);
		(*List) = (*List)->next;
		free(tmp);
	}
}
//������
SigleList_Node* SigleList_buynode() {
	SigleList_Node* result = (SigleList_Node*)malloc(sizeof(SigleList_Node));
	if (result == NULL) {
		return result;
	}
	result->next = NULL;
	return result;
}
//β����
size_t SigleList_push_back(SigleList* List, data_t data) {
	if (List == NULL) {
		return -1;
	}
	SigleList_Node* tmp = (*List);
	//���������һ�����
	while (tmp->next != NULL) {
		tmp = tmp->next;
	}
	tmp->next = SigleList_buynode();
	if (tmp->next == NULL) {
		return -1;
	}
	//��ʼ�����
	tmp->next->data = data;
	tmp->next->next = NULL;
	return 0;
}
//ͷ����
size_t SigleList_push_front(SigleList* List, data_t data) {
	if (List == NULL) {
		return -1;//���������
	}
	SigleList_Node* tmp = SigleList_buynode();
	if (tmp == NULL) {
		return -1;//������ʧ�ܴ���
	}
	tmp->next = (*List)->next;
	(*List)->next = tmp;
	tmp->data = data;
	return 0;
}
//���뷽������Ŀ������������
size_t SigleList_insert(SigleList_Node* dest, data_t data) {
	if (dest == NULL) {
		return -1;
	}
	SigleList_Node* tmp = SigleList_buynode();
	if (tmp == NULL) {
		return -1;
	}
	tmp->data = data;
	tmp->next = dest->next;
	dest->next = tmp;
	return 0;
}
//��������������������뵥�����������ȣ�ȷ������Ĳ����ǳ�ʼ������������������������ʵ����
size_t SigleList_random(SigleList* List, size_t size) {
	//�����Сָ��Ϊ0����ֱ�ӷ��ؼ���
	if (size == 0) {
		return 0;
	}
	size_t n = size;//��¼size
	while (size != 0) {
		//ͷ�������㣨֮����ͷ�壬��ΪЧ�ʸߣ�
		if (SigleList_push_front(List, rand()) == -1) {
			return n - size;//������ʧ�ܣ�������ʵ�������
		}
		--size;
	}
	return n - size;
}
//������ĿҪ�󣬱��������һ��ָ��ͨ���������أ�����ֵΪ������Ч����
size_t SigleList_traverse(SigleList List, data_t** res) {
	data_t* results = (data_t*)malloc(ALLOC * sizeof(data_t));
	//����ռ�ʧ�ܣ�����ListΪNULL(δ��ʼ����û��ͷ���)������ʧ�ܣ�����NULL
	if (results == NULL || List == NULL) {
		return NULL;
	}
	List = List->next;//����ͷ���
	if (List == NULL) {
		return NULL;//����û�����ݣ��ʷ���NULL
	}
	int size = ALLOC;
	size_t i = 0;	//����ֵ�±�
	while (1) {
		if (i >= size) {//����ռ䲻����������ռ�
			//��ȫ�ڼ䣬�ȱ�������
			data_t* tmp = results;
			results = (data_t*)realloc((void*)results, 1.5 * size * sizeof(data_t));
			size *= 1.5;
			if (results == NULL) {
				free((void*)tmp);//�ͷſռ䣬����ʧ�ܣ�����NULL
				return NULL;
			}
		}
		results[i++] = List->data;
		List = List->next;
		//ѭ���˳�����
		if (List == NULL) {
			break;
		}
	}
	(*res) = results;
	return i;
}
//ͨ������ķ�����������
size_t SigleList_stdin_creat(SigleList* List) {
	if (List == NULL || (*List) == NULL) {
		return -1;
	}
	//������������ȡ���ݵ�����
	int n = 0;
	printf("��Ҫ������ٸ���㣺");
	scanf("%d", &n);
	int* arr = (int*)malloc(n * sizeof(data_t));
	int i = 0;
	while (i != n) {
		scanf("%d", &arr[i++]);
	}
	//�������е����ݴ�������
	while (i > 0) {
		SigleList_push_front(List, arr[--i]);
	}
	return 0;
}
//������������
size_t SigleList_swap(SigleList* List1, SigleList* List2) {
	if (List1 == NULL || List2 == NULL || (*List1) == NULL || (*List2) == NULL) {
		return -1;
	}
	SigleList tmp = (*List1);
	(*List1) = (*List2);
	(*List2) = tmp;
	return 0;
}
//������Ԫ������
size_t SigleList_reverse(SigleList* List) {
	SigleList_Node* results = NULL;
	while ((*List)->next != NULL) {
		SigleList_Node* tmp = (*List)->next;
		(*List)->next = tmp->next;
		tmp->next = results;
		results = tmp;
	}
	(*List)->next = results;
	return 0;
}
//�ȽϹ���
int Bigger(data_t a, data_t b) {
	return a >= b;
}
int Lower(data_t a, data_t b) {
	return a <= b;
}
typedef int (*rule)(data_t, data_t);
//��˺һ�����ţ���������Ҳ����һ����ҵ���ѣ��Ͳ��Ѳ�������ӽ�ȥ�ˣ�Ҳ��������
size_t Getmid(data_t* arr, size_t first, size_t last) {
	data_t tmp = arr[(first + last) / 2];
	if ((tmp - arr[first]) * (arr[last] - tmp) >= 0) {
		return (first + last) / 2;
	}
	else if ((arr[first] - tmp) * (arr[last] - arr[first]) >= 0) {
		return first;
	}
	return last;
}
void _Swap(data_t* a, data_t* b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}
void _Sort(data_t* arr, int first, int last, rule r) {
	//�ݹ��������
	if (first >= last) {
		return;
	}
	//��ʼ����
	int mid = Getmid(arr, first, last);
	if (mid == first) {
		_Swap(&arr[first], &arr[last]);
	}
	else if (mid == (first + last) / 2) {
		_Swap(&arr[(first + last) / 2], &arr[last]);
	}
	//����lastָ����Ҫ������λ��
	int ptr = last;
	int left = first;
	int right = last;
	while (left < right) {
		while (left < right && r(arr[left], arr[ptr])) {
			++left;
		}
		_Swap(&arr[left], &arr[right]);
		ptr = left;
		while (left < right && r(arr[ptr], arr[right])) {
			--right;
		}
		_Swap(&arr[left], &arr[right]);
		ptr = right;
	}
	_Sort(arr, first, ptr - 1, r);
	_Sort(arr, ptr + 1, last, r);
}
void Sort(data_t* arr, size_t n, rule r) {
	size_t first = 0;
	size_t last = n - 1;
	_Sort(arr, first, last, r);
}
//����������
size_t SigleList_sort(SigleList* List, rule r) {
	if (List == NULL || (*List) == NULL) {
		return -1;
	}
	//�ȱ���
	data_t* arr = 0;
	size_t n = SigleList_traverse((*List), &arr);
	if (n == 0) {
		return -1;
	}
	//����������
	Sort(arr, n, r);
	SigleList_Node* tmp = (*List)->next;//ָ���һ����㣨��ͷ��㣩
	//ͨ����ֵ�������
	for (int i = 0; i < n; ++i) {
		tmp->data = arr[i];
		tmp = tmp->next;
	}
	return 0;
}
//���ڲ�֪����Ŀ��˵ɶ�����Ը������Լ�����⣬�ѵڶ��������ƶ�����һ����������Ч���ڶ�������
//�ɹ�����0��ʧ�ܷ���-1
size_t SigleList_move(SigleList* L1, SigleList* L2) {
	if (L1 == NULL || L2 == NULL) {
		return -1;
	}
	if ((*L2) == NULL) {
		return 0;
	}
	else if ((*L2)->next == NULL) {
		SigleList_destory(&L2);
		return 0;
	}
	SigleList_Node* ptr = (*L1);
	while (ptr->next != NULL) {
		ptr = ptr->next;
	}
	ptr->next = (*L2)->next;
	(*L2)->next = NULL;
	SigleList_destory(L2);
	return 0;
}
//�ڷǵݼ������������һ��Ԫ�أ�ʹ��������ĺ���
void SigleList_insert_work1(SigleList* l, data_t data) {
	if (l == NULL || (*l) == NULL) {
		return;
	}
	SigleList_Node* tmp = *l;
	while (tmp->next != NULL) {
		if (tmp->next->data > data) {
			break;
		}
		tmp = tmp->next;
	}
	SigleList_insert(tmp, data);
}
//ɾ��ֵΪx�Ľ�㣬����0����ɾ���ɹ���-1����ɾ��ʧ�ܻ����޷���Ҫ��Ľ��
size_t SigleList_erase(SigleList* l, data_t x) {
	if (l == NULL || (*l) == NULL) {
		return -1;
	}
	SigleList_Node* tmp = (*l);
	while (tmp->next != NULL && tmp->next->data != x) {
		tmp = tmp->next;
	}
	if (tmp == NULL || tmp->next == NULL) {
		return -1;
	}
	SigleList_Node* re = tmp->next;
	tmp->next = re->next;
	free(re);
	return 0;
}
int main() {
	srand(time(0));
	SigleList l;
	SigleList_init(&l);//��ʼ��
	SigleList_random(&l, 10);//�������������
	//SigleList_stdin_creat(&l);


	int* arr = 0;
	size_t n = SigleList_traverse(l, &arr);//����������
	printf("������l:\n");
	for (int i = 0; i < n; ++i) {
		printf("%d ", arr[i]);
	}
	printf("\n");
	free((void*)arr);
	arr = NULL;

	SigleList_reverse(&l);//��ת������
	arr = 0;
	n = SigleList_traverse(l, &arr);//����������
	printf("��ת������l:\n");
	for (int i = 0; i < n; ++i) {
		printf("%d ", arr[i]);
	}
	printf("\n");
	free((void*)arr);
	arr = NULL;

	SigleList_sort(&l, Lower);//����
	arr = 0;
	n = SigleList_traverse(l, &arr);//����������
	printf("����󣨷ǽ��򣩵�����l:\n");
	for (int i = 0; i < n; ++i) {
		printf("%d ", arr[i]);
	}
	printf("\n");
	free((void*)arr);
	arr = NULL;

	SigleList l2;
	SigleList_init(&l2);//��ʼ��
	SigleList_random(&l2, 10);//�������������
	arr = 0;
	n = SigleList_traverse(l2, &arr);//����������
	printf("������l2:\n");
	for (int i = 0; i < n; ++i) {
		printf("%d ", arr[i]);
	}
	printf("\n");
	free((void*)arr);
	arr = NULL;

	SigleList_sort(&l2, Lower);//��������2
	arr = 0;
	n = SigleList_traverse(l2, &arr);//����������
	printf("����󣨷ǵݼ���������l2:\n");
	for (int i = 0; i < n; ++i) {
		printf("%d ", arr[i]);
	}
	printf("\n");
	free((void*)arr);
	arr = NULL;

	SigleList_move(&l, &l2);//��l2�ƶ���l1��������
	SigleList_sort(&l,Lower);
	printf("������l2����l��������Ľ��:\n");
	arr = 0;
	n = SigleList_traverse(l, &arr);//����������
	for (int i = 0; i < n; ++i) {
		printf("%d ", arr[i]);
	}
	printf("\n");
	free((void*)arr);
	arr = NULL;

	SigleList_insert_work1(&l, 1000);
	printf("�ڵ�����l�в�������1000���:\n");
	arr = 0;
	n = SigleList_traverse(l, &arr);//����������
	for (int i = 0; i < n; ++i) {
		printf("%d ", arr[i]);
	}
	printf("\n");
	free((void*)arr);
	arr = NULL;

	data_t rm = l->next->data;
	SigleList_Node* ptr1 = l->next;
	for (int i = 0; i < n / 2; ++i) {
		ptr1 = ptr1->next;
	}
	if (ptr1 != NULL) {
		rm = ptr1->data;
	}
	SigleList_erase(&l, rm);
	printf("�ڵ�����l��ɾ������%d���:\n",rm);
	arr = 0;
	n = SigleList_traverse(l, &arr);//����������
	for (int i = 0; i < n; ++i) {
		printf("%d ", arr[i]);
	}
	printf("\n");
	free((void*)arr);
	arr = NULL;

	SigleList_destory(&l);
	return 0;

}