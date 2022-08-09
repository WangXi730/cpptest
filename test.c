#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define ALLOC 20	/*预处理申请空间大小*/
typedef int data_t;

typedef struct SigleList_Node {
	data_t data;
	struct SigleList_Node* next;
}SigleList_Node;

typedef SigleList_Node* SigleList;//把链表定义为结点指针
//由于直接void不是很好，所以0代表初始化成功，-1代表初始化失败
//参数传入一个指针
size_t SigleList_init(SigleList* List) {
	(*List) = (SigleList)malloc(sizeof(SigleList_Node));
	if ((*List) == NULL) {
		return -1;
	}
	//不对头节点的数据进行初始化，这样可以利用编译器规则防止对头节点数据的访问
	//(*List)->data = 0;
	(*List)->next = 0;//尾结点的表示方式是next指针为nullptr
	return 0;
}
//销毁链表
void SigleList_destory(SigleList* List) {
	if (List == NULL) {
		return;//如果是空指针，那么什么都不用做
	}
	while ((*List) != NULL) {
		SigleList_Node* tmp = (*List);
		(*List) = (*List)->next;
		free(tmp);
	}
}
//创造结点
SigleList_Node* SigleList_buynode() {
	SigleList_Node* result = (SigleList_Node*)malloc(sizeof(SigleList_Node));
	if (result == NULL) {
		return result;
	}
	result->next = NULL;
	return result;
}
//尾插结点
size_t SigleList_push_back(SigleList* List, data_t data) {
	if (List == NULL) {
		return -1;
	}
	SigleList_Node* tmp = (*List);
	//调整到最后一个结点
	while (tmp->next != NULL) {
		tmp = tmp->next;
	}
	tmp->next = SigleList_buynode();
	if (tmp->next == NULL) {
		return -1;
	}
	//初始化结点
	tmp->next->data = data;
	tmp->next->next = NULL;
	return 0;
}
//头插结点
size_t SigleList_push_front(SigleList* List, data_t data) {
	if (List == NULL) {
		return -1;//空链表错误
	}
	SigleList_Node* tmp = SigleList_buynode();
	if (tmp == NULL) {
		return -1;//申请结点失败错误
	}
	tmp->next = (*List)->next;
	(*List)->next = tmp;
	tmp->data = data;
	return 0;
}
//插入方法：在目标结点后插入数据
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
//生成随机单链表，参数传入单链表期望长度，确保传入的参数是初始化过的链表，返回生成链表真实长度
size_t SigleList_random(SigleList* List, size_t size) {
	//如果大小指定为0，则直接返回即可
	if (size == 0) {
		return 0;
	}
	size_t n = size;//记录size
	while (size != 0) {
		//头插随机结点（之所以头插，因为效率高）
		if (SigleList_push_front(List, rand()) == -1) {
			return n - size;//申请结点失败，返回真实结点数量
		}
		--size;
	}
	return n - size;
}
//根据题目要求，遍历结果以一个指针通过参数返回，返回值为数组有效长度
size_t SigleList_traverse(SigleList List, data_t** res) {
	data_t* results = (data_t*)malloc(ALLOC * sizeof(data_t));
	//申请空间失败，或者List为NULL(未初始化，没有头结点)，遍历失败，返回NULL
	if (results == NULL || List == NULL) {
		return NULL;
	}
	List = List->next;//跳过头结点
	if (List == NULL) {
		return NULL;//链表没有数据，故返回NULL
	}
	int size = ALLOC;
	size_t i = 0;	//返回值下标
	while (1) {
		if (i >= size) {//如果空间不够，则扩大空间
			//安全期间，先保存数据
			data_t* tmp = results;
			results = (data_t*)realloc((void*)results, 1.5 * size * sizeof(data_t));
			size *= 1.5;
			if (results == NULL) {
				free((void*)tmp);//释放空间，遍历失败，返回NULL
				return NULL;
			}
		}
		results[i++] = List->data;
		List = List->next;
		//循环退出条件
		if (List == NULL) {
			break;
		}
	}
	(*res) = results;
	return i;
}
//通过输入的方法创造链表
size_t SigleList_stdin_creat(SigleList* List) {
	if (List == NULL || (*List) == NULL) {
		return -1;
	}
	//首先输入流读取数据到数组
	int n = 0;
	printf("您要创造多少个结点：");
	scanf("%d", &n);
	int* arr = (int*)malloc(n * sizeof(data_t));
	int i = 0;
	while (i != n) {
		scanf("%d", &arr[i++]);
	}
	//用数组中的数据创造链表
	while (i > 0) {
		SigleList_push_front(List, arr[--i]);
	}
	return 0;
}
//交换两个链表
size_t SigleList_swap(SigleList* List1, SigleList* List2) {
	if (List1 == NULL || List2 == NULL || (*List1) == NULL || (*List2) == NULL) {
		return -1;
	}
	SigleList tmp = (*List1);
	(*List1) = (*List2);
	(*List2) = tmp;
	return 0;
}
//单链表元素逆置
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
//比较规则
int Bigger(data_t a, data_t b) {
	return a >= b;
}
int Lower(data_t a, data_t b) {
	return a <= b;
}
typedef int (*rule)(data_t, data_t);
//手撕一个快排，这里由于也就是一次作业而已，就不把插入排序加进去了，也不并行了
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
	//递归结束条件
	if (first >= last) {
		return;
	}
	//开始排序
	int mid = Getmid(arr, first, last);
	if (mid == first) {
		_Swap(&arr[first], &arr[last]);
	}
	else if (mid == (first + last) / 2) {
		_Swap(&arr[(first + last) / 2], &arr[last]);
	}
	//现在last指向需要调整的位置
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
//单链表排序
size_t SigleList_sort(SigleList* List, rule r) {
	if (List == NULL || (*List) == NULL) {
		return -1;
	}
	//先遍历
	data_t* arr = 0;
	size_t n = SigleList_traverse((*List), &arr);
	if (n == 0) {
		return -1;
	}
	//对数组排序
	Sort(arr, n, r);
	SigleList_Node* tmp = (*List)->next;//指向第一个结点（非头结点）
	//通过赋值完成排序
	for (int i = 0; i < n; ++i) {
		tmp->data = arr[i];
		tmp = tmp->next;
	}
	return 0;
}
//由于不知道题目在说啥，所以根据我自己的理解，把第二个链表移动到第一个链表，并无效化第二个链表
//成功返回0，失败返回-1
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
//在非递减有序链表插入一个元素，使依旧有序的函数
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
//删除值为x的结点，返回0代表删除成功，-1代表删除失败或者无符合要求的结点
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
	SigleList_init(&l);//初始化
	SigleList_random(&l, 10);//生成随机单链表
	//SigleList_stdin_creat(&l);


	int* arr = 0;
	size_t n = SigleList_traverse(l, &arr);//遍历单链表
	printf("单链表l:\n");
	for (int i = 0; i < n; ++i) {
		printf("%d ", arr[i]);
	}
	printf("\n");
	free((void*)arr);
	arr = NULL;

	SigleList_reverse(&l);//反转单链表
	arr = 0;
	n = SigleList_traverse(l, &arr);//遍历单链表
	printf("反转后单链表l:\n");
	for (int i = 0; i < n; ++i) {
		printf("%d ", arr[i]);
	}
	printf("\n");
	free((void*)arr);
	arr = NULL;

	SigleList_sort(&l, Lower);//排序
	arr = 0;
	n = SigleList_traverse(l, &arr);//遍历单链表
	printf("排序后（非降序）单链表l:\n");
	for (int i = 0; i < n; ++i) {
		printf("%d ", arr[i]);
	}
	printf("\n");
	free((void*)arr);
	arr = NULL;

	SigleList l2;
	SigleList_init(&l2);//初始化
	SigleList_random(&l2, 10);//生成随机单链表
	arr = 0;
	n = SigleList_traverse(l2, &arr);//遍历单链表
	printf("单链表l2:\n");
	for (int i = 0; i < n; ++i) {
		printf("%d ", arr[i]);
	}
	printf("\n");
	free((void*)arr);
	arr = NULL;

	SigleList_sort(&l2, Lower);//排序单链表2
	arr = 0;
	n = SigleList_traverse(l2, &arr);//遍历单链表
	printf("排序后（非递减）单链表l2:\n");
	for (int i = 0; i < n; ++i) {
		printf("%d ", arr[i]);
	}
	printf("\n");
	free((void*)arr);
	arr = NULL;

	SigleList_move(&l, &l2);//把l2移动到l1，再排序
	SigleList_sort(&l,Lower);
	printf("单链表l2并入l后再排序的结果:\n");
	arr = 0;
	n = SigleList_traverse(l, &arr);//遍历单链表
	for (int i = 0; i < n; ++i) {
		printf("%d ", arr[i]);
	}
	printf("\n");
	free((void*)arr);
	arr = NULL;

	SigleList_insert_work1(&l, 1000);
	printf("在单链表l中插入数字1000结果:\n");
	arr = 0;
	n = SigleList_traverse(l, &arr);//遍历单链表
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
	printf("在单链表l中删除数字%d结果:\n",rm);
	arr = 0;
	n = SigleList_traverse(l, &arr);//遍历单链表
	for (int i = 0; i < n; ++i) {
		printf("%d ", arr[i]);
	}
	printf("\n");
	free((void*)arr);
	arr = NULL;

	SigleList_destory(&l);
	return 0;

}