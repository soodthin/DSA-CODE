#include<iostream>
using namespace std;
#define MAX 100
struct Queue
{
	int a[MAX];
	int front;
	int rear;
};

void init(Queue&q) {
	q.front = -1;
	q.rear = -1;
}

bool isFull(Queue q) {
	return q.rear == MAX - 1;
}
bool isEmpty(Queue q) {
	return q.front == -1;
}
void enqueue(Queue& q, int x) {
	if (isFull(q))
	{
		cout << "Mang day!\n";
		return;
	}
	if (isEmpty(q))
	{
		q.front++;
	}
	q.rear++;//vi tri them cuoi ++
	q.a[q.rear] = x;
}

void dequeue(Queue& q) {
	if (!isEmpty(q))
	{
		q.front++;
		if (q.front>q.rear)
		{
			q.front = -1;
			q.rear = -1;
		}
	}
}
void output(Queue q) {
	for (int i = q.front; i <= q.rear; i++)
	{
		cout << q.a[q.front] << "\t";
	}
}
int get(Queue q) {
	return q.a[q.front];
}
int main() {
	Queue q;
	init(q);
	enqueue(q, 10);
	enqueue(q, 20);
	enqueue(q, 30);
	dequeue(q);
	cout << get(q);
	return 0;
}