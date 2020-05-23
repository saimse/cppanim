submodules = demos

.PHONY: all
all: $(submodules)
	@echo Done!

export CFLAGS
export CPP
export obj_dir
export bin_dir
export include_dir
export root_dir
export sofilename
export RMCMD
export MKDIRCMD
.PHONY: $(submodules)
$(submodules):
	@echo Building $(@F)
	@"$(MAKE)" -C $(@F)

demos: CFLAGS += -O0 -g
