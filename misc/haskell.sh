#!/bin/sh

stack ghc -- -o a.out -O2 $1 && ./a.out < input.txt
