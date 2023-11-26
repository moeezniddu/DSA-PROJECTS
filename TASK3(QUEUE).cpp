#include <iostream>
#include <queue>
#include <cstdlib> // For rand() function

using namespace std;

// Student class to store student information
class Student
{
public:
    string name;
    int merit;

    Student(string n, int m) : name(n), merit(m) {}
};

// Node class to store Student object as data member
class Node
{
public:
    Student data;
    Node *next;

    Node(Student s) : data(s), next(nullptr) {}
};

// Queue class to implement the queue data structure
class Queue
{
private:
    Node *front;
    Node *rear;

public:
    Queue() : front(nullptr), rear(nullptr) {}

    bool isEmpty()
    {
        return front == nullptr;
    }

    void enqueue(Student s)
    {
        Node *newNode = new Node(s);
        if (isEmpty())
        {
            front = rear = newNode;
        }
        else
        {
            rear->next = newNode;
            rear = newNode;
        }
    }

    Student dequeue()
    {
        if (isEmpty())
        {
            cerr << "Queue is empty." << endl;
            return Student(" ", 0);
        }

        Node *temp = front;
        front = front->next;
        Student data = temp->data;
        delete temp;
        return data;
    }

    int size()
    {
        int count = 0;
        Node *current = front;
        while (current != nullptr)
        {
            count++;
            current = current->next;
        }
        return count;
    }

    Student peek()
    {
        if (isEmpty())
        {
            cerr << "Queue is empty." << endl;
            return Student(" ", 0);
        }
        return front->data;
    }
};

// AdmissionSystem class to manage the admission process
class AdmissionSystem
{
private:
    Queue queues[3];

public:
    // void addStudentToQueue()
    // {
    //     string name;
    //     int merit;

    //     cout << "Enter student name: ";
    //     cin >> name;
    //     cout << "Enter student merit: ";
    //     cin >> merit;

    //     // Randomly enqueue in any of the queues if all queues have the same number of students
    //     int minSize = min(queues[0].size(), min(queues[1].size(), queues[2].size()));
    //     int randomQueue = rand() % 3;

    //     if (queues[0].size() == minSize && queues[1].size() == minSize && queues[2].size() == minSize)
    //     {
    //         randomQueue = rand() % 3;
    //         queues[randomQueue].enqueue(Student(name, merit));
    //         cout << "Student added to Queue " << randomQueue + 1 << endl;
    //     }

    //     else if (queues[1].size() == minSize)
    //     {
    //         queues[1].enqueue(Student(name, merit));
    //         cout << "Student added to Queue 2"  << endl;
    //     }

    //     else if (queues[2].size() < minSize)
    //     {
    //         queues[2].enqueue(Student(name, merit));
    //         cout << "Student added to Queue 3" << endl;
    //     }

    //     else
    //     {
    //         queues[0].enqueue(Student(name, merit));
    //         cout << "Student added to Queue 1" << endl;
    //     }

    // }
    void addStudentToQueue()
    {
        string name;
        int merit;

        cout << "Enter student name: ";
        cin >> name;
        cout << "Enter student merit: ";
        cin >> merit;

        int minSize = min(queues[0].size(), min(queues[1].size(), queues[2].size()));

        // If all queues have the same number of students, enqueue randomly
        if (queues[0].size() == minSize && queues[1].size() == minSize && queues[2].size() == minSize)
        {
            int randomQueue = rand() % 3;
            queues[randomQueue].enqueue(Student(name, merit));
            cout << "Student added to Queue " << randomQueue + 1 << endl;
        }
        else
        {
            // Find the first queue with the minimum number of students
            for (int i = 0; i < 3; ++i)
            {
                if (queues[i].size() == minSize)
                {
                    queues[i].enqueue(Student(name, merit));
                    cout << "Student added to Queue " << i + 1 << endl;
                    break;
                }
            }
        }
    }

    void processAdmissions()
    {
        for (int i = 0; i < 3; ++i)
        {
            while (!queues[i].isEmpty())
            {
                Student currentStudent = queues[i].peek();
                cout << "Processing admission for student " << currentStudent.name << " with merit " << currentStudent.merit << " in Queue " << i + 1 << endl;

                if (currentStudent.merit > 50)
                {
                    cout << "Admission approved for " << currentStudent.name << endl;
                }
                else
                {
                    cout << "Admission denied for " << currentStudent.name << endl;
                }

                queues[i].dequeue();
            }
        }
    }

    void checkQueueStatus()
    {
        for (int i = 0; i < 3; ++i)
        {
            cout << "Queue " << i + 1 << " - Number of students: " << queues[i].size() << endl;
        }
    }

    void seeWhoIsNext()
    {
        int queueNumber;
        cout << "Enter the queue number: ";
        cin >> queueNumber;

        if (queueNumber < 1 || queueNumber > 3)
        {
            cout << "Invalid queue number." << endl;
            return;
        }

        if (queues[queueNumber - 1].isEmpty())
        {
            cout << "Queue " << queueNumber << " is empty." << endl;
        }
        else
        {
            Student nextStudent = queues[queueNumber - 1].peek();
            cout << "Next student in Queue " << queueNumber << ": " << nextStudent.name << " with merit " << nextStudent.merit << endl;
        }
    }
};

int main()
{
    AdmissionSystem admissionSystem;
    int choice;

    do
    {
        cout << "\nMenu:\n";
        cout << "1. Add Student to Queue\n";
        cout << "2. Process Admissions\n";
        cout << "3. Check Queue Status\n";
        cout << "4. See who is next\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            admissionSystem.addStudentToQueue();
            break;

        case 2:
            admissionSystem.processAdmissions();
            break;

        case 3:
            admissionSystem.checkQueueStatus();
            break;

        case 4:
            admissionSystem.seeWhoIsNext();
            break;

        case 5:
            cout << "Exiting program.\n";
            break;

        default:
            cout << "Invalid choice. Please enter a valid option.\n";
        }

    } while (choice != 5);

    return 0;
}
