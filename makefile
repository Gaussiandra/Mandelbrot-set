SFML_flags = -lsfml-graphics -lsfml-window -lsfml-system
CXX_NoSSE_flags = -O2
CXX_SSE_flags = -D SSE -O2 -mavx2 

#---------------------------------------

exec_nosse: mandelbrot-nosse.out
	./mandelbrot-nosse.out

window-nosse.o: window.cpp
	g++ -c window.cpp $(CXX_NoSSE_flags) -o window-nosse.o

mandelbrot-nosse.out: window-nosse.o mandelbrot-nosse.o
	g++ window-nosse.o mandelbrot-nosse.o $(CXX_NoSSE_flags) $(SFML_flags) -o mandelbrot-nosse.out

mandelbrot-nosse.o: mandelbrot-nosse.cpp mandelbrot.hpp
	g++ -c mandelbrot-nosse.cpp $(CXX_NoSSE_flags) -o mandelbrot-nosse.o

#---------------------------------------

exec_sse: mandelbrot-sse.out
	./mandelbrot-sse.out

window-sse.o: window.cpp
	g++ -c window.cpp $(CXX_SSE_flags) -o window-sse.o

mandelbrot-sse.out: window-sse.o mandelbrot-sse.o
	g++ window-sse.o mandelbrot-sse.o $(CXX_SSE_flags) $(SFML_flags) -o mandelbrot-sse.out

mandelbrot-sse.o: mandelbrot-sse.cpp mandelbrot.hpp
	g++ -c mandelbrot-sse.cpp $(CXX_SSE_flags) -o mandelbrot-sse.o

#---------------------------------------

clear:
	rm mandelbrot-nosse.o mandelbrot-sse.o window-nosse.o window-sse.o mandelbrot-nosse.out mandelbrot-sse.out