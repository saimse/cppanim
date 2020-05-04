src_files = dummy

# TODO(milevuletic): implement src makefile
all: $(src_files)
	$(CPP) $(LINKFLAGS)
	@echo "Done!"

.PHONY: public
public:
	$(CPP) $(CFLAGS) -c $(include_dir)/cppanim.hpp

$(src_files):
	$(CPP) $(CFLAGS) -c $(@F).cpp -o $(obj_dir)/$(@F).o
