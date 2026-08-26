#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<iomanip>
using namespace std;
struct Sach
{
	int maSach;
	string tieuDe, tacGia, ngayXuatBan;
	double giaBan;
};
struct Node
{
	Sach info;
	Node* prev, * next;
};
struct ThuVien
{
	int soLuong;
	Node* head, * tail;
};
void init(ThuVien& tv) {
	tv.head = tv.tail = nullptr;
	tv.soLuong = 0;
}
Node* createNode(Sach s) {
	Node* p = new Node();
	p->info = s;
	p->prev = nullptr;
	p->next = nullptr;
	return p;
}
void addHead(ThuVien& tv, Sach s) {
	Node* p = createNode(s);
	p->next = tv.head;
	if (tv.head != nullptr) tv.head->prev = p;
	else tv.tail = p;
	tv.head = p;
	tv.soLuong++;
}
void addTail(ThuVien& tv, Sach s) {
	Node* p = createNode(s);
	p->prev = tv.tail;
	if (tv.tail != nullptr) tv.tail->next = p;
	else tv.head = p;
	tv.tail = p;
	tv.soLuong++;
}
void deleteHead(ThuVien& tv) {
	if (tv.head!=nullptr)
	{
		Node* p = tv.head;
		tv.head = p->next;
		p->next = nullptr;
		if (tv.head != nullptr) tv.head->prev = nullptr;
		else tv.tail = nullptr;
		delete p;
		tv.soLuong--;
	}
}
void deleteTail(ThuVien& tv) {
	if (tv.tail != nullptr)
	{
		Node* p = tv.tail;
		tv.tail = p->prev;
		p->prev = nullptr;
		if (tv.tail != nullptr) tv.tail->next = nullptr;
		else tv.head = nullptr;
		delete p;
		tv.soLuong--;
	}
}
void readFile(ThuVien& tv, const string& fileName) {
	ifstream fileInput(fileName);
	if (!fileInput.is_open())
	{
		cout << "Khong the mo file " << fileName << endl;
		return;
	}
	Sach s;
	string maSachStr, giaBanStr;
	while (getline(fileInput,maSachStr,'#'))
	{
		s.maSach = stoi(maSachStr);

		getline(fileInput, s.tieuDe, '#');
		getline(fileInput, s.tacGia, '#');
		getline(fileInput, s.ngayXuatBan, '#');

		getline(fileInput, giaBanStr, '\n');
		s.giaBan = stod(giaBanStr);

		addTail(tv, s);
	}
	fileInput.close();
}
void printBook(Sach s) {
	cout << left << setw(10) << s.maSach
		<< setw(35) << s.tieuDe
		<< setw(20) << s.tacGia
		<< setw(15) << s.ngayXuatBan
		<<fixed<<setprecision(0) << setw(15) << s.giaBan << endl;
}
void print(ThuVien& tv) {
	Node* p = tv.head;
	if (tv.head == nullptr) cout << "Danh sach rong!\n";
	cout << left << setw(10) << "\nMA SACH"
		<< setw(35) << "TIEU DE"
		<< setw(20) << "TAC GIA"
		<< setw(15)<<"NGAY XUAT BAN"
		<< setw(15) << "GIA BAN" << endl;
	cout << string(90, '-') << endl;
	while (p!=nullptr)
	{
		printBook(p->info);
		p = p->next;
	}
}
void searchAuthor(ThuVien& tv, string nameAuthor) {
	Node* p = tv.head;
	bool found=false;
	cout << "\nTac gia co ten " << nameAuthor << ":\n";
	while (p!=nullptr)
	{
		if (p->info.tacGia==nameAuthor)
		{
			found = true;
			printBook(p->info);
		}
		p = p->next;
	}
	if (found==false)
	{
		cout << "Khong tim thay tac gia\n";
	}
}
void addBeforeId(ThuVien& tv, Sach s) {
	int id;
	cout << "Nhap ma sach can them truoc: "; cin >> id;
	Node* q = tv.head;
	while (q!=nullptr&&q->info.maSach!=id)
	{
		q = q->next;
	}
	if (q!=nullptr)
	{
		if (q->prev == nullptr) addHead(tv, s);
		else
		{
			Node* p = createNode(s);
			p->next = q;
			p->prev = q->prev;
			q->prev->next = p;
			q->prev = q;
		}
		tv.soLuong++;
	}
}
void addAfterId(ThuVien& tv, Sach s) {
	int id;
	cout << "Nhap ma sach can them sau: "; cin >> id;
	Node* q = tv.head;
	while (q!=nullptr&&q->info.maSach!=id)
	{
		q = q->next;
	}
	if (q!=nullptr)
	{
		if (q->next == nullptr) addTail(tv, s);
		else
		{
			Node* p = createNode(s);
			p->next = q->next;
			p->prev = q;
			q->next->prev = p;
			q->next = p;
		}
		tv.soLuong++;
	}
}
void deleteX(ThuVien& tv) {
	int id;
	cout << "Nhap ma sach can xoa: "; cin >> id;
	Node* q = tv.head;
	while (q!=nullptr&&q->info.maSach!=id)
	{
		q = q->next;
	}
	if (q!=nullptr)
	{
		if (q->prev == nullptr) tv.head = tv.head->next;
		else q->prev->next = q->next;
		if (q->next == nullptr) tv.tail = tv.tail->prev;
		else q->next->prev = q->prev;
		q->next = nullptr;
		q->prev = nullptr;
		delete q;
		tv.soLuong--;
	}
	cout << "Da xoa thanh cong - " << id << endl;
}
void searchByDay(ThuVien& tv) {
	int day;
	cout << "Nhap ngay can tim: "; cin >> day;
	for (Node* p = tv.head; p != nullptr; p=p->next)
	{
		string date = p->info.ngayXuatBan;
		int pos = date.find('-');
		string d = date.substr(0, pos);
		if (stoi(d)==day)
		{
			printBook(p->info);
		}
	}
	cout << endl;
}
void searchByMonth(ThuVien& tv) {
	int month;
	cout << "Nhap thang can tim: "; cin >> month;
	for (Node* p = tv.head; p != nullptr; p=p->next)
	{
		string date = p->info.ngayXuatBan;
		int pos1 = date.find('-');
		int pos2 = date.rfind('-');
		string m = date.substr(pos1 + 1, 2);
		if (stoi(m)==month)
		{
			printBook(p->info);
		}
	}
	cout << endl;
}
void searchByYear(ThuVien& tv) {
	int year;
	bool found = false;
	cout << "\nNhap nam can tim: "; cin >> year;
	for (Node*p  = tv.head;  p!= nullptr;p=p->next)
	{
		string date = p->info.ngayXuatBan;
		int pos = date.rfind('-');
		string n = date.substr(pos + 1);
		if (stoi(n)==year)
		{
			found = true;
			printBook(p->info);
		}
	}
	if (found==false)
	{
		cout << "Khong tim thay sach co nam " << year << endl;
	}
	cout << endl;
}
Node* nodeAt(ThuVien& tv, int pos) {
	if (pos < 0) return nullptr;
	Node* p = tv.head;
	for (int i = 0; i < pos&&p!=nullptr; i++)
	{
		p = p->next;
	}
	return p;
}
//Selection Sort - DESC
void selectionSort(ThuVien& tv) {
	for (int i = 0; i < tv.soLuong - 1; i++) {
		int maxIdx = i; // Tim phan tu co giaBan lon nhat dua ve vi tri i
		for (int j = i + 1; j < tv.soLuong; j++) {
			if (nodeAt(tv, j)->info.giaBan > nodeAt(tv, maxIdx)->info.giaBan) // doi < thanh > - ASC (doi bien thanh min =i)
				maxIdx = j;
		}
		if (maxIdx != i) {
			swap(nodeAt(tv, i)->info, nodeAt(tv, maxIdx)->info);
		}
	}
}

//Insertion Sort - DESC
void insertionSort(ThuVien& tv) {
	for (int i = 1; i < tv.soLuong; i++) {
		Sach key = nodeAt(tv, i)->info;
		int pos = i - 1;
		while (pos >= 0 && nodeAt(tv, pos)->info.giaBan < key.giaBan) { // doi < thanh > - ASC
			nodeAt(tv, pos + 1)->info = nodeAt(tv, pos)->info;
			pos--;
		}
		nodeAt(tv, pos + 1)->info = key;
	}
}

// Interchange Sort - DESC
void interchangeSort(ThuVien& tv) {
	for (int i = 0; i < tv.soLuong - 1; i++) {
		for (int j = i + 1; j < tv.soLuong; j++) {
			if (nodeAt(tv, i)->info.giaBan < nodeAt(tv, j)->info.giaBan) { // doi < thanh > - ASC
				swap(nodeAt(tv, i)->info, nodeAt(tv, j)->info);
			}
		}
	}
}

//Bubble Sort - DESC
void bubbleSort(ThuVien& tv) {
	for (int i = 0; i < tv.soLuong - 1; i++) {
		for (int j = tv.soLuong - 1; j > i; j--) {
			if (nodeAt(tv, j - 1)->info.giaBan < nodeAt(tv, j)->info.giaBan) { // doi < thanh > - ASC
				swap(nodeAt(tv, j - 1)->info, nodeAt(tv, j)->info);
			}
		}
	}
}
int main() {
	ThuVien tv;
	init(tv);
	readFile(tv, "ThuVien.txt");
	print(tv);
	Sach test = { 2026,"Cau truc du lieu va giai thuat 1","Nguyen Quoc Huy", "21-02-2024",3200000 };
	searchByMonth(tv);
	return 0;
}