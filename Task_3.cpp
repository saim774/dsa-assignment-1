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
    MyStack<string> parkingLot(8);
    int choice;
    string carNum;

    do {
        cout << "\n--- Parking Lot Management System ---\n";
        cout << "1. Park a new car\n";
        cout << "2. Remove a car\n";
        cout << "3. View parked cars\n";
        cout << "4. Total cars parked\n";
        cout << "5. Search for a car\n";
        cout << "6. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            if (parkingLot.isFull()) {
                cout << "Parking lot is full (Limit 8 cars)!\n";
            } else {
                cout << "Enter car number/license plate: ";
                cin >> carNum;
                parkingLot.push(carNum);
                cout << "Car parked successfully.\n";
            }
            break;
        case 2:
            if (parkingLot.isEmpty()) {
                cout << "Parking lot is empty!\n";
            } else {
                cout << "Enter car number to remove: ";
                cin >> carNum;

                MyStack<string> tempStack(8);
                bool found = false;

                while (!parkingLot.isEmpty()) {
                    string currentCar = parkingLot.pop();
                    if (currentCar == carNum) {
                        found = true;
                        break;
                    }
                    tempStack.push(currentCar);
                }

                if (found) {
                    cout << "Car " << carNum << " removed from parking lot.\n";
                } else {
                    cout << "Car not found in the parking lot!\n";
                }

                while (!tempStack.isEmpty()) {
                    parkingLot.push(tempStack.pop());
                }
            }
            break;
        case 3:
            cout << "Currently Parked Cars:\n";
            parkingLot.display();
            break;
        case 4: {
            MyStack<string> tempStack(8);
            int count = 0;
            while (!parkingLot.isEmpty()) {
                tempStack.push(parkingLot.pop());
                count++;
            }
            while (!tempStack.isEmpty()) {
                parkingLot.push(tempStack.pop());
            }
            cout << "Total cars parked: " << count << "/8\n";
            break;
        }
        case 5: {
            if (parkingLot.isEmpty()) {
                cout << "Parking lot is empty!\n";
            } else {
                cout << "Enter car number to search: ";
                cin >> carNum;

                MyStack<string> tempStack(8);
                bool found = false;

                while (!parkingLot.isEmpty()) {
                    string currentCar = parkingLot.pop();
                    if (currentCar == carNum) {
                        found = true;
                    }
                    tempStack.push(currentCar);
                }

                while (!tempStack.isEmpty()) {
                    parkingLot.push(tempStack.pop());
                }

                if (found) {
                    cout << "Car " << carNum << " is present in the parking lot.\n";
                } else {
                    cout << "Car " << carNum << " is not found in the parking lot.\n";
                }
            }
            break;
        }
        case 6:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice!\n";
        }
    } while (choice != 6);

    return 0;
}
