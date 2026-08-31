#include <iostream>
#include <fstream>
#include <iomanip>
#include <cctype>

using namespace std;

class Account {
private:
    int accountNumber;
    char name[50];
    double balance;
    char type; // 'C' for Current, 'S' for Savings

public:
    void createAccount() {
        cout << "\nEnter Account Number: ";
        cin >> accountNumber;
        cin.ignore(); // Clear leftover '\n' after reading integer

        cout << "Enter Account Holder Name: ";
        cin.getline(name, 50);

        cout << "Enter Type of Account (S/C): ";
        cin >> type;
        type = toupper(type);

        cout << "Enter Initial Deposit Amount (>= 500 for S, >= 1000 for C): ";
        cin >> balance;
        cin.ignore(); // Clear leftover buffer

        cout << "\nAccount Created Successfully!";
    }

    void showAccount() const {
        cout << "\nAccount No.          : " << accountNumber;
        cout << "\nAccount Holder Name  : " << name;
        cout << "\nType of Account      : " << type;
        cout << "\nBalance Amount       : " << balance;
    }

    void modify() {
        cout << "\nAccount No. : " << accountNumber;
        cout << "\nModify Account Holder Name: ";
        cin.ignore(); // Clear leftover newline before reading line
        cin.getline(name, 50);

        cout << "Modify Type of Account (S/C): ";
        cin >> type;
        type = toupper(type);

        cout << "Modify Balance Amount: ";
        cin >> balance;
        cin.ignore();
    }

    void deposit(double amount) {
        balance += amount;
    }

    void draw(double amount) {
        if (amount > balance) {
            cout << "\nInsufficient balance!";
        } else {
            balance -= amount;
            cout << "\nAmount withdrawn successfully.";
        }
    }

    void report() const {
        cout << setw(10) << accountNumber << setw(20) << name << setw(10) << type << setw(12) << balance << endl;
    }

    int getAccountNumber() const {
        return accountNumber;
    }

    double getBalance() const {
        return balance;
    }

    char getType() const {
        return type;
    }
};

// Function declarations for File Operations
void writeAccount();
void displayDetails(int n);
void modifyAccount(int n);
void deleteAccount(int n);
void displayAll();
void depositWithdraw(int n, int option);

int main() {
    int choice;
    int num;

    do {
        cout << "\n\n====================================";
        cout << "\n     BANK MANAGEMENT SYSTEM";
        cout << "\n====================================";
        cout << "\n1. NEW ACCOUNT";
        cout << "\n2. DEPOSIT AMOUNT";
        cout << "\n3. WITHDRAW AMOUNT";
        cout << "\n4. BALANCE ENQUIRY";
        cout << "\n5. ALL ACCOUNT HOLDER LIST";
        cout << "\n6. CLOSE AN ACCOUNT";
        cout << "\n7. MODIFY AN ACCOUNT";
        cout << "\n8. EXIT";
        cout << "\n====================================";
        cout << "\nSelect Option (1-8): ";
        
        cin >> choice;
        cin.ignore(); // Prevent buffer leakage into subsequent inputs

        switch (choice) {
            case 1:
                writeAccount();
                break;
            case 2:
                cout << "\nEnter The Account No. : "; 
                cin >> num;
                cin.ignore();
                depositWithdraw(num, 1);
                break;
            case 3:
                cout << "\nEnter The Account No. : "; 
                cin >> num;
                cin.ignore();
                depositWithdraw(num, 2);
                break;
            case 4:
                cout << "\nEnter The Account No. : "; 
                cin >> num;
                cin.ignore();
                displayDetails(num);
                break;
            case 5:
                displayAll();
                break;
            case 6:
                cout << "\nEnter The Account No. : "; 
                cin >> num;
                cin.ignore();
                deleteAccount(num);
                break;
            case 7:
                cout << "\nEnter The Account No. : "; 
                cin >> num;
                modifyAccount(num);
                break;
            case 8:
                cout << "\nThank you for using the Bank Management System!";
                break;
            default:
                cout << "\nInvalid choice! Try again.";
        }
    } while (choice != 8);

    return 0;
}

void writeAccount() {
    Account ac;
    ofstream outFile;
    outFile.open("bank_accounts.dat", ios::binary | ios::app);
    ac.createAccount();
    outFile.write(reinterpret_cast<char*>(&ac), sizeof(Account));
    outFile.close();
}

void displayDetails(int n) {
    Account ac;
    bool flag = false;
    ifstream inFile;
    inFile.open("bank_accounts.dat", ios::binary);
    if (!inFile) {
        cout << "\nFile could not be opened! No records exist yet.";
        return;
    }
    while (inFile.read(reinterpret_cast<char*>(&ac), sizeof(Account))) {
        if (ac.getAccountNumber() == n) {
            ac.showAccount();
            flag = true;
        }
    }
    inFile.close();
    if (!flag) {
        cout << "\nAccount number does not exist!";
    }
}

void modifyAccount(int n) {
    bool found = false;
    Account ac;
    fstream File;
    File.open("bank_accounts.dat", ios::binary | ios::in | ios::out);
    if (!File) {
        cout << "\nFile could not be opened! No records exist yet.";
        return;
    }
    while (!File.eof() && !found) {
        File.read(reinterpret_cast<char*>(&ac), sizeof(Account));
        if (ac.getAccountNumber() == n) {
            ac.showAccount();
            cout << "\n\nEnter The New Details of Account:" << endl;
            ac.modify();
            int pos = (-1) * static_cast<int>(sizeof(Account));
            File.seekp(pos, ios::cur);
            File.write(reinterpret_cast<char*>(&ac), sizeof(Account));
            cout << "\nRecord Updated Successfully!";
            found = true;
        }
    }
    File.close();
    if (!found) {
        cout << "\nRecord Not Found!";
    }
}

void deleteAccount(int n) {
    Account ac;
    ifstream inFile;
    ofstream outFile;
    inFile.open("bank_accounts.dat", ios::binary);
    if (!inFile) {
        cout << "\nFile could not be opened! No records exist yet.";
        return;
    }
    outFile.open("Temp.dat", ios::binary);
    inFile.seekg(0, ios::beg);
    while (inFile.read(reinterpret_cast<char*>(&ac), sizeof(Account))) {
        if (ac.getAccountNumber() != n) {
            outFile.write(reinterpret_cast<char*>(&ac), sizeof(Account));
        }
    }
    inFile.close();
    outFile.close();
    remove("bank_accounts.dat");
    rename("Temp.dat", "bank_accounts.dat");
    cout << "\nRecord Deleted Successfully.";
}

void displayAll() {
    Account ac;
    ifstream inFile;
    inFile.open("bank_accounts.dat", ios::binary);
    if (!inFile) {
        cout << "\nFile could not be opened! No records exist yet.";
        return;
    }
    cout << "\n\nACCOUNT HOLDER LIST\n\n";
    cout << "====================================================\n";
    cout << setw(10) << "A/c no." << setw(20) << "NAME" << setw(10) << "Type" << setw(12) << "Balance\n";
    cout << "====================================================\n";
    while (inFile.read(reinterpret_cast<char*>(&ac), sizeof(Account))) {
        ac.report();
    }
    inFile.close();
}

void depositWithdraw(int n, int option) {
    double amt;
    bool found = false;
    Account ac;
    fstream File;
    File.open("bank_accounts.dat", ios::binary | ios::in | ios::out);
    if (!File) {
        cout << "\nFile could not be opened! No records exist yet.";
        return;
    }
    while (!File.eof() && !found) {
        File.read(reinterpret_cast<char*>(&ac), sizeof(Account));
        if (ac.getAccountNumber() == n) {
            ac.showAccount();
            if (option == 1) {
                cout << "\n\nTO DEPOSIT AMOUNT";
                cout << "\nEnter The Amount to be deposited: ";
                cin >> amt;
                cin.ignore();
                ac.deposit(amt);
            }
            if (option == 2) {
                cout << "\n\nTO WITHDRAW AMOUNT";
                cout << "\nEnter The Amount to be withdraw: ";
                cin >> amt;
                cin.ignore();
                ac.draw(amt);
            }
            int pos = (-1) * static_cast<int>(sizeof(Account));
            File.seekp(pos, ios::cur);
            File.write(reinterpret_cast<char*>(&ac), sizeof(Account));
            cout << "\nRecord Updated!";
            found = true;
        }
    }
    File.close();
    if (!found) {
        cout << "\nRecord Not Found!";
    }
}