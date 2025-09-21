Name:           expenses
Version:        0.0
Release:        1%{?dist}
Summary:        Precompiled tool with shared library
License:        Proprietary
BuildArch:      x86_64
Requires: libcurl
Requires: mysql-community-client
Requires: ncurses-libs

%description
This package contains a precompiled binary and shared library.


%install
mkdir -p %{buildroot}
cp -a %{_sourcedir}/* %{buildroot}/





%files
/usr/local/bin/expenses
/usr/lib64/libwindows.so
/usr/lib64/libutils.so 
/usr/lib64/libdb_functions.so


%changelog
* Sun Sep 21 2025 Anar <anar_abbasov@hotmail.com> - 0.0-1
- Initial binary RPM package