# -*- sh -*-
# Note that this is NOT a relocatable package
%define ver       1.0.7
%define rel       1
%define prefix    /usr
%define buildroot /tmp/build

Summary: Fast Light Tool Kit
Name: fltk
Version: %ver
Release: %rel
Copyright: LGPL
Group: Development/Libraries
BuildRoot: %{buildroot}/flek-root
Source: ftp://ftp.fltk.org/pub/fltk/1.0.7/fltk-1.0.7.tar.gz
URL: http://www.fltk.org
Packager: James Dean Palmer <james@tiger-marmalade.com>
Docdir: %{prefix}/doc

%description
The Fast Light Tool Kit ("FLTK", pronounced "fulltick") is a LGPL'd
C++ graphical user interface toolkit for X (UNIX(r)), OpenGL(r),
and Microsoft(r) Windows(r) NT 4.0, 95, or 98. It was originally
developed by Bill Spitzak and is currently maintained by a small 
group of developers across the world with a central repository in 
the US.

%changelog
* Sat Apr 15 2000 James Dean Palmer <james@tiger-marmalade.com>

  - First RPM for fltk
  
### Package: devel

%package devel
Summary: includes, etc to develop Fltk applications.
Group: Development/Libraries
Requires: fltk

%description devel
The fltk-devel package includes the libraries and include files that 
you will need to develop Fltk applications.

You should install the fltk-devel package if you would like to develop 
Fltk applications.

### Package: docs

%package docs
Summary: The Fltk documentation.
Group: Documentation

%description docs
This package contains Fltk developer documentation.

%prep
%setup

%build
./configure --enable-shared --prefix=$RPM_BUILD_ROOT/%{prefix}
cd src
make
cd ../fluid
make
cd ..

%install
rm -rf $RPM_BUILD_ROOT
mkdir $RPM_BUILD_ROOT
make install
  
%clean
rm -rf $RPM_BUILD_ROOT

%post -p /sbin/ldconfig

%postun -p /sbin/ldconfig

%files
%defattr(-, root, root)
%{prefix}/lib/libfltk.a
%{prefix}/lib/libfltk.so
%{prefix}/lib/libfltk.so.1
%{prefix}/bin/fluid

%files docs
%doc documentation/*
%defattr(-, root, root)

%files devel
%defattr(-, root, root)
%{prefix}/include/FL
%{prefix}/include/Fl

