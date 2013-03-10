all:	run

draw_c:
	g++ draw.cpp  -lglut -lGLU -lGL -o draw

draw_r:
	./draw

clean:
	rm -f draw compare grid
	
run:	clean draw_c draw_r

cmp_c:
	g++ compare.cpp  -o compare

cmp_r:
	./compare
	
compare:	clean cmp_c cmp_r
	
grid:	clean grid_c grid_r
	
grid_c:	
	g++ grid.cpp  -o grid  -lglut -lGLU -lGL

grid_r:
	./grid