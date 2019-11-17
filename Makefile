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

cov: cmake-build-cov dep
	cd cmake-build-cov; cmake -DCMAKE_BUILD_TYPE=Coverage ../; make Test
	./cmake-build-cov/test/Test

cmake-build-cov:
	mkdir cmake-build-cov;

valgrind: cmake-build-valgrind dep
	cd cmake-build-valgrind; cmake -DCMAKE_BUILD_TYPE=Valgrind ../; make all && ./test/Test

cmake-build-valgrind:
	mkdir cmake-build-valgrind

build:
	mkdir build

clean: cmake-build-cov cmake-build-valgrind build
	rm -rf cmake-build-*
	rm -rf build*
	rm cov.info
	rm -rf out

# see: https://stackoverflow.com/questions/18136918/how-to-get-current-relative-directory-of-your-makefile
ROOT_DIR:=$(shell dirname $(realpath $(firstword $(MAKEFILE_LIST))))

cov.info: cmake-build-cov
	chmod +x ./cov.sh
	lcov --capture --gcov-tool $(ROOT_DIR)/cov.sh --output-file cov.info --no-external --directory ./cmake-build-cov/ --base-directory ./
	lcov --remove cov.info -o cov.info "$(ROOT_DIR)/lib/*"

localcov: cmake-build-cov
	rm -rf cmake-build-cov
	make cov
	make cov.info
	genhtml -o out cov.info

out: localcov
	open out/index.html

win: cmake-build-win
	cd cmake-build-win; cmake -DCMAKE_TOOLCHAIN_FILE=../cmake/mingw.toolchain.cmake ../
	make all

cmake-build-win:
	mkdir cmake-build-win
