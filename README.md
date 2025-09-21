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




### How to build RPM

1. Set Up RPM Build Environment
sudo dnf install rpmdevtools rpm-build
rpmdev-setuptree


This creates ~/rpmbuild/{BUILD,RPMS,SOURCES,SPECS,SRPMS}.

2. Place Your Files in SOURCES
Structure your files as they should appear after installation:
~/rpmbuild/SOURCES/
└── payload/
    ├── usr/
    │   └── local/
    │       └── bin/
    │           └── mytool
    └── usr/
        └── lib64/
            └── libmytool.so



3. Create a Minimal .spec File
Inside ~/rpmbuild/SPECS/mypackage.spec:
Name:           mypackage
Version:        1.0
Release:        1%{?dist}
Summary:        Precompiled tool with shared library
License:        Proprietary
BuildArch:      x86_64
Requires:       libc.so.6

%description
This package contains a precompiled binary and shared library.

%prep
# No source prep needed

%build
# No build step needed

%install
mkdir -p %{buildroot}
cp -a %{_sourcedir}/payload/* %{buildroot}/

%files
/usr/local/bin/mytool
/usr/lib64/libmytool.so

%changelog
* Sun Sep 21 2025 Anar <anar@example.com> - 1.0-1
- Initial binary RPM package



4. Build the RPM
rpmbuild -bb ~/rpmbuild/SPECS/mypackage.spec


Your .rpm will appear in ~/rpmbuild/RPMS/x86_64/.

