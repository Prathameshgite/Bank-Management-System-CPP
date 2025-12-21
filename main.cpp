#include <iostream>
#include <fstream>
#include <windows.h>

using namespace std;

void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void clearInput() {
    cin.clear();
    cin.ignore(10000, '\n');
}

class Bank {
private:
    long long accNo;
    char name[50];
    double balance;

public:
    void createAccount() {
        cout << "\nEnter Account Number: ";
        while (!(cin >> accNo)) {
            cout << "Invalid number! Try again: ";
            clearInput();
        }

        clearInput();

        cout << "Enter Name: ";
        cin.getline(name, 50);

        cout << "Enter Initial Balance: ";
        while (!(cin >> balance)) {
            cout << "Invalid amount! Try again: ";
            clearInput();
        }

        setColor(10);
        cout << "\nAccount Created Successfully!\n";
        setColor(7);
    }

    void displayAccount() const {
        cout << "\nAccount Number: " << accNo
             << "\nName: " << name
             << "\nBalance: ₹" << balance << endl;
    }

    void saveToFile() {
        ofstream out("bank.dat", ios::binary | ios::app);
        out.write((char*)this, sizeof(*this));
        out.close();
    }

    long long getAccNo() const {
        return accNo;
    }

    void deposit(double amount) {
        balance += amount;
    }

    void withdraw(double amount) {
        balance -= amount;
    }

    static void displayAllAccounts() {
        Bank b;
        ifstream in("bank.dat", ios::binary);

        if (!in) {
            cout << "\nNo accounts found.\n";
            return;
        }

        cout << "\n----- ALL ACCOUNTS -----\n";
        while (in.read((char*)&b, sizeof(b))) {
            b.displayAccount();
            cout << "-----------------------\n";
        }
        in.close();
    }

    static void searchAccount(long long searchNo) {
        Bank b;
        ifstream in("bank.dat", ios::binary);

        bool found = false;

        while (in.read((char*)&b, sizeof(b))) {
            if (b.getAccNo() == searchNo) {
                setColor(10);
                cout << "\nAccount Found!\n";
                setColor(7);
                b.displayAccount();
                found = true;
                break;
            }
        }

        in.close();

        if (!found) {
            setColor(12);
            cout << "\nAccount not found.\n";
            setColor(7);
        }
    }

    static void depositMoney(long long searchNo) {
        Bank b;
        ifstream in("bank.dat", ios::binary);
        ofstream out("temp.dat", ios::binary);

        if (!in) {
            cout << "\nNo account file found.\n";
            return;
        }

        bool found = false;
        double amount;

        while (in.read((char*)&b, sizeof(b))) {
            if (b.getAccNo() == searchNo) {
                cout << "Enter amount to deposit: ";
                while (!(cin >> amount) || amount <= 0) {
                    cout << "Invalid amount! Enter again: ";
                    clearInput();
                }
                b.deposit(amount);
                setColor(10);
                cout << "\nAmount deposited successfully!\n";
                setColor(7);
                found = true;
            }
            out.write((char*)&b, sizeof(b));
        }

        in.close();
        out.close();

        remove("bank.dat");
        rename("temp.dat", "bank.dat");

        if (!found) {
            setColor(12);
            cout << "\nAccount not found.\n";
            setColor(7);
        }
    }

    static void withdrawMoney(long long searchNo) {
        Bank b;
        ifstream in("bank.dat", ios::binary);
        ofstream out("temp.dat", ios::binary);

        if (!in) {
            cout << "\nNo account file found.\n";
            return;
        }

        bool found = false;
        double amount;

        while (in.read((char*)&b, sizeof(b))) {
            if (b.getAccNo() == searchNo) {
                cout << "Enter amount to withdraw: ";
                while (!(cin >> amount) || amount <= 0) {
                    cout << "Invalid amount! Enter again: ";
                    clearInput();
                }

                if (b.balance < amount) {
                    setColor(12);
                    cout << "\nInsufficient balance!\n";
                    setColor(7);
                } else {
                    b.withdraw(amount);
                    setColor(10);
                    cout << "\nAmount withdrawn successfully!\n";
                    setColor(7);
                }
                found = true;
            }
            out.write((char*)&b, sizeof(b));
        }

        in.close();
        out.close();

        remove("bank.dat");
        rename("temp.dat", "bank.dat");

        if (!found) {
            setColor(12);
            cout << "\nAccount not found.\n";
            setColor(7);
        }
    }
};

int main() {
    int choice = 0;

    while (true) {
        setColor(11);
        cout << "\n===== BANK MANAGEMENT SYSTEM =====\n";
        setColor(7);

        cout << "1. Create Account\n";
        cout << "2. Display All Accounts\n";
        cout << "3. Search Account\n";
        cout << "4. Deposit Money\n";
        cout << "5. Withdraw Money\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";

        if (!(cin >> choice)) {
            setColor(12);
            cout << "\nInvalid input! Enter number only.\n";
            setColor(7);
            clearInput();
            continue;
        }

        if (choice == 1) {
            Bank b;
            b.createAccount();
            b.saveToFile();
        }
        else if (choice == 2) {
            Bank::displayAllAccounts();
        }
        else if (choice == 3) {
            long long acc;
            cout << "\nEnter account number to search: ";
            while (!(cin >> acc)) {
                cout << "Invalid input! Try again: ";
                clearInput();
            }
            Bank::searchAccount(acc);
        }
        else if (choice == 4) {
            long long acc;
            cout << "\nEnter account number: ";
            while (!(cin >> acc)) {
                cout << "Invalid input! Try again: ";
                clearInput();
            }
            Bank::depositMoney(acc);
        }
        else if (choice == 5) {
            long long acc;
            cout << "\nEnter account number: ";
            while (!(cin >> acc)) {
                cout << "Invalid input! Try again: ";
                clearInput();
            }
            Bank::withdrawMoney(acc);
        }
        else if (choice == 6) {
            setColor(10);
            cout << "\nThank you for using Bank Management System!\n";
            setColor(7);
            break;
        }
        else {
            setColor(12);
            cout << "\nInvalid choice! Try again.\n";
            setColor(7);
        }
    }

    return 0;
}
