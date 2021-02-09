TARGET = ../run

SOURCES = main IRProviderConst

EXTLIBS =

CXXFLAGS += -fPIC
CXXFLAGS += -std=c++17
CXXFLAGS += -O0 -g

LDFLAGS += -fPIC
LDFLAGS += -pthread
LDFLAGS += -Wl,--as-needed
LDFLAGS += -Wl,--no-undefined


BUILD_DIR = $(shell pwd)
OBJECTS_DIR = $(BUILD_DIR)/../obj
OBJECTS = $(patsubst %, $(OBJECTS_DIR)/%.o, $(SOURCES))

all: $(TARGET)

$(OBJECTS_DIR):
	$(shell mkdir -p $(OBJECTS_DIR))

$(OBJECTS_DIR)/%.o: %.cpp 
	@echo [CXX] $(@F)
	$(CXX) $(CXXFLAGS) -o $@ -c $(realpath $<)

$(OBJECTS_DIR)/%.o: %.c
	@echo [CC] $(@F)
	$(CC) $(CFLAGS) -o $@ -c $(realpath $<)

$(TARGET) : $(OBJECTS_DIR) $(OBJECTS)
	$(CXX) $(LDFLAGS) -o $(TARGET) $(OBJECTS) # '-Wl,-(' $(EXTLIBS)




clean:
	$(shell rm -fr $(OBJECTS_DIR))
	$(shell rm -f $(TARGET))
