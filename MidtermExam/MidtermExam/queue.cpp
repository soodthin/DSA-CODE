#include <iostream>
using namespace std;
const int MAX = 100;

// Queue (danh sach dac)
struct Queue
{
	int arr[MAX];
	int front;
	int rear;
};

void init(Queue& q)
{
	q.front = q.rear = -1;
}

bool isEmpty(Queue q)
{
	return q.front == -1;
}

bool isFull(Queue q)
{
	return q.rear == MAX - 1;
}

void enqueue(Queue& q, int x)
{
	if (!isFull(q))
	{
		if (isEmpty(q))
			q.front = 0;

		q.arr[++q.rear] = x;
	}
}

void dequeue(Queue& q)
{
	if (!isEmpty(q))
		q.front++;
}

// Queue (danh sach lien ket don)
struct Node
{
	int info;
	Node* next;
};

void init(Node*& head, Node*& tail)
{
	head = tail = NULL;
}

bool isEmpty(Node* head)
{
	return head == NULL;
}

void enqueue(Node*& head, Node*& tail, int x)
{
	Node* p = new Node;
	p->info = x;
	p->next = NULL;

	if (tail == NULL) // khi danh sach rong
		head = p;
	else
		tail->next = p;
	tail = p;
}

void dequeue(Node*& head, Node*& tail)
{
	if (!isEmpty(head))
	{
		Node* p = head;
		head = p->next;
		if (head == NULL) // danh sach chi co 1 phan tu
			tail == NULL;
		delete p;
	}
}

