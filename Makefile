.PHONY: test
test: debug
	$(MAKE) -C build Test
	./build/test/Test

main: debug
	(cd build; make main)

all: debug
	(cd build; make all)

dep:
	git submodule update --recursive --init

.PHONY: rebuild
rebuild: build
	rm -rf build
	$(MAKE) debug

.PHONY: ci
ci: dep build debug cov valgrind

.PHONY: debug
debug: build dep
	cmake -DCMAKE_BUILD_TYPE=Debug -Bbuild
	cmake --build build

cov: cmake-build-cov dep
	cmake -DCMAKE_BUILD_TYPE=Coverage -Bcmake-build-cov
	cmake --build cmake-build-cov
	./cmake-build-cov/test/Test

cmake-build-cov:
	mkdir cmake-build-cov;

valgrind: cmake-build-valgrind dep
	cmake -DCMAKE_BUILD_TYPE=Valgrind -Bcmake-build-valgrind
	cmake --build cmake-build-valgrind
	./cmake-build-valgrind/test/Test

cmake-build-valgrind:
	mkdir cmake-build-valgrind

build:
	mkdir build

clean: cmake-build-cov cmake-build-valgrind build
	rm -rf cmake-build-*
	rm -rf build*
	rm -rf cov.info
	rm -rf out
	rm -rf *.dat

# see: https://stackoverflow.com/questions/18136918/how-to-get-current-relative-directory-of-your-makefile
ROOT_DIR:=$(shell dirname $(realpath $(firstword $(MAKEFILE_LIST))))

cov.info: cmake-build-cov
	chmod +x ./cov.sh
	lcov --capture --gcov-tool $(ROOT_DIR)/cov.sh --output-file cov.info --no-external --directory ./cmake-build-cov/ --base-directory ./
	lcov --remove cov.info -o cov.info "$(ROOT_DIR)/lib/*"

localcov: cmake-build-cov
	$(MAKE) cov
	$(MAKE) cov.info
	genhtml -o out cov.info

out: localcov
	open out/index.html

win: cmake-build-win
	cmake -DCMAKE_TOOLCHAIN_FILE=../cmake/mingw.toolchain.cmake -Bcmake-build-win
	$(MAKE) -C cmake-build-win all

cmake-build-win:
	mkdir cmake-build-win

cloc:
	./cloc.sh
