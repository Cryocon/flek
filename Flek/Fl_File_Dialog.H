// Fl_file_dialog.H
// 
// Besides being a useful object on it's own, the Fl_file_dialog was
// an attempt to make a complex composite object that could be easily
// imbedded into a user interface.
// The C function fl_file_dialog() creates a window containing a browser
// open/close buttons and current filter input.
// It uses the Fl_input_file to display selected input breaking it down
// to the "/\" dividers, If you wish to imbed the control into you own
// include the Class and go from there - C Edwards/B Spitzak

#ifndef Fl_file_dialog_H
#define Fl_file_dialog_H

#include <FL/Fl.H>
#include <FL/Fl_Multi_Browser.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Return_Button.H>
#include <FL/Fl_Menu_Button.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Choice.H>

#include <Flek/Fl_Dir.H>
#include <Flek/Fl_Input_File.H>

class Fl_File_Dialog : public Fl_Group 
{
public:

  enum { 	
    NONE      = 0x00,      // All flags off
    MULTIMODE = 0x01,      // Multi Mode
    SAVEMODE  = 0x02,      // Save State
    MESSAGES  = 0x04,      // messages on
    DEFAULT   = 0x04       // Default mode Single,Open,Messages
  };
  
  int _flags;
  int lastSelection;   //for double click
  int isFlag(int flags) 
    { 
      return (_flags & flags);
    }
  
  Fl_Callback *exit_callback_;       // callback to run if exit from browser is set
  void *exit_user_data_;
  void exit_callback(Fl_Callback* c, void* p) 
    {
      exit_callback_=c; 
      exit_user_data_=p;
    }
  void exit_do_callback(Fl_Widget* o) const   
    {
      exit_callback_(o, exit_user_data_);
    }
  
  Fl_Multi_Browser   browser_file;
  Fl_Input_File      input_file;
  Fl_Choice          choice_sort;
  Fl_Choice          choice_filter;
  Fl_Choice          choice_pattern;
  Fl_Box             info_box;

  int getFilename(char *out) 
    { 
      return input_file.getFilename(out); 
    }

  Fl_File_Dialog (int,int,const char* title,char* pattern,int flags=DEFAULT, int sorting=0, int filters=0);
};

void loadBrowser(Fl_Browser *b, Fl_Input_File  *i);
int  fl_file_dialog(const char* title, char* patternpath, int flags, int sortType=0, int filterType=0);
void choice_sort_cb(Fl_Widget *o, void *v); 
void choice_filter_cb(Fl_Widget *o, void *v); 
void choice_pattern_cb(Fl_Widget *o, void *v); 
void input_file_cb( Fl_Widget *o, void *v);
void browser_file_cb(Fl_Widget *o, void *v); 
void exit_cb(Fl_Widget *o, void *v); 
void input_file_error_cb(Fl_Dir *fld,void *v);

#endif

