# Expenses

## Description
Expenses is a text-based GUI program completely written in C. It helps you enter and track your expenses, allowing you to see how much you've saved and spent on various categories like gas, groceries, etc.

## Features
- Terminal-based GUI using `ncurses`
- MySQL database integration
- Stored procedures for efficient data management

## Installation
To create project prerequisisites
~~~
make install
~~~

To compile the project, run:
~~~
make
~~~

to run project

~~~
make run
~~~


### Mysql DB 
Database is running on linux server "kubernetes" which is in garage and running  rhel9 with IP address 192.168.1.110
this is set by env variables in Makefile

~~~
DB_SERVER=192.168.1.110;export DBUSER=username;export PASSWORD=password
~~~