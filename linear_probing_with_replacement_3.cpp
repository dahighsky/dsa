/*
Title: Write Python/C++ program to implement linear probing with replacement collision
handling techniques in hashing.
Problem Statement: Consider the student database of N students and their marks. Make use
of a hash table implementation to quickly insert and lookup students PNR(key) and marks.
Data: {(3211, 72), (3233, 56), (3220, 78), (3288, 62), (3279, 55), (3298, 81), (3244, 71), (3268,
69), (3266, 66), (3222, 88)} Size of Hash Table: 10 Hash Function: (key % size)
Implement following operations.
1. Quick Insert (linear probing with chaining with replacement)
2. Delete
3. Lookup/ Search
*/

#include <iostream>
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
    Student *data;
    bool *isOccupied;

public:
    HashTable(int tableSize)
    {
        size = tableSize;
        data = new Student[size];
        isOccupied = new bool[size];
        for (int i = 0; i < size; i++)
        {
            isOccupied[i] = false;
        }
    }

    ~HashTable()
    {
        delete[] data;
        delete[] isOccupied;
    }

    int hashFunction(int key)
    {
        return key % size;
    }

    void insert(Student student)
    {
        int key = student.pnr;
        int index = hashFunction(key);

        if (isOccupied[index])
        {
            if (data[index].pnr == key)
            {

                data[index] = student;
                cout << "Student with PNR " << key << " updated in the hash table." << endl;
                return;
            }
            else
            {
                Student temp = data[index];
                insert(temp);
            }

            int i = 1;
            while (true)
            {
                int new_index = (index + i) % size;
                if (!isOccupied[new_index])
                {
                    index = new_index;
                    break;
                }
                i++;
            }
        }

        data[index] = student;
        isOccupied[index] = true;
    }

    void remove(int pnr)
    {
        int key = pnr;
        int index = hashFunction(key);

        if (!isOccupied[index])
        {
            cout << "Student with PNR " << pnr << " not found in the hash table." << endl;
            return;
        }

        int i = 0;
        while (true)
        {
            if (data[index].pnr == pnr)
            {
                isOccupied[index] = false;
                cout << "Student with PNR " << pnr << " removed from the hash table." << endl;
                return;
            }
            i++;
            index = (index + i) % size;
            if (!isOccupied[index])
            {
                cout << "Student with PNR " << pnr << " not found in the hash table." << endl;
                return;
            }
        }
    }

    void search(int pnr)
    {
        int key = pnr;
        int index = hashFunction(key);

        if (!isOccupied[index])
        {
            cout << "Student with PNR " << pnr << " not found in the hash table." << endl;
            return;
        }

        int i = 0;
        while (true)
        {
            if (data[index].pnr == pnr)
            {
                cout << "Student with PNR " << pnr << " found. Marks: " << data[index].marks << endl;
                return;
            }
            i++;
            index = (index + i) % size;
            if (!isOccupied[index])
            {
                cout << "Student with PNR " << pnr << " not found in the hash table." << endl;
                return;
            }
        }
    }

    void display()
    {
        cout << "Hash Table:" << endl;
        for (int i = 0; i < size; i++)
        {
            if (isOccupied[i])
            {
                cout << "Index " << i << ": PNR = " << data[i].pnr << ", Marks = " << data[i].marks << endl;
            }
            else
            {
                cout << "Index " << i << ": Empty" << endl;
            }
        }
    }
};

int main()
{
    HashTable hashTable(10);

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

    cout << "After inserting student data:" << endl;
    hashTable.display();

    cout << endl;

    int pnrToDelete = 3268;
    hashTable.remove(pnrToDelete);

    cout << endl;

    cout << "After removing student with PNR " << pnrToDelete << ":" << endl;
    hashTable.display();

    cout << endl;

    int pnrToSearch = 3220;
    hashTable.search(pnrToSearch);

    return 0;
}
