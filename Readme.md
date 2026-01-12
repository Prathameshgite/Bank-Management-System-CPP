      🏦 Bank Management System

A menu-driven Bank Management System implemented in C++, designed to demonstrate core programming concepts such as Object-Oriented Programming (OOP), file handling, and robust input validation.

This application allows users to create bank accounts, store them persistently using files, and display all saved accounts through a console-based interface.

✨ Features :

Create bank accounts

Persistent data storage using binary file handling

Display all stored accounts

Menu-driven console interface

Strong input validation to prevent crashes and infinite loops

Clean and beginner-friendly code structure

🛠️ Technologies & Concepts Used :

C++

Object-Oriented Programming (OOP)

Classes and Objects

File Handling (fstream)

Binary Files

Input Validation (cin.clear(), cin.ignore())

Menu-driven programs

Git & GitHub

📂 Project Structure :

BMS/
├── main.cpp
├── README.md
└── .gitignore

Generated files such as .exe and .dat are excluded using .gitignore

▶️ How to Compile and Run

Compile the program using

g++ main.cpp -o bank -mconsole

Run the program:

./bank

On Windows PowerShell:

.\bank

🧪 Sample Menu :

===== BANK MANAGEMENT SYSTEM =====

Create Account

Display All Accounts

Exit

🚀 Future Enhancements :

Search account by account number

Deposit and withdraw functionality

Delete account support

Split code into header (.h) and source (.cpp) files

Authentication using PIN

👤 Author :
Prathamesh Gite

📌 Note :

Binary files depend on the exact class structure.
If class members are modified, previously created .dat files should be deleted to avoid corrupted reads.

✅ To add and push this README to GitHub

Run the following commands in your project folder:

git add README.md
git commit -m "Add professional README"
git push
