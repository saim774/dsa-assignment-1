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
            return;
        }
        arr[++topIndex] = value;
    }

    T pop() override {
        if (isEmpty()) {
            return T();
        }
        return arr[topIndex--];
    }

    T top() const override {
        if (isEmpty()) {
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

template <typename T>
class MinStack : public AbstractStack<T> {
private:
    MyStack<T> mainStack;
    MyStack<T> minStack;

public:
    MinStack(int size) : mainStack(size), minStack(size) {}

    void push(T value) override {
        if (mainStack.isFull()) {
            cout << "Stack Overflow!\n";
            return;
        }
        mainStack.push(value);
        if (minStack.isEmpty() || value <= minStack.top()) {
            minStack.push(value);
        }
    }

    T pop() override {
        if (mainStack.isEmpty()) {
            cout << "Stack Underflow!\n";
            return T();
        }
        T poppedVal = mainStack.pop();
        if (poppedVal == minStack.top()) {
            minStack.pop();
        }
        return poppedVal;
    }

    T top() const override {
        return mainStack.top();
    }

    bool isEmpty() const override {
        return mainStack.isEmpty();
    }

    bool isFull() const override {
        return mainStack.isFull();
    }

    T getMin() const {
        if (minStack.isEmpty()) {
            cout << "Stack is Empty!\n";
            return T();
        }
        return minStack.top();
    }

    void display() const {
        mainStack.display();
    }
};

int main() {
    int size;
    cout << "Enter stack capacity: ";
    cin >> size;

    MinStack<int> stack(size);
    int choice;
    int val;

    do {
        cout << "\n1. Push element\n";
        cout << "2. Pop element\n";
        cout << "3. Show top element\n";
        cout << "4. Check if stack is empty\n";
        cout << "5. Check if stack is full\n";
        cout << "6. Display stack elements\n";
        cout << "7. Show minimum element\n";
        cout << "8. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter value to push: ";
            cin >> val;
            stack.push(val);
            break;
        case 2:
            stack.pop();
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
            val = stack.getMin();
            if (!stack.isEmpty()) {
                cout << "Minimum element: " << val << "\n";
            }
            break;
        case 8:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice!\n";
        }
    } while (choice != 8);

    return 0;
}
