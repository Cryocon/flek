#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <Flek/Flve_Combo.H>

int main(int argc, char **argv) {
  Fl_Window* w;
  { Fl_Window* o = new Fl_Window(254, 200);
    w = o;
		{ Flve_Combo* o = new Flve_Combo(100, 25, 90, 25, "label");
			o->list_title("Numbers");
		  o->item.add("Eight", 8);
		  o->item.add("One",1);
		  o->item.add("Five", 5);
		  o->item.add("Three", 3);
		  o->item.add("Ten", 10);
		  o->item.add("Six", 6);
		  o->item.add("Seven", 7);
		  o->item.add("Nine", 9);
		  o->item.add("Two", 2);
		  o->item.add("Four", 4);
		  o->align(FL_ALIGN_LEFT);
		  o->list_only (false);
		  o->item.sort();
		}
		{ Flve_Combo* o = new Flve_Combo(100, 60, 90, 25, "label");
			o->item.add("Male", 'M');
			o->item.add("Female", 'F' );
			o->align(FL_ALIGN_LEFT);
		}
		{ Fl_Input* o = new Fl_Input(100, 90, 90, 25, "label");
			o->align(FL_ALIGN_LEFT);
		}
		{ Fl_Input* o = new Fl_Input(100, 120, 90, 25, "label");
			o->align(FL_ALIGN_LEFT);
		}
		o->end();
	}
  w->show(argc, argv);
  return Fl::run();
}
