include ../makeinclude

ALL = calendar stock_buttons docking toggle_tree \
	testlist testtable testtable2 basiclist testedit testcombo \
	socket time
# excercise

ifdef GL_LIB
	ALL += arcball image
endif

ifdef XML_LIB
	ALL += fxml
endif

all: $(ALL)

CORECOMPILE=`../flek-config --use-core --cxxflags` -g3
CORELINK=`../flek-config --use-core --ldflags`

UICOMPILE=`../flek-config --use-ui --cxxflags` -g3
UILINK=`../flek-config --use-ui --ldflags`

IMGCOMPILE=`../flek-config --use-ui --use-jpeg --cxxflags` -g3
IMGLINK=`../flek-config --use-ui --use-jpeg --ldflags`

GLCOMPILE=`../flek-config --use-gl --cxxflags`
GLLINK=`../flek-config --use-gl --ldflags`

arcball: arcball.cxx
	$(CXX) $(GLCOMPILE) $@.cxx $(GLLINK) -o $@

calendar: calendar.cxx
	$(CXX) $(UICOMPILE) $@.cxx $(UILINK) -lstdc++ -o $@

time: time.cxx
	$(CXX) $(UICOMPILE) $@.cxx $(UILINK) -lstdc++ -o $@

image: image.cxx
	$(CXX) -g3 $(IMGCOMPILE) $@.cxx $(IMGLINK) -ljpeg -o $@

stock_buttons: stock_buttons.cxx
	$(CXX) $(UICOMPILE) $@.cxx $(UILINK) -o $@

docking: docking.cxx
	$(CXX) $(UICOMPILE) $@.cxx $(UILINK) -o $@

toggle_tree: toggle_tree.cxx
	$(CXX) $(UICOMPILE) $@.cxx $(UILINK) -o $@

testlist: testlist.cxx
	$(CXX) $(UICOMPILE) $@.cxx $(UILINK) -o $@

testcombo: testcombo.cxx
	$(CXX) $(UICOMPILE) $@.cxx $(UILINK) -o $@

testtable: testtable.cxx
	$(CXX) $(UICOMPILE) $@.cxx $(UILINK) -o $@

testtable2: testtable2.cxx
	$(CXX) $(UICOMPILE) $@.cxx $(UILINK) -o $@

basiclist: basiclist.cxx
	$(CXX) $(UICOMPILE) $@.cxx $(UILINK) -o $@

exercise: exercise.cxx
	$(CXX) $(UICOMPILE) $@.cxx $(UILINK) -o $@

testedit: testedit.cxx
	$(CXX) $(UICOMPILE) $@.cxx $(UILINK) -o $@

socket: socket.cxx
	$(CXX) $(CORECOMPILE) $@.cxx $(CORELINK) -o $@

fxml: fxml.cxx
	$(CXX) `../flek-config --use-xml --cxxflags` -g3 $@.cxx `../flek-config --use-xml --ldflags` -o $@

clean:
	rm -f core *.o calendar stock_buttons docking toggle_tree \
	testlist testtable testtable2 basiclist exercise testedit \
	arcball image fxml testcombo socket

install:
