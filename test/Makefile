include ../makeinclude

all: arcball calendar stock_buttons dockable_group toggle_tree image \
	fxml testlist testtable testtable2 basiclist exercise testedit 

UICOMPILE=`../flek-config --use-ui --cxxflags` -g3
UILINK=`../flek-config --use-ui --ldflags` 

GLCOMPILE=`../flek-config --use-gl --cxxflags`
GLLINK=`../flek-config --use-gl --ldflags`

arcball: arcball.cxx
	$(CXX) $(GLCOMPILE) $@.cxx $(GLLINK) -o $@

calendar: calendar.cxx
	$(CXX) $(UICOMPILE) $@.cxx $(UILINK) -o $@

image: image.cxx
	$(CXX) -g3 $(GLCOMPILE) $@.cxx $(GLLINK) -ljpeg -o $@

stock_buttons: stock_buttons.cxx
	$(CXX) $(UICOMPILE) $@.cxx $(UILINK) -o $@

dockable_group: dockable_group.cxx
	$(CXX) $(UICOMPILE) $@.cxx $(UILINK) -o $@

toggle_tree: toggle_tree.cxx
	$(CXX) $(UICOMPILE) $@.cxx $(UILINK) -o $@

testlist: testlist.cxx
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

fxml: fxml.cxx
	$(CXX) `../flek-config --use-xml --cxxflags` -g3 $@.cxx `../flek-config --use-xml --ldflags` -o $@

clean:
	rm -f core *.o toggle_tree dockable_group bitmaps filedialog \
	arcball calendar frametab pixbutton slider pixbutton packfu wtest wtest2 stock_buttons \
	testlist testtable testtable2 basiclist exercise testedit fdom

install:
