#!/bin/sh
# This is a simple way to run the test program with the properly
# set path.
java -cp .:.. -Djava.library.path=. $@
