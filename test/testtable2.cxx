//	======================================================================
//	File:    testtable2.cxx
//	Program: testtable2
//	Version: 0.1.0
//	Started: 11/21/99
//
//	Copyright (C) 1999 Laurence Charlton
//
//	Description:
//	Example of using an Flv_Table with dynamic column widths.
//	This will also demonstrate mixed styling (dynamic and virtual)
//	======================================================================

#include <FL/Flv_Table.H>
#include <FL/Fl_Window.H>
#include <FL/fl_draw.H>
#include <stdio.h>
#include <string.h>

//	Demonstrate Simplest Fl_List_Child
class Flv_Table_Child : public Flv_Table
{
public:
	Flv_Table_Child( int X, int Y, int W, int H, const char *l=0 ) :
		Flv_Table(X,Y,W,H,l) {};
	virtual void draw_cell( int Offset, int &X, int &Y, int &W, int &H, int R, int C );
	void get_style( Flv_Style &s, int R, int C );
	virtual int col_width( int C );
};

char *val[12][5] =
{
	{ "",									"",				"",					"Total",		"$213.23"	},
	{ "Name",							"Male",		"Phone",		"Meet",				"Due"	},
	{	"Smith, John", 			"Male", 	"555-1212", "05/14/1999", "$50.00" },
	{	"Jet, Joan", 				"Female", "234-1234", "12/22/1999", "$25.75" },
	{	"Frampton, Peter", 	"Male", 	"324-8723", "09/17/1999", "$35.22" },
	{	"Ozborne, Ozzy", 		"Male", 	"545-8273", "04/05/1999", "$84.72" },
	{	"Person, Test", 		"Male", 	"563-2938", "08/04/1999", "$38.83" },
	{	"Clairborne, Liz", 	"Female", "723-9382", "03/17/1999", "-$61.34" },
	{	"Curie , Madam", 		"Female", "234-7382", "02/23/1999", "$22.43" },
	{	"Benetar, Pat", 		"Female", "121-2837", "06/09/1999", "$14.18" },
	{	"Krull, Diane", 		"Female", "345-2384", "01/11/2000", "-$68.88" },
	{	"Simpson, Bart", 		"Male", 	"928-1342", "07/23/1999", "$72.32" }
};

char *get_value( int R, int C )
{
	return val[R+2][C];
}

//	Note: This is so flexible, you don't *have* to use style
//	if you'd rather program the conditions...
void Flv_Table_Child::get_style( Flv_Style &s, int R, int C )
{
	const char *st;
	
	Flv_Table::get_style(s,R,C);					//	Get standard style
	if (R<0)															//	Heading/Footing is bold
		s.font( (Fl_Font)(s.font()+FL_BOLD));
	if (R==-2)														//	Row footer exception
	{	s.background( FL_BLACK );						//	Black background
		s.foreground( FL_WHITE );						//	White text
		s.frame( FL_FLAT_BOX );							//	No box
		s.align(FL_ALIGN_RIGHT);						//	Right aligned
	}
	if (R>-1 && C>-1 && (R%2)==0 && C<4 )				//	Highlight every other row
		s.background( (Fl_Color)(FL_GRAY_RAMP+21) );
	st = get_value(R,C);
	if (st)
	if (strstr(st,"-$"))	//	Negative $ are RED
  {
  	s.border(FLVB_OUTER_ALL);						//	Nice dark box
		s.foreground(FL_RED);								//	Text in red
   s.background(Fl_Color(215));									//	Pale yellow background
  }
}

#define SZ 5

void Flv_Table_Child::draw_cell( int Offset, int &X, int &Y, int &W, int &H, int R, int C )
{
	Flv_Style s;
  int x, y, w, h;

	get_style(s,R,C);
	Flv_Table::draw_cell(Offset,X,Y,W,H,R,C);

  //	Draw an X
  if (C==1 && R>-1)
	{
		if (*get_value(R,C)=='M')
			fl_draw_symbol("@circle", X-Offset+(W-SZ)/2, Y+(H-SZ)/2, SZ,
											SZ, (Fl_Color)(FL_GRAY_RAMP+16) );
	} else
		fl_draw(get_value(R,C), X-Offset, Y, W, H, s.align() );
}

static int cw[10];	//	Column width
//	Another way would be to override handle for FL_SIZE.  We could also
//	spend a lot of time setting styles for the columns and returning
//	that, but since we're calculating it anyway, why bother.
int Flv_Table_Child::col_width( int C )
{
	static int LW=-1;
	int scrollbar_width = (scrollbar.visible()?scrollbar.w():0);
	int W = w()- scrollbar_width-1;
	int ww, t;

	//	Either always calculate or be sure to check that width
	//	hasn't changed.
	if (W!=LW)							//	Width change, recalculate
	{
		cw[0] = (W*30)/100;		//	30		Name
		cw[1] = (W*15)/100;		//	10		Gender
		cw[2] = (W*20)/100;		//	 5%		Phone
		cw[3] = (W*20)/100;		//	15%		Date
		for (ww=0, t=0;	t<4;	t++ )
		{
			ww += cw[t];
		}
		cw[4] = W-ww-1;	 				//	~30% +/- previous rounding errors
		LW = W;
	}
	return cw[C];
}

int main(int argc, char **argv)
{
	Fl_Window *w = new Fl_Window( 432, 255, "Dynamic row size example" );
	Flv_Table_Child *l = new Flv_Table_Child( 10, 10, 412, 235, "Current Appointments" );
	w->end();

	w->resizable(l);
  //	row height (17) * rows (10) +
  //	row height headers (17+4) * number of headers (3) +
  //	Top/Bottom box margins (2)

	//	Comment/or uncomment any of these lines to see the result
	l->rows(10);
	l->cols(5);
	l->has_scrollbar(FLVS_VERTICAL);
	l->feature(FLVF_ROW_ENDS|FLVF_ROW_SELECT);
	l->global_style.align(FL_ALIGN_LEFT);		//	Left alignment
	l->global_style.height(17);

	l->col_style[4].border_color(FL_BLACK);		//	Black line
	l->col_style[4].border(FLVB_LEFT);				//	On left of last column
  l->col_style[4].background((Fl_Color)(93));						//	Orange background? :)

	//	Have to align something differently! :)
	l->col_style[1].align(FL_ALIGN_CENTER);		//	Gender
	l->col_style[4].align(FL_ALIGN_RIGHT);		//	Amount

	//	We have a created 3 styles at this point, besides of course
	//	global_style, row_style, col_style, and the cell_style in our
	//	one row_style.
  w->end();
	w->show(argc, argv);
	return Fl::run();
}
