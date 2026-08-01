#include <iostream>
#include <string>
using namespace std;

#define MAX 100

struct Stack {
    int a[MAX];
    int top;
};

void init(Stack& s) { s.top = -1; }
bool isEmpty(const Stack s) { return s.top == -1; }
bool isFull(const Stack s) { return s.top == MAX - 1; }

void push(Stack& s, int x) {
    if (!isFull(s)) s.a[++s.top] = x;
}
void pop(Stack& s) {
    if (!isEmpty(s)) s.top--;
}
int get(const Stack s) { return s.a[s.top]; }


//QUEUE (DSLKD)
struct Node {
    int info;
    Node* next;
};

Node* createNode(int x) {
    Node* p = new Node();
    p->info = x;
    p->next = nullptr;
    return p;
}

struct Queue {
    Node* head;
    Node* tail;
    int count;
};

void init(Queue& q) {
    q.head = nullptr;
    q.tail = nullptr;
    q.count = 0;
}

bool isEmpty(const Queue q) {
    return q.head == nullptr;
}

bool isFull(const Queue q) {
    return q.count == MAX;
}

void enqueue(Queue& q, int x) { //them cuoi
    if (!isFull(q)) {
        Node* p = createNode(x);
        if (isEmpty(q)) {
            q.head = p;
        }
        else {
            q.tail->next = p;
        }
        q.tail = p;
        q.count++;
    }
}

void dequeue(Queue& q) { //xoa dau
    if (!isEmpty(q)) {
        Node* p = q.head;
        q.head = p->next;
        if (q.head == nullptr) { //th hang doi chi co 1 pt
            q.tail = nullptr;
        }
        p->next = nullptr;
        delete p;
        q.count--;
    }
}

int getFront(const Queue q) {
    return q.head->info;
}


// === KIEM TRA CHUOI DOI XUNG ===
bool checkPalindrome(string str) {
    Stack s; init(s);
    Queue q; init(q);

    // Dua ky tu vao ca stack va queue
    for (int i = 0; i < str.length(); i++) {
        push(s, str[i]);
        enqueue(q, str[i]);
    }

    // Lay ra so sanh tung cap
    while (!isEmpty(s) && !isEmpty(q)) {
        if (get(s) != getFront(q)) {
            return false;
        }
        pop(s);
        dequeue(q);
    }

    return true;
}

int main() {
    string str;
    cout << "Nhap vao chuoi can kiem tra: ";
    cin >> str;

    if (checkPalindrome(str)) {
        cout << "Chuoi '" << str << "' LA chuoi doi xung!" << endl;
    }
    else {
        cout << "Chuoi '" << str << "' KHONG PHAI la chuoi doi xung!" << endl;
    }

    return 0;
}