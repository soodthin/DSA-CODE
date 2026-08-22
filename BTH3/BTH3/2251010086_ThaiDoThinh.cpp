#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<iomanip>
using namespace std;
//Ma san pham,Ten san pham,So luong ton kho,Gia san pham,Nha cung cap
struct SanPham
{
	int maSP, soLuongTonKho;
	string tenSP, nhaCungCap;
	double giaSP;
};
struct Node
{
	SanPham info;
	Node* next;
};
void init(Node*& head) {
	head = nullptr;
}
bool isEmpty(Node* head) {
	return head == nullptr;
}
Node* createNode(SanPham& sp) {
	Node* p = new Node();
	p->info = sp;
	p->next = nullptr;
	return p;
}
void addTail(Node*& head, SanPham& sp) {
	Node* p = createNode(sp);
	if (isEmpty(head))
	{
		head = p;
		return;
	}
	else
	{
		Node* tail = head;
		while (tail->next!=nullptr)
		{
			tail = tail->next;
		}
		tail->next = p;
	}
}
void readFile(Node*& head, const string&fileName) {
	ifstream fileInput(fileName);
	if (!fileInput.is_open())
	{
		cout << "Khong the mo file " << fileName << endl;
		return;
	}
	string header;
	getline(fileInput, header);

	SanPham sp;
	string maSPstr, soLuongTonKhoStr, giaSPstr;
	while (getline(fileInput,maSPstr,','))
	{
		sp.maSP = stoi(maSPstr);
		
		getline(fileInput, sp.tenSP, ',');

		getline(fileInput, soLuongTonKhoStr, ',');
		sp.soLuongTonKho = stoi(soLuongTonKhoStr);


		getline(fileInput, giaSPstr, ',');
		sp.giaSP = stod(giaSPstr);

		getline(fileInput, sp.nhaCungCap, '\n');

		addTail(head, sp);
	}
	fileInput.close();
}
void printProd(SanPham sp) {
	cout << left << setw(15) << sp.maSP
		<< setw(40) << sp.tenSP
		<< setw(20) << sp.soLuongTonKho
		<< fixed << setprecision(0) << setw(20) << sp.giaSP
		<< setw(20) << sp.nhaCungCap << endl;
}
void print(Node* head) {
	if (isEmpty(head))
	{
		cout << "Danh sach rong\n";
		return;
	}
	cout << left << setw(15) << "\nMA SAN PHAM"
		<< setw(36) << "TEN SAN PHAM"
		<< setw(23) << "SO LUONG TON KHO"
		<< fixed << setprecision(0)<< setw(20) << "GIA SAN PHAM"
		<< setw(20) << "NHA CUNG CAP" << endl;
	cout << string(110, '-') << endl;
	Node* p = head;
	while (p!=nullptr)
	{
		printProd(p->info);
		p = p->next;
	}
}
void deleteBeforeId(Node*& head) {
	int id;
	cout << "\nNhap ma san pham can xoa phia truoc: "; cin >> id;
	if (isEmpty(head))
	{
		cout << "Danh sach rong!\n"; return;
	}
	if (head->info.maSP==id)
	{
		cout << "San pham dang o vi tri dau tien\n"; return;
	}
	if (head->next!=nullptr&&head->next->info.maSP==id)
	{
		Node* temp = head;
		head = head->next;
		delete temp;
		cout << "Da xoa thanh cong!\n";
		return;
	}
	Node* prev = head;
	while (prev->next!=nullptr&&prev->next->next!=nullptr&&prev->next->next->info.maSP!=id)
	{
		prev = prev->next;
	}
	if (prev->next==nullptr||prev->next->next==nullptr)
	{
		cout << "Khong tim thay san pham\n";
		return;
	}
	Node* temp = prev->next;
	prev->next = temp->next;
	delete temp;
	cout << "Da xoa thanh cong!\n";
}
void searchByName(Node* head) {
	cin.ignore();
	string name;
	cout << "\nNhap ten san pham can tim: "; getline(cin,name);
	Node* p = head;
	while (p!=nullptr)
	{
		if (p->info.tenSP.find(name) < p->info.tenSP.length()) 
		{
			printProd(p->info);
		}
		p = p->next;
	}
}
void interchangeSortDESC(Node* head) {
	if (isEmpty(head))
	{
		return;
	}
	for (Node* p = head; p !=nullptr ; p=p->next)
	{
		for (Node* q = p->next; q !=nullptr; q=q->next)
		{
			if (p->info.soLuongTonKho<q->info.soLuongTonKho)
			{
				swap(p->info, q->info);
			}
		}
	}
}
int main() {
	Node* head;
	init(head);
	readFile(head, "SanPham.txt");
	print(head);
	/*deleteBeforeId(head);
	print(head);*/
	/*searchByName(head);*/
	interchangeSortDESC(head);
	print(head);
	return 0;
}