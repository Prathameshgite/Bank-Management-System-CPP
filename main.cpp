#include "Bank.h"

int main() {
    Bank::cleanExpired();

    int ch;
    long long acc;

    while (true) {
        cout << "\n===== BANK MANAGEMENT SYSTEM =====\n";
        cout << "1. Create Account\n";
        cout << "2. Display Accounts\n";
        cout << "3. Deposit\n";
        cout << "4. Withdraw (PIN)\n";
        cout << "5. Delete Account (PIN)\n";
        cout << "6. Recycle Bin\n";
        cout << "7. Restore Account (PIN)\n";
        cout << "8. Exit\n";
        cout << "Choice: ";

        cin >> ch;

        if (ch == 1) {
            Bank b;
            b.createAccount();
            ofstream out("bank.dat", ios::binary | ios::app);
            out.write((char*)&b, sizeof(b));
            out.close();
        }
        else if (ch == 2) {
            Bank::displayAll();
        }
        else if (ch == 3) {
            cout << "Account Number: ";
            cin >> acc;
            Bank::depositMoney(acc);
        }
        else if (ch == 4) {
            cout << "Account Number: ";
            cin >> acc;
            Bank::withdrawMoney(acc);
        }
        else if (ch == 5) {
            cout << "Account Number: ";
            cin >> acc;
            Bank::deleteAccount(acc);
        }
        else if (ch == 6) {
            Bank::recycleBin();
        }
        else if (ch == 7) {
            cout << "Account Number: ";
            cin >> acc;
            Bank::restoreAccount(acc);
        }
        else if (ch == 8) {
            break;
        }
    }
    return 0;
}
