TARGET = Ofes

CPPFILES  = $(wildcard ./src/*.cpp)
CPPFILES += $(wildcard ./src/**/*.cpp)
CPPFILES += $(wildcard ./src/**/**/*.cpp)

CFILES  = $(wildcard ./src/*.c)
CFILES += $(wildcard ./src/**/*.c)
CFILES += $(wildcard ./src/**/**/*.c)

OBJS = $(CPPFILES:.cpp=.o) $(CFILES:.c=.o)

export OBJS = $(CFILES:.c=.o) $(CPPFILES:.cpp=.o)

#---------------------------------------------------------------------------------
## Any other build targets you want to add
#---------------------------------------------------------------------------------
#OBJS += logo.o

CDEPS = $(CFILES:.c=.d)
CPPDEPS += $(CPPFILES:.cpp=.d)
DEPS = $(CDEPS) $(CPPDEPS)

BUILD_PRX=1

INCDIR = ./include
CFLAGS = -G0 -Wall
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

PSP_LARGE_MEMORY=1
PSP_FW_VERSION=371

LIBDIR =
LDFLAGS =
LIBS= -lm -lstdc++ -lsqlite3 -lpspgu -lpspgum_vfpu -lpspvfpu

EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = $(TARGET)


export PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak


#---------------------------------------------------------------------------------
# Rules for building cpp files (if you have them)
#---------------------------------------------------------------------------------
%.o: %.cpp
	@echo $(notdir $<)
	$(CXX) -MMD -MP -MF $*.d $(CXXFLAGS) -c $< -o $@
	
#---------------------------------------------------------------------------------
#  Rules for building c files if you have them
#---------------------------------------------------------------------------------
%.o:  %.c
	@echo $(notdir $<)
	$(CC) -MMD -MP -MF $*.d $(CFLAGS) -c $< -o $@


-include $(DEPS)


#---------------------------------------------------------------------------------
#   Maybe for a logo/image target, you could use something like this
#---------------------------------------------------------------------------------
#logo.o: logo.raw
#	bin2o -i logo.raw logo.o logo

#---------------------------------------------------------------------------------
#   Get rid of all the intermediary makefiles (.d files)
#---------------------------------------------------------------------------------
clean-deps:
	-rm $(DEPS)

#---------------------------------------------------------------------------------
#   Clean Deps and all object files
#---------------------------------------------------------------------------------
clean-all: clean-deps clean



#---------------------------------------------------------------------------------
#  Maybe use this target if you have usbhostfs_pc running and want to use
#    psplink
#---------------------------------------------------------------------------------
run:
	pspsh -e $(PWD)/EBOOT

