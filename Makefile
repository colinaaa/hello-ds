.PHONY: test
test: build
	(cd build; make Test)
	./build/test/Test

main: build
	(cd build; make main)

all: build
	(cd build; make all)

.PHONY: dep
dep:
	git submodule init
	git submodule update --recursive

.PHONY: rebuild
rebuild: build
	rm -r build
	mkdir build; cd build; cmake ../

.PHONY: cmake
cmake: dep build
	cd build; cmake ../

.PHONY: ci
ci: dep build debug

.PHONY: debug
debug: build dep
	cd build; cmake -DCMAKE_BUILD_TYPE=Debug ../

build:
	mkdir build
