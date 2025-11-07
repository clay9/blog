CXX = g++
CXXINCLUDE =
CXXLIB =
CXXFLAGS = -g -O2 -std=c++20 -W -Wall -Wl,--as-needed $(CXXINCLUDE) $(CXXLIB)

# 输出打印
SHOW_COMPILE = @echo "\033[36mCompling \033[35m==> \033[33m$<\033[0m"
SHOW_LINK    = @echo "\033[31mLINKING \033[35m==> \033[33m$@\033[0m"

# .cpp path
CODE_SOURCES_COMM   += $(shell find . -name '*.cpp')

# .o path
OBJDIR=_obj
COMM_OBJECTS   += $(CODE_SOURCES_COMM:%.cpp=$(OBJDIR)/%.o)

# 目标文件
TARGET_CENTER = ds

###  依赖关系 ###
all: center
center: $(TARGET_CENTER)


$(OBJDIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(SHOW_COMPILE);$(CXX) $(CXXFLAGS) -c $< -o $@

$(TARGET_CENTER): $(COMM_OBJECTS)
	$(SHOW_LINK);$(CXX) $(COMM_OBJECTS) -o $@ $(CXXFLAGS)

clean:
	@rm -rf $(OBJDIR)
