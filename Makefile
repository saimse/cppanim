submodules = test src utils

root_dir = $(realpath .)
src_dir = $(root_dir)/src
test_dir = $(src_dir)/test
obj_dir = $(root_dir)/obj
utils_dir = $(root_dir)/utils
bin_dir = $(root_dir)/bin
include_dir = $(root_dir)/include
docs_dir = $(root_dir)/docs

sofilename :=
RMCMD :=
MKDIRCMD := mkdir 

CPP = g++

BUILDFLAGS = -I$(include_dir) -lpthread

ifeq ($(OS),Windows_NT)
# Necessary for pthreads to work under MinGW
	OSFLAG += -Wl,-Bstatic -lpthread -Wl,-Bdynamic -w
	sofilename = libcppanim.dll

	RMCMD = rd /S /Q

	LINKFLAGS += -shared -Wl,--out-implib,$(bin_dir)/$(sofilename).a -o $(bin_dir)/$(sofilename)

	ifeq ($(PROCESSOR_ARCHITECTURE),AMD64)
		OSFLAG += -m64
	endif
	ifeq ($(PROCESSOR_ARCHITECTURE),x86)
		OSFLAG += -m32
	endif
else
	sofilename = libcppanim.so
	RMCMD = rm -rf
	MKDIRCMD += -p
	LINKFLAGS += -o $(bin_dir)/$(sofilename)
	UNAME_P := $(shell uname -p)
	ifeq ($(UNAME_P),x86_64)
		OSFLAG += -m64
	endif
	ifneq ($(filter %86,$(UNAME_P)),)
		OSFLAG += -m32
	endif
endif
LINKFLAGS += -shared $(obj_dir)/*.o

override CFLAGS += $(OSFLAGS) $(BUILDFLAGS) -fPIC -O2

# cppanim is an alias for src
.PHONY: cppanim
cppanim: src

debug: CFLAGS += -O0 -g
debug: cleanso src

test: debug

all: $(submodules)

# Utils are built with the library, hence the dependency
utils: cppanim

.PHONY: cleanso
cleanso:
	$(RMCMD) $(bin_dir)/$(sofilename)

.PHONY: clean
clean:
	$(RMCMD) $(bin_dir)/*
	$(RMCMD) $(obj_dir)/*

.PHONY: cleandocs
cleandocs:
	$(RMCMD) $(docs_dir)/output/*

.PHONY: mrproper
mrproper: clean cleandocs

.PHONY: $(submodules)
export CFLAGS
export BUILDFLAGS
export LINKFLAGS
export CPP
export obj_dir
export bin_dir
export include_dir
export root_dir
export sofilename
export RMCMD
export MKDIRCMD
$(submodules):
	@echo [INFO] Building submodule $(@F)...
	@"$(MAKE)" -C $($(@F)_dir)

###################################################

.PHONY: docs
docs:
	@echo TODO(milevuletic): Implement docs build system

.PHONY: help
help:
	@echo 
	@echo cppanim is a standalone console animation library.
	@echo Available build targets are:
	@echo 
	@echo   cppanim: Builds the library into bin/
	@echo   utils: Builds util programs to aid with development
	@echo   test: Builds and runs the entire test suite
	@echo   all: Builds cppanim, utils and test
	@echo   docs: Builds documentation into docs/
	@echo   help: Prints this help screen
	@echo 
	@echo The following clean operations are available:
	@echo 
	@echo   clean: Deletes bin/ output
	@echo   cleandocs: Deletes generated documentation
	@echo   mrproper: Deletes everything built
	@echo 
