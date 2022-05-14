#SRC=main.cpp sms.cpp tests.cpp
SRC=$(wildcard *.cpp)
SRC_NO_MAIN=$(filter-out main.cpp, $(SRC))
CXX=g++
EXE=./prog
EXE_TEST=../test/progTest

CXXFLAGS+=-Wall -Wextra -MMD -g -O2 -fdiagnostics-color=auto
LDFLAGS= -lSDL2 -lSDL2_image -lSDL2_ttf

OBJ=$(addprefix ../build/,$(SRC:.cpp=.o))
DEP=$(addprefix ../build/,$(SRC:.cpp=.d))

OBJ_NO_MAIN=$(addprefix ../build/,$(SRC_NO_MAIN:.cpp=.o))
DEP_NO_MAIN=$(addprefix ../build/,$(SRC_NO_MAIN:.cpp=.d))

OBJ_TEST=$(addprefix ../build/,$(SRC_TEST:../test/%.cpp=%.o))
DEP_TEST=$(addprefix ../build/,$(SRC_TEST:../test/%.cpp=%.d))

all: $(OBJ)
	$(CXX) -o $(EXE) $^ $(LDFLAGS)

../build/%.o: %.cpp
	@mkdir -p ../build
	$(CXX) $(CXXFLAGS) -o $@ -c $<

test : $(OBJ_TEST) $(OBJ_NO_MAIN)
	$(CXX) -o $(EXE_TEST) $^ $(LDFLAGS)

../build/%.o: ../test/%.cpp
	@mkdir -p ../build
	$(CXX) $(CXXFLAGS) -o $@ -c $<

clean:
	rm -rf ../build core *.gch
	rm $(EXE)

clean_test:
	rm -rf ../build core *.gch
	rm $(EXE_TEST)


-include $(DEP)