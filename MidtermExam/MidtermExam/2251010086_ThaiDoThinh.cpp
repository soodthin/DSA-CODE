#include<iostream>
#include<fstream>
#include<iomanip>
#include<sstream>
#include<string>
using namespace std;
struct SanPham
{
	int maSP;
	string tenSP;
	int soLuongTonKho;
	double giaSP;
	string nhaCungCap;
};
struct Node
{
	SanPham info;
	Node* next;
};
struct DanhSach
{
	int soLuong;
	Node* head;
};
bool isEmpty(DanhSach& ds) {
	return ds.head == nullptr;
}
void init(DanhSach& ds) {
	ds.head = nullptr;
	ds.soLuong = 0;
}

Node* createNode(SanPham sp) {
	Node* p = new Node();
	p->info = sp;
	p->next = nullptr;
	return p;
}
void addTail(DanhSach& ds, SanPham sp) {
	Node* p = createNode(sp);
	if (isEmpty(ds)) ds.head = p;
	else
	{
		Node* tail = ds.head;
		while (tail->next != nullptr)
		{
			tail = tail->next;
		}
		tail->next = p;
	}
	ds.soLuong++;
}
void readFile(DanhSach& ds, const string& fileName) {
	ifstream fileInput(fileName);
	if (!fileInput.is_open())
	{
		cout << "Khong the doc file " << fileName << endl;
		return;
	}
	string title;
	getline(fileInput, title);
	SanPham sp;
	string maSPstr, soLuongTonKhoStr, giaSPstr;
	while (getline(fileInput, maSPstr, ','))
	{
		sp.maSP = stoi(maSPstr);

		getline(fileInput, sp.tenSP, ',');

		getline(fileInput, soLuongTonKhoStr, ',');
		sp.soLuongTonKho = stoi(soLuongTonKhoStr);

		getline(fileInput, giaSPstr, ',');
		sp.giaSP = stod(giaSPstr);

		getline(fileInput, sp.nhaCungCap, '\n');

		addTail(ds, sp);
	}
	fileInput.close();
}
void printProd(SanPham sp) {
	cout << left << setw(15) << sp.maSP
		<< setw(35) << sp.tenSP
		<< setw(15) << sp.soLuongTonKho
		<< setw(20) << sp.giaSP
		<< setw(20) << sp.nhaCungCap << endl;
}
void print(DanhSach& ds) {
	Node* p = ds.head;
	if (isEmpty(ds)) {
		cout << "Danh sach rong!\n";
		return;
	}
	cout << left << setw(15) << "\nMA SAN PHAM"
		<< setw(25) << "TEN SAN PHAM"
		<< setw(25) << "SO LUONG TON KHO"
		<< fixed << setprecision(0) << setw(20) << "GIA SAN PHAM"
		<< setw(20) << "NHA CUNG CAP" << endl;
	cout << string(100, '-') << endl;
	while (p != nullptr)
	{
		printProd(p->info);
		p = p->next;
	}
}
void deleteBeforeId(DanhSach& ds) {
	int id;
	cout << "\nNhap ma san pham can xoa phia truoc: "; cin >> id;
	if (isEmpty(ds))
	{
		cout << "Danh sach rong!\n"; return;
	}
	if (ds.head->info.maSP == id)
	{
		cout << "San pham dang o vi tri dau tien\n"; return;
	}
	if (ds.head->next != nullptr && ds.head->next->info.maSP == id)
	{
		Node* temp = ds.head;
		ds.head = ds.head->next;
		delete temp;
		ds.soLuong--;
		cout << "Da xoa thanh cong!\n";
		return;
	}
	Node* prev = ds.head;
	while (prev->next != nullptr && prev->next->next != nullptr && prev->next->next->info.maSP != id)
	{
		prev = prev->next;
	}
	if (prev->next == nullptr || prev->next->next == nullptr)
	{
		cout << "Khong tim thay san pham\n";
		return;
	}
	Node* temp = prev->next;
	prev->next = temp->next;
	delete temp;
	ds.soLuong--;
	cout << "Da xoa thanh cong!\n";
}
void searchByName(DanhSach&ds) {
	cin.ignore();
	string name;
	cout << "\nNhap ten san pham can tim: "; getline(cin, name);
	Node* p = ds.head;
	while (p != nullptr)
	{
		if (p->info.tenSP.find(name) < p->info.tenSP.length())
		{
			printProd(p->info);
		}
		p = p->next;
	}
}
void interchangeSortDESC(DanhSach&ds) {
	if (isEmpty(ds))
	{
		return;
	}
	for (Node* p = ds.head; p != nullptr; p = p->next)
	{
		for (Node* q = p->next; q != nullptr; q = q->next)
		{
			if (p->info.soLuongTonKho < q->info.soLuongTonKho)
			{
				swap(p->info, q->info);
			}
		}
	}
}
int main() {
	DanhSach ds;
	init(ds);
	readFile(ds, "SanPham.txt");
	print(ds);
	SanPham test = { 2026,"Iphone 13",12,11000000,"Apple" };
	print(ds);
	return 0;
}