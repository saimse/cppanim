objdir = $(obj_dir)/utils/demos
files = singleAnimation

binfiles = $(addprefix $(bin_dir)/, $(files))
objects = $(addprefix $(objdir)/, $(addsuffix .o,$(files)))

.PHONY: all
all: dirstruct $(binfiles)

$(binfiles): $(objects)
	$(CPP) -Wl,-rpath,. -o $@ \
        $(addprefix $(objdir)/,$(addsuffix .o,$(@F))) -L$(bin_dir) -lcppanim

.PHONY: dirstruct
dirstruct:
	@$(MKDIRCMD) $(objdir)

$(objdir)/%.o: $(notdir %.cpp)
	$(CPP) -c -o $@ $< $(CFLAGS) -Wall
