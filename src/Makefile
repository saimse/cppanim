files = animation frame fundamentals diffbuff screen symbol focusable focusController mixin

objects = $(addprefix $(obj_dir)/, $(addsuffix .o,$(files)))

# TODO(milevuletic): implement src makefile
$(bin_dir)/$(sofilename): $(objects)
	$(CPP) $(CFLAGS) -shared $^ -o $(bin_dir)/$(sofilename)
	@echo "Done!"

$(obj_dir)/%.o: $(notdir %.cpp)
	$(CPP) -c -o $(obj_dir)/$(@F) $< $(CFLAGS)

%.cpp: %.hpp
