# -*- sh -*-
# Note that this is NOT a relocatable package
%define ver       0.1
%define rel       1
%define prefix    /usr
%define buildroot /tmp/build

Summary: Flek core library.
Name: flek
Version: %ver
Release: %rel
Copyright: LGPL
Group: System Environment/Libraries
Source: http://download.sourceforge.net/flek/flek-%{ver}.tar.gz
BuildRoot: %{buildroot}/flek-root
Packager: James Dean Palmer <james@tiger-marmalade.com>
URL: http://flek.sourceforge.net/
Prereq: /sbin/install-info
Docdir: %{prefix}/doc

%description
FLEK (Fast Light Environment Kit) is a powerful set of libraries and
tools to build user-friendly applications.  Flek is similar in purpose 
to Gnome, CDE, KDE, or wxWindows, but Flek is based on the excellent 
Fltk toolkit instead of Gtk or Qt.

flek_core is the base library that all Flek applications require.  It
contains primitive classes like Vectors, Matrices, Quaternions, File IO, 
etc.

### Package: devel

%package devel
Summary: includes, etc to develop Flek applications with libflek_core.
Group: Development/Libraries
Requires: flek

%description devel
The flek-devel package includes the libraries and include files that 
you will need to develop Flek applications.

You should install the flek-devel package if you would like to develop 
Flek applications.

### Pacakge: gl

%package gl
Summary: Flek library for using OpenGL.
Group: System Environment/Libraries
Requires: flek

%description gl
FLEK (Fast Light Environment Kit) is a powerful set of libraries and
tools to build user-friendly applications.  Flek is similar in purpose 
to Gnome, CDE, KDE, or wxWindows, but Flek is based on the excellent 
Fltk toolkit instead of Gtk or Qt.

flek_gl provides functionality based on OpenGL.  This includes c++
wrapper functions that utilize Flek core classes as well as intuitive
user interface controls for working with 3d.

### Pacakge: gl-devel

%package gl-devel
Summary: Includes for developing with libflek_gl.
Group: Development/Libraries
Requires: flek-gl

%description gl-devel
The flek-gl-devel package includes the libraries and include files that 
you will need to develop Flek applications that utilize OpenGL.

You should install the flek-gl-devel package if you would like to develop 
Flek applications that use OpenGL.

### Pacakge: ui

%package ui
Summary: Flek library for applications that use libflek_ui.
Group: System Environment/Libraries
Requires: flek

%description ui
FLEK (Fast Light Environment Kit) is a powerful set of libraries and
tools to build user-friendly applications.  Flek is similar in purpose 
to Gnome, CDE, KDE, or wxWindows, but Flek is based on the excellent 
Fltk toolkit instead of Gtk or Qt.

flek_ui provides additional widgets and functionality not provided 
directly by Fltk.

### Pacakge: ui-devel

%package ui-devel
Summary: Includes for developing applications with libflek_ui.
Group: Development/Libraries
Requires: flek-ui

%description ui-devel
The flek-ui-devel package includes the libraries and include files that 
you will need to develop Flek applications.

You should install the flek-ui-devel package if you would like to develop 
Flek applications that use Flek's widgets.

### Pacakge: xml

%package xml
Summary: Flek library for applications that use libflek_xml.
Group: System Environment/Libraries
Requires: flek

%description xml
FLEK (Fast Light Environment Kit) is a powerful set of libraries and
tools to build user-friendly applications.  Flek is similar in purpose 
to Gnome, CDE, KDE, or wxWindows, but Flek is based on the excellent 
Fltk toolkit instead of Gtk or Qt.

flek_xml provides a c++ wrapper to libxml.

### Pacakge: xml-devel

%package xml-devel
Summary: Includes for developing applications with libflek_xml.
Group: Development/Libraries
Requires: flek-xml

%description xml-devel
The flek-ui-devel package includes the libraries and include files that 
you will need to develop Flek applications.

You should install the flek-xml-devel package if you would like to develop 
Flek applications that use XML.

### Package: devel

%package docs
Summary: Flek developer documentation.
Group: Documentation

%description docs
FLEK (Fast Light Environment Kit) is a powerful set of libraries and
tools to build user-friendly applications.  Flek is similar in purpose 
to Gnome, CDE, KDE, or wxWindows, but Flek is based on the excellent 
Fltk toolkit instead of Gtk or Qt.

This package contains Flek developer documentation.

%prep
%setup


%build
./configure --enable-shared --prefix=$RPM_BUILD_ROOT/%{prefix}
cd src
make flek-core
make flek-ui
make flek-xml
make flek-gl


%install
rm -rf $RPM_BUILD_ROOT
mkdir $RPM_BUILD_ROOT

cd src
make flek-core-install
make flek-ui-install
make flek-gl-install
make flek-xml-install
cd ../docs
make

%clean
rm -rf $RPM_BUILD_ROOT

%post -p /sbin/ldconfig

%postun -p /sbin/ldconfig


## Libraries


## core library:
%files
%defattr(-, root, root)
%doc AUTHORS Changelog README INSTALL
%{prefix}/bin/flek-config
%{prefix}/lib/libflek_core.a
%{prefix}/lib/libflek_core.so.1

## ui library:
%files ui 
%{prefix}/lib/libflek_ui.a
%{prefix}/lib/libflek_ui.so.1

## xml library:
%files xml
%{prefix}/lib/libflek_xml.a
%{prefix}/lib/libflek_xml.so.1

## gl library:
%files gl 
%{prefix}/lib/libflek_gl.a
%{prefix}/lib/libflek_gl.so.1

## Development files:


%files devel -f src/flek_core_h.list
%defattr(-, root, root)

%files ui-devel -f src/flek_ui_h.list
%defattr(-, root, root)

%files xml-devel -f src/flek_xml_h.list
%defattr(-, root, root)

%files gl-devel -f src/flek_gl_h.list
%defattr(-, root, root)

%files docs
%docs docs/*

%changelog
* Sat Apr 15 2000 James Dean Palmer <james@tiger-marmalade.com>

- First try at RPM
