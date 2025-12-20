#include <iostream>
#include <fstream>
using namespace std;

/* ---------- Clear input safely ---------- */
void clearInput() {
    cin.clear();
    cin.ignore(10000, '\n');
}

/* ---------------- Bank Class ---------------- */
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

        clearInput(); // clear newline

        cout << "Enter Name: ";
        cin.getline(name, 50);

        cout << "Enter Initial Balance: ";
        while (!(cin >> balance)) {
            cout << "Invalid amount! Try again: ";
            clearInput();
        }

        cout << "\nAccount Created Successfully!\n";
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
};

/* ---------------- Main ---------------- */
int main() {
    int choice = 0;

    while (true) {
        cout << "\n===== BANK MANAGEMENT SYSTEM =====";
        cout << "\n1. Create Account";
        cout << "\n2. Display All Accounts";
        cout << "\n3. Exit";
        cout << "\nEnter choice: ";

        if (!(cin >> choice)) {
            cout << "\nInvalid input. Enter a number.\n";
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
            cout << "\nExiting program.\n";
            break;
        }
        else {
            cout << "\nInvalid choice.\n";
        }
    }

    return 0;
}
