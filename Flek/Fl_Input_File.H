/*      Test input fields       */
//handel  fl_font(font,pointsize)   FL_INSIDE(EVENT
//get current font -textfont,then get the size with textsize(returns-point size)
//draw content fl_draw_box(FL_UP_BOX(xywh) to lefdt   srnncpy +nul  fl::value(newbuff)
#ifndef Fl_Input_File__H
#define Fl_Input_File__H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Bitmap.H>
#include <FL/Fl_Input.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Menu_Button.H>
#include "Fl_Dir.H"


//needs to change the value to take the directory/path and the path_File to copy to it

class Fl_Input_File : public Fl_Input, public Fl_Dir
{
public:

//#2-error ,callback when directory changed and needs refresh
    Dir_Callback* input_callback_error_;
    void* input_user_data_error_;
    void  input_callback_error(Dir_Callback* c=NULL, void* p=0) {input_callback_error_=c; input_user_data_error_=p;}
    void  input_do_callback_error()              {if(input_callback_error_) input_callback_error_(this, input_user_data_error_);}

  int handle(int);
  void stripTopBtn(int button);
  void drawTopBtn();
  void draw();
  void updateUserDir(char *out);
  void refreshValue(char *l);
  int value(const char*);
  int value(const char*, int);
  const char *value();
  int getFilename(char *out);   //fillin out(path+file),return 0 if invalid selection else length to last slash
  int setFilename(char *in);
  int btnTopDown;
  int pushed_button;
  int btnSideDown;
  int okEntry;
  int refreshEntry;
  Fl_Menu_Button *menu;         //menu for quick fix home/current/root
  Fl_Input_File(int,int,int,int,const char *t,char *path_File,int st=0,int ty=0 );
  ~Fl_Input_File();
};

#define TOP_HEIGHT 12
#define SIDE_WIDTH 0     // reset in favor or right mouse click
void quickfix_cb( Fl_Widget *o, void *v);
void Fl_Dir_cb1(Fl_Dir *fld,void *v);
void Fl_Dir_cbERROR(Fl_Dir *fld,void *v);
#endif 

