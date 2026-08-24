#include<iostream>
using namespace std;
struct Node
{
	int key;
	Node* left, * right;
};
void init(Node*& root) {
	root = nullptr;
}
Node* createNode(int x) {
	Node* p = new Node();
	p->key = x;
	p->left = nullptr;
	p->right = nullptr;
	return p;
}
void addNode(Node*& root, int x) {
	Node* p = createNode(x);
	if (root == nullptr) root = p;
	else
	{
		Node* q = root;
		Node* parent = nullptr;
		while (q!=nullptr)
		{
			parent = q;
			if (x == q->key) root = p;
			if (x < q->key) q = q->left;
			else q = q->right;
		}
		if (x < parent->key) parent->left = p;
		else parent->right = p;
	}
}
void addNodeRec(Node*& root, int x) {
	if (root == nullptr) createNode(x);
	else if (x < root->key) addNodeRec(root->left, x);
	else if (x > root->key) addNodeRec(root->right, x);
}

void deleteNode(Node*& root,int x) {
	Node* p = root;
	Node* parent = nullptr;
	while (p!=nullptr&&p->key!=x)
	{
		parent = p;
		if (x < p->key) p = p->left;
		else p = p->right;
	}
	if (p != nullptr) { //tim thay node can xoa
		if (p->left==nullptr&&p->right==nullptr) //node la
		{
			if (parent == nullptr) root = nullptr;//cay chi co 1 node
			else // co nhieu hon 1 node
			{
				if (p->key < parent->key) parent->left = nullptr;
				else parent->right = nullptr;
			}
			delete p;
		}
		else //cay co 2 con
		{
			if (p->left!=nullptr&&p->right!=nullptr) // nho nhat cua cay con phai
			{
				parent = p;
				Node* temp = p->right;
				while (temp->left!=nullptr)
				{
					parent = temp;
					temp = temp->left;
				}
				p->key = temp->key;
				p = temp;
			}
			//xoa p khi chi con cay con trai hoac phai
			Node* r; //la con duy nhat cua node can xoa
			if (p->left == nullptr) r = p->right;
			else r = p->left;
			if (parent == nullptr) root = r;//node xoa la node goc
			else
			{
				if (p->key < parent->key) parent->left = r;
				else parent->right = r;
			}
			delete p;
		}
	}
}
void deleteNodeX(Node*& root) {
	int x;
	cout << "Nhap node can xoa: "; cin >> x;
	Node* p = root;
	Node* parent = nullptr;
	while (p!=nullptr&& p->key!=x)
	{
		parent = p;
		if (x < p->key) p = p->left;
		else p = p->right;
	}
	if (p!=nullptr)
	{
		if (p->left==nullptr&&p->right==nullptr)//node la
		{
			if (parent == nullptr) root = nullptr;
			else
			{
				if (p->key < parent->key) parent->left = nullptr;
				else parent->right = nullptr;
			}
			delete p;
		}
		else //th co 2 con
		{
			if (p->left!=nullptr&&p->right!=nullptr)
			{
				parent = p;
				Node* temp = p->right;
				while (temp->left!=nullptr)
				{
					parent = temp;
					temp = temp->left;
				}
				p->key = temp->key;
				p = temp;
			}
			//node can xoa co 2 con trai hoac phai
			Node* r;//con cua node can xoa
			if (p->right == nullptr) r = p->left;
			else r = p->right;
			if (parent == nullptr) root = r;
			else
			{
				if (p->key < parent->key) parent->left = r;
				else parent->right = r;
			}
			delete p;
		}
	}
}
void deleteNodeRec(Node*& root, int x) {
	if (root!=nullptr)
	{
		if (x < root->key) deleteNodeRec(root->left, x);
		else if (x < root->key) deleteNodeRec(root->right, x);
		else // tim thay x
		{
			if (root->left!=nullptr&&root->right!=nullptr)
			{
				Node* parent = root;
				Node* temp = root->right;
				while (temp->left!=nullptr)
				{
					parent = temp;
					temp = temp->left;
				}
				root->key = temp->key;
				deleteNodeRec(root->right, temp->key);
			}
			else //node la hoac co 1 cay con
			{
				Node* p = root;
				if (root->left == nullptr) root = root->right;
				else if (root->right == nullptr)root = root->left;
				delete p;
			}
		}
	}
}
Node* searchNode(Node* root, int x) {
	Node* p = root;
	while (p!=nullptr)
	{
		if (p->key == x) return p;
		else if (x < p->key) p = p->left;
		else p = p->right;
	}
	return nullptr;
}
void lnr(Node* root) {
	if (root!=nullptr)
	{
		lnr(root->left);
		cout << root->key << "\t";
		lnr(root->right);
	}
}
int main() {
	Node* root;
	init(root);
	addNode(root,521);
	addNode(root, 1234);
	addNode(root, 1);
	lnr(root);
	cout << endl;

	searchNode(root,1234);
	return 0;
}