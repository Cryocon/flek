# Note that this is NOT a relocatable package
%define ver       0.1
%define rel       1
%define prefix    /usr
%define buildroot /tmp/build

Summary: Flek core libraries.
Name: flek
Version: %ver
Release: %rel
Copyright: LGPL
Group: X11/Libraries
Source: flek-0.1.tar.gz
#http://download.sourceforge.net/flek/flek-%{ver}.tar.gz
BuildRoot: %{buildroot}/flek-root
Packager: James Dean Palmer <james@tiger-marmalade.com>
URL: http://flek.sourceforge.net/
Prereq: /sbin/install-info
Docdir: %{prefix}/doc

%description
Core library required for Flek.  The core library includes support
for primitive classes like Vectors, Matrices, Quaternions, File IO, 
and more.

%package devel
Summary: includes, etc to develop Flek applications.
Group: X11/Libraries
Requires: flek

%description devel
Core library required for Flek.  Developer stuff.

%prep
mkdir /tmp/build
%setup
%build

./configure --prefix=%{buildroot}/%{prefix}
cd src
make flek-core

%install
cd src
make flek-core-install

%clean
rm -rf $RPM_BUILD_ROOT

%post -p /sbin/ldconfig

%postun -p /sbin/ldconfig

%files
%defattr(-, root, root)
%doc AUTHORS Changelog README INSTALL
%{prefix}/lib/libflek_core.a
%{prefix}/bin/flek-config

%files devel -f src/flek_core_h.list
%defattr(-, root, root)

%changelog
* Sat Apr 15 2000 James Dean Palmer <james@tiger-marmalade.com>

- First try at RPM
