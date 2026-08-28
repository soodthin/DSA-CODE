#include<iostream>
#include<fstream>
#include<string>
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
	Node* head, * tail;
	int soLuong;
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
			q->prev = p;
			tv.soLuong++;
		}
	}
}
void addAfterId(ThuVien& tv, Sach s) {
	int id;
	cout << "Nhap ma sach can them sau: "; cin >> id;
	Node* q = tv.tail;
	while (q != nullptr && q->info.maSach != id)
	{
		q = q->prev;
	}
	if (q != nullptr)
	{
		if (q->next == nullptr) addTail(tv, s);
		else
		{
			Node* p = createNode(s);
			p->prev = q;
			p->next = q->next;
			q->next->prev = p;
			q->next = p;
			tv.soLuong++;
		}
	}
}
void readFile(ThuVien& tv, const string& fileName) {
	ifstream fileInput(fileName);
	if (!fileInput.is_open())
	{
		cout << "Khong the doc file " << fileName << endl;
		return;
	}
	string title;
	getline(fileInput, title);
	Sach s;
	string maSachStr, giaBanStr;
	while (getline(fileInput,maSachStr,'#'))
	{
		s.maSach = stoi(maSachStr);
		
		getline(fileInput, s.tieuDe, '#');
		getline(fileInput, s.tacGia, '#');
		getline(fileInput, s.ngayXuatBan, '#');

		getline(fileInput,giaBanStr, '\n');
		s.giaBan = stod(giaBanStr);

		addTail(tv, s);
	}
	fileInput.close();
}
void printBook(Sach s) {
	cout << left << setw(10) << s.maSach
		<< setw(30) << s.tieuDe
		<< setw(25) << s.tacGia
		<< setw(25) << s.ngayXuatBan
		<<fixed<<setprecision(0) << setw(15) << s.giaBan << endl;
}
void print(ThuVien& tv){ 
	if (tv.head == nullptr) {
		cout << "Danh sach rong!\n"; return;
	}
	Node* p = tv.head;
	cout << left << setw(10) << "MA SACH"
		<< setw(30) << "TIEU DE"
		<< setw(25) << "TAC GIA"
		<< setw(25) << "NGAY XUAT BAN"
		<< setw(15) << "GIA BAN" << endl;
	cout << string(90, '-') << endl;
	while (p!=nullptr)
	{
		printBook(p->info);
		p = p->next;
	}
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
void deleteX(ThuVien& tv) {
	int id;
	cout << "Nhap ma sach can them truoc: "; cin >> id;
	Node* q = tv.head;
	while (q != nullptr && q->info.maSach != id)
	{
		q = q->next;
	}

	if (q!=nullptr)
	{
		if (tv.head->prev == nullptr) tv.head = tv.head->next;
		else q->prev->next = q->next;
		if (tv.tail->next == nullptr) tv.tail = tv.tail->prev;
		else q->next->prev = q->prev;
		q->next = nullptr;
		q->prev = nullptr;
		delete q;
		tv.soLuong--;
	}
}
int main() {
	ThuVien tv;
	init(tv);
	readFile(tv, "ThuVien.txt");
	print(tv);
	Sach test = { 2026, "Cau truc du lieu va giai thuat 1","Nguyen Quoc Huy","21-2-2004",1500000 };
	deleteHead(tv);
	print(tv);
	return 0;
}