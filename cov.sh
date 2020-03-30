#!/bin/bash

if [[ $CC =~ ^[Gg]cc.* ]]; then
	exec "${CC/cc/cov}" "$@";
else
	exec llvm-cov gcov "$@";
fi
