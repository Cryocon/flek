//	======================================================================
//	File:    testlist.cxx
//	Program: testlist
//	Version: 0.1.0
//	Started: 11/21/99
//
//	Copyright (C) 1999 Laurence Charlton
//
//	Description:
//	Example of using an Flv_List
//	======================================================================

#include <FL/Flv_List.H>
#include <FL/Fl_Window.H>
#include <FL/fl_draw.H>
#include <stdio.h>
#include <string.h>

//	Demonstrate Simplest Flv_List_Child
class Flv_List_Child : public Flv_List
{
public:
	Flv_List_Child( int X, int Y, int W, int H, const char *l=0 ) :
		Flv_List(X,Y,W,H,l) {};
	void draw_row( int Offset, int &X, int &Y, int &W, int &H, int R );
	void get_style( Flv_Style &s, int R, int C=0 );
};

void Flv_List_Child::get_style( Flv_Style &s, int R, int )
{
	Flv_List::get_style(s, R);
	if (R>-1 && (R%2)==0 )
		s.background( Fl_Color(FL_GRAY_RAMP+22) );
}

void Flv_List_Child::draw_row( int Offset, int &X, int &Y, int &W, int &H, int R )
{
	Flv_Style s;

	get_style( s, R );

	Flv_List::draw_row( Offset, X, Y, W, H, R );
	//	Draw Headers/Footers
	if (R<0)
		fl_draw((R==-1?"Header":"Footer"), X+1-Offset, Y+1, W-2, H-2, s.align() );
	else
	{
		char buf[50];
		sprintf( buf, " %d", R );
		strcat(buf,"     *-*-*-*-*-*-*-*-");
		fl_draw(buf, X+1-Offset, Y+1, W-2, H-2, s.align() );
	}
}


int main(int argc, char **argv)
{
	Fl_Window *w = new Fl_Window( 200, 200, "Test list" );
	Flv_List_Child *l = new Flv_List_Child( 10, 10, 180, 180 );
	w->end();

	w->resizable(l);

	l->rows(20);
	l->has_scrollbar(FLVS_BOTH);
	l->row_width(200);
	l->feature(FLVF_ALL_ROW|FLVF_MULTI_SELECT);

  l->global_style.resizable(true);
	l->global_style.align(FL_ALIGN_CLIP);
//  l->global_style.border(FLVB_RIGHT|FLVB_BOTTOM);

	w->show(argc, argv);
	return Fl::run();
}
