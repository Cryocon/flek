/* Fl_File_Dialog for WidgetSet, Copyright (c) 1998 curtis Edwards (curt1@jps.net)
 * Permission to use, copy, modify, and distribute this software and its
 * documentation for any purpose and without fee is hereby granted, provided
 * that the above copyright notice appear in all copies and that both the
 * copyright notice and this permission notice appear in supporting
 * documentation.  All work developed as a consequence of the use of
 * this program should duly acknowledge such use. No representations are
 * made about the suitability of this software for any purpose.  It is
 * provided "as is" without express or implied warranty.
 Description	- Directory Dialog Class
*/

#include <FL/Fl_Box.H>
#include <FL/Fl_Pixmap.H>
#include <FL/Fl_Button.H>
#include <FL/fl_draw.H>

#include <Flek/Fl_File_Dialog.H>

Fl_Menu menuSort[] = {
 {"Alpha"        , 97,  0, 0, 0, 0, 3, 14, 0},
 {"Alpha NoCase" ,  0,  0, 0, 0, 0, 3, 14, 0},
 {"Alpha Reverse",  0,  0, 0, 0, 0, 3, 14, 0},
 {"Numeric"      ,  0,  0, 0, 0, 0, 3, 14, 0},
 {"Time"         ,  0,  0, 0, 0, 0, 3, 14, 0},
 {"Size"         ,  0,  0, 0, 0, 0, 3, 14, 0},
 {"None"         ,  0,  0, 0, 0, 0, 3, 14, 0},
 {"Directories"  ,  0,  0, 0, 0, 0, 3, 14, 0},
 {0}
};

Fl_Menu menuFilter[] = {
	{"Directories"        ,0x64, 0, 0, FL_MENU_TOGGLE|FL_MENU_BOX}, 
	{"Files"              ,0x66, 0, 0, FL_MENU_TOGGLE|FL_MENU_BOX}, 
	{"Hidden (Dot Files)" ,0x68, 0, 0, FL_MENU_TOGGLE|FL_MENU_BOX}, 
	{"Executables"        ,0x65, 0, 0, FL_MENU_TOGGLE|FL_MENU_BOX}, 
	{"Symbolic Link Files",0x73, 0, 0, FL_MENU_TOGGLE|FL_MENU_BOX|FL_MENU_DIVIDER}, 
	{"Parent Directory"   ,0x70, 0, 0, FL_MENU_TOGGLE|FL_MENU_BOX}, 
	{0}
};
Fl_Menu menuPattern[] = {
	{"*"          ,49},
	{"*.*"        ,50},
	{"*.txt"      ,51},
	{"*.sgi"      ,52},
	{"*.bmp"      ,53},
	{"*.aiff"     ,54},
	{"*.wav"      ,55},
	{"*.html"     ,56},
	{"*.C*"       ,FL_ALT+'c'},
	{"*.H*"       ,FL_ALT+'h', 0, 0, FL_MENU_DIVIDER},
	{"*"          ,0},
	{0}
};

static char *image_singleMode[] = {
"32 32 -7 1",
" \x80\0\0!\0\0\0\"\0\x80\x80#\xc0\xc0\xc0$\x80\x80\x80%\0\xff\xff&\xff\xff\
\xff",
"                                ",
"                                ",
"                                ",
"                                ",
"                                ",
"                  !!!!!!!!!!!!!!",
"                  !&%&%&%&%&%&%!",
"                  !%&%&%&%&%&%&!",
"                  !&%&%&%&%&%&%!",
"                  !%&%&%&%&%&%&!",
"                  !&%&%&%&%&%&%!",
"                  !%&%&%&%&%&%&!",
"                  !&%&%&%&%&%&%!",
"                  !%&%&%&%&%&%&!",
"               !!!!!!!!!!!!!%&%!",
"              !&&&&&&&&&&&&#!\"%!",
"      !!!!!!!!&############$!\"\"!",
"      !&&&&&&&#############$!\"\"!",
"      !&###################$!\"\"!",
"      !&###################$!\"\"!",
"      !&###################$!\"\"!",
"      !&###################$!\"\"!",
"      !&###################$!\"\"!",
"      !&###################$!\"\"!",
"      !&###################$!\"\"!",
"      !&###################$!\"\"!",
"      !&###################$!\"\"!",
"      !&###################$!!!!",
"      !&###################$!   ",
"      !&###################$!   ",
"      !#$$$$$$$$$$$$$$$$$$$$!   ",
"      !!!!!!!!!!!!!!!!!!!!!!!   "
};
static Fl_Pixmap pixmap_singleMode(image_singleMode);
static char *image_multiMode[] = {
"32 32 -7 1",
" \xff\xff\xff!\xc0\xc0\xc0\"\x80\x80\x80#\0\xff\xff$\0\x80\x80%\0\0\0&\xff\
\xff\xff",
"            %%%%%%%%%%%%%%      ",
"            %#&#&#&#&#&#&%      ",
"            %&#%%%%%%%%%%%%%%   ",
"            %#&%&#&#&#&#&#&#%   ",
"            %&#%#&#&#&#&#&#&%   ",
"            %#&%&#%%%%%%%%%%%%%%",
" %%%%%%%    %&#%#&%&#&#&#&#&#&#%",
"%%&&&&&&%   %#&%&#%#&#&#&#&#&#&%",
"%&&!!!!!!%%%%%%%#&%&#&#&#&#&#&#%",
"%&!!%%%%%%%&&&&%&#%#&#&#&#&#&#&%",
"%%%%%&&&&&&%!!!%#&%&#&#&#&#&#&#%",
"%&&%&&!!!!!!%%%%%%%#&#&#&#&#&#&%",
"%&!%&!!%%%%%%%&&&&%&#&#&#&#&#&#%",
"%&!%%%%%&&&&&&%!!!%#&#&#&#&#&#&%",
"%&!%&&%&&!!!!!!%%%%%%%%%%%%%#&#%",
"%&!%&!%&!!!!!!%&&&&&&&&&&&&!%$#%",
"%&!%&!%%%%%%%%&!!!!!!!!!!!!\"%$$%",
"%&!%&!%&&&&&&&!!!!!!!!!!!!!\"%$$%",
"%&!%&!%&!!!!!!!!!!!!!!!!!!!\"%$$%",
"%&!%&!%&!!!!!!!!!!!!!!!!!!!\"%$$%",
"%&!%&!%&!!!!!!!!!!!!!!!!!!!\"%$$%",
"%&!%&!%&!!!!!!!!!!!!!!!!!!!\"%$$%",
"%&!%&!%&!!!!!!!!!!!!!!!!!!!\"%$$%",
"%&!%&!%&!!!!!!!!!!!!!!!!!!!\"%$$%",
"%!\"%&!%&!!!!!!!!!!!!!!!!!!!\"%$$%",
"%%%%&!%&!!!!!!!!!!!!!!!!!!!\"%$$%",
"   %&!%&!!!!!!!!!!!!!!!!!!!\"%$$%",
"   %!\"%&!!!!!!!!!!!!!!!!!!!\"%%%%",
"   %%%%&!!!!!!!!!!!!!!!!!!!\"%   ",
"      %&!!!!!!!!!!!!!!!!!!!\"%   ",
"      %!\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"%   ",
"      %%%%%%%%%%%%%%%%%%%%%%%   "
};
static Fl_Pixmap pixmap_multiMode(image_multiMode);

////load the given browser with dir files
void loadBrowser(Fl_Browser *b, Fl_File_Dialog* flfd)
{
  Fl_Dir_File    *lst;
  Fl_Input_File  *i    = &flfd->input_file;
  Fl_Box         *info = &flfd->info_box;	
  char nameIn[FL_MAX_FILENAME+2];
  info->label("Please enter or select file");
  info->redraw();
  b->clear();
  while ( (lst = i->fileList()) )   //32-36 97-99
  {
    switch(lst->type)  // *(bufPtr+3) 0-none/files,2-dir,3-hidden,4-exe,5-Parent,7-symDir,8-symFile
    {
	case FL_TYPE_NONE:   sprintf(nameIn,"@C00@.%s", lst->name); 
	                     b->add( nameIn);
	                     break;
	case FL_TYPE_PARENT: sprintf(nameIn,"@C35@b%s/", lst->name); 
	                     b->add( nameIn);
	                     break;
	case FL_TYPE_DIR:    sprintf(nameIn,"@C32@b%s/", lst->name); 
	                     b->add( nameIn);
	                     break;
	case FL_TYPE_FILES:  sprintf(nameIn,"@C00@.%s", lst->name); 
	                     b->add( nameIn);
	                     break;
	case FL_TYPE_HIDDEN: sprintf(nameIn,"@C33@i%s", lst->name);
	                     b->add(nameIn);
	                     break;
	case FL_TYPE_EXE:    sprintf(nameIn,"@C34@.%s*", lst->name);
	                     b->add(nameIn);
	                     break;
	case FL_TYPE_SYMDIR: sprintf(nameIn,"@C97@b%s/", lst->name);
	                     b->add(nameIn);
	                     break;
	case FL_TYPE_SYMFILE:sprintf(nameIn,"@C98@.%s ", lst->name);
	                     b->add(nameIn);
	                     break;
    }
  }
 b->position(0);
 
 }

void browser_file_cb(Fl_Widget *o, void *v) 
{
  Fl_Multi_Browser   *b    = (Fl_Multi_Browser*)o;
  Fl_File_Dialog     *flfd = (Fl_File_Dialog*)v;
  Fl_Input_File      *i    = &flfd->input_file;
  Fl_Box             *info = &flfd->info_box;	
//  const char *bufPtr;
  char        buf[FL_MAX_PATH+FL_MAX_FILENAME];
  char        buf2[FL_MAX_FILENAME];
  int         nSelected = 0;
  int         len=0;
  if(b->value() < 1 ) return;
  if(b->type() == 3 || !Fl::event_clicks()) {    //multimode and multi selected
      strcpy(buf, i->dirPath);
      buf[i->dirPathSlash] = '\0';
      for(int j=1; j<=b->size(); j++) {
	 if( b->selected(j) ) { 
	     strcpy(buf2, b->text(j));
	     switch (buf2[3])
             {
               case '4':  len = strlen(buf2) ;  //remove *
                          buf2[len-1] = '\0';			 
               case '0':   
               case '3':   
               case '8': if(nSelected) strcat(buf,","); 
	                 strcat(buf,(char *)(buf2+6)); 
                         nSelected++; 
	                 break;
	       default : break;
	     }
	 }
     }
     if(nSelected>1) {
         i->refreshValue(buf);
               info->label("Multi Files Selected...");
               info->redraw();
         return;
    }
  }    //End of multimode and multi selected
  strcpy(buf, i->dirPath);
  buf[i->dirPathSlash] = '\0';
  strcpy(buf2, b->text(b->value()));
  switch (buf2[3])  // *(bufPtr+3) 0-none/files,2-dir,3-hidden,4-exe,5-Parent,7-symDir,8-symFile
  {
     case '7':                                      //sub directorys
     case '2': if(!Fl::event_clicks()) break;
               info->label("Changing to Directory...");
               info->redraw();
	       strcat(buf,(char *)(buf2+6));        //remove formatting codes
               i->cd(buf);  
               i->updateUserDir(buf);
	       break;
     case '5': if(!Fl::event_clicks()) break;       //parent dir
               info->label("Changing to Parent Driectory...");
               info->redraw();
	       i->cdUp();
               i->updateUserDir(buf);
	       break;
     case '4': len = strlen(buf2) ;  
               buf2[len-1] = '\0';	            //remove *			 
     default : strcat(buf,(char *)(buf2+6));        //Default is a file,load input
               i->refreshValue(buf);
               info->label("Single File Selected...");
               info->redraw();
	       if(Fl::event_clicks())  flfd->exit_do_callback(flfd);
               break;
  }
}

////change the sort method
void choice_sort_cb(Fl_Widget *o, void *v) 
{
  Fl_Choice         *ch   = (Fl_Choice*)o;
  Fl_File_Dialog    *flfd = (Fl_File_Dialog*)v;
  Fl_Multi_Browser  *b    = &flfd->browser_file;	
  Fl_Input_File     *i    = &flfd->input_file;
  i->dirSetSort(ch->value());
  loadBrowser(b,flfd);
}

////change the filter in input_file and set new filter
void choice_filter_cb(Fl_Widget *o, void *v) 
{
  Fl_Choice      *ch   = (Fl_Choice*)o;
  Fl_File_Dialog *flfd = (Fl_File_Dialog*)v;
  Fl_Input_File  *i    = &flfd->input_file;
  Fl_Browser     *b    = &flfd->browser_file;	
  switch(ch->value())
  {
        case 0:  i->dirToggelFilter(FL_TYPE_DIR);     break;
	case 1:  i->dirToggelFilter(FL_TYPE_FILES);   break;
	case 2:  i->dirToggelFilter(FL_TYPE_HIDDEN);  break;
	case 3:  i->dirToggelFilter(FL_TYPE_EXE);     break;
	case 4:  i->dirToggelFilter(FL_TYPE_SYMFILE); break;
	case 5:  i->dirToggelFilter(FL_TYPE_PARENT);  break;
  }
 loadBrowser(b,flfd);
}

////
void choice_pattern_cb(Fl_Widget *o, void *v) 
{
  Fl_Choice      *ch   = (Fl_Choice*)o;
  Fl_File_Dialog *flfd = (Fl_File_Dialog*)v;
  Fl_Input_File  *i    = &flfd->input_file;

  char buf[FL_MAX_PATH+FL_MAX_FILENAME];
  strcpy(buf, i->dirPath);
  int lenSlash, lenPattern, lenPrevSlash;
  lenSlashPattern(buf,lenSlash,lenPattern,lenPrevSlash);   
  buf[lenSlash] = '\0';
  strcat(buf,ch->text()); 
  i->cd(buf);
  i->refreshValue(i->dirPath); 
}

////load the browser if file input change
void input_file_cb( Fl_Widget *o, void *v)
{
  Fl_File_Dialog    *flfd = (Fl_File_Dialog*)v;
  Fl_Multi_Browser  *b    = &flfd->browser_file;	
  loadBrowser(b,flfd);
}

void input_file_error_cb(Fl_Dir *fld,void *v)
{
  Fl_File_Dialog    *flfd = (Fl_File_Dialog*)v;
  Fl_Box            *b    = &flfd->info_box;	
  Fl_Input_File     *i    = &flfd->input_file;

  if(flfd->isFlag(Fl_File_Dialog::SAVEMODE) && i->dirMessage==7 ) b->label("Entering a new file"); 
  else b->label(fl_dir_messages[i->dirMessage]);
  b->redraw(); 
}

////browser pressed 
Fl_File_Dialog::Fl_File_Dialog(int X, int Y, const char* L,char *patternpath ,int flags,  int sortType, int filterType)
  : Fl_Group(X, Y, 461, 299, L),
    browser_file(X+7, Y+35, 448, 196),
    input_file(X+6, Y+232, 449, 40, "", patternpath, sortType, filterType), 
    choice_sort(X+34, Y+6, 108, 25, "Sort"),
    choice_filter(X+182, Y+6, 108, 25, "Filter"), 
    choice_pattern(X+342, Y+5, 108, 25, "Pattern"), 
    info_box(X+7, Y+274, 446, 20, "label") 
 {
  box(FL_THIN_DOWN_FRAME);                    //group border
  Fl_Group::current()->resizable(browser_file);
  _flags=flags;  
  int slash,pattern;
  lenSlashPattern(patternpath,slash,pattern);  //check if a pattern is set

  exit_callback_= NULL;
  if(isFlag(MULTIMODE)) { 
     browser_file.type(3);
     if(isFlag(SAVEMODE)) info_box.label("Please select Files to Save"); 
     else                 info_box.label("Please select Files to Open"); 
  }
  else {
     browser_file.type(2);
     if(isFlag(SAVEMODE)) info_box.label("Please select File to Save"); 
     else                 info_box.label("Please select File to Open"); 
  }
  choice_sort.menu(menuSort);                 //sort.menu
  choice_sort.color(49);
  choice_sort.labelfont(1);
  choice_sort.labelsize(12);
  choice_sort.textsize(12);
  choice_sort.callback(choice_sort_cb,this);

  choice_filter.menu(menuFilter);            //filter.menu
  choice_filter.color(49);
  choice_filter.labelfont(1);
  choice_filter.labelsize(12);
  choice_filter.textsize(12);
  choice_filter.value(1);
  choice_filter.callback(choice_filter_cb,this);
  choice_filter.when(FL_WHEN_RELEASE|FL_WHEN_NOT_CHANGED);

  choice_pattern.menu(menuPattern);          //pattern.menu
  choice_pattern.color(49);
  choice_pattern.labelfont(1);
  choice_pattern.labelsize(12);
  choice_pattern.textsize(12);
  choice_pattern.callback(choice_pattern_cb,this);
  choice_pattern.when(FL_WHEN_RELEASE|FL_WHEN_NOT_CHANGED);
  if(pattern > slash){  
     choice_pattern.replace(10,(char*)(patternpath+slash) );
     choice_pattern.value(10);
  }

  browser_file.color(52);
  browser_file.textsize(12);
  browser_file.callback(browser_file_cb,this);  

  input_file.color(52);
  input_file.callback(input_file_cb,this);
  input_file.input_callback_error(input_file_error_cb, this);
  
  info_box.box(FL_THIN_DOWN_BOX);
  info_box.color(48);
  info_box.color2(9);
  info_box.labelfont(1);
  info_box.labelsize(12);
  
  menuFilter[0].clear();
  menuFilter[2].clear();
  menuFilter[3].clear();
  menuFilter[4].clear();
  menuFilter[5].clear();

  loadBrowser(&browser_file,this);
 end();   //close of grouping
 }

////exit to call when browser called
void exitdialog_cb(Fl_Widget *o, void *v)
{
  Fl_Return_Button *flrb = (Fl_Return_Button*)v;
  flrb->do_callback();
}

//C code for creating the complete dialog
int fl_file_dialog(const char* Title,char* patternpath, int flags , int sortType, int filterType) 
{
   Fl_Window        w(472, 343, Title);
   Fl_File_Dialog   fd(5, 5,"", patternpath, flags, sortType, filterType);
   Fl_Box           mb(208, 306, 56, 34);
   Fl_Button        cb(267, 311, 197, 25, "Cancel");
   Fl_Return_Button ob(8, 311, 196, 25, "Ok");
   Fl_Group::current()->resizable(fd);
   
   if( fd.isFlag(Fl_File_Dialog::MULTIMODE)) pixmap_multiMode.label(&mb);
   else pixmap_singleMode.label(&mb);
   fd.exit_callback(exitdialog_cb,&ob);

   w.set_modal();
   w.end();
   w.show();
   while (w.shown()) {
     Fl::wait();
     Fl_Widget* o;
     while ((o = Fl::readqueue())) {
       if (o == &ob)  return fd.getFilename(patternpath);  //report back the value
       if (o == &w || o == &cb) return 0;
     }
   }
  return 0;
}
