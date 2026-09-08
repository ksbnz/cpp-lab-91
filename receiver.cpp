#include <iostream>
using namespace std;

int main() {
    int n, i = 0, j = 0, count = 0;
    int a[100], b[100];

    cout << "Enter stuffed frame length: ";
    cin >> n;

    cout << "Enter the stuffed frame: ";
    for (i = 0; i < n; i++) {
        cin >> a[i];
    }

    i = 0;
    j = 0;
    count = 0;

    while (i < n) {
        b[j] = a[i];

        if (a[i] == 1)
            count++;
        else
            count = 0;

        if (count == 5) {
            i++;
            count = 0;
        }

        i++;
        j++;
    }

    cout << "Frame after bit de-stuffing: ";

    for (i = 0; i < j; i++) {
        cout << b[i];
    }

    return 0;
}