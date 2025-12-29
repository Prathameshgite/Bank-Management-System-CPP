#include "bank.h"
#include <windows.h>

void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void clearScreen() {
    system("cls");
}

void drawLine(int width) {
    for (int i = 0; i < width; i++) cout << "═";
}

void showMainMenu() {
    clearScreen();
    setColor(11); // Cyan

    cout << "╔";
    drawLine(38);
    cout << "╗\n";

    cout << "║        BANK MANAGEMENT SYSTEM        ║\n";

    cout << "╠";
    drawLine(38);
    cout << "╣\n";

    setColor(7);
    cout << "║ 1. Create Account                    ║\n";
    cout << "║ 2. Display Accounts                  ║\n";
    cout << "║ 3. Deposit Money                     ║\n";
    cout << "║ 4. Withdraw Money (PIN)              ║\n";
    cout << "║ 5. Delete Account (PIN)              ║\n";
    cout << "║ 6. Recycle Bin                       ║\n";
    cout << "║ 7. Restore Account (PIN)             ║\n";
    cout << "║ 8. Mini Statement                    ║\n";
    cout << "║ 9. Exit                              ║\n";

    setColor(11);
    cout << "╚";
    drawLine(38);
    cout << "╝\n";

    setColor(14);
    cout << "Choice: ";
    setColor(7);
}

int main() {
    Bank::cleanExpired();

    int ch;
    long long acc;

    while (true) {
        showMainMenu();

        if (!(cin >> ch)) {
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        if (ch == 1) {
            clearScreen();
            Bank b;
            b.createAccount();
            ofstream out("bank.dat", ios::binary | ios::app);
            out.write((char*)&b, sizeof(b));
            out.close();
        }
        else if (ch == 2) {
            clearScreen();
            Bank::displayAll();
        }
        else if (ch == 3) {
            clearScreen();
            cout << "Account Number: ";
            cin >> acc;
            Bank::depositMoney(acc);
        }
        else if (ch == 4) {
            clearScreen();
            cout << "Account Number: ";
            cin >> acc;
            Bank::withdrawMoney(acc);
        }
        else if (ch == 5) {
            clearScreen();
            cout << "Account Number: ";
            cin >> acc;
            Bank::deleteAccount(acc);
        }
        else if (ch == 6) {
            clearScreen();
            Bank::recycleBin();
        }
        else if (ch == 7) {
            clearScreen();
            cout << "Account Number: ";
            cin >> acc;
            Bank::restoreAccount(acc);
        }
        else if (ch == 8) {
            clearScreen();
            cout << "Account Number: ";
            cin >> acc;
            Bank::showMiniStatement(acc);
        }
        else if (ch == 9) {
            clearScreen();
            setColor(10);
            cout << "\nThank you for using Bank Management System\n";
            setColor(7);
            break;
        }

        cout << "\n\nPress Enter to continue...";
        cin.ignore();
        cin.get();
    }

    return 0;
}
