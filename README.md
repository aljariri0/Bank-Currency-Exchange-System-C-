# Bank and Currency Exchange Management System

A comprehensive, console-based enterprise application built in C++ utilizing Object-Oriented Programming (OOP) principles. This system manages banking transactions, user permissions, and currency exchange operations with persistent file-based data storage.

## Features

### Security & User Management
* **Role-Based Access Control:** Custom bitwise permission system granting specific access rights to users (e.g., viewing clients, managing users, accessing transaction logs).
* **Authentication:** Secure login screen with an account lockout mechanism after 3 failed attempts.
* **Encryption:** Integrated simple encryption/decryption for user passwords before storing them in text files.
* **Audit Logging:** System automatically logs all login attempts and bank transfers with timestamps and user details.

### Banking System
* **Client Management:** Add, delete, update, and find client records.
* **Transactions:** Process deposits, withdrawals, and account-to-account transfers.
* **Data Persistence:** All client and transaction data is saved and retrieved dynamically using standard file I/O.

### Currency Exchange
* **Live Calculations:** Convert between dozens of global currencies using USD as a base rate.
* **Currency Management:** Search currencies by country or code, list all available currencies, and dynamically update conversion rates.

### Custom Utility Libraries
* **`clsDate`:** A custom-built date and time manipulation library handling leap years, business days, and calendar generation.
* **`clsString`:** A string manipulation library for formatting, splitting, trimming, and casing strings without relying on external libraries.

## Tech Stack
* **Language:** C++
* **Architecture:** Object-Oriented Programming (Encapsulation, Inheritance, Abstraction)
* **Data Storage:** Flat Text Files (`.txt`) using `fstream` standard library.
* **Libraries used:** Standard Template Library (STL), `<vector>`, `<string>`, `<iomanip>`

## How to Run
1. Clone the repository.
2. Compile the source code using any C++ compiler (e.g., GCC, MSVC).
3. Ensure the text files (`Clients.txt`, `Users.txt`, `Currencies.txt`, etc.) are in the same directory as the executable.
4. Run the program. (Default Admin Login: *[Provide the default username/password here based on your Users.txt]*).
