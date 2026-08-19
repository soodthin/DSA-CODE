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
	Node* next, *prev;
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
Node* createNode(Sach& s) {
	Node* p = new Node();
	p->info = s;
	p->next = nullptr;
	p->prev = nullptr;
	return p;
}
void addHead(ThuVien& tv, Sach& s) {
	Node* p = createNode(s);
	p->next = tv.head;
	if (tv.head==nullptr)
	{
		tv.tail = p;
	}
	else
	{
		tv.head->prev = p;
	}
	tv.head = p;
	tv.soLuong++;
}
void addTail(ThuVien& tv, Sach& s) {
	Node* p = createNode(s);
	p->prev = tv.tail;
	if (tv.tail == nullptr)
	{
		tv.head = p;
	}
	else
	{
		tv.tail->next= p;
	}
	tv.tail = p;
	tv.soLuong++;
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
void printBook(Sach&s) {
	cout << left << setw(10) << s.maSach
		<< setw(35) << s.tieuDe
		<< setw(20) << s.tacGia
		<< setw(15) << s.ngayXuatBan
		<< setw(15) << s.giaBan << endl;
}
void print(ThuVien& tv) {
	Node* p = tv.head;
	cout << endl;
	cout << left << setw(10) << "MA SACH"
		<< setw(35) << "TIEU DE"
		<< setw(20) << "TAC GIA"
		<< setw(15) << "NGAY XUAT BAN"
		<< setw(15) << "GIA BAN" << endl;
	cout << string(95, '-') << endl;
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
		if (tv.head!=nullptr)
		{
			tv.head->prev = nullptr;
		}
		else
		{
			tv.tail = nullptr;
		}
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
		if (tv.tail != nullptr)
		{
			tv.tail->next = nullptr;
		}
		else
		{
			tv.head = nullptr;
		}
		delete p;
		tv.soLuong--;
	}
}
void searchByAuthor(ThuVien& tv, string author) {
	Node* p = tv.head;
	bool found = false;
	while (p!=nullptr)
	{
		Sach s;
		if (p->info.tacGia==author)
		{
			cout << "\nTim thay tac gia " << author << endl;
			printBook(p->info);
		}
		p = p->next;
	}
}
void addBeforeId(ThuVien& tv, Sach	s) {
	int id;
	cout << "\nNhap ma sach can them truoc: "; cin >> id;
	Node* q = tv.head;
	while (q !=nullptr&& q->info.maSach!=id)
	{
		q = q->next;
	}
	if (q ==nullptr)
	{
		cout << "Khong tim thay ma sach " << id << endl;
		return;
	}
	if (q->prev==nullptr)
	{
		addHead(tv, s);
	}
	else
	{
		Node* p = createNode(s);
		q->prev->next = p;
		p->prev = q->prev;
		p->next = q;
		q->prev = p;
		tv.soLuong++;
	}
	cout << "Da chen thanh cong truoc - " << id << endl;;
}
void addAfterId(ThuVien& tv, Sach s) {
	int id;
	cout << "Nhap ma sach can them sau: "; cin >> id;
	Node* q = tv.head;
	while (q!=nullptr&&q->info.maSach!=id)
	{
		q = q->next;
	}
	if (q==nullptr)
	{
		cout << "Khong tim thay id!\n";
		return;
	}
	if (q->next==nullptr)
	{
		addTail(tv, s);
	}
	else
	{
		Node* p = createNode(s);
		p->next = q->next;
		p->prev = q;
		q->next->prev = p;
		q->next = p;
		tv.soLuong++;
	}
	cout << "Da chen thanh cong sau - " << id << endl;;
}
void deleteX(ThuVien&tv){
	int id;
	cout << "Nhap ma sach can xoa: "; cin >> id;
	Node* p = tv.head;
	while (p!=nullptr&&p->info.maSach!=id)
	{
		p = p->next;
	}
	if (p!=nullptr)//tim thay nut can xoa
	{
		if (p->prev==nullptr)
		{
			tv.head = p->next;
		}
		else
		{
			p->prev->next = p->next;
		}
		if (p->next==nullptr)
		{
			tv.tail = p->prev;
		}
		else
		{
			p->next->prev = p->prev;
		}
		p->next = nullptr;
		p->prev = nullptr;

		delete p;
		tv.soLuong--;
	}
}
int main() {
	ThuVien tv;
	init(tv);
	readFile(tv, "ThuVien.txt");
	print(tv);
	/*Sach newS = {2026,"Cau truc du lieu va giai thuat 1", "Nguyen Quoc Huy","19-8-2026",50000};
	addAfterId(tv, newS);*/
	deleteX(tv);
	print(tv);
	return 0;
}