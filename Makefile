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

SUBDIRS	=	src test

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


#
# End of "$Id: Makefile,v 1.1 2000/01/25 19:40:48 jamespalmer Exp $".
#
