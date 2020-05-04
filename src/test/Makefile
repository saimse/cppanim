src_files = testsuite tester

# TODO(milevuletic): implement test suite makefile
all: prepare $(src_files)
	$(CPP) -fopenmp -Wl,-rpath,. -L$(bin_dir) -lcppanim $(obj_dir)/test/*.o -o $(bin_dir)/test
	@cd $(bin_dir)
#test

.PHONY: prepare
prepare:
	@mkdir $(obj_dir)/test -p

#.PHONY: $(src_files)
$(src_files):
	$(CPP) -fopenmp -L$(bin_dir) -lcppanim $(BUILDFLAGS) -c $(@F).cpp -o $(obj_dir)/test/$(@F).o
