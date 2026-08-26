#include<iostream>
#include<cmath> 
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
		while (q != nullptr)
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
	else addNodeRec(root->right, x);
}
void deleteNode(Node*& root, int x) {
	Node* p = root;
	Node* parent = nullptr;
	while (p != nullptr && p->key != x)
	{
		parent = p;
		if (x < p->key) p = p->left;
		else p = p->right;
	}
	if (p != nullptr) //tim thay node can xoa
	{
		if (p->left == nullptr && p->right == nullptr)
		{
			if (parent == nullptr) root = nullptr;
			else
			{
				if (p->key < parent->key) parent->left = nullptr;
				else parent->right = nullptr;
			}
			delete p;
		}
		else //node co 2 con
		{
			if (p->left != nullptr && p->right != nullptr) //xoa node nho nhat cay con trai
			{
				parent = p;
				Node* temp = p->right;
				while (temp->left != nullptr)
				{
					parent = temp;
					temp = temp->left;
				}
				p->key = temp->key;
				p = temp;
			}
			//xoa node co con trai hoac phai
			Node* r; // con cua node can xoa
			if (p->left == nullptr) r = p->right;
			else r = p->left;
			if (parent == nullptr) root = r;//node can xoa la node goc
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
	if (root != nullptr)
	{
		if (x < root->key) deleteNodeRec(root->left, x);
		else if (x > root->key) deleteNodeRec(root->right, x);
		else //tim thay x
		{
			if (root->left != nullptr && root->right != nullptr)
			{
				Node* parent = root;
				Node* temp = root->right;
				while (temp->left != nullptr)
				{
					parent = temp;
					temp = temp->left;
				}
				root->key = temp->key;
				deleteNodeRec(root->right, temp->key);
			}
			else //node la hoac cay co 1 con
			{
				Node* p = root;
				if (root->left == nullptr) root = root->right;
				else if (root->right == nullptr) root = root->left;
				delete p;
			}

		}
	}
}
void lnr(Node* root) {
	if (root != nullptr)
	{
		lnr(root->left);
		cout << root->key << "\t";
		lnr(root->right);
	}
}
Node* searchNode(Node* root, int x) {
	Node* p = root;
	while (p != nullptr)
	{
		if (p->key == x) return p;
		else if (x < p->key) p = p->left;
		else p = p->right;
	}
	return nullptr;
}
void rnl(Node* root) { //sap xep thu tu giam dan
	if (root != nullptr)
	{
		rnl(root->right);
		cout << root->key << "\t";
		rnl(root->left);
	}
}
int countNodes(Node* root) {
	if (root == nullptr) return 0;
	return 1 + countNodes(root->left) + countNodes(root->right);
}
int countLeaves(Node* root) {
	if (root == nullptr) return 0;
	if (root->left == nullptr && root->right == nullptr) return 1;
	else return countLeaves(root->left) + countLeaves(root->right);
}
int countOneChild(Node* root) {
	if (root == nullptr) return 0;

	int count = 0;
	if ((root->left != nullptr && root->right == nullptr) || (root->left == nullptr && root->right != nullptr))
	{
		count = 1;
	}
	return count + countOneChild(root->left) + countOneChild(root->right);
}
int countTwoChildren(Node* root) {
	if (root == nullptr) return 0;

	int count = 0;
	if (root->left != nullptr && root->right != nullptr)
	{
		count = 1;
	}
	return count + countTwoChildren(root->left) + countTwoChildren(root->right);
}
bool isPrime(int n) {
	if (n < 2) return false;
	if (n == 2) return true;
	for (int i = 2; i <= sqrt(n); i++)
	{
		if (n % i == 0)
		{
			return false;
		}
	}
	return true;
}
int countPrime(Node* root) {
	if (root == nullptr) return 0;

	int count = 0;
	if (isPrime(root->key))
	{
		count = 1;
	}
	return count + countPrime(root->left) + countPrime(root->right);
}
int sumTree(Node* root) {
	if (root == nullptr) return 0;
	return root->key + sumTree(root->left) + sumTree(root->right);
}
int findMin(Node* root) {
	if (root->left == nullptr)
		return root->key;
	return findMin(root->left);
}
int findMax(Node* root) {
	if (root->right == nullptr)
	{
		return root->key;
	}
	return findMax(root->right);
}
int height(Node* root) {
	if (root == nullptr) return 0;

	int left = height(root->left);
	int right = height(root->right);
	return 1 + max(left, right);
}
void printTree90(Node* root, int space = 0, int gap = 5) {
	if (root == nullptr) return;

	space += gap;
	printTree90(root->right, space, gap);//in cay con phai

	for (int i = gap; i < space; i++)
	{
		cout << " ";
	}
	cout << root->key << endl;//in node cha
	printTree90(root->left, space, gap);//in cay con trai
}
int main() {
	Node* root;
	init(root);
	addNodeRec(root, 45);
	addNodeRec(root, 17);
	addNodeRec(root, 88);
	addNodeRec(root, 23);
	addNodeRec(root, 6);
	addNodeRec(root, 91);
	addNodeRec(root, 34);
	addNodeRec(root, 79);
	addNodeRec(root, 12);
	rnl(root);
	cout << endl;
	printTree90(root, 0, 5);
	return 0;
}