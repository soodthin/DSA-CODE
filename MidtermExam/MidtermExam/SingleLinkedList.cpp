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
void addHead(DanhSach& ds, SanPham sp) {
	Node* p = createNode(sp);
	p->next = ds.head;
	ds.head = p;
}
void addTail(DanhSach& ds, SanPham sp) {
	Node* p = createNode(sp);
	if (isEmpty(ds)) ds.head = p;
	else
	{
		Node* tail = ds.head;
		while (tail->next!=nullptr)
		{
			tail = tail->next;
		}
		tail->next = p;
	}
}
void addAfterId(DanhSach& ds, SanPham sp) {
	int id;
	cout << "Nhap ma san pham can them sau: "; cin >> id;
	Node* q = ds.head;
	while (q!=nullptr&&q->info.maSP!=id)
	{
		q = q->next;
	}
	if (q!=nullptr)
	{
		Node* p = createNode(sp);
		p->next = q->next;
		q->next = p;
		ds.soLuong++;
	}
}
void addBeforeId(DanhSach& ds, SanPham sp) {
	int id;
	cout << "Nhap ma san pham can them truoc: "; cin >> id;
	Node* q = ds.head;
	Node* prev = nullptr;
	while (q!=nullptr&&q->info.maSP!=id)
	{
		prev = q;
		q = q->next;
	}
	if (q!=nullptr)
	{
		Node* p = createNode(sp);
		p->next = q;
		if (prev == nullptr) ds.head = p;
		else prev->next = p;
	}
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
	if (isEmpty(ds)) cout << "Danh sach rong!\n";
	cout << left << setw(15) << "\nMA SAN PHAM"
		<< setw(25) << "TEN SAN PHAM"
		<< setw(25) << "SO LUONG TON KHO"
		<<fixed<<setprecision(0)<< setw(20) << "GIA SAN PHAM"
		<< setw(20) << "NHA CUNG CAP" << endl;
	cout << string(100, '-') << endl;
	while (p!=nullptr)
	{
		printProd(p->info);
		p = p->next;
	}
}
void deleteHead(DanhSach& ds) {
	if (!isEmpty(ds))
	{
		Node* p = ds.head;
		ds.head = p->next;
		p->next = nullptr;
		delete p;
		ds.soLuong--;
	}
}
void deleteTail(DanhSach& ds) {
	if (!isEmpty(ds))
	{
		Node* tail = ds.head;
		Node* prev = nullptr;
		while (tail->next!=nullptr)
		{
			prev = tail;
			tail = tail->next;
		}
		if (prev == nullptr) ds.head = nullptr;
		else prev->next = nullptr;
		delete tail;
		ds.soLuong--;
	}
}
void deleteBeforeId(DanhSach&ds) {
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
	cout << "Da xoa thanh cong!\n";
}
void deleteAfterID(DanhSach&ds) {
	int id;
	cout << "\nNhap ma san pham can xoa phia sau: "; cin >> id;
	Node* p = ds.head;
	while (p != nullptr && p->info.maSP != id)
	{
		p = p->next;
	}
	if (p == nullptr)
	{
		cout << "Khong tim thay san pham\n";
		return;
	}
	if (p->next == nullptr)
	{
		cout << "San pham o vi tri cuoi cung\n";
		return;
	}
	Node* temp = p->next;
	p->next = temp->next;
	delete temp;
	cout << "Da xoa thanh cong!\n";
}
void deleteByID(DanhSach&ds){
	int id;
	cout << "\nNhap ma san pham can xoa: "; cin >> id;
	Node* q = ds.head;
	Node* prev = nullptr;
	while (q != nullptr && q->info.maSP != id)
	{
		prev = q;
		q = q->next;
	}
	if (q != nullptr)
	{
		if (prev == nullptr)
			ds.head = q->next;
		else
			prev->next = q->next;

		q->next = nullptr;
		delete q;
		cout << "Da xoa thanh cong san pham - " << id << endl;
	}
	else cout << "Khong tim thay san pham - " << id << endl;
}
void searchByName(DanhSach& ds) {
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
Node* nodeAt(DanhSach& ds, int pos) {
	if (pos < 0 || pos >= ds.soLuong) return nullptr;
	Node* p = ds.head;
	for (int i = 0; i < pos && p != nullptr; i++) {
		p = p->next;
	}
	return p;
}
// 2. Selection Sort giam dan
void selectionSortDESC(DanhSach& ds) {
	for (int i = 0; i < ds.soLuong - 1; i++) {
		int maxIdx = i;
		for (int j = i + 1; j < ds.soLuong; j++) {
			if (nodeAt(ds, j)->info.soLuongTonKho > nodeAt(ds, maxIdx)->info.soLuongTonKho) {
				maxIdx = j;
			}
		}
		if (maxIdx != i) {
			swap(nodeAt(ds, i)->info, nodeAt(ds, maxIdx)->info);
		}
	}
}
// 3. Insertion Sort giam dan
void insertionSortDESC(DanhSach& ds) {
	for (int i = 1; i < ds.soLuong; i++) {
		SanPham x = nodeAt(ds, i)->info;
		int pos = i - 1;

		while (pos >= 0 && nodeAt(ds, pos)->info.soLuongTonKho < x.soLuongTonKho) {
			nodeAt(ds, pos + 1)->info = nodeAt(ds, pos)->info;
			pos--;
		}

		nodeAt(ds, pos + 1)->info = x;
	}
}
// 4. Interchange Sort giam dan
void interchangeSortDESC(DanhSach& ds) {
	for (int i = 0; i < ds.soLuong - 1; i++) {
		for (int j = i + 1; j < ds.soLuong; j++) {
			if (nodeAt(ds, i)->info.soLuongTonKho < nodeAt(ds, j)->info.soLuongTonKho) {
				swap(nodeAt(ds, i)->info, nodeAt(ds, j)->info);
			}
		}
	}
}
// 5. Bubble Sort giam dan
void bubbleSortDESC(DanhSach& ds) {
	for (int i = 0; i < ds.soLuong - 1; i++) {
		for (int j = ds.soLuong - 1; j > i; j--) {
			if (nodeAt(ds, j - 1)->info.soLuongTonKho < nodeAt(ds, j)->info.soLuongTonKho) {
				swap(nodeAt(ds, j - 1)->info, nodeAt(ds, j)->info);
			}
		}
	}
}
int main() {
	DanhSach ds;
	init(ds);
	readFile(ds, "SanPham.txt");
	print(ds);
	//SanPham test = { 2026,"Iphone 13",12,11000000,"Apple" };
	deleteBeforeId(ds);
	deleteAfterID(ds);
	deleteByID(ds);
	print(ds);
	return 0;
}