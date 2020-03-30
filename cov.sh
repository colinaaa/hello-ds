#!/bin/bash

if [[ $CC =~ ^[Gg]cc.* ]]; then
	echo "${CC/cc/cov} $@"
	exec "${CC/cc/cov} $@";
else
	exec llvm-cov gcov "$@";
fi
