#
# Top-level makefile for the Fast Light Environment Kit (FLEK).
#
# Copyright 1999 by James Dean Palmer and others.
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Library General Public
# License as published by the Free Software Foundation; either
# version 2 of the License, or (at your option) any later version.
#
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Library General Public License for more details.
#
# You should have received a copy of the GNU Library General Public
# License along with this library; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
# USA.
#
# Please report all bugs and problems to "james@tiger-marmalade.com".
#

SHELL=/bin/sh

SUBDIRS	=	src test docs

# Does this require GNU make?
DIRS	=	$(SUBDIRS) `if [ ! "$(OSTYPE)" = "cygwin32" ]; then echo $(PLUGINS); fi`

all: makeinclude
	@for dir in $(DIRS); do\
		echo "=== making $$dir ===";\
		if test ! -f $$dir/makedepend; then\
			touch $$dir/makedepend;\
		fi;\
		(cd $$dir;$(MAKE));\
	done

install: makeinclude
	@for dir in $(DIRS); do\
		echo "=== installing $$dir ===";\
		if test ! -f $$dir/makedepend; then\
			touch $$dir/makedepend;\
		fi;\
		(cd $$dir;$(MAKE) install);\
	done

depend: makeinclude
	@for dir in $(DIRS); do\
		echo "=== making dependencies in $$dir ===";\
		if test ! -f $$dir/makedepend; then\
			touch $$dir/makedepend;\
		fi;\
		(cd $$dir;$(MAKE) depend);\
	done

clean:
	-@ rm -f core config.cache *.o *.bck lib/*
	@for dir in $(DIRS); do\
		echo "=== cleaning $$dir ===";\
		(cd $$dir;$(MAKE) clean);\
	done

distclean: clean
	rm -f config.log config.status makeinclude

makeinclude: configure makeinclude.in
	./configure

configure: configure.in
	autoconf

rpm:
	cd src; $(MAKE) list-headers; cd ..
	cd ..; rm -rf /tmp/flek-0.1 /tmp/flek-0.1.tar.gz; cp -R ./flek /tmp/flek-0.1
	cd /tmp; cp ./flek-0.1/flek.spec ./flek.spec; tar cv flek-0.1 > flek-0.1.tar; \
	  gzip flek-0.1.tar; cp flek-0.1.tar.gz /usr/src/RPM/SOURCES/; \
	  rpm -ba ./flek.spec

#
# End of "$Id: Makefile,v 1.3 2000/04/15 20:04:53 jamespalmer Exp $".
#
