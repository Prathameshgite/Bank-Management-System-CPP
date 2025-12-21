#ifndef BANK_H
#define BANK_H

#include <iostream>
#include <fstream>
#include <ctime>
#include <windows.h>

using namespace std;

class Bank {
private:
    long long accNo;
    char name[50];
    double balance;
    int pin;
    bool isDeleted;
    time_t deletedAt;

public:
    void createAccount();
    void displayAccount() const;

    long long getAccNo() const;

    void deposit(double amt);
    bool withdraw(double amt);

    bool authenticate(int enteredPin) const;

    void markDeleted();
    void restore();

    static void cleanExpired();
    static bool verify(long long acc, int enteredPin, Bank &found);
    static void saveAll(Bank &updated);

    static void displayAll();
    static void depositMoney(long long acc);
    static void withdrawMoney(long long acc);
    static void deleteAccount(long long acc);
    static void restoreAccount(long long acc);
    static void recycleBin();
};

#endif
