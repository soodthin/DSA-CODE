#include<iostream>
#include<string>
#include<iomanip>
#include<fstream>
using namespace std;
struct SinhVien
{
	string maSo;
	string hoTen;
	string ngaySinh;
	float diemTB;
};
struct Node
{
	SinhVien info;
	Node* next;
};
void init(Node*& head) {
	head = nullptr;
}
bool isEmpty(Node* head) {
	return head == nullptr;
}
Node* createNode(const SinhVien& sv) {
	Node* p = new Node();
	p->info = sv;
	p->next = nullptr;
	return p;
}
void addHead(Node*& head, const SinhVien& sv) {
	Node* p = createNode(sv);
	p->next = head;
	head = p;
}
void addTail(Node*& head, const SinhVien& sv) {
	Node* p = createNode(sv);
	if (isEmpty(head))
	{
		head = p;
		return;
	}
	else
	{
		Node* tail = head;
		while (tail->next != nullptr)
		{
			tail = tail->next;
		}
		tail->next = p;
	}
}
void readFile(Node*& head, const string& fileName) {
	ifstream fileInput(fileName);
	if (!fileInput.is_open())
	{
		cout << "Khong the doc file " << fileName << endl;
		return;
	}
	while (!fileInput.eof()) {
		SinhVien sv;
		string diemStr;
		getline(fileInput, sv.maSo, ',');
		getline(fileInput, sv.hoTen, ',');
		getline(fileInput, sv.ngaySinh, ',');
		getline(fileInput, diemStr, '\n');
		sv.diemTB = stof(diemStr);

		addTail(head, sv);

	}
}
void output(Node* head) {
	cout << left << setw(12) << "\nMA SO"
		<< setw(20) << "HO TEN"
		<< setw(12) << "NGAY SINH"
		<< setw(10) << "DIEM TRUNG BINH" << endl;
	cout << "-----------------------------------------------------------\n";
	Node* p = head;
	while (p != nullptr)
	{
		cout << left << setw(12) << p->info.maSo
			<< setw(20) << p->info.hoTen
			<< setw(12) << p->info.ngaySinh
			<< setw(10) << p->info.diemTB << endl;
		p = p->next;
	}
}
void deleteHead(Node*& head) {
	if (!isEmpty(head))
	{
		Node* p = head;
		head = p->next;
		p->next = nullptr;

		delete p;
	}
	cout << "\nDA XOA THANH CONG SINH VIEN DAU TIEN\n";
}
void deleteTail(Node*& head) {
	if (head != nullptr)
	{
		Node* tail = head;
		Node* prev = nullptr;
		while (tail->next != nullptr)
		{
			prev = tail;
			tail = tail->next;
		}
		if (prev == nullptr)
		{
			head = nullptr;
		}
		else
		{
			prev->next = nullptr;
		}
		delete tail;
	}
	cout << "\nDA XOA THANH CONG SINH VIEN CUOI CUNG\n";
}
void searchByName(Node* head, const string& name) {
	if (head == nullptr)
	{
		cout << "Khong co ten can tim\n";
		return;
	}
	Node* p = head;
	int count = 0;
	while (p != nullptr)
	{
		if (p->info.hoTen == name)
		{
			count++;
			cout << count << "."
				<< p->info.maSo << "|"
				<< p->info.hoTen << "|"
				<< p->info.ngaySinh << "|"
				<< p->info.diemTB << "\n";
		}
		p = p->next;
	}
	if (count == 0)
	{
		cout << "KHONG TIM THAY SINH VIEN CO TEN " << name << endl;
	}
}
void insertAfterID(Node* head, const SinhVien& newSV, const string& targetID) {
	Node* p = head;
	while (p != nullptr && p->info.maSo != targetID)
	{
		p = p->next;
	}
	if (p == nullptr)
	{
		cout << "DANH SACH RONG!\n";
		return;
	}
	Node* q = createNode(newSV);
	q->next = p->next;
	p->next = q;
	cout << "Da chen thanh cong!\n";
}
void deleteAfterID(Node* head, const string& targetID) {
	Node* p = head;
	while (p != nullptr && p->info.maSo != targetID)
	{
		p = p->next;
	}
	if (p == nullptr)
	{
		cout << "KHONG TIM THAY SINH VIEN\n";
		return;
	}
	if (p->next == nullptr)
	{
		cout << "SINH VIEN DANG O VI TRI CUOI CUNG\n";
		return;
	}
	Node* temp = p->next;
	p->next = temp->next;
	delete temp;
	cout << "Da xoa thanh cong!\n";
}	
void deleteByID(Node*& head, const string& targetID)
{
	Node* q = head;
	Node* prev = nullptr;

	while (q != nullptr && q->info.maSo != targetID)
	{
		prev = q;
		q = q->next;
	}

	if (q != nullptr)
	{
		if (prev == nullptr)
			head = q->next;
		else
			prev->next = q->next;

		q->next = nullptr;
		delete q;
		cout << "Da xoa thanh cong sinh vien co ma so: " << targetID << endl;
	}
	else
	{
		cout << "Khong tim thay sinh vien co ma so: " << targetID << endl;
	}
}
void selectionSort(Node* head)
{
	for (Node* i = head; i != nullptr && i->next != nullptr; i = i->next)
	{
		Node* minNode = i;
		for (Node* j = i->next; j != nullptr; j = j->next)
		{
			if (j->info.diemTB < minNode->info.diemTB)
			{
				minNode = j;
			}
		}
		swap(minNode->info, i->info);
	}
}
void bubbleSort(Node* head)
{
	if (head == nullptr) return;

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
	Node* head;
	SinhVien sv;
	init(head);
	readFile(head, "SinhVien.txt");
	output(head);

	/*deleteHead(head);
	output(head);
	deleteTail(head);
	output(head);*/
	/*string nameSearch;
	cout << "Nhap ten can tim: ";
	getline(cin, nameSearch);
	searchByName(head, nameSearch);*/

	/*SinhVien newSV = { "999999", "Nguyen Van A", "2005-05-05", 9.9 };
	string targetId;
	cout << "\nNhap ma so sinh vien X (can chen sinh vien moi phia sau): ";
	cin >> targetId;
	insertAfterID(head, newSV, targetId);
	output(head);*/

	string targetId;
	cout << "\nNhap ma so sinh vien X (can xoa sinh vien phia sau): ";
	cin >> targetId;
	deleteAfterID(head, targetId);
	output(head);

	//string targetId;
	//cout << "\nNhap ma so sinh vien X can xoa: ";
	//cin >> targetId;
	//deleteByID(head, targetId);
	//cout << "\n--- DANH SACH SAU KHI XOA ---";
	//output(head);

	/*selectionSort(head);
	cout << "\n--- DANH SACH SAU KHI SAP XEP TANG DAN THEO DIEM TRUNG BINH (SELECTION SORT)---";
	output(head);

	bubbleSort(head);
	cout << "\n--- DANH SACH SAU KHI SAP XEP GIAM DAN THEO DIEM TRUNG BINH (BUBBLE SORT)---";
	output(head);*/

	return 0;
}