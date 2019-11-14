.PHONY: test
test: debug
	./build/test/Test

main: debug
	(cd build; make main)

all: debug
	(cd build; make all)

dep:
	git submodule update --recursive --init

.PHONY: rebuild
rebuild: build
	rm -r build
	make debug

.PHONY: ci
ci: dep build debug cov valgrind

.PHONY: debug
debug: build dep
	cd build; cmake -DCMAKE_BUILD_TYPE=Debug ../ ; make Test

cov: build-cov dep
	cd cmake-build-cov; cmake -DCMAKE_BUILD_TYPE=Cov ../; make all

build-cov:
	mkdir cmake-build-cov;

valgrind: build-valgrind dep
	cd cmake-build-valgrind; cmake -DCMAKE_BUILD_TYPE=Valgrind ../; make all

build-valgrind:
	mkdir cmake-build-valgrind

build:
	mkdir build
