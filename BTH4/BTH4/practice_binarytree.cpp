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
		while (q!=nullptr)
		{
			parent = q;
			if (q->key == x) return;
			if (x < q->key) q = q->left;
			else q = q->right;
		}
		if (x < parent->key) parent->left = p;
		else parent->right = p;
	}
}
void addNodeRec(Node*& root, int x) {
	if (root == nullptr) root = createNode(x);
	else if (x < root->key) addNodeRec(root->left, x);
	else if (x > root->key) addNodeRec(root->right, x);
}
void nlr(Node* root) {
	if (root!=nullptr)
	{
		cout << root->key << "\t";
		nlr(root->left);
		nlr(root->right);
	}
}
void deleteNode(Node*& root, int x) {
	Node* p = root;
	Node* parent = nullptr;
	while (p!=nullptr&&p->key!=x)
	{
		parent = p;
		if (x < p->key) p = p->left;
		else p = p->right;
	}
	if (p!=nullptr)
	{
		if (p->left==nullptr&&p->right==nullptr) //p la node la
		{
			if (parent == nullptr) root = nullptr; //cay chi co 1 node
			else //cay co > 1 node
			{
				if (p->key < parent->key) parent->left = nullptr;
				else parent->right = nullptr;
			}
			delete p;
		}
		else //th co 2 cay con
		{
			if (p->left!=nullptr&&p->right!=nullptr) //tim the mang: trai nhat cua cay con phai
			{

			}
		}
	}
}
int main() {
	Node* root;
	init(root);
	addNode(root, 10);
	addNode(root, 1320);
	addNode(root, 521);
	nlr(root);
	return 0;
}