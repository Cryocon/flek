/*  Fl_Dir for WidgetSet, Copyright (c) 1998 curtis Edwards (curt1@jps.net)
 * Permission to use, copy, modify, and distribute this software and its
 * documentation for any purpose and without fee is hereby granted, provided
 * that the above copyright notice appear in all copies and that both the
 * copyright notice and this permission notice appear in supporting
 * documentation.  All work developed as a consequence of the use of
 * this program should duly acknowledge such use. No representations are
 * made about the suitability of this software for any purpose.  It is
 * provided "as is" without express or implied warranty.
   Description Directory management Class implementation
*/
#include <FL/Fl_Dir.H>
char *fl_dir_messages[]=
{
  "Sorry - No files match with selected Filter",
  "Sorry - Invalid directory was entered",
  "Sorry - No such directory or permission denied",
  "Sorry - No files match the Pattern/Filter",
  "Sorry - No HOME directory found",
  "Sorry - No CURRENT DIRECTORY found", 
  "Sorry - Tab-Complete found no match", 
  "Sorry - No file matches entry", 
  "Please Select Files",
  "",
  0
};

//////gives length of String,Slash, and any Pattern Chars, faster to do all at once
int lenSlashPattern(char *buf,int &slash, int &hasPattern,int &prevSlash , int &prePatternSlash, int &lastComma)
{
    slash      = 0;
    lastComma  = 0;
    hasPattern = 0;
    prevSlash  = 0;
    prePatternSlash = 0;                  //does a small valid check on the directory(no patterns allowed)
    register char *c;
    register int j=0;
    for (c=buf; ;c++,j++)                 //check for last slash,also '/' = *
    {  
	switch(*c) 
      {
         case 1: 
         case 0: 
                    if(!prePatternSlash) prePatternSlash = slash;
                    return j;             //length of string
         case '?' : 
         case '[' : 
         case '*' : 
         case '{' : hasPattern = j+1;    //length to last patternchar
                    if(!prePatternSlash) prePatternSlash = slash;
		    break;
         case '\\': 
         case ':' : 
         case '/' : prevSlash  = slash;
                    slash      = j+1;    //store length to '/' char
		    break;
         case ',' : lastComma = j+1;
		    break;
      }
    }
}

Fl_Dir::Fl_Dir(char *pathAndFile,int sortType, int filterType )
{
    nDirFiles      = 0;                      //totalFiles in array
    dirListCount   = 0;                      //keeps track of listed files
    strcpy(dirPath,pathAndFile);             //current dir & starname
    dirMallocCount = 0;                      //index to last malloc call
    dirMessage     = DIR_MSG_NONE;
    dir_callback1();
    dir_callback2();
    dir_callback_error();
    fileFilterType = filterType;             //type of filter to use
    fileSortType   = sortType;               //type of sort to apply
    dirPathSize    = lenSlashPattern(pathAndFile,dirPathSlash);
    cd(pathAndFile);
}

////free up memory before exit
Fl_Dir::~Fl_Dir()
{
   for (int i=0; i < dirMallocCount; i++) 
   {
       free((Fl_Dir_File *) dirFiles[i]);
   }
}

///return list of file entries (resets when complete)
Fl_Dir_File* Fl_Dir::fileList() 
{
   if( dirListCount >= nDirFiles) return fileListReset();
   if ( dirFiles[ dirSortIdx1[dirListCount]]->display == TRUE) return dirFiles[dirSortIdx1[dirListCount++]];
   else
   {   dirListCount++;
       for(;dirListCount < nDirFiles;)
       { 
          if( dirFiles[dirSortIdx1[dirListCount]]->display == TRUE) return dirFiles[dirSortIdx1[dirListCount++]];
          dirListCount++;
       }
   }
   return fileListReset();
}

//////check if file is currently shown in dir List,use Spec&filter TRUE/FALSE
Fl_Dir_File* Fl_Dir::fileInList(char *file,int filteronoff)
{
   int i=0;
   if(filteronoff)
   {     for(  i=0; i < nDirFiles; i++)
          if( dirFiles[dirSortIdx1[i]]->display == TRUE) 
          if( simpleExp(dirFiles[dirSortIdx1[i]]->name,file) ) return dirFiles[dirSortIdx1[i]];
   }
   else
   {     for(  i=0; i < nDirFiles; i++)
          if( simpleExp(dirFiles[dirSortIdx1[i]]->name,file) ) return dirFiles[dirSortIdx1[i]];
          //strcmp(dirFiles[dirSortIdx1[i]]->name,file) == 0) return dirFiles[dirSortIdx1[i]];
   }
   return fileListReset();
} 

////sort the directory files currently loaded
int Fl_Dir::dirSort(int type)
{
   int c=0;
   int f=1;
   int tmp;
   switch(type)
   {
      case FL_SORT_NAME_NOCASE :
           for(f=1; f < nDirFiles; f++)    //create a bubblesort by name assending "<"
           {
             c=f;
             while(  c>0 && STRCASECMP( dirFiles[dirSortIdx1[c]]->name ,dirFiles[dirSortIdx1[c-1]]->name))
             {   tmp=dirSortIdx1[c];
                 dirSortIdx1[c]   = dirSortIdx1[c-1];
                 dirSortIdx1[c-1] = tmp;
                 c--;
             }
           }  
           break;
      case FL_SORT_NAME_REVERSE:
           for(f=1; f < nDirFiles; f++)    //create a bubblesort by name ">"
           {
              c=f;
              while(  c>0 && strcmp( dirFiles[dirSortIdx1[c]]->name ,dirFiles[dirSortIdx1[c-1]]->name) > 0 )
              {   
                  tmp=dirSortIdx1[c];
                  dirSortIdx1[c]   = dirSortIdx1[c-1];
                  dirSortIdx1[c-1] = tmp;
                  c--;
              }
           }  
           break;
      case FL_SORT_NUMERIC	   :
           break;
      case FL_SORT_TIME        :
           break;
      case FL_SORT_SIZE        :
           break;
      case FL_SORT_NONE        :
 		  for(f=0; f < nDirFiles; f++)    //create the default sorting
           {
             dirSortIdx1[f] = f;
           }
            break;
      case FL_SORT_DIR         :
      case FL_SORT_NAME        :
      default:
           for(f=1; f < nDirFiles; f++)    //create a bubblesort by name assending "<"
           {
             c=f;
             while( c > 0 &&strcmp( dirFiles[dirSortIdx1[c]]->name ,dirFiles[dirSortIdx1[c-1]]->name) < 0)
             {   tmp=dirSortIdx1[c];
                 dirSortIdx1[c]   = dirSortIdx1[c-1];
                 dirSortIdx1[c-1] = tmp;
                 c--;
             }
           }  
           if(type != FL_SORT_DIR) break;
           for(f=1; f < nDirFiles; f++)    //create a bubblesort by name assending "<"
           {
             c=f;
             while(c > 0 && dirFiles[dirSortIdx1[c]]->type < FL_TYPE_DIR)
             {   tmp=dirSortIdx1[c];
                 dirSortIdx1[c]   = dirSortIdx1[c-1];
                 dirSortIdx1[c-1] = tmp;
                 c--;
             }
           }  
	   
           break;
   }
return f;
}
                    
////add Fl_Dir_File Struct to array doing malloc if needed
int Fl_Dir::dirAddFile(int idx, char *d_name, int d_namlen, int type, int size,time_t t)
{
  if(idx > dirMallocCount || idx > FL_MAX_DIR) return FALSE;
  if(idx == dirMallocCount) 
  {
      dirFiles[idx] = (struct Fl_Dir_File*)new char[sizeof(Fl_Dir_File)+1];
      dirMallocCount++;
  }
  strncpy( dirFiles[idx]->name,d_name,FL_MAX_FILENAME);
  if(d_namlen < FL_MAX_FILENAME) dirFiles[idx]->name[d_namlen] = '\0';  //just to be safe
  dirFiles[idx]->nameLen = d_namlen;
  dirFiles[idx]->type    = type;
  dirFiles[idx]->size    = size;
  dirFiles[idx]->display = TRUE;   //should default to display all
  dirSortIdx1[idx] = idx;          //set the sort default something
return TRUE;
}
////////////////////////////////////////////////////
int  Fl_Dir::dirClearFilter()
{   
    fileFilterType = 0; 
    dirSetDisplay();
    dir_do_callback1(); 
    dir_do_callback2(); 
    return fileFilterType; 
}
////////////////////////////////////////////////////
int  Fl_Dir::dirSetFilter(int flags)
{   
    fileFilterType |= flags; 
    if(!dirSetDisplay()) dir_do_callback_error(0);
    dir_do_callback1(); 
    dir_do_callback2(); 
    return flags; 
}
///////////////////////////////////////////////////
int Fl_Dir::dirToggelFilter(int flags)
{ 
    fileFilterType ^= flags; 
    if(!dirSetDisplay()) dir_do_callback_error(0);
    dir_do_callback1(); 
    dir_do_callback2(); 
    return flags; 
}

//// read directory entries in sequence
int Fl_Dir::dirRead(const char *dir)
{
  register int nfiles=0;

#ifdef WIN32    // WINDOZ NT
  WIN32_FIND_DATA find;
  HANDLE h;
 
  int  slash;
  int  pattern;
  char fname[FL_MAX_PATH + FL_MAX_FILENAME];
  strcpy(fname, dir);
  int  len  = lenSlashPattern(fname,slash, pattern);    // gives back length of string,Slash,Pattern
  if(len==0) { strcpy(fname, "./*"); }
  else {fname[slash]='*'; fname[slash+1]='\0';} 

  if ((h=FindFirstFile(fname, &find))==INVALID_HANDLE_VALUE) return FALSE;
  do {
          len = strlen(find.cFileName);
          if( strcmp(find.cFileName,".")==0) continue;  //skip self
          if( strcmp(find.cFileName,"..")==0) dirAddFile(nfiles, find.cFileName,len, FL_TYPE_PARENT   ,find.nFileSizeHigh ,0);
          else if((find.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) dirAddFile(nfiles, find.cFileName,len, FL_TYPE_DIR   ,find.nFileSizeHigh ,0);
          else if((find.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN   )) dirAddFile(nfiles, find.cFileName,len, FL_TYPE_HIDDEN,find.nFileSizeHigh ,0);
          else if((find.dwFileAttributes & FILE_ATTRIBUTE_SYSTEM   )) dirAddFile(nfiles, find.cFileName,len, FL_TYPE_SYSTEM,find.nFileSizeHigh ,0);
          else if( toupper(find.cFileName[len-4]) == '.' && toupper(find.cFileName[len-3]) == 'E' && toupper(find.cFileName[len-2]) == 'X' && toupper(find.cFileName[len-1]) == 'E') dirAddFile(nfiles, find.cFileName,len, FL_TYPE_EXE,find.nFileSizeHigh ,0);
          else if( toupper(find.cFileName[len-4]) == '.' && toupper(find.cFileName[len-3]) == 'C' && toupper(find.cFileName[len-2]) == 'O' && toupper(find.cFileName[len-1]) == 'M') dirAddFile(nfiles, find.cFileName,len, FL_TYPE_EXE,find.nFileSizeHigh ,0);
          else if( toupper(find.cFileName[len-4]) == '.' && toupper(find.cFileName[len-3]) == 'B' && toupper(find.cFileName[len-2]) == 'A' && toupper(find.cFileName[len-1]) == 'T') dirAddFile(nfiles, find.cFileName,len, FL_TYPE_EXE,find.nFileSizeHigh ,0);
          else dirAddFile(nfiles, find.cFileName,len, FL_TYPE_FILES,find.nFileSizeHigh ,0);
          nfiles++;
    } while (FindNextFile(h, &find));
  FindClose(h);

#else          // UNIX and all OTHERS
    DIR	        *ptDir;
    dirent      *ptFile;
    ptDir = opendir( dir );
    if ( !ptDir) return FALSE;
    while ( (ptFile = readdir(ptDir)) && nDirFiles < FL_MAX_DIR ) 
    {
	if( strcmp(ptFile->d_name,".")==0) continue;  //skip self
        if( strcmp(ptFile->d_name,"..")==0) dirAddFile(nfiles, ptFile->d_name, strlen(ptFile->d_name), FL_TYPE_PARENT,0,0);
        else dirAddFile(nfiles, ptFile->d_name, strlen(ptFile->d_name), FL_TYPE_NONE,0,0);
        nfiles++;
    }
    closedir(ptDir);
#endif
 nDirFiles = nfiles;
 return nfiles;
}

//// read directory entries in sequence
int Fl_Dir::dirReadType()
{
if( dirScanCount >= nDirFiles) return FALSE;
#ifdef WIN32
dirScanCount = nDirFiles;
#else
  int idx, lenSlash;
  char  buf[FL_MAX_PATH+FL_MAX_FILENAME];
  strcpy(buf, dirPath);
  lenSlashPattern((char*)buf, lenSlash);
  char *bufPtr = &buf[lenSlash];

  struct stat stBuf;	
  for(dirScanCount=0; dirScanCount < nDirFiles; dirScanCount++){ 
     idx = dirScanCount;
     if( dirFiles[idx]->name[0] == '.' ) { 
        if(dirFiles[idx]->name[1] == '.' ) dirFiles[idx]->type = FL_TYPE_PARENT; 
        else dirFiles[idx]->type = FL_TYPE_HIDDEN; 
     }
     else {
        strcpy(bufPtr, dirFiles[idx]->name);
        lstat(buf, &stBuf);
        if( S_ISLNK(stBuf.st_mode) ) {   
           stat(buf, &stBuf);
	   if( S_ISDIR(stBuf.st_mode) ) dirFiles[idx]->type = FL_TYPE_SYMDIR;
           else dirFiles[idx]->type = FL_TYPE_SYMFILE;
        }
        else 
	  if( S_ISDIR(stBuf.st_mode) )  dirFiles[idx]->type = FL_TYPE_DIR; 
        else
	  if( (stBuf.st_mode & S_IXOTH) && (stBuf.st_mode & S_IXGRP) && (stBuf.st_mode & S_IXUSR))  dirFiles[idx]->type = FL_TYPE_EXE;  
        else 
	  dirFiles[idx]->type = FL_TYPE_FILES;
     }
  }
#endif
return TRUE;
}

////set the display flag for files matching pattern
int  Fl_Dir::dirSetDisplay()            
 {
    char buf[FL_MAX_FILENAME];
    register int i;
    int match=0;
    strcpy(buf,(char*)(dirPath+dirPathSlash));

    if(dirPathSize == dirPathSlash){   //last slash & no filter make it an '*' for display all
       if(!fileFilterType) { 
           for(i=0; i< nDirFiles;i++) dirFiles[i]->display = TRUE; 
           return i;
       }  
       else strcpy(buf, "*");
    }
    strcat(buf, "*");
    for(i=0; i< nDirFiles;i++)
    {
       dirFiles[i]->display = FALSE;
       if( dirFiles[i]->type & FL_TYPE_PARENT )
       {   if( dirIsFilter(FL_TYPE_PARENT)) continue;
	   dirFiles[i]->display = TRUE; 
	   if(nDirFiles ==1) match++; 
	   continue;
       }
       if( (dirFiles[i]->type == FL_TYPE_DIR) ) 
       {
	      if( dirIsFilter(FL_TYPE_DIR))  continue;
          dirFiles[i]->display = TRUE; 
          if(simpleExp((char*)dirFiles[i]->name,buf,FALSE)) match++;
		  continue;
       }
       if( (dirFiles[i]->type == FL_TYPE_FILES)  && dirIsFilter(FL_TYPE_FILES))   continue;
       if( (dirFiles[i]->type == FL_TYPE_SYMFILE)&& dirIsFilter(FL_TYPE_SYMFILE)) continue;
       if( (dirFiles[i]->type == FL_TYPE_SYMDIR) && dirIsFilter(FL_TYPE_DIR))     continue;
       if( (dirFiles[i]->type == FL_TYPE_HIDDEN) && dirIsFilter(FL_TYPE_HIDDEN))  continue;
       if( (dirFiles[i]->type == FL_TYPE_EXE)    && dirIsFilter(FL_TYPE_EXE))     continue;
       if(simpleExp((char*)dirFiles[i]->name,buf,FALSE)) {
           dirFiles[i]->display = TRUE; 
	   match++;
       }
    }
return match;
}

////// convert the directory to UNIX style
void Fl_Dir::convertSlash(char *findIn) 
{
#ifdef WIN32 
 register char *d;
 for (d = findIn; *d; d++) if (*d=='\\') *d='/';
#endif
}

////// "cd" the current value by changing the directory being listed and
int Fl_Dir::cd(const char *dir, int cb_mode) 
{
 int match, len, lenSlash, lenPattern, prevSlash,prePatternSlash, lastComma;
 dirMessage     = DIR_MSG_NONE;
 dirResetScan();  //stop scanning directory
 char buf[FL_MAX_PATH+FL_MAX_FILENAME];
 char patternBuf[FL_MAX_PATH+FL_MAX_FILENAME];
 filename_expand(buf,dir); 
 len = lenSlashPattern((char*)buf, lenSlash, lenPattern, prevSlash,prePatternSlash, lastComma);
 if (lenSlash != dirPathSlash || strncmp(buf ,dirPath ,lenSlash) || dirMallocCount==0) 
 {

       if(prePatternSlash < lenSlash || lastComma>0 && lastComma < lenSlash) {    
	     dir_do_callback_error(1);
             return FALSE;
       }
       strcpy(patternBuf, (char*)(buf+lenSlash) );             //save the pattern + slash
       if(!lenSlash) {    
             if(!dirPathSlash) {
                 GETCWD(buf, FL_MAX_PATH);
	         strcat(buf,"/");
             }
	     else {
                 char buf2[FL_MAX_PATH+FL_MAX_FILENAME];
                 strcpy(buf2, buf);
	         strcpy(buf , dirPath); 
	         buf[dirPathSlash] = '\0'; 
	         strcat(buf, buf2);
	     } 
       } 
       len = lenSlashPattern((char*)buf, lenSlash, lenPattern);  //reset values
       buf[lenSlash] = '\0';
       convertSlash(buf);
       if(!dirRead(buf)) {
	     dir_do_callback_error(2);
             return FALSE;
	}
	 strcat(buf,patternBuf);                             //insure dir has currect information
         strcpy(dirPath, buf); 
         len = lenSlashPattern((char*)buf, lenSlash, lenPattern);  //reset values
	 dirPathSlash   = lenSlash;                          //index to last slash
         dirPathSize    = len;                               //length of string
	 dirPathPattern = lenPattern;                        //length of last pattern char 
         if(fileSortType>FL_SORT_NUMERIC || fileFilterType){ //if sort() needs to know before processing
	     dirReadType();
	     dirSort(fileSortType);
	     match = dirSetDisplay();
 	  }
          else {                       //we can speed it up a bit pre read and update
             dirSort(fileSortType);
             match = dirSetDisplay();
             if( cb_mode ==0 || cb_mode == 1) dir_do_callback1();
             if( cb_mode ==0 || cb_mode == 2) dir_do_callback2();
             dirReadType();     
             match = dirSetDisplay();          
	   }
         if( cb_mode==0 || cb_mode == 1) dir_do_callback1();
         if( cb_mode==0 || cb_mode == 2) dir_do_callback2();
         if(!match) {
	       if(lenPattern)dir_do_callback_error(3);
               else dir_do_callback_error(7);
	 }
	 return match;   
  }
 strcpy(dirPath, buf);
 dirPathSize    = len;                               //length of string
 dirPathPattern = lenPattern;                        //length of last pattern char 
 if( !dirSetDisplay()) {   
       if(lenPattern)dir_do_callback_error(3);
       else dir_do_callback_error(7);
       return FALSE;
 }
if( cb_mode ==0 || cb_mode == 1) dir_do_callback1();
if( cb_mode ==0 || cb_mode == 2) dir_do_callback2();
return TRUE;
}

//////change to the previous directory
int Fl_Dir::cdUp() 
{
   char buf[FL_MAX_PATH+FL_MAX_FILENAME];
   int lenSlash, lenPattern, lenPrevSlash;

   lenSlashPattern(dirPath,lenSlash,lenPattern,lenPrevSlash);   
   if(!lenPrevSlash) return FALSE;
   strcpy(buf,dirPath);
   buf[lenPrevSlash] = '\0';
   if(lenPattern>lenSlash) strcat(buf, (char*)(dirPath+lenSlash) );  //save the pattern of one
   lenSlash = cd(buf);
return lenSlash;
}

// find root directory
int Fl_Dir::cdRoot()
{
 char buf[FL_MAX_FILENAME];
#ifdef WIN32    // WINDOZ NT
	strcpy( buf, "c:/");
#else          // UNIX and all OTHERS
	strcpy( buf,  "/");
#endif
  return cd(buf);
}

//// find home directory
int Fl_Dir::cdHome()
{
   char buf[FL_MAX_PATH+FL_MAX_FILENAME];
   char *envVar;
   envVar = getenv( "HOME" );  //Get value of HOME environment variable.
   if( envVar == NULL ) {   
        dir_do_callback_error(4); 
        return FALSE;
   }
   strcpy(buf,envVar); 
   strcat(buf, "/");
   convertSlash(buf);
   return cd(buf);
}
////  Returns and sets path of current directory.
int Fl_Dir::cdCurrent()
{
   char buf[FL_MAX_PATH+FL_MAX_FILENAME];
   if( GETCWD(buf, FL_MAX_PATH ) == NULL ){   
        dir_do_callback_error(5); 
        return FALSE;
   }
   strcat(buf, "/");
   convertSlash(buf);
   return cd(buf);
}
//////try to change into a subdirectory of curent one
int Fl_Dir::cdSub(char *dir)
{
   int slash, pattern;
   char buf[FL_MAX_PATH+FL_MAX_FILENAME];
   strcpy(buf, dirPath);
   buf[dirPathSlash] = '\0';
   strcat(buf, dir);    
   lenSlashPattern((char*)dir,slash, pattern);      // gives back length and last slash
   if(!pattern && !slash) strcat(buf,"/");
   return cd(buf);    
}

//////try to do tab complete on the dir list
int  Fl_Dir::tabComplete(const char *dir, char *buf)
{
    int slash,pattern;
    char filename[FL_MAX_PATH+FL_MAX_FILENAME];
    register int i=0;
    register int j=0;
    int      match=0;
    int      match2 =0;
    int      lastFound=-1;
    int len = lenSlashPattern((char*)dir,slash, pattern);      // gives back length and last slash
    if(len == 0 || len == slash || nDirFiles < 2 || pattern)   //check if valid Dir and files Exists ,".." is not a file
    {  
        strcpy(buf, dir);
        return match;                                          //check if any files ".." is not a file
    }
    else
    {
	strcpy(filename, (char*)(dir+slash) );
	match = match2 =strlen(filename); 
	
	for(i=0; i< nDirFiles;i++) {
		if(dirFiles[i]->display == FALSE || (dirFiles[i]->type & FL_TYPE_PARENT) ) continue;     //test only displayed files(saves a little time)
		if( strncmp(filename, dirFiles[i]->name, match) != 0) continue;
		if(lastFound != -1)
		{	
			for(j=match; j<=match2; j++) if(dirFiles[i]->name[j] != filename[j]) break;
			if( j == match2) {
				strcpy(filename,dirFiles[i]->name);	
				match2 = dirFiles[i]->nameLen;
			}
			else 
			{
				match2 = j;
				break;
			}	 
		}	
		strcpy(filename,dirFiles[i]->name);	
		match2 = dirFiles[i]->nameLen; 
		lastFound = i;		
	}
    }
 strncpy(buf, dir, slash);
 if( match2 == dirFiles[lastFound]->nameLen && (dirFiles[lastFound]->type & FL_TYPE_DIR))
 {    filename[match2++]='/'; 
 }
 filename[match2]='\0';
 convertSlash(filename);
 strcpy((char*)(buf+slash),filename);
 if(!match) dir_do_callback_error(6);
return match;
}

////small globing *?{chars}[pattern|pattern]
int Fl_Dir::simpleExp(const char *strIn, const char *patternIn,int CaseSensitive) 
{
    if ( !patternIn  || !strIn ) return 0;   // cannot match
    register char *str     = (char *)strIn;
    register char *pattern = (char *)patternIn;

    if(!CaseSensitive) while ( *str && tolower(*str) ) str++;
    str = (char *)strIn;
    int matched;
 
for (;;) {
    switch(*pattern++) 
	{

    case '?' :	// match any single character
        if (!*str++) return 0;
        break;

    case '*' :	// match 0-n of any characters
        if (!*pattern) return 1; // do trailing * quickly
        while (!simpleExp(str, pattern)) if (!*str++) return 0;
        return 1;

    case '[': {	// match one character in set of form [abc-d] or [^a-b]
        if (!*str) return 0;
        int reverse = (*pattern=='^' || *pattern=='!'); if (reverse) pattern++;
        matched = 0;
        char last = 0;
        while (*pattern) 
		{
            if (*pattern=='-' && last) 
			{
                if (*str <= *++pattern && *str >= last ) matched = 1;
	            last = 0;
			} else if (*str == *pattern) matched = 1;
			last = *pattern++;
	        if (*pattern==']') break;
		}
        if (matched == reverse) return 0;
        str++; pattern++;}
    break;

    case '{' : // {pattern1|pattern2|pattern3}
NEXTCASE:
        if (simpleExp(str,pattern)) return 1;
        for (matched = 0;;) 
		{
            switch (*pattern++) 
			{
              case '\\': if (*pattern) pattern++; break;
              case '{': matched++; break;
              case '}': if (!matched--) return 0; break;
              case '|': case ',': if (matched==0) goto NEXTCASE;
              case  0 : return 0;
			}
		}
    case '|':	// skip rest of |pattern|pattern} when called recursively
    case ',':
        for (matched = 0; *pattern && matched >= 0;) 
		{
	        switch (*pattern++) 
			{
              case '\\': if (*pattern) pattern++; break;
	          case '{': matched++; break;
	          case '}': matched--; break;
			}
		}
        break;
    case '}':
        break;

    case 0:	// end of pattern
        return !*str;

    case '\\':	// quote next character
        if (*pattern) pattern++;
    default  :	// other characters
        if (*str++ != *(pattern-1)) return 0;
        break;
    }
  }
}

//// check for $HOME etc.. and ~ values expand them if found
int  Fl_Dir::filename_expand(char *to,const char *from) 
{

  char temp[FL_MAX_PATH+FL_MAX_FILENAME];
  strcpy(temp,from);
  const char *start = temp;
  const char *end = temp+strlen(temp);

  int ret = 0;

  for (char *a=temp; a<end; ) 
  {	// for each slash component
    char *e; 
    for (e=a; e<end && !isdirsep(*e); e++); // find next slash
    const char *value = 0; // this will point at substitute value
    switch (*a) {
    case '~':	// a home directory name
      if (e <= a+1) {	// current user's directory
	value = getenv("HOME");
#ifndef WIN32
      } else {	// another user's directory
	struct passwd *pwd;
	char t = *e; *(char *)e = 0; 
        pwd = getpwnam(a+1); 
        *(char *)e = t;
	    if (pwd) value = pwd->pw_dir;
#endif
      }
      break;
    case '$':		/* an environment variable */
      {char t = *e; *(char *)e = 0; value = getenv(a+1); *(char *)e = t;}
      break;
    }
    if (value) {
      // substitutions that start with slash delete everything before them:
      if (isdirsep(value[0])) start = a;
#ifdef WIN32
      // also if it starts with "A:"
      if (value[0] && value[1]==':') start = a;
#endif
      int t = strlen(value); if (isdirsep(value[t-1])) t--;
      memmove(a+t, e, end+1-e);
      end = a+t+(end-e);
      memcpy(a, value, t);
      ret++;
    } else {
      a = e+1;
#ifdef WIN32
      if (*e == '\\') {*e = '/'; ret++;} // ha ha! -?dont think I need this
#endif
    }
  }
  strcpy(to,start);
  return ret;
}

