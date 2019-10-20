.PHONY: test
test: build
	(cd build; make Test)
	./build/test.out

main: build
	(cd build; make main)
	./main.out

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
ci: dep build cmake

build:
	mkdir build