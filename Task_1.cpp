#include <iostream>

using namespace std;

template <typename T>
class AbstractStack {
public:
    virtual void push(T value) = 0;
    virtual T pop() = 0;
    virtual T top() const = 0;
    virtual bool isEmpty() const = 0;
    virtual bool isFull() const = 0;
    virtual ~AbstractStack() {}
};

template <typename T>
class MyStack : public AbstractStack<T> {
private:
    T* arr;
    int capacity;
    int topIndex;

public:
    MyStack(int size) {
        capacity = size;
        arr = new T[capacity];
        topIndex = -1;
    }

    ~MyStack() {
        delete[] arr;
    }

    void push(T value) override {
        if (isFull()) {
            cout << "Stack Overflow!\n";
            return;
        }
        arr[++topIndex] = value;
    }

    T pop() override {
        if (isEmpty()) {
            cout << "Stack Underflow!\n";
            return T();
        }
        return arr[topIndex--];
    }

    T top() const override {
        if (isEmpty()) {
            cout << "Stack is Empty!\n";
            return T();
        }
        return arr[topIndex];
    }

    bool isEmpty() const override {
        return topIndex == -1;
    }

    bool isFull() const override {
        return topIndex == capacity - 1;
    }

    void display() const {
        if (isEmpty()) {
            cout << "Stack is Empty!\n";
            return;
        }
        cout << "Stack elements (Top to Bottom):\n";
        for (int i = topIndex; i >= 0; i--) {
            cout << arr[i] << "\n";
        }
    }
};

int main() {
    int size;
    cout << "Enter stack capacity: ";
    cin >> size;

    MyStack<int> stack(size);
    int choice;
    int val;

    do {
        cout << "\n1. Push element\n";
        cout << "2. Pop element\n";
        cout << "3. Show top element\n";
        cout << "4. Check if stack is empty\n";
        cout << "5. Check if stack is full\n";
        cout << "6. Display stack elements\n";
        cout << "7. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter value to push: ";
            cin >> val;
            stack.push(val);
            break;
        case 2:
            val = stack.pop();
            if (!stack.isEmpty() || val != int()) {
                cout << "Popped element successfully.\n";
            }
            break;
        case 3:
            val = stack.top();
            if (!stack.isEmpty()) {
                cout << "Top element: " << val << "\n";
            }
            break;
        case 4:
            if (stack.isEmpty()) {
                cout << "Stack is empty.\n";
            } else {
                cout << "Stack is not empty.\n";
            }
            break;
        case 5:
            if (stack.isFull()) {
                cout << "Stack is full.\n";
            } else {
                cout << "Stack is not full.\n";
            }
            break;
        case 6:
            stack.display();
            break;
        case 7:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice!\n";
        }
    } while (choice != 7);

    return 0;
}
