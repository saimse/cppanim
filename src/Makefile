src_files = dummy

# TODO(milevuletic): implement src makefile
all: public $(src_files)
	$(CPP) $(LINKFLAGS)
	@echo "Done!"

.PHONY: public
public:
	$(CPP) $(CFLAGS) -c $(include_dir)/cppanim.h

$(src_files):
	$(CPP) $(CFLAGS) -c $(@F).cpp -o $(obj_dir)/$(@F).o
