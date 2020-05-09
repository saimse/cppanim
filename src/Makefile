files = $(obj_dir)/animation.o $(obj_dir)/frame.o $(obj_dir)/fundamentals.o

# TODO(milevuletic): implement src makefile
$(bin_dir)/$(sofilename): $(files)
	$(CPP) $(CFLAGS) -shared $^ -o $(bin_dir)/$(sofilename)
	@echo "Done!"

%.o: $(notdir %.cpp)
	$(CPP) -c -o $(obj_dir)/$@ $< $(CFLAGS)
