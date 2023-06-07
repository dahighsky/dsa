#include <bits/stdc++.h>
using namespace std;

struct Student
{
    int pnr;
    int marks;
};

class HashTable
{
private:
    int size;
    bool *isOccupied;
    Student *data;

    int hash(int key)
    {
        return key % size;
    }

public:
    HashTable(int s)
    {
        size = s;
        isOccupied = new bool[size];
        data = new Student[size];
        cout << " Constructed" << endl;
        for (int i = 0; i < size; i++)
        {
            isOccupied[i] = false;
        }
    }
    ~HashTable()
    {
        delete isOccupied;
        delete data;
    }

    void insert(Student student)

    {
        int key = student.pnr;
        int index = hash(key);

        if (isOccupied[index])
        {
            if (data[index].pnr == key)
            {
                data[index].marks = student.marks;
                cout << "Student marks updated for PNR " << key << endl;
            }
            else
            {
                int i = hash(index + 1);
                while (i != index)
                {
                    if (!isOccupied[i])
                    {
                        data[i] = student;
                        isOccupied[i] = true;
                        cout << "Student with PNR " << key << " inserted at position " << i << " with collisions" << endl;
                        break;
                    }
                    else
                    {
                        i = hash(++i);
                    }
                }
                if (i == index)
                {
                    cout << "Insert failed, table overflow" << endl;
                }
            }
        }
        else
        {
            data[index] = student;
            isOccupied[index] = true;
            cout << "Student with PNR " << key << " inserted at position " << index << endl;
        }
    }
    void display()
    {
        cout << "---------------------------------------------"
             << endl;
        for (int i = 0; i < size; i++)
        {
            cout << "| " << i << ". | ";
            if (!isOccupied[i])
            {
                cout << "\t Empty \t\t | \t Empty"
                     << " \t \0 "
                     << " \0 "
                     << " \0 "
                     << " |" << endl;
            }
            else
            {
                cout << "\t PNR = " << data[i].pnr << "\t |\t Marks = " << data[i].marks << " |" << endl;
            }
        }
        cout << "---------------------------------------------" << endl;
    }
    int search(int key)
    {
        // cout << key << endl;
        int index = hash(key);
        if (!isOccupied[index])
        {
            cout << "The requested Student PNR " << key << " does not exist in the table" << endl;
            return -1;
        }

        if (data[index].pnr == key)
        {
            cout << "Student with PNR " << key << " found at index " << index << endl;
            return index;
        }

        int i = hash(index + 1);
        while (i != index)
        {
            if (data[i].pnr == key)
            {
                cout << "Student with PNR " << key << " found at index " << i << endl;
                return i;
            }
            else
            {
                i = hash(++i);
            }
        }
        cout << "The requested Student PNR " << key << " does not exist in the table" << endl;
        return -1;
    }

    void remove(int key)
    {
        int index = search(key);
        if (index != -1)
        {
            data[index] = {0, 0};
            isOccupied[index] = false;
            cout << "Student with PNR " << key << " deleted from the table" << endl;
        }
    }
};

int main()
{
    int size = 10;
    // cout << "Please enter the size of the hash table : ";
    // cin >> size;

    HashTable hashTable(size);
    Student students[] = {
        {3211, 72},
        {3233, 56},
        {3220, 78},
        {3288, 62},
        {3279, 55},
        {3298, 81},
        {3242, 71},
        {3268, 69},
        {3266, 66},
        {3222, 88}};
    int numStudents = sizeof(students) / sizeof(students[0]);

    for (int i = 0; i < numStudents; i++)
    {
        hashTable.insert(students[i]);
    }

    cout << "Table : \n"
         << endl;
    hashTable.display();

    hashTable.remove(3242);
    hashTable.remove(3220);
    hashTable.remove(3268);

    cout << "\nTable after delteting 3242, 3220, 3268: "
         << endl;
    hashTable.display();
}
