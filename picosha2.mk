CXX = clang++ -std=c++98 -D__STRICT_ANSI__
CXXFLAGS = -Wall -g -D PICOSHA2_UNIT_TEST
INCLUDES = 
LIBS =
OBJS = picosha2.o
PROGRAM = picosha2.out

all:$(PROGRAM)

$(PROGRAM): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ $(INCLUDES) $(LIBS) -o $(PROGRAM)

.cpp.o:
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(LIBS) -c $<

.PHONY: clean
clean:
	rm -f *o $(PROGRAM)
