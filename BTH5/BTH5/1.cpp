#include<iostream>
#include<fstream>
#include<iomanip>
#include<string>
#include<sstream>
using namespace std;
struct QuyenSach
{
	int maSach;
	string tieuDe;
	string tacGia;
	string ngayXuatBan;
	double giaBan;
};
struct Node
{
	QuyenSach info;
	Node* prev, * next;
};

struct ThuVien
{
	int soLuong;
	Node* head, * tail;
};
void init(ThuVien&tv) {
	tv.head = tv.tail = nullptr;
	tv.soLuong = 0;
}
Node* createNode(const QuyenSach& qs) {
	Node* p = new Node();
	p->info = qs;
	p->prev = nullptr;
	p->next = nullptr;
	return p;
}
void addHead(ThuVien&tv, const QuyenSach& qs) {
	Node* p = createNode(qs);
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
void addTail(ThuVien&tv, const QuyenSach& qs) {
	Node* p = createNode(qs);
	p->prev = tv.tail;
	if (tv.tail ==nullptr)
	{
		tv.head = p;
	}
	else
	{
		tv.tail->next = p;
	}
	tv.tail = p;
	tv.soLuong++;
}
void deleteHead(ThuVien& tv) {
	if (tv.head==nullptr)
	{
		return;
	}
	Node* p = tv.head;
	tv.head = tv.head->next;
	if (tv.head==nullptr)
	{
		tv.tail = nullptr;
	}
	else
	{
		tv.head->prev = nullptr;
	}
	delete p;
	tv.soLuong--;
}
void deleteTail(ThuVien& tv) {
	if (tv.tail == nullptr)
	{
		return;
	}
	Node* p = tv.tail;
	tv.tail = tv.tail->prev;
	if (tv.tail == nullptr)
	{
		tv.head = nullptr;
	}
	else
	{
		tv.tail->next = nullptr;
	}
	delete p;
	tv.soLuong--;
}
void readFile(ThuVien& tv, const string& fileName) {
	ifstream fileInput(fileName);
	if (!fileInput.is_open())
	{
		cout << "Khong the doc file " << fileName << endl;
		return;
	}
	QuyenSach qs;
	string maSachStr, giaBanStr;
	while (getline(fileInput, maSachStr, '#'))
	{	
		qs.maSach = stoi(maSachStr);

		getline(fileInput, qs.tieuDe, '#');
		getline(fileInput, qs.tacGia, '#');
		getline(fileInput, qs.ngayXuatBan, '#');

		getline(fileInput, giaBanStr, '\n');
		qs.giaBan = stof(giaBanStr);

		addTail(tv, qs);
	}
	fileInput.close();
}
void printTitle() {
	cout << left << setw(10) << "MA SACH"
		<< setw(35) << "TIEU DE"
		<< setw(20) << "TEN TAC GIA"
		<< setw(15) << "NGAY XUAT BAN"
		<< setw(10) << "GIA BAN" << endl;
	cout << string(90, '-') << endl;
}
void printBook(QuyenSach qs) {
	cout << left << setw(10) << qs.maSach
		<< setw(35) << qs.tieuDe
		<< setw(20) << qs.tacGia
		<< setw(15) << qs.ngayXuatBan
		<< setw(10) << qs.giaBan << endl;
}
void print(ThuVien& tv) {
	if (tv.head==nullptr)
	{
		cout << "DANH SACH RONG!\n";
		return;
	}
	cout << endl;
	printTitle();
	Node* p = tv.head;
	while (p!=nullptr)
	{
		printBook(p->info);
		p = p->next;
	}
}
void searchByAuthor(ThuVien&tv, string authorName) {
	Node* p = tv.head;
	bool found = false;
	while (p != nullptr) {
		if (p->info.tacGia == authorName) {
			if (!found) {
				cout << "\nKet qua tim kiem tac gia '" << authorName << "':" << endl;
				printTitle();
				found = true;
			}
			printBook(p->info);
		}
		p = p->next;
	}
	if (!found) {
		cout << "Khong tim thay sach cua tac gia: " << authorName << endl;
	}
}

void insertBeforeID(ThuVien&tv, QuyenSach qs) {
	int id;
	cout << "Nhap ma can them truoc: "; cin >> id;
	Node* q = tv.head;
	while (q != nullptr && q->info.maSach != id) {
		q = q->next;
	}
	if (q == nullptr) {
		cout << "Khong tim thay sach co ma " << id << endl;
		return;
	}
	if (q->prev == nullptr) {
		addHead(tv, qs); // Neu q la dau danh sach, goi addHead de chen p lam head moi
	}
	else {
		Node* p = createNode(qs);
		q->prev->next = p; // Cho nut dung truoc q tro den nut moi p
		p->prev = q->prev; // Cho prev cua p tro nguoc ve nut dung truoc q
		p->next = q;       // Cho next cua p tro den q
		q->prev = p;       // Cho prev cua q tro nguoc ve p
		tv.soLuong++;
	}
	cout << "Da chen thanh cong truoc - " << id << endl;
}

void insertAfterID(ThuVien& tv, QuyenSach qs) {
	int id;
	cout << "Nhap ma can them sau: "; cin >> id;
	Node* q = tv.head;
	while (q != nullptr && q->info.maSach != id)
	{
		q = q->next;
	}
	if (q == nullptr)
	{
		cout << "Khong tim thay sach co ma " << id << endl;
		return;
	}

	if (q->next == nullptr) {
		addTail(tv, qs); // Neu q la dau danh sach, goi addHead de chen p lam head moi
	}
	else {
		Node* p = createNode(qs);
		p->next = q->next;       // Cho next cua p tro den nut dung sau q [2]
		p->prev = q;             // Cho prev cua p tro nguoc ve q [2]
		q->next->prev = p;       // Cho prev cua nut dung sau q tro nguoc ve p [2]
		q->next = p;			// Cho next cua q huong den p [2]
		tv.soLuong++;
	}
	cout << "Da chen thanh cong sau - " << id << endl;
}
void deleteByID(ThuVien&tv)
{
	int id;
	cout << "Nhap ma can xoa: "; cin >> id;
	Node* p = tv.head; 
	while (p != nullptr && p->info.maSach != id)
		p = p->next;
	if (p != nullptr) 
	{
		if (p->prev == nullptr) 
			tv.head = p->next;
		else
			p->prev->next = p->next; 
		if (p->next == nullptr) 
			tv.tail = p->prev;
		else
			p->next->prev = p->prev; 
		p->next = nullptr;
		p->prev = nullptr; 
		delete p;
		tv.soLuong--;
	}
}
//string getYear(string ngayXuatBan) {
//	if (ngayXuatBan.length()>=10)
//	{
//		return ngayXuatBan.substr(6, 4);
//	}
//	return "";
//}
//void searchByYear(ThuVien& tv) {
//	string year;
//	cout << "Nhap nam can in ra: "; cin >> year;
//	Node* p = tv.head;
//	bool found = false;
//	while (p!=nullptr)
//	{
//		if (getYear(p->info.ngayXuatBan)==year)
//		{
//			if (!found)
//			{
//				cout << "\nCac sach xuat ban nam " << year << ":" << endl;
//				printTitle();
//				found = true;
//			}
//			printBook(p->info);
//		}
//		p = p->next;
//
//	}
//	if (!found)
//	{
//		cout << "Khong tim thay sach nao xuat ban nam " << year << endl;
//	}
//
//}
void searchByYear(ThuVien tv) {
	int year;
	cout << "Nhap nam: "; cin >> year;
	for (Node *p  = tv.head; p !=nullptr; p = p->next)
	{
		string nxb = p->info.ngayXuatBan;
		int vitri = nxb.rfind("-");
		string n = nxb.substr(vitri + 1);
		if (stoi(n)==year)
		{
			printBook(p->info);
		}
	}
}
Node* truyCap(ThuVien tv, int pos) {
	if (pos<0)
	{
		return nullptr;
	}
	int i = 0;
	Node* p = tv.head;
	while (p!=nullptr&&i<pos)
	{
		p = p->next;
		i++;
	}
	return p;
}

//InsertionSort nguyen ban
//void insertionSortDESC(int a[], int n) {
//	for (int i = 1; i < n; i++)
//	{
//		int x = a[i];
//		int pos = i - 1;
//		while (pos>=0&&a[pos]<x)
//		{
//			a[pos + 1] = a[pos];
//			pos--;
//		}
//		a[pos + 1] = x;
//	}
//}


//void insertionSortDESC(ThuVien &tv) {
//	for (int i = 1; i < tv.soLuong; i++)
//	{
//		int id = truyCap(tv,i)->info.maSach;
//		string title = truyCap(tv, i)->info.tieuDe;
//		string author = truyCap(tv, i)->info.tacGia;
//		string date = truyCap(tv, i)->info.ngayXuatBan;
//		double price = truyCap(tv, i)->info.giaBan;
//
//		int pos = i - 1;
//		while ( pos>=0 && (truyCap(tv, pos)->info.giaBan) < price )
//		{
//			truyCap(tv, pos + 1)->info.maSach = truyCap(tv, pos)->info.maSach;
//			truyCap(tv, pos + 1)->info.tieuDe = truyCap(tv, pos)->info.tieuDe;
//			truyCap(tv, pos + 1)->info.tacGia = truyCap(tv, pos)->info.tacGia;
//			truyCap(tv, pos + 1)->info.ngayXuatBan = truyCap(tv, pos)->info.ngayXuatBan;
//			truyCap(tv, pos + 1)->info.giaBan = truyCap(tv, pos)->info.giaBan;
//
//			pos--;
//		}
//		truyCap(tv, pos+1)->info.maSach = id;
//		truyCap(tv, pos + 1)->info.tieuDe = title;
//		truyCap(tv, pos + 1)->info.tacGia = author;
//		truyCap(tv, pos + 1)->info.ngayXuatBan =date;
//		truyCap(tv, pos + 1)->info.giaBan = price;
//
//	}
//}

//toi uu
void insertionSortDESC(ThuVien& tv) {
	for (int i = 1; i < tv.soLuong; i++)
	{
		QuyenSach x = truyCap(tv, i)->info;

		int pos = i - 1;
		while (pos >= 0 && truyCap(tv, pos)->info.giaBan < x.giaBan) 
		{
			truyCap(tv, pos + 1)->info = truyCap(tv, pos)->info;

			pos--;
		}
		truyCap(tv, pos + 1)->info = x;
	}
}


int main() {
	ThuVien tv;
	init(tv);
	readFile(tv, "ThuVien.txt");
	print(tv);

	//cout << "\nTIM KIEM THEO TAC GIA";
	//searchByAuthor(tv, "Pham Thi Lan");

	/*QuyenSach qs1 = { 2026, "Cau truc du lieu va thuat giai 1", "Nguyen Quoc Huy", "20-10-2025", 95000 };
	insertAfterID(tv, qs1);*/

	insertionSortDESC(tv);
	print(tv);
	return 0;
}