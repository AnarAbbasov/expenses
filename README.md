# 💸 Expenses — Terminal-Based Expense Tracker (C + ncurses + MySQL)

**Expenses** is a lightweight, terminal‑based expense tracking application written entirely in **C**.  
It provides a clean ncurses‑powered text UI and integrates with a **MySQL database** to help you track spending, savings, and categories like gas, groceries, utilities, and more.

---

## ✨ Features

- 🖥️ **Text‑based GUI** using **ncurses**
- 🗄️ **MySQL database integration**
- ⚙️ **Stored procedures** for efficient data operations
- 📊 Track expenses by category
- 💾 Persistent storage on a remote Linux server
- 🚀 Fast, minimal, and written in pure C

---

## 📦 Installation

### 1️⃣ Install prerequisites

```bash
make install
2️⃣ Compile the project
bash
make
3️⃣ Run the program
bash
make run
🗄️ MySQL Database Configuration
The MySQL database runs on a Linux server named kubernetes, located in your garage and running RHEL 9.

Server IP: 192.168.1.110

These values are configured via environment variables inside the Makefile.

Environment variables used:
bash
export DB_SERVER=192.168.1.110
export DBUSER=username
export PASSWORD=password
Make sure these are set before running the application.

📁 Project Structure
Code
Expenses/
├── src/
│   ├── main.c
│   ├── ui.c
│   ├── db.c
│   └── ...
├── include/
│   ├── ui.h
│   ├── db.h
│   └── ...
├── sql/
│   └── stored_procedures.sql
├── Makefile
└── README.md
🛠️ Technologies Used
C programming

ncurses

MySQL

Stored procedures

Linux (RHEL9)

Makefile automation

🚀 Future Enhancements
CSV export

ASCII‑based charts

Budget alerts

Category analytics

Dockerized MySQL instance

👤 Author
Anar Abbasov  
📧 anar_abbasov@hotmail.com
🔧 Embedded Systems • Linux C • Python/Django • Automation


Just tell me and I’ll shape it exactly how you want.
