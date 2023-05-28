/*
Title: Write Python/C++ program to implement linear probing without replacement collision 
handling techniques in hashing. 
Problem Statement: Consider the student database of N students and their marks. Make use 
of a hash table implementation to quickly insert and lookup students PNR(key) and marks. 
Data: {(3211, 72), (3233, 56), (3220, 78), (3288, 62), (3279, 55), (3298, 81), (3244, 71), (3268, 
69), (3266, 66), (3222, 88)} Size of Hash Table: 10 Hash Function: (key % size) 
Implement following operations. 
1. Quick Insert (linear probing with chaining without replacement) 
2. Delete 
3. Lookup/ Search 
*/

#include <iostream>
using namespace std;

const int SIZE = 10;

struct Student {
    int pnr;
    int marks;
};

class HashTable {
private:
    Student data[SIZE];
    bool isOccupied[SIZE];

public:
    HashTable() {
        for (int i = 0; i < SIZE; i++) {
            isOccupied[i] = false;
        }
    }

    int hashFunction(int key) {
        return key % SIZE;
    }

    void insert(Student student) {
        int key = student.pnr;
        int index = hashFunction(key);

        while (isOccupied[index]) {
            index = (index + 1) % SIZE;
        }

        data[index] = student;
        isOccupied[index] = true;
    }

    void remove(int pnr) {
        int index = searchIndex(pnr);
        if (index != -1) {
            isOccupied[index] = false;
            cout << "Student with PNR " << pnr << " removed from the hash table." << endl;
        } else {
            cout << "Student with PNR " << pnr << " not found in the hash table." << endl;
        }
    }

    int searchIndex(int pnr) {
        int key = pnr;
        int index = hashFunction(key);

        while (isOccupied[index]) {
            if (data[index].pnr == pnr) {
                return index;
            }
            index = (index + 1) % SIZE;
        }

        return -1; // Student not found
    }

    void search(int pnr) {
        int index = searchIndex(pnr);
        if (index != -1) {
            cout << "Student with PNR " << pnr << " found. Marks: " << data[index].marks << endl;
        } else {
            cout << "Student with PNR " << pnr << " not found in the hash table." << endl;
        }
    }

    void display() {
        cout << "Hash Table:" << endl;
        for (int i = 0; i < SIZE; i++) {
            if (isOccupied[i]) {
                cout << "Index " << i << ": PNR = " << data[i].pnr << ", Marks = " << data[i].marks << endl;
            } else {
                cout << "Index " << i << ": Empty" << endl;
            }
        }
    }
};

int main() {
    HashTable hashTable;

    Student students[] = {
        {3211, 72},
        {3233, 56},
        {3220, 78},
        {3288, 62},
        {3279, 55},
        {3298, 81},
        {3244, 71},
        {3268, 69},
        {3266, 66},
        {3222, 88}
    };

    int numStudents = sizeof(students) / sizeof(students[0]);

    for (int i = 0; i < numStudents; i++) {
        hashTable.insert(students[i]);
    }

    cout << "After inserting students:" << endl;
    hashTable.display();

    cout << endl;

    int pnrToDelete = 3279;
    hashTable.remove(pnrToDelete);

    cout << endl;

    cout << "After removing student with PNR " << pnrToDelete << ":" << endl;
    hashTable.display();

    cout << endl;

    int pnrToSearch = 3268;
    hashTable.search(pnrToSearch);

    return 0;
}
