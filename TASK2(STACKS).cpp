#include <iostream>
#include <cmath>
#include <climits>

using namespace std;

// Stack Class
class Stack {
public:
    int capacity;
    int top;
    int* array;

    // Constructor
    Stack(int cap) {
        capacity = cap;
        top = -1;
        array = new int[cap];
    }

    // Destructor
    ~Stack() {
        delete[] array;
    }
};

// Function to check if the stack is full
bool isFull(Stack& st) {
    return (st.top == st.capacity - 1);
}

// Function to check if the stack is empty
bool isEmpty(Stack& st) {
    return (st.top == -1);
}

// Function to push an item onto the stack
void push(Stack& st, int item) {
    if (isFull(st)) {
        return;
    }
    st.array[++st.top] = item;
}

// Function to pop an item from the stack
int pop(Stack& st) {
    if (isEmpty(st)) {
        return INT_MIN;
    }
    return st.array[st.top--];
}

// Function to carry out the movement of the disk between two poles
void move(Stack& src, Stack& dest, char s, char d) {
    int disk1 = pop(src);
    int disk2 = pop(dest);

    //when source is empty , push a disk from the destination stack (dest) to the source stack
    if (disk1 == INT_MIN) {
        push(src, disk2);
        cout << "Move the disk " << disk2 << " from " << d << " to " << s << endl;
    } 
    //when destinition is empty , push a disk from the source stack (dest) to the destination stack
    else if (disk2 == INT_MIN) {
        push(dest, disk1);
        cout << "Move the disk " << disk1 << " from " << s << " to " << d << endl;
    } 
    // If this is true, it means that the disk being moved from the source stack (src) is larger than the disk 
    //being moved from the destination stack (dest).
    else if (disk1 > disk2) {
        push(src, disk1);
        push(src, disk2);
        cout << "Move the disk " << disk2 << " from " << d << " to " << s << endl;
    } else {
        push(dest, disk2);
        push(dest, disk1);
        cout << "Move the disk " << disk1 << " from " << s << " to " << d << endl;
    }
}

// Function to implement the algorithm
void iterativeTowerOfHanoi(int n, Stack& src, Stack& aux, Stack& dest) {
    int moves;
    char s = 'S', d = 'D', a = 'A';

    // If n is even then exchange the position of destination rod and auxiliary rod.
    if (n % 2 == 0) {
        char temp = d;
        d = a;
        a = temp;
    }

    moves = (pow(2, n) - 1);

    for (int i = n; i >= 1; i--) {
        push(src, i);
    }
    int count = 0;
    for (int i = 1; i <= moves; i++) {
        if (i % 3 == 1) {
            move(src, dest, s, d);
        } else if (i % 3 == 2) {
            move(src, aux, s, a);
        } else if (i % 3 == 0) {
            move(aux, dest, a, d);
        }
        count++;
    }

    cout<<"\nTotal "<<count << " moves done to shift from source to destination stack\n";
}

// Main function
int main() {
    int n = 5;

    // Create three stacks (Source, destination, Auxiliary)
    Stack source(n);
    Stack destination(n);
    Stack auxiliary(n);

    iterativeTowerOfHanoi(n, source, auxiliary, destination);

    return 0;
}