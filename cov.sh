#!/bin/bash

if [[ $CC =~ ^[Gg]cc.* ]]; then
	exec gcov "$@";
else
	exec llvm-cov gcov "$@";
fi
