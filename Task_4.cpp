#include <iostream>
#include <string>

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
    MyStack<string> undoStack(100);
    MyStack<string> redoStack(100);
    string currentText = "";
    int choice;

    undoStack.push(currentText);

    do {
        cout << "\n--- Text Editor ---\n";
        cout << "Current Text: \"" << currentText << "\"\n";
        cout << "1. Type text\n";
        cout << "2. Delete characters\n";
        cout << "3. Undo\n";
        cout << "4. Redo\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            string textToAdd;
            cout << "Enter text to add: ";
            cin >> textToAdd;
            currentText += textToAdd;
            undoStack.push(currentText);

            while (!redoStack.isEmpty()) {
                redoStack.pop();
            }
            break;
        }
        case 2: {
            int n;
            cout << "Enter number of characters to delete from end: ";
            cin >> n;
            if (n > currentText.length()) {
                currentText = "";
            } else {
                currentText = currentText.substr(0, currentText.length() - n);
            }
            undoStack.push(currentText);

            while (!redoStack.isEmpty()) {
                redoStack.pop();
            }
            break;
        }
        case 3: {
            MyStack<string> temp(100);
            int count = 0;
            while (!undoStack.isEmpty()) {
                temp.push(undoStack.pop());
                count++;
            }
            while (!temp.isEmpty()) {
                undoStack.push(temp.pop());
            }

            if (count > 1) {
                redoStack.push(currentText);
                undoStack.pop();
                currentText = undoStack.top();
                cout << "Undo performed successfully.\n";
            } else {
                cout << "Nothing to undo!\n";
            }
            break;
        }
        case 4: {
            if (!redoStack.isEmpty()) {
                undoStack.push(currentText);
                currentText = redoStack.top();
                redoStack.pop();
                cout << "Redo performed successfully.\n";
            } else {
                cout << "Nothing to redo!\n";
            }
            break;
        }
        case 5:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice!\n";
        }
    } while (choice != 5);

    return 0;
}
