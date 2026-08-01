#include <iostream>
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

void convertToBinary(int n) {
    Stack s;
    init(s);

    if (n == 0) {
        cout << 0 << endl;
        return;
    }

    while (n != 0) {
        push(s, n % 2);
        n /= 2;
    }

    while (!isEmpty(s)) {
        cout << get(s);
        pop(s);
    }
    cout << endl;
}

int main() {
    int n;
    cout << "Nhap vao mot so nguyen he thap phan: ";
    cin >> n;

    cout << "Gia tri he nhi phan cua " << n << " la: ";
    convertToBinary(n);

    return 0;
}