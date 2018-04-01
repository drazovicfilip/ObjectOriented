#include "mainwindow.h"
#include <QApplication>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    int* pointer1 = new int(6);
    int integer1 = 9;
    int* pointer2 = &integer1;
    int* pointer3 = pointer2;

    cout << integer1 << ", " << *pointer1 << ", " << *pointer2 << ", " << *pointer3 << endl;

    *pointer3 += 3;
    cout << integer1 << endl;
    *pointer2 = *pointer1 + *pointer3;
    cout << integer1 << ", " << *pointer1 << ", " << *pointer2 << ", " << *pointer3 << endl;

    delete pointer1;
    pointer1 = new int(1);
    pointer2 = new int(2);
    pointer3 = new int(3);
    cout << *pointer1 * *pointer2 * *pointer3 << endl;
    cout << *pointer1 - *pointer2 + *pointer3 << endl;

    *pointer1 = *pointer3 - *pointer2 - *pointer1;
    *pointer2 = *pointer3 - *pointer2 + *pointer1;
    *pointer3 = *pointer3 + *pointer2 - *pointer1;
    cout << *pointer1 << endl;
    cout << *pointer2 << endl;
    cout << *pointer3 << endl;
    delete pointer1;
    delete pointer2;
    delete pointer3;


    return 0;
}
