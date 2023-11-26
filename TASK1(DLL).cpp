#include <iostream>
using namespace std;

class Date
{
private:
    int day, month, year;

public:
    Date(int d, int m, int y)
    {
        this->day = d;
        this->month = m;
        this->year = y;
    }

    void setdate()
    {
        this->day = 0;
        this->month = 0;
        this->year = 0;
    }

    void setday(int d)
    {
        day = d;
    }

    void setmonth(int m)
    {
        month = m;
    }

    void setyear(int y)
    {
        year = y;
    }

    int getyear()
    {
        return year;
    }

    int getmonth()
    {
        return month;
    }

    int getday()
    {
        return day;
    }
};

class node
{
private:
public:
    int ISBN;
    node *next, *previous;
    string author, title, genra;
    Date P_date;

    node() : P_date(0, 0, 0)
    {
        ISBN = 0000;
        author = " ";
        title = " ";
        genra = " ";
        next = previous = NULL;
    }
};

class library
{
public:
    node *head;
    int length;

    library()
    {
        head = NULL;
    }

    void AddBook()
{
    int isbn, dy, mt, yr;
    string aut, title, genra;
    char ch;
    cout << "Enter Book Title :\n";
    cin >> title;
    cout << "Enter ISBN Number :\n";
    cin >> isbn;
    cout << "Enter Author Name :\n";
    cin >> aut;
    cout << "Enter Book Genra :\n";
    cin >> genra;
    cout << "Enter Publishing Date in DD/MM/YYYY Format :\n";
    cin >> dy >> ch >> mt >> ch >> yr;
    node *temp = new node();
    node *current = head;

    temp->title = title;
    temp->author = aut;
    temp->ISBN = isbn;
    temp->genra = genra;
    Date tdate(dy, mt, yr);
    temp->P_date = tdate;

    if (head == NULL || head->P_date.getyear() > temp->P_date.getyear() ||
        (head->P_date.getyear() == temp->P_date.getyear() && (head->P_date.getmonth() > temp->P_date.getmonth() ||
                                                              (head->P_date.getmonth() == temp->P_date.getmonth() && head->P_date.getday() > temp->P_date.getday()))))
    {
        temp->next = head;
        if (head != NULL)
            head->previous = temp;
        head = temp;
    }
    else
    {
        current = head;
        while (current->next != NULL && (current->next->P_date.getyear() < temp->P_date.getyear() ||
                                         (current->next->P_date.getyear() == temp->P_date.getyear() && (current->next->P_date.getmonth() < temp->P_date.getmonth() ||
                                                                                                        (current->next->P_date.getmonth() == temp->P_date.getmonth() && current->next->P_date.getday() <= temp->P_date.getday())))))
        {
            current = current->next;
        }

        temp->next = current->next;
        if (current->next != NULL)
        current->next->previous = temp;
        temp->previous = current;
        current->next = temp;
    }

    length++;
    return;
}


    void searchByIsbn()
    {
        int isbn;
        cout << "Enter ISBN Number to Search book : ";
        cin >> isbn;
        node *current = head;

        if (head == NULL)
        {
            cout << "Digital Library Is Empty" << endl;
            return;
        }

        while (current->next != NULL)
        {
            if (current->ISBN == isbn)
            {
                cout << "Book Found Named As :" << current->title << " Of Author : " << current->author;
                return;
            }
            current = current->next;
        }
        cout << "Book Not Found With ISBN Number : " << isbn;
        return;
    }

    void Display()
    {
        int i = 1;
        if (head == NULL)
        {
            cout << "Empty Digital Library";
            return;
        }
        node *current = head;
        cout << "\n\n---------------BOOKS DETAILS---------------\n";
        while (current != NULL)
        {
            cout << i << ". " << current->ISBN << " --> " << current->title << " --> " << current->author << " -->" << current->genra << " -->" << current->P_date.getday() << "/" << current->P_date.getmonth() << "/" << current->P_date.getyear() << endl;
            i++;
            current = current->next;
        }
    }

    void FilterByAuthor()
    {
        string auther;
        int i = 1;
        if (head == NULL)
        {
            cout << "Empty Digital Library";
            return;
        }
        node *current = head;
        cout << "Enter Author Name To Filter Books : ";
        cin >> auther;
        while (current->next != NULL)
        {
            if (auther == current->author)
            {
                cout << i << ". " << current->ISBN << " --> " << current->title << " --> " << current->author << " -->" << current->genra << " -->" << current->P_date.getday() << "/" << current->P_date.getmonth() << "/" << current->P_date.getyear() << endl;
                i++;
                current = current->next;
            }
            else
                current = current->next;
        }
        return;
    }

    void RecommendedBooks()
    {
        string BookName;
        cout << "Enter Book Name : " << endl;
        cin >> BookName;
        string gen;
        int i = 1;

        node *current = head;
        while (current->next != NULL)
        {
            if (current->title == BookName)
            {
                gen = current->genra;
                break;
            }
            current = current->next;
        }
        cout << "RECOMMENDED BOOKS ARE " << endl;
        while ((current->next != NULL) && (i < 4))
        {
            if (current->genra == gen)
            {
                cout << i << ". " << current->ISBN << " --> " << current->title << " --> " << current->author << " -->" << current->genra << " -->" << current->P_date.getday() << "/" << current->P_date.getmonth() << "/" << current->P_date.getyear() << endl;
                i++;
            }
            current = current->next;
        }
    }

    void DeleteBook()
    {
        int isbn;

        if (head == NULL)
        {
            cout << "Empty Digital Library!!!";
            return;
        }

        cout << "Enter ISBN To Delete That Book" << endl;
        cin >> isbn;

        node *current = head;
        while (current->next != NULL)
        {
            if (current->ISBN == isbn)
            {
                node *temp = current;
                current->next->previous = current->previous;
                current->previous->next = current->next;
                delete current;
                cout << "DELETED SUCCESSFULLY !!!!" << endl;
                return;
            }
            current = current->next;
        }
        cout << "BOOK With This ISBN Not Found !!!!" << endl;
    }
};

int main()
{
    library myLibrary;
    int choice;

    do
    {
        cout << "\n\n------ MENU ------\n";
        cout << "1. Add a Book\n";
        cout << "2. Search by ISBN\n";
        cout << "3. Display All Books\n";
        cout << "4. Filter by Author\n";
        cout << "5. Recommended Books\n";
        cout << "6. Delete a Book\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            myLibrary.AddBook();
            break;

        case 2:
            myLibrary.searchByIsbn();
            break;

        case 3:
            myLibrary.Display();
            break;

        case 4:
            myLibrary.FilterByAuthor();
            break;

        case 5:
            myLibrary.RecommendedBooks();
            break;

        case 6:
            myLibrary.DeleteBook();
            break;

        case 7:
            cout << "Exiting the program. Goodbye!\n";
            break;

        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 7);

    return 0;
}
