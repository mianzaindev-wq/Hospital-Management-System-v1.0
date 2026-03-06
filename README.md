# Hospital Management System v1.0

🏥 **Hospital Management System** (C++ Console Application)

A terminal‑based hospital management prototype designed with clean architecture, robust validation, and a modular folder layout. The code is suitable for educational use or as a starting point for a larger system.

---

## ✨ Features
- **Multi‑role login** – Admin, Doctor, Patient, Receptionist
- **Interactive dashboards** with clear menus and colourless terminal UI
- **Input validation** for numbers, emails, dates, times, passwords, phones
- **Exception‑safe logic** using custom `HmsException`
- **Appointment scheduling** with conflict detection
- **Medical record entry and retrieval**
- **Billing and room assignment workflows**
- **User & staff management** (add/remove, profile updates)
- **Improved internal design** – `std::unordered_map`, `unique_ptr`, namespace `hms`

## 🏗️ Updated Project Structure
```
/include/hms/          # public headers
    BaseInterface.h
    DataControl.h
    DataModels.h
    InputTools.h
    Roles.h
    AccountGenerator.h
    EngineLoader.h
    Exceptions.h
/src/
    main.cpp           # application entrypoint
    utils/
        InputTools.cpp
    models/
        BaseInterface.cpp
        Roles.cpp
    controllers/
        DataControl.cpp
        AccountGenerator.cpp
        EngineLoader.cpp
```
*Legacy `Module*.h` files remain for reference but are no longer used.*

## 🚀 Building & Running
Use a C++17 (or later) compatible compiler. From the workspace root:

```sh
# compile all sources, adjust path to compiler if necessary
g++ -std=c++17 -Iinclude src/**/*.cpp -o hospital_system.exe
```

Once built you can start the application in a new terminal window by invoking the helper batch file:

```sh
# on Windows (PowerShell or cmd)
./run.bat
```

New users with the **Patient** role can also create their own accounts directly from the **main menu** (option 2). Only the seeded admin account may add doctors or receptionists from the admin dashboard.

or manually with `start`:

```sh
start "Hospital Management System" "hospital_system.exe"
```

No external dependencies are required; the program is pure standard‑library.

## 🧪 Default Credentials (seeded on startup)
| Role         | Email                 | Password  |
|--------------|-----------------------|-----------|
| Admin        | admin@hospital.com    | admin123  |
| Doctor       | zarak@hospital.com    | doc123    |
| Receptionist | shabih@hospital.com   | rec123    |
| Patient      | adan@hospital.com     | adan123   |

(you can create additional accounts through the administration dashboard)

## 🛠️ Technologies & Patterns
- **C++17**, standard library only
- Object‑oriented design with polymorphic dashboards
- Singleton for central state (`DataControl`)
- Factory‑like helpers for user creation
- Thorough input validation and user feedback

## 🔧 Future Ideas
- Persistence layer (files/DB)
- Networked client/server or GUI front‑end
- Role permissions and audit logging
- Reporting and export functionality

## 📄 License
Educational/demo code. Feel free to read, modify, and learn.
#
