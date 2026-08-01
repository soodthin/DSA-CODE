#include<iostream>
using namespace std;
struct Node
{
	int info;
	Node* next, * prev;
};
void init(Node*& head, Node*& tail) {
	head = tail = nullptr;
}
bool isEmpty(Node* head) {
	return head == nullptr;
}
Node* createNode(const int& x) {
	Node* p = new Node();
	p->info = x;
	p->next = nullptr;
	p->prev = nullptr;
	return p;
}
void addHead(Node*& head, Node*& tail, const int& x) {
	Node* p = createNode(x);
	p->next = head;
	if (head != nullptr)
	{
		head->prev = p;
	}
	else
	{
		tail = p;
	}
	head = p;
}
void addTail(Node*& head, Node*& tail, const int& x) {
	Node* p = createNode(x);
	p->prev = tail;
	if (tail != nullptr)
	{
		tail->next = p;
	}
	else
	{
		head = p;
	}
	tail = p;
}
void printForward(Node* head) {
	if (isEmpty(head))
	{
		cout << "DANH SACH RONG!\n";
		return;
	}
	Node* p = head;
	while (p != nullptr)
	{
		cout << p->info << "\t";
		p = p->next;
	}
	cout << endl;
}
void printBackward(Node* tail) {
	if (isEmpty(tail))
	{
		cout << "DANH SACH RONG!\n";
		return;
	}
	Node* p = tail;
	while (p != nullptr)
	{
		cout << p->info << "\t";
		p = p->prev;
	}
	cout << endl;
}
void deleteHead(Node*& head, Node*& tail) {
	if (isEmpty(head))
	{
		cout << "DANH SACH RONG!\n";
		return;
	}
	Node* p = head;
	head = head->next;
	if (head != nullptr)
	{
		head->prev = nullptr;
	}
	else
	{
		tail = nullptr;
	}
	delete p;
	cout << "DA XOA PHAN TU DAU THANH CONG!\n";
}
void deleteTail(Node*& head, Node*& tail) {
	if (isEmpty(tail))
	{
		cout << "DANH SACH RONG!\n";
		return;
	}
	Node* p = tail;
	tail = tail->prev;
	if (tail != nullptr)
	{
		tail->next = nullptr;
	}
	else
	{
		head = nullptr;
	}
	delete p;
	cout << "DA XOA PHAN TU CUOI THANH CONG!\n";
}
void deleteAfter(Node*& head, Node*& tail, Node* q) {
	//th: q k ton tai or node cuoi cung
	if (q == nullptr || q->next == nullptr) {
		cout << "KHONG CO PHAN TU PHIA SAU DE XOA!\n";
		return;
	}

	Node* p = q->next;

	q->next = p->next;

	// th: p khong phai node cuoi cung
	if (p->next != nullptr) {
		p->next->prev = q; //cap nhat lien ket ve q
	}
	// th: p la node cuoi
	else {
		tail = q;
	}

	delete p;
	cout << "DA XOA PHAN TU PHIA SAU THANH CONG!\n";
}
/*void deleleAfter(Node*& head, Node*& tail, int x) {
	Node* q = head;
	while (q!=nullptr&& q->info!=x)
	{
		q = q->next;
	}
	if (q!=nullptr)
	{
		if (q->next!=nullptr) // kiem tra co phan tu can xoa khong?
		{
			Node* p = q->next;
			q->next = p->next;
			if (p->next==nullptr) // kiem tra phia sau co phan tu khong?
			{
				tail = q;
			}
			else
			{
				p->next->prev = q;
			}
			p->next=nullptr;
			p->prev=nullptr;
			delete p;
		}
	}
}*/
Node* searchNode(Node* head, int x) {
	Node* p = head;
	while (p != nullptr) {
		if (p->info == x) {
			return p;
		}
		p = p->next;
	}
	return nullptr;
}
int main() {
	Node* head, * tail;
	init(head, tail);


	addHead(head, tail, 30);
	addTail(head, tail, 40);
	addHead(head, tail, 21);
	addTail(head, tail, 599);
	printForward(head);
	int deletePoint;
	cout << "Nhap so can xoa phia sau: "; cin >> deletePoint;
	Node* q = searchNode(head, deletePoint);
	deleteAfter(head, tail, q);
	printForward(head);

	return 0;
}