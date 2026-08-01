#include<iostream>
using namespace std;
struct Node
{
	int info;
	Node* next;
};
struct StackList
{
	Node* top;
	int count;
};
void init(StackList& s) {
	s.top = nullptr;
	s.count = 0;
}
bool isEmpty(StackList s) {
	return s.top == nullptr;
}
bool isFull(StackList s) {
	return s.count >= 100;
}
void push(StackList& s, int x) {
	if (!isFull(s))
	{
		Node* p = new Node();
		p->info = x;
		p->next = s.top;
		s.top = p;
		s.count++;
	}
}
void pop(StackList& s) {
	if (!isEmpty(s))
	{
		Node* p = s.top;
		s.top = p->next;
		delete p;
		s.count--;
	}
}
int get(const StackList s) {
	return s.top->info;
}
void convertToBinary(int n) {
	if (n == 0)
	{
		cout << "0\n";
		return;
	}
	StackList s;
	init(s);
	while (n != 0)
	{
		push(s, n % 2);
		n /= 2;
	}
	cout << "Ket qua chuyen sang nhi phan\n";
	while (!isEmpty(s))
	{
		cout << get(s);
		pop(s);
	}
	cout << endl;
}
int main() {
	int n;
	cout << "Nhap n:"; cin >> n;
	convertToBinary(n);
	return 0;
}