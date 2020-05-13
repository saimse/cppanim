files = $(obj_dir)/testsuite.o $(obj_dir)/tester.o

$(bin_dir)/test: $(files)
	@mkdir $(obj_dir)/test -p
	$(CPP) -fopenmp -Wl,-rpath,. -L$(bin_dir) -lcppanim $^ -o $@

$(obj_dir)/%.o: $(notdir %.cpp)
	$(CPP) -c -o $(obj_dir)/$(@F) $< $(CFLAGS)

%.cpp: testsuite.hpp
