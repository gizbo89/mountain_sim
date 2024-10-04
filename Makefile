CC     = g++
HERE   = $(CURDIR)
INCLUDEPATH += -I/usr/local/include -I/usr/include/gdal/ -I$(PWD)
CPPFLAGS = -Wall -std=c++11 -pthread -O3 $(INCLUDEPATH)
LIBRARIES= -L/usr/lib
LIBS     = -lgdal
DEPS   = nvector.h
EXEC   = exe 
OBJ    = $(HERE)/input/geotiff.o \
		$(HERE)/common/logger.o \
	 	mountain_sim.o
####$@: is the output variable, below is the .o
#Out of date if .o does not exist or .o is older than .c or DEPS=>build
%.o: %.cpp $(DEPS)  
	$(CC) $(CPPFLAGS) $(INCLUDEPATH) -c $< -o $@ 
##In the command below $^ represents all the contents in $(OBJ)
##make: has dependencies upon al $(OBJ)
make: $(OBJ)
	g++ $(LIBRARIES) -o $(EXEC) $^ $(LIBS)
clean:
	rm -f $(OBJ) exe

