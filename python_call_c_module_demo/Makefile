
CC := gcc
C_FLAGS := -fPIC -shared
INCLUDE_FLAGS := -I/usr/include/python2.7/
LD_FLAGS := -lpython2.7


demo_module: demo_module.c
	$(CC) $(C_FLAGS) $^ -o $@.so $(INCLUDE_FLAGS) $(LD_FLAGS)


.PHONY: clean

clean:
	rm -rf *.so
