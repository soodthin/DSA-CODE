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
	if (root==nullptr)
	{
		root = p;
	}
	else
	{
		Node* q = root;
		Node* parent = nullptr;
		while (q != nullptr)
		{
			parent = q;
			if (q->key > x)
			{
				q = q->left;
			}
			else
			{
				q = q->right;
			}
		}
		if (parent->key > x)
		{
			parent->left = p;
		}
		else
		{
			parent->right = p;
		}
	}
}
void addNodeRec(Node*& root, int x) {
	Node* p = createNode(x);
	if (root==nullptr)
	{
		root = createNode(x);
	}
	else if (root->key>x)
	{
		addNodeRec(root->left, x);
	}
	else
	{
		addNodeRec(root->right, x);
	}
}
void lnr(Node* root) {
	if (root!=nullptr)
	{
		lnr(root->left);
		cout << root->key << "\t";
		lnr(root->right);
	}
}
void nlr(Node* root) {
	if (root!=nullptr)
	{
		cout << root->key << "\t";
		nlr(root->left);
		nlr(root->right);
	}
}
void lrn(Node* root) {
	if (root != nullptr)
	{
		lrn(root->left);
		lrn(root->right);
		cout << root->key << "\t";
	}
}
void deleteNode(Node*& root, int x) {
	Node* p = root;
	Node* parent = nullptr;
	while (p!=nullptr&&p->key!=x)
	{
		parent = p;
		if (p->key>x)
		{
			p = p->left;
		}
		else
		{
			p = p->right;
		}
	}
	if (p!=nullptr) //tim thay nut can xoa
	{
		if (p->left==nullptr&&p->right==nullptr) //p la nut la
		{
			if (parent==nullptr) //cay chi co 1 nut
			{
				root = nullptr;
			}
			else//cay co hon 1 nut
			{
				if (p->key<parent->key)
				{
					parent->left = nullptr;
				}
				else
				{
					parent->right = nullptr;
				}
			}
			delete p;
		}
		else //cay co 2 nut
		{
			if (p->left!=nullptr&&p->right!=nullptr) //tim the mang: trai nhat cua cay phai
			{
				parent = p;
				Node* temp = p->right;
				while (temp->left!=nullptr)
				{
					parent = temp;
					temp = temp->left;
				}
				p->key = temp->key; //thay the gia tri
				p = temp;
			}
			Node* r;
			if (p->right == nullptr)
			{
				r = p->left;
			}
			else
			{
				r = p->right;
			}
			if (parent == nullptr)//nut xoa la nut goc
			{
				root = r;
			}
			else
			{
				if (p->key < parent->key)
				{
					parent->left = r;
				}
				else
				{
					parent->right = r;
				}
			}
			delete p;
		}
	}
}
void deleteNodeRec(Node*& root, int x) {
	if (root != nullptr)//tim nut chua x
	{
		if (x < root->key)
		{
			deleteNodeRec(root->left, x);
		}
		else if (x > root->key)
		{
			deleteNodeRec(root->right, x);
		}
		else //tim thay x
		{
			if (root->left != nullptr && root->right != nullptr)
			{
				Node* temp = root->right;
				Node* parent = root;
				while (temp->left != nullptr)
				{
					parent = temp;
					temp = temp->left;
				}
				root->key = temp->key;
				deleteNodeRec(root->right, temp->key);
			}
			else //nut la hoac co 1 cay con
			{
				Node* p = root;
				if (root->left == nullptr)
				{
					root = root->right;
				}
				else if (root->right == nullptr)
				{
					root = root->left;
				}
				delete p;
			}
		}
	}
}
int main() {
	Node* root;
	init(root);
	addNode(root, 10);
	addNode(root, 50);
	addNode(root, 20);


	lrn(root);
	cout << endl;
	nlr(root);
	cout << endl;
	deleteNodeRec(root, 20);
	lnr(root);

	return 0;
}