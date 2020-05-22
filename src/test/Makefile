files = testsuite tester
objects = $(addprefix $(obj_dir)/, $(addsuffix .o,$(files)))

$(bin_dir)/test: $(objects)
	@mkdir $(obj_dir)/test -p
	$(CPP) -fopenmp -Wl,-rpath,. $^ -o $@ -L$(bin_dir) -lcppanim

$(obj_dir)/%.o: $(notdir %.cpp)
	$(CPP) -fopenmp -c -o $@ $< $(CFLAGS) -Wall

%.cpp: testsuite.hpp
