#include <iostream>
using namespace std;
const int MAX = 100;

// Stack (danh sach dac)
struct Stack
{
	int arr[MAX];
	int top;
};

void init(Stack& s)
{
	s.top = -1;
}

bool isEmpty(Stack s)
{
	return s.top == -1;
}

bool isFull(Stack s)
{
	return s.top == MAX - 1;
}

void push(Stack& s, int x) // them cuoi
{
	if (!isFull(s))
		s.arr[++s.top] = x;
}

void pop(Stack& s) // xoa cuoi
{
	if (!isEmpty(s))
		s.top--;
}

int get(Stack s)
{
	return s.arr[s.top];
}

// Stack (danh sach lien ket don)
struct Node
{
	int info;
	Node* next;
};

void init(Node*& head)
{
	head = NULL;
}

bool isEmpty(Node* head)
{
	return head == NULL;
}

void push(Node*& head, int x) // them dau
{
	Node* p = new Node;
	p->info = x;
	p->next = head;
	head = p;
}

void pop(Node*& head) // xoa dau
{
	if (!isEmpty(head))
	{
		Node* p = head;
		head = p->next;
		p->next = NULL; // co hay khong deu duoc
		delete p;
	}
}

void chuyen10Sang2(int n)
{
	Stack s;
	init(s);
	while (n > 0)
	{
		push(s, n % 2);
		n /= 2;
	}

	while (!isEmpty(s))
	{
		int x = get(s);
		cout << x;
		pop(s);
	}
}

int main()
{
	cout << "He nhi phan cua so 5: ";
	chuyen10Sang2(5);
	cout << endl;
	system("pause");
	return 0;
}
