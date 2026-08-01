#include <iostream>
#include <cmath>
using namespace std;

struct Node {
    int key;
    Node* left;
    Node* right;
};

Node* createNode(int x) {
    Node* p = new Node;
    p->key = x;
    p->left = NULL;
    p->right = NULL;
    return p;
}

//them nut (ko de quy)
void addNode(Node*& root, int x) {
    Node* p = createNode(x);
    if (root == NULL) root = p;
    else {
        Node* q = root;
        Node* parent = NULL;
        while (q != NULL) {
            parent = q;
            if (q->key == x) return;
            if (q->key > x) q = q->left;
            else q = q->right;
        }
        if (parent->key > x) parent->left = p;
        else parent->right = p;
    }
}

//them nut (de quy)
void addNodeRec(Node*& root, int x) {
    if (root == NULL) root = createNode(x);
    else if (root->key > x) addNodeRec(root->left, x);
    else if (root->key < x) addNodeRec(root->right, x);
}

//xoa nut (ko de quy)
void deleteNode(Node*& root, int x) {
    Node* p = root;
    Node* parent = NULL;

    while (p != NULL && p->key != x) {
        parent = p;
        if (p->key > x) p = p->left;
        else p = p->right;
    }

    if (p != NULL) {
        // TH co 2 con: Tim the mang la trai nhat cua cay con phai
        if (p->left != NULL && p->right != NULL) {
            Node* tmp = p->right;
            parent = p;
            while (tmp->left != NULL) {
                parent = tmp;
                tmp = tmp->left;
            }
            p->key = tmp->key;
            p = tmp;
        }

        // TH co 1 con hoac 0 con
        Node* child;
        if (p->left == NULL) child = p->right;
        else child = p->left;

        if (parent == NULL) root = child; // Xoa goc
        else {
            if (parent->left == p) parent->left = child;
            else parent->right = child;
        }
        delete p;
    }
}

//xoa nut (de quy)
void deleteNodeRec(Node*& root, int x) {
    if (root == NULL) return;
    if (x < root->key) deleteNodeRec(root->left, x);
    else if (x > root->key) deleteNodeRec(root->right, x);
    else { //tim thay x
        if (root->left != NULL && root->right != NULL) { //th: 2 nut con
            Node* tmp = root->right;
            while (tmp->left != NULL) tmp = tmp->left;
            root->key = tmp->key;
            deleteNodeRec(root->right, tmp->key);
        }
        else { //th: nut la va nut con
            Node* p = root;
            if (root->left == NULL) root = root->right;
            else if (root->right == NULL) root = root->left;
            delete p;
        }
    }
}

Node* searchNode(Node* root, int x) {
    Node* p = root;
    while (p != NULL) {
        if (p->key == x) return p;
        else if (p->key > x) p = p->left;
        else p = p->right;
    }
    return NULL;
}

void nlr(Node* root) {
    if (root != NULL) {
        cout << root->key << " ";
        nlr(root->left);
        nlr(root->right);
    }
}

void lnr(Node* root) {
    if (root != NULL) {
        lnr(root->left);
        cout << root->key << " ";
        lnr(root->right);
    }
}

void lrn(Node* root) {
    if (root != NULL) {
        lrn(root->left);
        lrn(root->right);
        cout << root->key << " ";
    }
}

//in giam dan
void RNL(Node* root) {
    if (root != NULL) {
        RNL(root->right);
        cout << root->key << " ";
        RNL(root->left);
    }
}

void printTree90(Node* root, int space = 0, int gap = 5) {
    if (root==nullptr)
        return;
    space += gap;
    printTree90(root->right, space, gap);
    cout << endl;
    for (int i = gap; i < space; i++)
    {
        cout << " ";
    }
    cout << root->key << endl;

    printTree90(root->left, space, gap);
    
 }


int countNodes(Node* root) {
    if (root == NULL) return 0;
    return 1 + countNodes(root->left) + countNodes(root->right);
}

int countLeaves(Node* root) {
    if (root == NULL) return 0;
    if (root->left == NULL && root->right == NULL) return 1;
    return countLeaves(root->left) + countLeaves(root->right);
}

int countOneChild(Node* root) {
    if (root == NULL) return 0;
    int count = 0;
    if ((root->left == NULL && root->right != NULL) || (root->left != NULL && root->right == NULL))
        count = 1;
    return count + countOneChild(root->left) + countOneChild(root->right);
}

int countTwoChildren(Node* root) {
    if (root == NULL) return 0;
    int count = 0;
    if (root->left != NULL && root->right != NULL) count = 1;
    return count + countTwoChildren(root->left) + countTwoChildren(root->right);
}

bool isPrime(int n) {
    if (n < 2) return false;
    for (int i = 2; i * i <= n; i++)
        if (n % i == 0) return false;
    return true;
}

int countPrimes(Node* root) {
    if (root == NULL) return 0;
    int count = isPrime(root->key) ? 1 : 0;
    return count + countPrimes(root->left) + countPrimes(root->right);
}

int sumTree(Node* root) {
    if (root == NULL) return 0;
    return root->key + sumTree(root->left) + sumTree(root->right);
}

Node* findMax(Node* root) {
    if (root == NULL) return NULL;
    while (root->right != NULL) root = root->right;
    return root;
}

Node* findMin(Node* root) {
    if (root == NULL) return NULL;
    while (root->left != NULL) root = root->left;
    return root;
}

int height(Node* root) {
    if (root == NULL) return 0;
    int leftH = height(root->left);
    int rightH = height(root->right);
    return (leftH > rightH ? leftH : rightH) + 1;
}

int main() {
    Node* root = NULL;

    int arr[] = { 50, 25, 75, 15, 35, 65, 85, 10, 20, 60, 80 };
    for (int i = 0; i < 11; i++) {
        addNode(root, arr[i]);
    }

    cout << "j. Dang cay xoay 90 do: \n";
    printTree90(root);

    cout << "\nf. Duyet NLR: "; nlr(root);
    cout << "\ng. Duyet LNR (Tang dan): "; lnr(root);
    cout << "\nh. Duyet LRN: "; lrn(root);
    cout << "\ni. In giam dan: "; RNL(root);

    cout << "\n\nk. Tong so nut: " << countNodes(root);
    cout << "\nl. So nut la: " << countLeaves(root);
    cout << "\nm. So nut 1 con: " << countOneChild(root);
    cout << "\nn. So nut 2 con: " << countTwoChildren(root);
    cout << "\no. So nut nguyen to: " << countPrimes(root);
    cout << "\np. Tong gia tri: " << sumTree(root);

    Node* maxNode = findMax(root);
    Node* minNode = findMin(root);
    cout << "\nq. Max: " << (maxNode ? maxNode->key : -1);
    cout << "\nr. Min: " << (minNode ? minNode->key : -1);
    cout << "\ns. Chieu cao cua cay: " << height(root) << endl;

    // Test d. Xoa nut
    cout << "\n=> Thuc hien xoa nut 25 (nut co 2 con)...";
    deleteNode(root, 25);
    cout << "\nLNR sau khi xoa: "; lnr(root);

    return 0;
}