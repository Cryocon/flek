//
// "$Id: Fl_Dir.H,v 1.1 2000/01/27 15:00:18 jamespalmer Exp $"
//
// Group header file for the Fast Light Tool Kit (FLTK).
//
// Copyright 1998-1999 by the Flek Team.  (See AUTHORS)
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Library General Public
// License as published by the Free Software Foundation; either
// version 2 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Library General Public License for more details.
//
// You should have received a copy of the GNU Library General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
// USA.
//
// Please report all bugs and problems to "fltk-bugs@easysw.com".
//

//  name	- Fl_Dir.H
//  programmer	- C Edwards
//  Incept	- 5/98
//  Description	- Directory management Class
//  		  Traverse directory structure and read contents. with sorting/filtering/tab complete
//  Changes	-  Ver.1.2 speed up callbacks, removed scan_callback may put back in later,removed some NT bugs

#ifndef Fl_Dir_H
#define Fl_Dir_H

#define FL_MAX_PATH     2048       //path length
#define FL_MAX_FILENAME	180        //filename length 255max
#define FL_MAX_DIR      3000       //max directories 4000max
#define TRUE	        1
#define FALSE	        0

enum { //directory file types also includes (MAIN ERRORS & MESSAGES)
	FL_TYPE_NONE      = 0x00,      //also unknown type,needs type call
	FL_TYPE_PARENT    = 0x01,      //is a parent directory
	FL_TYPE_DIR       = 0x02,      //is a directory
	FL_TYPE_FILES	  = 0x04,      //is a raw file
	FL_TYPE_SYMFILE   = 0x08,      //is a symbolic link file
	FL_TYPE_SYMDIR    = 0x10,      //is symbolic directory
	FL_TYPE_HIDDEN    = 0x20,      //is an hidden
	FL_TYPE_EXE       = 0x40,      //is an exe file
	FL_TYPE_SYSTEM    = 0x80,      //is a system file
	FL_TYPE_ERROR     = -1      //error for file exists  (unknown type)
};
enum { // sorting types Options
	FL_SORT_NAME	    = 0,
	FL_SORT_NAME_NOCASE = 1,
	FL_SORT_NAME_REVERSE= 2,
	FL_SORT_NUMERIC	    = 3,
	FL_SORT_TIME	    = 4,
	FL_SORT_SIZE        = 5,
	FL_SORT_NONE	    = 6,
	FL_SORT_DIR         = 7,
	FL_SORT_DEFAULT	    = -1 
};


// used by read and close directory
// all
        #include <string.h>
        #include <stdlib.h>
        #include <ctype.h>
        //#include <stdio.h>
        //#include <errno.h>

#ifdef WIN32
        #include <windows.h>
        //#include <io.h>
        #include <time.h>
        #include <direct.h>
        #define GETCWD      _getcwd
        #define STRCASECMP  _stricmp

#else   // unix and others
        #include <pwd.h>
        #include <unistd.h>
        #include <dirent.h>
        #include <sys/stat.h>
        #include <sys/types.h>
        #define GETCWD     getcwd
        #define STRCASECMP  strcasecmp
#endif

typedef struct Fl_Dir_File
{
    char   name[FL_MAX_FILENAME];
    int    nameLen;                // index to lastchar in name
    int    type;
    long   size;
    time_t time;
    int display;                //the item should be hidded in the GUI from the user (pattern match)
} Fl_Dir_File;

extern char *fl_dir_messages[];
#define DIR_MSG_NONE 9

class Fl_Dir;
typedef void (Dir_Callback)(Fl_Dir *,void *);   //defind new style of callback for Fl_Dir Class
static inline int isdirsep(char c) {return c=='/' || c=='\\' || c==':';}

//common and usfull "c" functions
static int tmpInt=0;   //needed for giving defaults
int  lenSlashPattern(char *ch,int &slash=tmpInt,int &hasPattern=tmpInt,int &prevSlash=tmpInt,int &lastValidSlash=tmpInt,int &lastComma=tmpInt);  //returns len of str,slash,pattern,and prev slash (lastValid slash before pattern)


//// Class Fl_Dir def
class Fl_Dir
{
public:
//#1-Input ,callback when directory changed and needs refresh
    Dir_Callback* dir_callback1_;
    void* dir_user_data1_;
    void  dir_callback1(Dir_Callback* c=NULL, void* p=0) {dir_callback1_=c; dir_user_data1_=p;}
    void  dir_do_callback1()                             {if(dir_callback1_) dir_callback1_(this,dir_user_data1_);}

//#2-Scroll ,callback when directory changed and needs refresh
    Dir_Callback* dir_callback2_;
    void* dir_user_data2_;
    void  dir_callback2(Dir_Callback* c=NULL, void* p=0) {dir_callback2_=c; dir_user_data2_=p;}
    void  dir_do_callback2()                             {if(dir_callback2_) dir_callback2_(this,dir_user_data2_);}

//#2-error ,callback when directory changed and needs refresh
    Dir_Callback* dir_callback_error_;
    void* dir_user_data_error_;
    void  dir_callback_error(Dir_Callback* c=NULL, void* p=0) {dir_callback_error_=c; dir_user_data_error_=p;}
    void  dir_do_callback_error(int n)              {dirMessage=n; if(dir_callback_error_) dir_callback_error_(this,dir_user_data_error_);}

    Fl_Dir_File  *dirFiles[FL_MAX_DIR];        //struct of directory files
    int          dirSortIdx1[FL_MAX_DIR];      //sorted file index    
    int          nDirFiles;                    //totalFiles in array
    char         dirPath[FL_MAX_PATH];         //current dir & starname
    int          dirPathSlash;                 //index to last slash
    int          dirPathSize;                  //length of path string
    int          dirPathPattern;               //length to last pattern 
    int          dirMessage;
    int          dirMallocCount;               //index to last malloc'ed stuct call 
    int          dirListCount;                 //this counts as list is being given
    int          dirScanCount;                 //this counts as scan is being done if=nDirFiles will Stop

    char         filePattern[FL_MAX_FILENAME]; //default pattern (in menu)
    int          fileFilterType;               //type of filter to use
    int          fileSortType;	               //type of sort to apply

    Fl_Dir( char *pathAndFile="", int sortType = FL_SORT_NAME, int filterType = 0 );
   ~Fl_Dir();

 Fl_Dir_File *fileList();                                           //return list of file entries (resets when reached nDirFiles total)
 Fl_Dir_File *fileListReset(){ dirListCount=0; return NULL;}        //reset list to start from 0 again  
 Fl_Dir_File *fileListSet(int num){ dirListCount=num; return NULL;} //set the list to a number(ie..tracking progress)
 Fl_Dir_File *fileInList(char *file,int filteronoff=1);             //check if file is currently shown in dir List,use Spec&filter TRUE/FALSE; 

 //check if filename exists in dir,with Filtering on/off; 
 int  dirAddFile(int idx, char *str, int ln, int ty=0, int sz=0,time_t tm=0);
 int  dirSort(int type);                      //main function to do sorting
 int  dirSetSort(int type)   { fileSortType=type; return(dirSort(type));   }
 int  dirIsFilter(int flags) { return ( fileFilterType & flags); }     //return if flag set
 int  dirSetFilter(int flags);                //set and refresh the filter doing callbacks for updates
 int  dirClearFilter();                       //clear refresh the filter doing callbacks for updates
 int  dirToggelFilter(int flags);             //toggel and refresh the filter doing callbacks for updates

 char* dir(){ return dirPath;}                //return the directory currently set 
 int  dirRead(const char *dir);               //Read All directories files (on UNIX NO stat call)
 int  dirReadType();                          //Read type from Dir Idn to Idx,UNIX)(NT already gives type on readDir)
 int  dirSetDisplay();                        //set the display flag for files maching pattern
 void dirHaltScan(){dirScanCount=nDirFiles;}  //request that the scan be stopped,done by GUI 
 void dirResetScan(){dirScanCount=0;}         //reset the scan to start from start. 
 void convertSlash(char *findIn);             //convert NT style to UNIX style slash 

 int  cd(const char *buf,int cb_mode=0);      //set the directory to this if needed and callback limits
 int  cdUp();                                 //change up one directory
 int  cdRoot();                               //goto root directory or NT C:
 int  cdHome();                               //look for env HOME and change if exists
 int  cdCurrent();
 int  cdSub(char *dir);                       //try to change into a subdirectory of curent one
 int  tabComplete(const char *dir,char *buf); //try to do tab complete on the dir list
 int  simpleExp( const char *s, const char *e, int CaseSens = TRUE );
 int  filename_expand(char *t,const char *f);  //check for ~,$HOME 
};
#endif 

