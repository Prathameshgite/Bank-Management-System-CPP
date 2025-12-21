#include "Bank.h"

void Bank::createAccount() {
    cout << "\nEnter Account Number: ";
    while (!(cin >> accNo)) {
        cout << "Invalid input! Try again: ";
        cin.clear();
        cin.ignore(10000, '\n');
    }

    cin.ignore();
    cout << "Enter Name: ";
    cin.getline(name, 50);

    cout << "Enter Initial Balance: ";
    while (!(cin >> balance)) {
        cout << "Invalid amount! Try again: ";
        cin.clear();
        cin.ignore(10000, '\n');
    }

    cout << "Set 4-digit PIN: ";
    while (!(cin >> pin) || pin < 1000 || pin > 9999) {
        cout << "Invalid PIN! Enter 4 digits: ";
        cin.clear();
        cin.ignore(10000, '\n');
    }

    isDeleted = false;
    deletedAt = 0;

    cout << "\nAccount Created Successfully!\n";
}

void Bank::displayAccount() const {
    cout << "\nAccount Number: " << accNo
         << "\nName: " << name
         << "\nBalance: ₹" << balance << endl;
}

long long Bank::getAccNo() const {
    return accNo;
}

bool Bank::authenticate(int enteredPin) const {
    return pin == enteredPin && !isDeleted;
}

void Bank::deposit(double amt) {
    balance += amt;
}

bool Bank::withdraw(double amt) {
    if (balance < amt) return false;
    balance -= amt;
    return true;
}

void Bank::markDeleted() {
    isDeleted = true;
    deletedAt = time(nullptr);
}

void Bank::restore() {
    isDeleted = false;
    deletedAt = 0;
}

void Bank::cleanExpired() {
    Bank b;
    ifstream in("bank.dat", ios::binary);
    ofstream out("temp.dat", ios::binary);

    if (!in) return;

    time_t now = time(nullptr);

    while (in.read((char*)&b, sizeof(b))) {
        if (b.isDeleted && difftime(now, b.deletedAt) > 30 * 24 * 60 * 60)
            continue;
        out.write((char*)&b, sizeof(b));
    }

    in.close();
    out.close();
    remove("bank.dat");
    rename("temp.dat", "bank.dat");
}

bool Bank::verify(long long acc, int enteredPin, Bank &found) {
    ifstream in("bank.dat", ios::binary);
    while (in.read((char*)&found, sizeof(found))) {
        if (found.accNo == acc && found.authenticate(enteredPin)) {
            in.close();
            return true;
        }
    }
    in.close();
    return false;
}

void Bank::saveAll(Bank &updated) {
    Bank b;
    ifstream in("bank.dat", ios::binary);
    ofstream out("temp.dat", ios::binary);

    while (in.read((char*)&b, sizeof(b))) {
        if (b.accNo == updated.accNo)
            out.write((char*)&updated, sizeof(updated));
        else
            out.write((char*)&b, sizeof(b));
    }

    in.close();
    out.close();
    remove("bank.dat");
    rename("temp.dat", "bank.dat");
}

void Bank::displayAll() {
    Bank b;
    ifstream in("bank.dat", ios::binary);
    bool any = false;

    while (in.read((char*)&b, sizeof(b))) {
        if (!b.isDeleted) {
            b.displayAccount();
            cout << "-----------------------\n";
            any = true;
        }
    }

    in.close();
    if (!any) cout << "\nNo active accounts found.\n";
}

void Bank::depositMoney(long long acc) {
    Bank b;
    ifstream in("bank.dat", ios::binary);
    ofstream out("temp.dat", ios::binary);
    bool found = false;
    double amt;

    while (in.read((char*)&b, sizeof(b))) {
        if (b.accNo == acc && !b.isDeleted) {
            cout << "Enter amount: ";
            cin >> amt;
            b.deposit(amt);
            found = true;
        }
        out.write((char*)&b, sizeof(b));
    }

    in.close();
    out.close();
    remove("bank.dat");
    rename("temp.dat", "bank.dat");

    if (!found) cout << "\nAccount not found.\n";
}

void Bank::withdrawMoney(long long acc) {
    int enteredPin;
    cout << "Enter PIN: ";
    cin >> enteredPin;

    Bank b;
    if (!verify(acc, enteredPin, b)) {
        cout << "\nAuthentication failed.\n";
        return;
    }

    double amt;
    cout << "Enter amount: ";
    cin >> amt;

    if (!b.withdraw(amt)) {
        cout << "\nInsufficient balance.\n";
        return;
    }

    saveAll(b);
    cout << "\nWithdrawal successful.\n";
}

void Bank::deleteAccount(long long acc) {
    int enteredPin;
    cout << "Enter PIN: ";
    cin >> enteredPin;

    Bank b;
    if (!verify(acc, enteredPin, b)) {
        cout << "\nAuthentication failed.\n";
        return;
    }

    b.markDeleted();
    saveAll(b);
    cout << "\nAccount moved to Recycle Bin.\n";
}

void Bank::restoreAccount(long long acc) {
    int enteredPin;
    cout << "Enter PIN: ";
    cin >> enteredPin;

    Bank b;
    if (!verify(acc, enteredPin, b)) {
        cout << "\nAuthentication failed.\n";
        return;
    }

    b.restore();
    saveAll(b);
    cout << "\nAccount restored.\n";
}

void Bank::recycleBin() {
    Bank b;
    ifstream in("bank.dat", ios::binary);
    bool any = false;

    while (in.read((char*)&b, sizeof(b))) {
        if (b.isDeleted) {
            cout << "\nAccount Number: " << b.accNo
                 << "\nName: " << b.name << endl;
            any = true;
        }
    }

    in.close();
    if (!any) cout << "\nRecycle Bin empty.\n";
}
