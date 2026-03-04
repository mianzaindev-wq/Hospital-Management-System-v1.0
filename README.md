# Hospital Management System v1.0

🏥 Hospital Management System (C++ Console Application)
A comprehensive console-based Hospital Management System built in C++ that demonstrates object-oriented programming principles, user role management, and hospital workflow automation.

✨ Features
Multi-role Authentication System

Admin: Full system control

Doctor: Medical records & appointments

Patient: Appointment booking & profile management

Receptionist: Front desk operations

Core Functionalities

Patient registration and profile management

Appointment scheduling with conflict detection

Medical record creation and retrieval

Billing and payment handling

Room assignment management

Staff management (add/remove doctors, receptionists)

Technical Implementation

Object-oriented design with inheritance hierarchy

Singleton pattern for data management

Input validation and error handling

Modular architecture with separate header files

🏗️ Project Structure
text
main.cpp              - Entry point with main menu
Module.h              - Input validation utilities
Module (2).h          - Base interface class
Module (3).h          - Role-specific subclasses
Module (4).h          - Data management (Singleton)
Module (5).h          - Account generator declarations
Module (6).h          - Account generator implementations
🚀 How to Run
Compile all .cpp files together:

bash
g++ -o hospital_system *.cpp
Run the executable:

bash
./hospital_system
🧪 Default Login Credentials
Role	Email	Password
Admin	admin@hospital.com	admin123
Doctor	zarak@hospital.com	doc123
Receptionist	shabih@hospital.com	rec123
Patient	adan@hospital.com	adan123
🛠️ Technologies Used
C++ (Standard 11+)

Object-Oriented Programming

File-based data persistence (arrays)

Console I/O with validation

📌 Key Design Patterns
Singleton for centralized data control

Factory Pattern for user account creation

Inheritance for role-based functionality

Polymorphism for dashboard interfaces

🔧 Future Enhancements
Database integration (SQLite/MySQL)

File persistence for data storage

GUI implementation

Email/SMS notifications

Prescription management

Inventory tracking

📄 License
This project is for educational purposes. Feel free to observe and learn.
#
