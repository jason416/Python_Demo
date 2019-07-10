OBJ := py_variant.so

CPP := g++-5

$(OBJ): py_module.cpp binary_variant.cpp
	$(CPP) -std=c++11 -shared $^ -o $@ -fPIC -I/usr/include/python2.7/ -lpython2.7 -lboost_python

.PHONTY: clean

clean:
	rm -rf *.so
