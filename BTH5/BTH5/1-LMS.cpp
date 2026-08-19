#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Khai bao cau truc Sach
struct Sach
{
	int ma;
	string tieuDe, tacGia, ngayXuatBan;
	double gia;
	Sach* prev, * next;

	void xuat()
	{
		cout << "=========================\n";
		cout << "Ma: " << ma << endl;
		cout << "Tieu de: " << tieuDe << endl;
		cout << "Tac gia: " << tacGia << endl;
		cout << "Ngay xuat ban: " << ngayXuatBan << endl;
		cout << "Gia: " << gia << endl;
	}
};

// Khai bao cau truc Danh sach Thu vien (Danh sach lien ket kep)
struct ThuVien
{
	int soLuong;
	Sach* head, * tail;
};

// Ham khoi tao danh sach rong
void init(ThuVien& tv)
{
	tv.head = tv.tail = NULL;
	tv.soLuong = 0;
}

// Ham khoi tao sach moi
Sach* taoSach(int m, string td, string tg, string nxb, double g)
{
	Sach* s = new Sach;
	s->ma = m;
	s->tieuDe = td;
	s->tacGia = tg;
	s->ngayXuatBan = nxb;
	s->gia = g;
	s->next = s->prev = NULL;
	return s;
}

// Ham them sach moi vao dau danh sach
void themDau(ThuVien& tv, int m, string td, string tg, string nxb, double g)
{
	Sach* s = taoSach(m, td, tg, nxb, g);
	s->next = tv.head;
	if (tv.head == NULL)
		tv.tail = s;
	else
		tv.head->prev = s;
	tv.head = s;
	tv.soLuong++;
}

// Ham them sach moi vao cuoi danh sach
void themCuoi(ThuVien& tv, int m, string td, string tg, string nxb, double g)
{
	Sach* s = taoSach(m, td, tg, nxb, g);
	s->prev = tv.tail;
	if (tv.tail == NULL)
		tv.head = s;
	else
		tv.tail->next = s;
	tv.tail = s;
	tv.soLuong++;
}

// Ham xoa sach dau danh sach
void xoaDau(ThuVien& tv)
{
	if (tv.head != NULL)
	{
		Sach* s = tv.head;
		tv.head = tv.head->next;
		if (tv.head == NULL)
			tv.tail = NULL; // DS rong
		else
			tv.head->prev = NULL;
		s->next = NULL; // khong bat buoc
		delete s;
		tv.soLuong--;
	}
}

// Ham xoa sach cuoi danh sach
void xoaCuoi(ThuVien& tv)
{
	if (tv.tail != NULL)
	{
		Sach* s = tv.tail;
		tv.tail = tv.tail->prev;
		if (tv.tail == NULL)
			tv.head = NULL; // DS rong
		else
			tv.tail->next = NULL;
		s->prev = NULL; // khong bat buoc
		delete s;
		tv.soLuong--;
	}
}

// Ham doc du lieu tu tap tin
void docFile(ThuVien& tv)
{
	ifstream doc("ThuVien.txt");
	if (doc.is_open())
	{
		while (!doc.eof())
		{
			int m;
			doc >> m;
			doc.ignore();
			string td;
			getline(doc, td, '#');
			string tg;
			getline(doc, tg, '#');
			string nxb;
			getline(doc, nxb, '#');
			double g;
			doc >> g;
			doc.ignore();
			themCuoi(tv, m, td, tg, nxb, g);
		}
		doc.close();
	}
	else
		cout << "Khong the doc file\n";
}

// Ham xuat danh sach thu vien
void xuatTV(ThuVien tv)
{
	for (Sach* s = tv.head; s != NULL; s = s->next)
		s->xuat();
	cout << "So luong: " << tv.soLuong << endl;
}

// Ham them sach truoc sach co ma X
void themTruoc(ThuVien& tv, int m, string td, string tg, string nxb, double g)
{
	int x;
	cout << "Nhap ma x: ";
	cin >> x;
	Sach* p = tv.head;
	while (p != NULL && p->ma != x)
		p = p->next;
	if (p != NULL)
	{
		if (p->prev == NULL) // p == tv.head la nut dau tien
			themDau(tv, m, td, tg, nxb, g);
		else
		{
			Sach* s = taoSach(m, td, tg, nxb, g);
			p->prev->next = s;
			s->prev = p->prev;
			s->next = p;
			p->prev = s;
			tv.soLuong++;
		}
	}
}

// Ham them sach sau sach co ma X
void themSau(ThuVien& tv, int m, string td, string tg, string nxb, double g)
{
	int x;
	cout << "Nhap ma x: ";
	cin >> x;
	Sach* p = tv.head;
	while (p != NULL && p->ma != x)
		p = p->next;
	if (p != NULL)
	{
		if (p->next == NULL) // p == tv.tail la nut cuoi cung
			themCuoi(tv, m, td, tg, nxb, g);
		else
		{
			Sach* s = taoSach(m, td, tg, nxb, g);
			s->next = p->next;
			p->next->prev = s;
			s->prev = p;
			p->next = s;
			tv.soLuong++;
		}
	}
}

// Ham xoa sach co ma X
void xoaX(ThuVien& tv)
{
	int x;
	cout << "Nhap ma x: ";
	cin >> x;

	Sach* q = tv.head;
	while (q != nullptr && q->ma != x)
		q = q->next;
	if (q != nullptr)
	{
		if (q->prev == nullptr)
			tv.head = q->next;
		else
			q->prev->next = q->next; // 1
		if (q->next == nullptr)
			tv.tail = q->prev;
		else
			q->next->prev = q->prev; // 2
		q->next = nullptr; // 3
		q->prev = nullptr; // 4
		delete q;
		tv.soLuong--;
	}
}

// Ham tim kiem sach theo nam
void timKiemTheoNam(ThuVien tv)
{
	int nam;
	cout << "Nhap nam: ";
	cin >> nam;
	for (Sach* s = tv.head; s != NULL; s = s->next)
	{
		string nxb = s->ngayXuatBan;
		int vt = nxb.rfind("-");
		string n = nxb.substr(vt + 1);
		if (stoi(n) == nam)
			s->xuat();
	}
}

// Ham truy cap sach theo vi tri pos
Sach* truyCap(ThuVien tv, int pos)
{
	if (pos < 0)
		return NULL;
	int i = 0;
	Sach* s = tv.head;
	while (s != NULL && i < pos)
	{
		s = s->next;
		i++;
	}
	return s;
}

// Ham sap xep giam dan theo gia ban (Insertion sort)
void insertionSort(ThuVien& tv)
{
	for (int i = 1; i < tv.soLuong; i++)
	{
		int m = truyCap(tv, i)->ma;
		string td = truyCap(tv, i)->tieuDe;
		string tg = truyCap(tv, i)->tacGia;
		string nxb = truyCap(tv, i)->ngayXuatBan;
		double g = truyCap(tv, i)->gia;
		int pos = i - 1;
		while (pos >= 0 && truyCap(tv, pos)->gia < g)
		{
			truyCap(tv, pos + 1)->ma = truyCap(tv, pos)->ma;
			truyCap(tv, pos + 1)->tieuDe = truyCap(tv, pos)->tieuDe;
			truyCap(tv, pos + 1)->tacGia = truyCap(tv, pos)->tacGia;
			truyCap(tv, pos + 1)->ngayXuatBan = truyCap(tv, pos)->ngayXuatBan;
			truyCap(tv, pos + 1)->gia = truyCap(tv, pos)->gia;
			pos--;
		}
		truyCap(tv, pos + 1)->ma = m;
		truyCap(tv, pos + 1)->tieuDe = td;
		truyCap(tv, pos + 1)->tacGia = tg;
		truyCap(tv, pos + 1)->ngayXuatBan = nxb;
		truyCap(tv, pos + 1)->gia = g;
	}
}

// Ham sap xep tang dan theo gia ban (Bubble sort)
void bubbleSort(ThuVien& tv)
{
	for (int i = 0; i < tv.soLuong - 1; i++)
		for (int j = tv.soLuong - 1; j > i; j--)
			if (truyCap(tv, j - 1)->gia > truyCap(tv, j)->gia)
			{
				swap(truyCap(tv, j - 1)->ma, truyCap(tv, j)->ma);
				swap(truyCap(tv, j - 1)->tieuDe, truyCap(tv, j)->tieuDe);
				swap(truyCap(tv, j - 1)->tacGia, truyCap(tv, j)->tacGia);
				swap(truyCap(tv, j - 1)->ngayXuatBan, truyCap(tv, j)->ngayXuatBan);
				swap(truyCap(tv, j - 1)->gia, truyCap(tv, j)->gia);
			}
}

// Ham sap xep giam dan theo ma sach (Interchange sort)
void interchangeSort(ThuVien& tv)
{
	for (int i = 0; i < tv.soLuong - 1; i++)
		for (int j = i + 1; j < tv.soLuong; j++)
			if (truyCap(tv, i)->ma < truyCap(tv, j)->ma)
			{
				swap(truyCap(tv, i)->ma, truyCap(tv, j)->ma);
				swap(truyCap(tv, i)->tieuDe, truyCap(tv, j)->tieuDe);
				swap(truyCap(tv, i)->tacGia, truyCap(tv, j)->tacGia);
				swap(truyCap(tv, i)->ngayXuatBan, truyCap(tv, j)->ngayXuatBan);
				swap(truyCap(tv, i)->gia, truyCap(tv, j)->gia);
			}
}

// Ham sap xep tang dan theo ma sach (Selection sort)
void selectionSort(ThuVien& tv)
{
	for (int i = 0; i < tv.soLuong - 1; i++)
	{
		int m = i;
		for (int j = i + 1; j < tv.soLuong; j++)
			if (truyCap(tv, j)->ma < truyCap(tv, m)->ma)
				m = j;

		if (m != i)
		{
			swap(truyCap(tv, i)->ma, truyCap(tv, m)->ma);
			swap(truyCap(tv, i)->tieuDe, truyCap(tv, m)->tieuDe);
			swap(truyCap(tv, i)->tacGia, truyCap(tv, m)->tacGia);
			swap(truyCap(tv, i)->ngayXuatBan, truyCap(tv, m)->ngayXuatBan);
			swap(truyCap(tv, i)->gia, truyCap(tv, m)->gia);
		}
	}
}


int main()
{
	ThuVien tv;
	init(tv);
	docFile(tv);
	cout << "====DANH SACH BAN DAU====\n";
	xuatTV(tv);

	cout << "====INSERTION SORT====\n";
	insertionSort(tv);
	xuatTV(tv);

	cout << "====BUBBLE SORT====\n";
	bubbleSort(tv);
	xuatTV(tv);

	cout << "====INTERCHANGE SORT====\n";
	interchangeSort(tv);
	xuatTV(tv);

	cout << "====SELECTION SORT====\n";
	selectionSort(tv);
	xuatTV(tv);
	return 0;
}