#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>
using namespace std;
struct SinhVien
{
	string maSV;
	string hoTen;
	string ngaySinh;
	float diemTB;
	SinhVien() {}
	SinhVien(string msv, string ht, string ns, float dtb) {
		this->maSV = msv;
		this->hoTen = ht;
		this->ngaySinh = ns;
		this->diemTB = dtb;
	}
};
struct Node
{
	SinhVien info;
	Node* next;
	Node* prev;
};
void init(Node*& head, Node*& tail) {
	head = nullptr;
	tail = nullptr;
}
bool isEmpty(Node* head) {
	return head == nullptr;

}
Node* createNode(const SinhVien& sv) {
	Node* p = new Node();
	p->info = sv;
	p->next = nullptr;
	p->prev = nullptr;
	return p;
}
void addHead(Node*& head, Node*& tail, const SinhVien& sv) {
	Node* p = createNode(sv);
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
void addTail(Node*& head, Node*& tail, const SinhVien& sv) {
	Node* p = createNode(sv);
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
	cout << "\nDA XOA PHAN TU DAU THANH CONG!\n";
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
	cout << "\nDA XOA PHAN TU CUOI THANH CONG!\n";
}

void readFile(Node*& head, Node*& tail, const string& fileName) {
	ifstream fileInput(fileName);
	if (!fileInput.is_open())
	{
		cout << "Khong the doc file " << fileName << endl;
		return;
	}
	SinhVien sv;
	string diemStr;
	while (getline(fileInput, sv.maSV, ';'))
	{
		getline(fileInput, sv.hoTen, ';');
		getline(fileInput, sv.ngaySinh, ';');
		getline(fileInput, diemStr, '\n');
		sv.diemTB = stof(diemStr);

		addTail(head, tail, sv);
	}
	fileInput.close();
}

void output(Node* head, Node* tail) {
	if (isEmpty(head))
	{
		cout << "DANH SACH RONG!\n";
		return;
	}
	cout << endl;
	cout << left << setw(10) << "ID"
		<< setw(20) << "HO TEN"
		<< setw(14) << "NGAY SINH"
		<< setw(10) << "DIEM TRUNG BINH" << endl;
	cout << "-----------------------------------------------------------\n";
	Node* p = head;
	while (p != nullptr)
	{
		cout << left << setw(10) << p->info.maSV
			<< setw(20) << p->info.hoTen
			<< setw(14) << p->info.ngaySinh
			<< setw(10) << p->info.diemTB << endl;
		p = p->next;
	}
}
void searchByName(Node*& head, const string& name) {
	Node* p = head;
	int count = 0;
	while (p != nullptr)
	{
		if (p->info.hoTen == name)
		{
			count++;
			cout << count << "." << p->info.maSV << "|"
				<< p->info.hoTen << "|"
				<< p->info.ngaySinh << "|"
				<< p->info.diemTB << "\n";
		}
		p = p->next;
	}
	if (count == 0)
	{
		cout << "Khong tim thay sinh vien co ten " << name << endl;
	}
}
Node* searchById(Node*& head, const string& id) {
	Node* p = head;
	while (p != nullptr)
	{
		if (p->info.maSV == id)
		{
			return p;
		}
		p = p->next;
	}
	return nullptr;
}
void insertAfterId(Node*& head, Node*& tail, const SinhVien& sv, const string& id) {
	Node* p = searchById(head, id);
	if (p == nullptr)
	{
		cout << "Khong tim thay id!\n";
		return;
	}
	if (p->next == nullptr)
	{
		addTail(head, tail, sv);
	}
	else
	{
		Node* q = createNode(sv);
		Node* d = p->next;
		q->prev = p;
		q->next = d;
		d->prev = q;
		p->next = q;
	}
}
void deleteAfterId(Node*& head, Node*& tail, const string& id) {
	Node* p = searchById(head, id);
	if (p == nullptr)
	{
		cout << "Khong tim thay id!\n";
		return;
	}
	while (p != nullptr && p->info.maSV != id)
	{
		p = p->next;
	}
	if (p->next == nullptr)
	{
		cout << "\nDang o phan tu cuoi\n";
		return;
	}
	if (p->next->next == nullptr)
	{
		deleteTail(head, tail);
		return;
	}
	else
	{
		Node* temp = p->next;
		Node* q = p->next->next;
		p->next = q;
		q->prev = p;
		delete temp;
		temp = nullptr;
	}
}
void printBackward(Node* head, Node* tail) {
	if (isEmpty(head))
	{
		cout << "DANH SACH RONG!\n";
		return;
	}
	cout << left << setw(10) << "ID"
		<< setw(20) << "HO TEN"
		<< setw(14) << "NGAY SINH"
		<< setw(10) << "DIEM TRUNG BINH" << endl;
	cout << "-----------------------------------------------------------\n";
	Node* p = tail;
	while (p != nullptr)
	{
		cout << left << setw(10) << p->info.maSV
			<< setw(20) << p->info.hoTen
			<< setw(14) << p->info.ngaySinh
			<< setw(10) << p->info.diemTB << endl;
		p = p->prev;
	}
}
void deleteById(Node* head, const string& targetId) {
	if (head == nullptr)
	{
		cout << "Danh sach rong!\n";
		return;
	}
	Node* p = head;
	while (p != nullptr && p->info.maSV != targetId)
	{
		p = p->next;
	}
	if (p == nullptr)
	{
		cout << "Khong tim thay ma sinh vien can xoa!\n";
		return;
	}
	//th1: p la not dau (head)
	if (p == head)
	{
		head = head->next;
		if (head != nullptr)
		{
			head->prev = nullptr;
		}
	}
	//th2: p la not giua hoac not dau
	else
	{
		p->prev->next = p->next;
		if (p->next != nullptr)
		{
			p->next->prev = p->prev;
		}
	}
	delete p;
	cout << "Da xoa thanh cong sinh vien co ma so " << targetId << endl;
}
void selectionSortASC(Node* head) {
	for (Node* i = head; i != nullptr && i->next != nullptr; i = i->next)//cho i = head duyet toi truoc tail
	{
		Node* minNode = i; //gia su cho min = i
		for (Node* j = i->next; j != nullptr; j = j->next)// duyet, cho j la node tiep theo
		{
			if (j->info.diemTB < minNode->info.diemTB)
			{
				minNode = j;
			}
		}
		if (minNode != i)
		{
			swap(i->info, minNode->info);
		}
	}
}
void bubbleSortDESC(Node* head) {
	if (head == nullptr)
	{
		return;
	}
	for (Node* i = head; i != nullptr && i->next != nullptr; i = i->next)
	{
		for (Node* j = head; j->next != nullptr; j = j->next)
		{
			if (j->info.diemTB < j->next->info.diemTB)
			{
				swap(j->info, j->next->info);
			}
		}
	}
}
int main() {
	Node* head, * tail;
	init(head, tail);
	SinhVien sv("999", "Trong Dinh", "5/6/2026", 10);
	readFile(head, tail, "SinhVien.txt");

	output(head, tail);

	/*string id;
	cout << "Nhap id can xoa: "; getline(cin,id);
	deleteById(head, id);
	output(head, tail);*/

	bubbleSortDESC(head);
	output(head, tail);
	return 0;
}