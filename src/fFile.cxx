#include <Flek/fFile.h>
#include <Fl/filename.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h> // realpath
#include <stdio.h> // tmpnam

uchar fFile::VFS = 0;
fXmlDocument fFile::VfsTable;
fXmlDocument fFile::VfsHandlers;

void LoToHi (ulong *buffer, int len)
{
//  return;
  char* cbuffer = (char*)buffer;
  register ulong  value;
  for (register int i=0; i<len; i++, cbuffer+=4)
    {
      value = buffer[i];
      cbuffer[0] = ((value >> 24) & 0xff);
      cbuffer[1] = ((value >> 16) & 0xff);
      cbuffer[2] = ((value >> 8) & 0xff);
      cbuffer[3] = ((value & 0xff));
    }
}

char* fFile::expand (char *filename)
{
  /*
  fXmlNode MountPoint;
  fXmlNode Handler;
  char expanded[256];
  char *err = realpath (filename, expanded);

  if (!err)
    return 0;

  if (!UseVfs) 
    return strdup (expanded);

  // Check for Vfs support
  if ((VfsTable.valid ()) 
      && (VfsTable.children().valid())
      && (VfsTable.children().children().valid())
      && (VfsHandlers.valid ())
      && (VfsHandlers.children().valid())
      && (VfsHandlers.children().children().valid()))
    {
      MountPoint = VfsTable.children().children();
      Handler    = VfsHandlers.children().children();
    }
  else 
    return strdup (expanded);
  
  while (MountPoint.valid ())
    {
      printf ("valid mountpoint.\n");
      char *mount;
      mount = MountPoint.property ("mount");
      if (mount)
	{
	  printf ("expanded name=\"%s\", strlen=%d\n", expanded, strlen(expanded));
	  printf ("checking mount=\"%s\", strlen=%d\n", mount, strlen(mount));
	  if (strlen(mount) <= strlen (expanded))
	    {
	      printf ("size okay\n");
	      if (!strncmp (mount, expanded, strlen(mount)))
		{
		  char ForeignFileName[256];
		  char *uri = MountPoint.property ("uri");
		  char *type = MountPoint.property ("type");
		  char *username = MountPoint.property ("username");
		  char *password = MountPoint.property ("password");

		  strncpy (ForeignFileName, 
			  strlen(mount)+expanded, 
			  strlen(expanded) - strlen(mount));

		  char *handler=0;
		  while (Handler.valid ())
		  {
		    char *htype;
		    htype = MountPoint.property ("type");
		    if (!strcmp (htype, type))
		      {
			handler = MountPoint.property ("get-handler");
			free (htype);
			break;
		      }
		    if (htype) free (htype);
		    Handler = Handler.next ();
		  }

		  tmpname (expanded);

		  // Get the file and put it in "expanded".
		  // getVirtualFile (handler, uri, ForeignFileName, expanded, username, password);

		  if (handler) free (handler);
		  if (type) free (type);
		  if (username) free (username);
		  if (password) free (password);

		  return strdup (expanded);
		}
	    }
	  free (mount);
	}
      MountPoint = MountPoint.next ();
    }

  printf ("filename=%s\n", expanded);
  return strdup (expanded);
   */
}

void fFile::open (char *filename, fFileMode mode)
{
  char* m;
  //if (UseVfs && (!VFS))
  //initializeVFS ();

  switch (mode) {
   case fFileNull:
    m = "";
    break;
   case fFileRead:
    m = "r";
    break;
   case fFileReadPlus:
    m = "r+";
    break;
   case fFileWrite:
    m = "w";
    break;
   case fFileWritePlus:
    m = "w+";
    break;
   case fFileAppend:
    m = "a";
    break;
   case fFileAppendPlus:
    m = "a+";
    break;
  }
  
  //realfilename = expand (filename);

  //Fd = fopen (realfilename, mode);
  Fd = fopen (filename, m);
  
  if (!Fd)
    Error = 1;
  else
    Error = 0;
}

/* NOT IN USE ...
char* VFSHandler::expand (char* command, char* uri, char* user, char* pass)
    {
      char rval[256];
      char *e = rval;
      char *end = command + strlen (command);

      fXmlNode handlers = VfsHandlers.children ();

      for (char *a=command; a<=end; e++, a++) 
	{
	  if (*a == '$')
	    {
	      char *var;
	      char *sub;

	      // Substitute username
	      var = "username";
	      sub = user;

	      if ((end - a) >= (unsigned char)strlen (var))
		if (!strncmp (a, var, strlen (var)))
		  {
		    strncpy (e, sub, strlen (sub));
		    e += strlen (var);
		    a += strlen (var);
		    continue;
		  }

	      // Substitute password
	      var = "password";
	      sub = pass;

	      if ((end-a) >= (unsigned char)strlen (var))
		if (!strncmp (a, var, strlen (var)))
		  {
		    strncpy (e, sub, strlen (sub));
		    e += strlen (var);
		    a += strlen (var);
		    continue;
		  }

	      // Substitute password
	      var = "uri";
	      sub = uri;

	      if ((end-a) >= (unsigned char)strlen (var))
		if (!strncmp (a, var, strlen (var)))
		  {
		    strncpy (e, sub, strlen (sub));
		    e += strlen (var);
		    a += strlen (var);
		    continue;
		  }
	      
	    }
	  else
	    *e = *a;
	}

      *e = 0;
      return strdup (rval);

    }

*/
