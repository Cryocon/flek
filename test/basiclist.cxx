#include <FL/Flv_List.H>
#include <FL/Fl_Window.H>
#include <FL/fl_draw.H>

// These will be the 10 values we display in the list
char *values[] = {"1","2","3","4","5","6","7","8","9","10" };

class My_Flv_List : public Flv_List
{
public:
	My_Flv_List(int X, int Y, int W, int H, const char *l=0 ) :
		Flv_List(X,Y,W,H,l) {};
	void draw_row( int Offset, int &X, int &Y, int &W, int &H, int R );
};

void My_Flv_List::draw_row( int Offset, int &X, int &Y, int &W, int &H, int R )
{
	Flv_Style s;

	get_style( s, R );
	Flv_List::draw_row( Offset, X, Y, W, H, R );
	fl_draw(values[R], X+1-Offset, Y+1, W-2, H-2, s.align() );
}

int main(int argc, char **argv)
{
	Fl_Window *w = new Fl_Window( 200, 173, "Basic List" );
	My_Flv_List *l = new My_Flv_List( 10, 10, 180, 153 );
	w->end();

	w->resizable(l);           							// List resizable
	l->rows(10);               							// List has 10 rows
	l->has_scrollbar(FLVS_VERTICAL); 				// Automatic vertical scroll bar

	l->global_style.align(FL_ALIGN_CLIP); 	// Center text

	w->show(argc, argv);        						// Show main window
	return Fl::run();     									// Run program
}

