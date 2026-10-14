PROJECT_NAME=Ccode

SDK_DIR = $(PWD)/../repo_tools
REPO_LIBS_PREFIX = $(PWD)/../repo_libs
INCLUDES = -I$(BUILD_DIR)/lib/out
CFLAGS = $(INCLUDES) -g -std=c++20

BUILD_DIR = $(PWD)/build
OUT_DIR = $(BUILD_DIR)/out

x86_64_CC=gcc
x86_64_CPP=g++
x86_64_AR=ar
x86_64_LD=g++
x86_64_CFLAGS=
x86_64_LDFLAGS=


x86_64_OBJ_DIR = $(BUILD_DIR)/obj/x86_64
x86_64_OUT = $(OUT_DIR)/$(PROJECT_NAME).x86_64

#libraries
LIB_openGL=openGL
LIB_lib_imgui=lib_imgui

#source directory
SRC_src = src

SRC =
#source directory
SRC += $(wildcard $(SRC_src)/*.c)
SRC += $(wildcard $(SRC_src)/*.cpp)

x86_64_LIB =
#architecture
x86_64_LIB += $(BUILD_DIR)/lib/out/openGL.x86_64.a
x86_64_LIB += $(BUILD_DIR)/lib/out/lib_imgui.x86_64.a

#architecture
all: $(x86_64_OUT)


#architecture and source directory
$(x86_64_OBJ_DIR)/$(SRC_src)/%.o: $(SRC_src)/%.c | lib_headers
	@mkdir -p $(x86_64_OBJ_DIR)/$(SRC_src)
	$(x86_64_CC) $(x86_64_CFLAGS) $(CFLAGS) -c $^ -o $@

$(x86_64_OBJ_DIR)/$(SRC_src)/%.o: $(SRC_src)/%.cpp | lib_headers
	@mkdir -p $(x86_64_OBJ_DIR)/$(SRC_src)
	$(x86_64_CPP) $(x86_64_CFLAGS) $(CFLAGS) -c $^ -o $@



#architecture
x86_64_OBJ = $(patsubst %.cpp, $(x86_64_OBJ_DIR)/%.o, $(patsubst %.c, $(x86_64_OBJ_DIR)/%.o, $(SRC)))
$(x86_64_OUT): $(x86_64_OBJ) $(x86_64_LIB)
	@mkdir -p $(OUT_DIR)
	$(x86_64_LD) $(CFLAGS) $(LDFLAGS) $(x86_64_CFLAGS) $(x86_64_LDFLAGS) -o $@ $(x86_64_OBJ) $(x86_64_LIB)
	@echo "\033[0;32m$(PROJECT_NAME).x86_64 built\033[0m"


#architecture and libraries
$(x86_64_LIB): lib_headers
	@CC=$(x86_64_CC) \
	CPP=$(x86_64_CPP) \
	AR=$(x86_64_AR) \
	LD=$(x86_64_LD) \
	CFLAGS=$(x86_64_CFLAGS) \
	BUILD_DIR=$(PWD)/build/lib/$(LIB_openGL) \
	OUT_DIR=$(PWD)/build/lib/out \
	ARCH=x86_64 \
	$(MAKE) -C $(REPO_LIBS_PREFIX)/$(LIB_openGL)/
	@CC=$(x86_64_CC) \
	CPP=$(x86_64_CPP) \
	AR=$(x86_64_AR) \
	LD=$(x86_64_LD) \
	CFLAGS=$(x86_64_CFLAGS) \
	BUILD_DIR=$(PWD)/build/lib/$(LIB_lib_imgui) \
	OUT_DIR=$(PWD)/build/lib/out \
	ARCH=x86_64 \
	$(MAKE) -C $(REPO_LIBS_PREFIX)/$(LIB_lib_imgui)/


#libraries
lib_headers:
	@OUT_DIR=$(PWD)/build/lib/out \
	$(MAKE) -C $(REPO_LIBS_PREFIX)/$(LIB_openGL)/ headers
	@OUT_DIR=$(PWD)/build/lib/out \
	$(MAKE) -C $(REPO_LIBS_PREFIX)/$(LIB_lib_imgui)/ headers
