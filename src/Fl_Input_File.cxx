/* Fl_Input_File for WidgetSet, Copyright (c) 1998 curtis Edwards (curt1@jps.net)
 * Permission to use, copy, modify, and distribute this software and its
 * documentation for any purpose and without fee is hereby granted, provided
 * that the above copyright notice appear in all copies and that both the
 * copyright notice and this permission notice appear in supporting
 * documentation.  All work developed as a consequence of the use of
 * this program should duly acknowledge such use. No representations are
 * made about the suitability of this software for any purpose.  It is
 * provided "as is" without express or implied warranty.
   Description	-  This is based onthe text input and decodes user actions creating
                 buttons where "/\:" are found.
                 pressing any of the buttons will strip the text to the nerest "/\:"
                 The widget was developed for the File_dialog class to assest
                 in directory managment,in includes the Fl_Dir class to manage directories
*/

#include <FL/Fl_Input_File.H>

#define FL_DIR_USERSTART 4      //index to start (0-13) of "quickfix" user directories
#define FL_DIR_USEREND  13      //number of end index for "quickfix" user directories
static  int  Fl_Dir_User_Index = FL_DIR_USERSTART; 
static  char Fl_Dir_User_Array[10][FL_MAX_PATH+FL_MAX_FILENAME];

Fl_Menu_Item pulldown[] = {
  {"Up directory",     0},
  {"Root directory",   0},
  {"Home directory",   0},
  {"Current directory",0, 0 , 0,FL_MENU_DIVIDER}, 
  {"",  49},
  {"",  50}, 
  {"",  51},     
  {"",  52},   
  {"",  53},   
  {"",  54},   
  {"",  55},   
  {"",  56},  
  {"",  57},   
  {"",  48},   
  {0}
};

////
void Fl_Dir_cb1(Fl_Dir *fld,void *v)
{
   Fl_Input_File  *i = (Fl_Input_File*)v;
   i->refreshValue(i->dirPath);
   i->do_callback();
}
////
void Fl_Dir_cbERROR(Fl_Dir *fld,void *v)
{
   Fl_Input_File  *i = (Fl_Input_File*)v;
   i->okEntry=0;
   i->redraw();
   i->input_do_callback_error();
   Fl::check();
}

//// add fuction to quickfix callback
void quickfix_cb( Fl_Widget *o, void *v)
{
  Fl_Menu_Button *mb   = (Fl_Menu_Button*)o;
  Fl_Input_File  *flif = (Fl_Input_File*)v;
  switch(mb->value())
  {
        case 0:   flif->okEntry = flif->cdUp();	  break;
	case 1:   flif->okEntry = flif->cdRoot();  break;
	case 2:   flif->okEntry = flif->cdHome();   break;
	case 3:   flif->okEntry = flif->cdCurrent();  break;
        default:  if(mb->text()) flif->cd(mb->text());   break;
  }
}

////pass the details to parent 
Fl_Input_File::Fl_Input_File(int x, int y, int w, int h, const char *l,char *pathAndFile, int sortType, int filterType)
: Fl_Input(x, y, w, h, l),  Fl_Dir(pathAndFile,sortType,filterType)
{
   dir_callback1(Fl_Dir_cb1, this);
   dir_callback_error(Fl_Dir_cbERROR, this);
   menu = new Fl_Menu_Button(x, y, w, h,"Quick Fix");
   menu->box((Fl_Boxtype)0);
   menu->menu(pulldown);
   menu->callback(quickfix_cb, this); 
   if (pathAndFile && *pathAndFile) replace(0,size(),pathAndFile);
   refreshEntry  = 0;
   btnTopDown    = 0;
   btnSideDown   = 0;
   pushed_button = 0;
   okEntry       = 1;
   when(0);
   selection_color(9);
}

////destructor
Fl_Input_File::~Fl_Input_File()
{
    free((Fl_Menu_Button *) menu);
}

////fillin out(path+file),return 0 if invalid selection else length to last slash
int Fl_Input_File::getFilename(char *out)
{

    if(out)
    {
        int slash;
        int pattern;
        lenSlashPattern((char*)value(),slash, pattern);
	if( pattern ) {  strcpy(out, "");  return FALSE;}
	strcpy(out, value());
        if(slash) updateUserDir(out);
	return slash;
    }
return FALSE;
}

////Use the input string to change directory and update input cd(string)
int Fl_Input_File::setFilename(char *in)
{
    if(in)
    {
	cd(in);
	return TRUE;
    }
 return FALSE;
}

//// Draw all top buttons,depending on typed text
void Fl_Input_File::drawTopBtn()
{
  int X = 0;
  int i = 0;
  int button = 1;
  for (;; button++) 
  {   while (i < size() && !isdirsep(index(i))) i++;
      if (i >= size()) break;
      while (i < size() && isdirsep(index(i))) i++;
      int RstrWidth = (int) fl_width(value(),i)+6-xscroll();
      if (RstrWidth > w()-SIDE_WIDTH) RstrWidth = w()-SIDE_WIDTH;
      if (RstrWidth > X) 
      { 
         fl_draw_box(button == pushed_button ? FL_DOWN_BOX : FL_UP_BOX, x()+X, y(), RstrWidth-X, TOP_HEIGHT, (Fl_Color)(FL_DARK1+button));
         X = RstrWidth;
      }
  }
  int RstrWidth = w()-SIDE_WIDTH;
  if (RstrWidth > X) fl_draw_box(FL_UP_BOX, x()+X, y(), RstrWidth-X, TOP_HEIGHT, (Fl_Color)(FL_DARK1+button));
}
/////update the user "quickfix area" with last changed directory
void Fl_Input_File::updateUserDir(char *dir)
{
   int slash;
   int pattern;
   lenSlashPattern((char*)dir,slash, pattern);
   if(slash)
   {
      if(Fl_Dir_User_Index > FL_DIR_USEREND) Fl_Dir_User_Index = FL_DIR_USERSTART;
      strcpy(Fl_Dir_User_Array[Fl_Dir_User_Index-FL_DIR_USERSTART], dir);
      Fl_Dir_User_Array[Fl_Dir_User_Index-FL_DIR_USERSTART][slash]='\0';
      pulldown[Fl_Dir_User_Index].label(Fl_Dir_User_Array[Fl_Dir_User_Index-FL_DIR_USERSTART]);
      Fl_Dir_User_Index++;
   }
}
///refresh the input value checking if redraw needed and resetting okEntry
void Fl_Input_File::refreshValue(char *l)
{
   okEntry=1;
   replace(0,size(),l);
   Fl::check();
}

//// needed for C++ crap
int Fl_Input_File::value(const char *str, int len) 
{
  return Fl_Input::value(str,len);
}
//// check if null, if so, add current dir
int Fl_Input_File::value(const char *str) 
{
  if(*str) return Fl_Input::value(str);
  else  return FALSE;
}
//// needed for C++ crap
const char *Fl_Input_File::value() 
{
  return Fl_Input::value();
}

//// Draw all top buttons,depending on typed text
void Fl_Input_File::stripTopBtn(int buttonPressed)
{
   int i = 0;
   int button;
   for (button = 1; button<=buttonPressed; button++) 
     {
        while (i < size() && !isdirsep(index(i))) i++;
        if (i >= size()) 
	{
	    button = 0; 
	    return;
	}
        while (i < size() && isdirsep(index(i))) i++;
        int R = (int)fl_width(value(),i)+6-xscroll();
        if (R > w()-SIDE_WIDTH) R = w()-SIDE_WIDTH;
        if (x()+R > Fl::event_x()) break;
    }
   char dirValue[FL_MAX_PATH+FL_MAX_FILENAME];
   strcpy(dirValue, value());
   dirValue[i] = NULL;
   okEntry = cd(dirValue);
}

////  Main Draw Widget
void Fl_Input_File::draw() 
{
   if(!okEntry) textcolor(FL_RED);
   else textcolor(FL_BLACK);
   int oy = y();
   int ow = w();
   int oh = h();
   y(y()+TOP_HEIGHT); w(w()-SIDE_WIDTH);
   h(h()-TOP_HEIGHT);
   Fl_Input::draw();
   y(oy); w(ow); h(oh);
   drawTopBtn();
}

//// Handel Events
int Fl_Input_File::handle(int event) 
{
  int oy = y();
  int ow = w();
  int oh = h();
  y(y()+TOP_HEIGHT); w(w()-SIDE_WIDTH);
  h(h()-TOP_HEIGHT);
  Fl_Input::handle(event);
  y(oy); w(ow); h(oh);

   switch (event) 
    {
    case FL_KEYBOARD:
         okEntry=1;
	 if(Fl::event_key() == FL_Tab)     //File Compleation
	 {
             char buf[FL_MAX_PATH+FL_MAX_FILENAME];
             tabComplete(value(), buf);
             cd(buf);
	 }
        else  if(Fl::event_key() < FL_Pause || Fl::event_key() > FL_Alt_R)  
	     { 
	       cd(value());
	     }
	break;
    case FL_PASTE:
	       cd(value());
	       break;
    case FL_PUSH:
      if (!Fl::event_inside(x(), y(), w(), TOP_HEIGHT)) break;
      btnTopDown = 1; redraw();
    case FL_DRAG: {
      if (!btnTopDown) break;
      // figure out what button is pushed:
      int i = 0;
      int button;
      if (!Fl::event_inside(x(), y(), w(), TOP_HEIGHT)) button = 0;
      else for (button = 1; ; button++) {
        while (i < size() && !isdirsep(index(i))) i++;
        if (i >= size()) {button = 0; break;}
        while (i < size() && isdirsep(index(i))) i++;
        int R = (int)fl_width(value(),i)+6-xscroll();
        if (R > w()-SIDE_WIDTH) R = w()-SIDE_WIDTH;
        if (x()+R > Fl::event_x()) break;
      }
      if (button != pushed_button) {pushed_button = button; redraw();}
      return 1;}
    case FL_RELEASE:
      if (btnTopDown) {
        btnTopDown = 0;
        if (pushed_button)       //the value button has been released, do the string alteration
	{
            stripTopBtn(pushed_button);
	    pushed_button = 0;   //reset state
	    redraw();
	 }
        return 1;
      } 
      break;
    }

  return event;  
}
