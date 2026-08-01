#include <iostream>
#include <string>
using namespace std;

#define MAX 100

struct Stack {
    int a[MAX];
    int top;
};

void init(Stack& s) {
    s.top = -1;
}

bool isEmpty(const Stack s) {
    return s.top == -1;
}

bool isFull(const Stack s) {
    return s.top == MAX - 1;
}

void push(Stack& s, int x) {
    if (!isFull(s))
        s.a[++s.top] = x;
}

void pop(Stack& s) {
    if (!isEmpty(s))
        s.top--;
}

int get(const Stack s) {
    return s.a[s.top];
}

struct Queue {
    int a[MAX];
    int front;
    int rear;
};

void init(Queue& q) {
    q.front = -1;
    q.rear = -1;
}

bool isEmpty(const Queue q) {
    return q.front == -1;
}

bool isFull(const Queue q) {
    return q.rear == MAX - 1;
}

void enqueue(Queue& q, int x) { //them cuoi
    if (!isFull(q)) {
        if (isEmpty(q))
            q.front++;
        q.a[++q.rear] = x;
    }
}

void dequeue(Queue& q) { //xoa dau
    if (!isEmpty(q)) {
        q.front++;
        if (q.front > q.rear) {
            q.front = -1;
            q.rear = -1;
        }
    }
}

int getFront(Queue q) {
    return q.a[q.front];
}

bool checkPalindrome(string str) {
    Stack s;
    init(s);
    Queue q;
    init(q);

    for (int i = 0; i < str.length(); i++) {
        push(s, str[i]);
        enqueue(q, str[i]);
    }

    while (!isEmpty(s) && !isEmpty(q)) {
        if (get(s) != getFront(q)) {
            return false;
        }
        pop(s);
        dequeue(q);
    }

    return true;
}
void output(Queue q) {
    if (!isEmpty(q)) {
        for (int i = q.front; i <= q.rear; i++)
            cout << q.a[i] << "\t";
        cout << endl;
    }
    else {
        cout << "Queue hien dang rong!" << endl;
    }
}
int main() {
    Queue q;
    init(q);

    enqueue(q, 10);
    enqueue(q, 20);
    enqueue(q, 30);
    output(q);


    dequeue(q);
    output(q);

    /* string str;
     cout << "Nhap vao chuoi can kiem tra: ";
     cin >> str;

     if (checkPalindrome(str)) {
         cout << "Chuoi '" << str << "' LA chuoi doi xung!" << endl;
     }
     else {
         cout << "Chuoi '" << str << "' KHONG PHAI la chuoi doi xung!" << endl;
     }*/

    return 0;
}