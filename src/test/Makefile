files = $(obj_dir)/testsuite.o $(obj_dir)/tester.o

$(bin_dir)/test: $(files)
	@mkdir $(obj_dir)/test -p
	$(CPP) -fopenmp -Wl,-rpath,. $^ -o $@ -L$(bin_dir) -lcppanim

$(obj_dir)/%.o: $(notdir %.cpp)
	$(CPP) -c -o $@ $< $(CFLAGS) -Wall

%.cpp: testsuite.hpp
