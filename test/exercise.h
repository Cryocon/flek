// generated by Fast Light User Interface Designer (fluid) version 2.0000

#ifndef exercise_h
#define exercise_h
#include <FL/Fl.H>
#include <Flek/Flv_Table.H>

class Flv_List2 : public Flv_List {
public:
  Flv_List2(int x, int y, int w, int h, const char *l=0) ;
  void draw_row(int Offset, int &X, int &Y, int &W, int &H, int R);
};

class Flv_ListE : public Flv_List {
public:
  Flv_ListE(int x, int y, int w, int h, const char *l=0) ;
  void draw_row(int Offset, int &X, int &Y, int &W, int &H, int R);
};

class Flv_TableE : public Flv_Table {
public:
  Flv_TableE(int x, int y, int w, int h, const char *l=0) ;
  void draw_cell(int Offset, int &X, int &Y, int &W, int &H, int R, int C);
};

class Flv_List_Alignment : public Flv_List {
public:
  Flv_List_Alignment(int x, int y, int w, int h, const char *l=0) ;
  void draw_row(int Offset, int &X, int &Y, int &W, int &H, int R);
};

class Flv_List_Font : public Flv_List {
public:
  Flv_List_Font(int x, int y, int w, int h, const char *l=0) ;
  void draw_row(int Offset, int &X, int &Y, int &W, int &H, int R);
};

class Flv_List_Frame : public Flv_List {
public:
  Flv_List_Frame(int x, int y, int w, int h, const char *l=0) ;
  void draw_row(int Offset, int &X, int &Y, int &W, int &H, int R);
};

class Flv_List_Style_Section : public Flv_List {
public:
  Flv_List_Style_Section( int x, int y, int w, int h, const char *l=0 ) ;
  void draw_row(int Offset, int &X, int &Y, int &W, int &H, int R);
};
#include <FL/Fl_Window.H>
extern Fl_Window *win;
#include <FL/Fl_Group.H>
#include <FL/Fl_Check_Button.H>
extern void row_header_callback(Fl_Check_Button*, void*);
extern void row_footer_callback(Fl_Check_Button*, void*);
extern void row_divider_callback(Fl_Check_Button*, void*);
extern void col_header_callback(Fl_Check_Button*, void*);
extern void col_footer_callback(Fl_Check_Button*, void*);
extern void col_divider_callback(Fl_Check_Button*, void*);
extern void vertical_callback(Fl_Check_Button*, void*);
extern void horizontal_callback(Fl_Check_Button*, void*);
extern void always_callback(Fl_Check_Button*, void*);
#include <FL/Fl_Roller.H>
extern void rows_callback(Fl_Roller*, void*);
extern Fl_Group *Rows_Value;
extern void cols_callback(Fl_Roller*, void*);
extern Fl_Group *Cols_Value;
extern void row_width_callback(Fl_Roller*, void*);
extern Fl_Group *Row_Width_Value;
extern void multi_select_callback(Fl_Check_Button*, void*);
extern void row_select_callback(Fl_Check_Button*, void*);
extern void persist_select_callback(Fl_Check_Button*, void*);
extern void full_resize_callback(Fl_Check_Button*, void*);
#include <FL/Fl_Input.H>
extern Fl_Input *title;
extern Fl_Input *row_header;
extern Fl_Input *row_footer;
extern Fl_Input *col_header;
extern Fl_Input *col_footer;
extern Fl_Input *cell;
#include <FL/Fl_Output.H>
extern Fl_Output *table_loc;
extern Fl_Output *list_loc;
extern void style_type_callback(Flv_List2*, void*);
extern Flv_List2 *Style_Type;
extern void style_section_callback(Flv_List_Style_Section*, void*);
extern Flv_List_Style_Section *Style_Section;
extern Fl_Group *Color_Group;
#include <FL/Fl_Button.H>
extern void Foreground_callback(Fl_Button*, void*);
extern Fl_Button *Foreground_Style_Clear;
extern Fl_Group *Foreground_Style_Defined;
extern Fl_Group *Foreground_Style_Value;
extern Fl_Button *Background_Style_Clear;
extern Fl_Group *Background_Style_Defined;
extern Fl_Group *Background_Style_Value;
extern Fl_Group *Font_Group;
extern void font_style_callback(Flv_List_Font*, void*);
extern Flv_List_Font *Font_Style;
extern Fl_Button *Font_Style_Clear;
extern Fl_Group *Font_Style_Defined;
extern void font_size_callback(Fl_Roller*, void*);
extern Fl_Roller *Font_Size_Style;
extern Fl_Group *Font_Size_Style_Value;
extern Fl_Button *Font_Size_Style_Clear;
extern Fl_Group *Font_Size_Style_Defined;
extern Fl_Group *Frame_Group;
extern Fl_Button *Frame_Style_Clear;
extern Fl_Group *Frame_Style_Defined;
extern void frame_style_callback(Flv_List_Frame*, void*);
extern Flv_List_Frame *Frame_Style;
extern Fl_Group *Alignment_Group;
extern Fl_Button *Alignment_Style_Clear;
extern Fl_Group *Alignment_Style_Defined;
extern void alignment_style_callback(Flv_List_Alignment*, void*);
extern Flv_List_Alignment *Alignment_Style;
extern Fl_Group *Size_Group;
extern void width_style_callback(Fl_Roller*, void*);
extern Fl_Roller *Width_Style;
extern Fl_Button *Width_Style_Clear;
extern Fl_Group *Width_Style_Value;
extern Fl_Group *Width_Style_Defined;
extern Fl_Group *Height_Style_Defined;
extern void height_style_callback(Fl_Roller*, void*);
extern Fl_Roller *Height_Style;
extern Fl_Button *Height_Style_Clear;
extern Fl_Group *Height_Style_Value;
extern Fl_Group *Misc_Group;
extern Fl_Group *Resizable_Style_Defined;
extern void locked_style_callback(Fl_Check_Button*, void*);
extern Fl_Check_Button *Locked_Style;
extern void resizable_style_callback(Fl_Check_Button*, void*);
extern Fl_Check_Button *Resizable_Style;
extern Fl_Button *Resizable_Style_Clear;
extern Fl_Button *Locked_Style_Clear;
extern Fl_Group *Locked_Style_Defined;
extern Fl_Group *Border_Group;
extern void border_style_callback(Fl_Check_Button*, void*);
extern Fl_Check_Button *Border_Inner_Left_Style;
extern Fl_Check_Button *Border_Inner_Bottom_Style;
extern Fl_Check_Button *Border_Inner_Right_Style;
extern Fl_Check_Button *Border_Top_Style;
extern Fl_Check_Button *Border_Inner_Top_Style;
extern Fl_Check_Button *Border_Right_Style;
extern Fl_Check_Button *Border_Bottom_Style;
extern Fl_Check_Button *Border_Left_Style;
extern Fl_Group *Border_Color_Style_Value;
extern Fl_Button *Border_Color_Style;
extern Fl_Button *Border_Color_Style_Clear;
extern Fl_Group *Border_Color_Style_Defined;
extern Fl_Button *Border_Style_Clear;
extern Fl_Group *Border_Style_Defined;
extern void border_spacing_style_callback(Fl_Roller*, void*);
extern Fl_Roller *Border_Spacing_Style;
extern Fl_Button *Border_Spacing_Style_Clear;
extern Fl_Group *Border_Spacing_Style_Value;
extern Fl_Group *Border_Spacing_Style_Defined;
extern Fl_Group *Style_Type_Defined;
extern Fl_Window *win_table;
extern void table_callback(Flv_TableE*, void*);
extern Flv_TableE *wintable;
extern Fl_Window *win_list;
extern void list_callback(Flv_ListE*, void*);
extern Flv_ListE *winlist;
Fl_Window* make_window();
void init_table();
void init_list();
void row_header_callback(Fl_Check_Button*n, void*);
void row_footer_callback(Fl_Check_Button*n, void*);
void row_divider_callback(Fl_Check_Button *n, void *);
void rows_callback(Fl_Roller *n, void *);
void row_select_callback(Fl_Check_Button *n, void *);
void row_width_callback(Fl_Roller *n, void *);
void col_header_callback(Fl_Check_Button *n, void *);
void col_footer_callback(Fl_Check_Button *n, void *);
void col_divider_callback(Fl_Check_Button *n, void *);
void cols_callback(Fl_Roller *n, void *);
void vertical_callback(Fl_Check_Button *n, void*);
void horizontal_callback(Fl_Check_Button *n, void *);
void always_callback(Fl_Check_Button *n, void *);
void multi_select_callback(Fl_Check_Button *n, void *);
void persist_select_callback(Fl_Check_Button *n, void *);
void table_callback(Flv_TableE *n, void *);
void list_callback(Flv_ListE *n, void *);
void style_type_callback( Flv_List2 *n, void *);
void full_resize_callback(Fl_Check_Button *n, void *);
void style_section_callback(Flv_List_Style_Section *n, void *);
void change_style_group( int style, bool visible );
Flv_Style * read_table_style();
Flv_Style * write_table_style();
Flv_Style * read_list_style();
Flv_Style * write_list_style();
void font_size_callback(Fl_Roller *n, void *);
void font_style_callback(Flv_List_Font *n, void *);
void frame_style_callback(Flv_List_Frame *n, void *);
void alignment_style_callback(Flv_List_Alignment *n, void *);
void width_style_callback(Fl_Roller *n, void *);
void height_style_callback(Fl_Roller *n, void *);
void locked_style_callback(Fl_Check_Button *n, void *);
void resizable_style_callback(Fl_Check_Button *n, void *);
void border_style_callback( Fl_Check_Button *, void *);
void border_spacing_style_callback(Fl_Roller *n, void *);
void Foreground_callback(Fl_Button *, void *);
void update_style_info(void);
#endif