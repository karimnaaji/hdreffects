#!/bin/bash
make && (cd build ; date >> out.log ; ./hdr.out 2>> out.log ; cd ..)
