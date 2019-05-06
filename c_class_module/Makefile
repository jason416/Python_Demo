all: setup.py
	python $^ build
	cp build/lib.linux-x86_64-2.7/*.so .
	
.PHONY:clean

clean:
	rm -rf build *.so
