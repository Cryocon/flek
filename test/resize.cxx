#include <FL/Fl_Window.H>
#include <FL/Flv_Table.H>

#include <FL/Enumerations.H>
#include <FL/fl_draw.H>

#define FUDGE 2
#define MOVE_X 1
#define MOVE_Y 2
#define MOVE_XY (MOVE_X|MOVE_Y)

class Flv_Resize : public Flv_Table
{
public:
	Flv_Resize( int x, int y, int w, int h, const char *l=0 ):
		Flv_Table(x,y,w,h) {};
	int handle(int event);
private:
	void check_cursor(void);
	void check_resize(void);
};

static Fl_Cursor last_cursor = FL_CURSOR_DEFAULT;
static drag_col=-4, drag_row=-4, anchor_left, anchor_top;

void Flv_Resize::check_resize(void)
{
	int ex, ey;
	ex = Fl::event_x();
	ey = Fl::event_y();

	if (drag_col>-4)
	{
		if (ex>anchor_left+1)
		{
			col_style[drag_col].width(ex-anchor_left);
			damage(FL_DAMAGE_CHILD);
		}
	}
	if (drag_row>-4)
	{
		if (ey>anchor_top+1)
		{
			row_style[drag_row].height(ey-anchor_top);
			damage(FL_DAMAGE_CHILD);
		}
	}
}

//	See if we can resize, if so change cursor
void Flv_Resize::check_cursor(void)
{
	int X, Y, W, H, R, ey, ex, move=0, WW, size;
	int v;
	Fl_Cursor cursor;

	ex = Fl::event_x();
	ey = Fl::event_y();
	client_area(X,Y,W,H);

	if (label() && *label())
	{
		Y+=row_height(-3);
		H-=row_height(-3);
	}

	if (col_header())
	{
		if ((ey>=Y && ey<=Y+row_height(-1)) || full_resize())	//	Trival test first
		{
			WW = X;
			if (row_header())
			{
				size = col_width(-1);
				if (ex>=WW+size-FUDGE && ex<=WW+size+FUDGE)
				{
					if (!col_resizable(-1))
					{
						drag_col = -1;
						anchor_left = WW;
						move |= MOVE_X;
					}
				}
				WW += size;
				X += size;
				W -= size;
			}
			if ( (move & MOVE_X)==0 )
			{
				R = X-row_offset()+row_width()+FUDGE;		//	Right edge of row
				for (WW-=row_offset(), v=0;	WW<R && WW<X+W && v<cols();	WW+=size, v++ )
				{
					size = col_width(v);
					if (WW+size<X)		//	Off left
						continue;
					if (ex>=WW+size-FUDGE && ex<=WW+size+FUDGE)
					{
						if (!col_locked(v))
						{
							drag_col = v;
							anchor_left = WW;
							move |= MOVE_X;		//	Moving col
						}
						break;
					}
					if (col_divider())
						size++;
				}
			}
			if (row_header())
			{
				X-=col_width(-1);
				W+=col_width(-1);
			}
		}
	}

	if (row_header())
	{
		if ((ex>=X && ex<=X+col_width(-1)) || full_resize())	//	Trival test first
		{
			WW = Y;
			if (col_header())
			{
				size = row_height(-1);
				if (ey>=WW+size-FUDGE && ey<=WW+size+FUDGE)
				{
					if (!row_locked(-1))
					{
						drag_row = -1;
						anchor_top = WW;
						move |= MOVE_Y;
					}
				}
				WW += size;
				Y += size;
				H -= size;
			}
			if ( (move & MOVE_Y)==0 )
				for (v=top_row();	v<rows();	WW+=size, v++ )
				{
					size = row_height(v);
					if (WW+size+FUDGE>=Y+H)
						break;
					if (ey>=WW+size-FUDGE && ey<=WW+size+FUDGE)
					{
						if (!row_locked(v))
						{
							drag_row = v;
							anchor_top = WW;
							move |= MOVE_Y;		//	Moving
						}
						break;
					}
					if (row_divider())
						size++;
				}
		}
	}

	switch( move )
	{
		case MOVE_X:	cursor = FL_CURSOR_WE;		  break;
		case MOVE_Y:	cursor = FL_CURSOR_NS;			break;
		case MOVE_XY:	cursor = FL_CURSOR_NWSE;		break;
		default:
			drag_row = drag_col = -4;
			cursor = FL_CURSOR_DEFAULT;
			break;
	}
	if (cursor!=last_cursor)
	{
		fl_cursor(cursor,FL_BLACK,FL_WHITE);
		last_cursor = cursor;
	}
}

int Flv_Resize::handle(int event)
{

	switch( event )
	{
		case FL_PUSH:
		case FL_RELEASE:
			Flv_Table::handle(event);
			return 1;

		case FL_DRAG:	//	Dragging
			check_resize();
			break;

		case FL_MOVE:	//	Mouse moving
			check_cursor();
			break;
	}
	return Flv_Table::handle(event);
}

main(int argc, char *argv[])
{
	Fl_Window *w = new Fl_Window( 200, 200, "Test resize" );
	Flv_Resize *l = new Flv_Resize( 10, 10, 180, 180, "Sample Resize View" );
	w->resizable(l);

	l->label("Sample Resize View");
	l->rows(10);
	l->cols(10);
	l->col_width(0,50);
	l->feature(FLVF_HEADERS|FLVF_DIVIDERS|FLVF_MULTI_SELECT|FLVF_FULL_RESIZE);

	l->row_style[-1].align(FL_ALIGN_CLIP);
	l->row_locked(true,-1);

	l->col_style[-1].align(FL_ALIGN_CLIP);
	l->col_locked(true,-1);

	l->global_style.locked(false);

	w->show(argc, argv);
	return Fl::run();
}

