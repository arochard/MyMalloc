#!/bin/sh

export DYLD_LIBRARY_PATH=.
export DYLD_INSERT_LIBRARIES="../Malloc-github/libft_malloc.so"
export DYLD_FORCE_FLAT_NAMESPACE=1
$@
