#!/usr/bin/python

# This scripts generates the dependency files that are used for
# the library.  gcc generates the actual dependencies, but we
# add in some directory information.

import re
import os
import sys
import string
import xreadlines


# Determine what the source file is.
sourceFile = None
for arg in sys.argv[1:]:
    if re.search(".c$", arg):
        sourceFile = arg
if sourceFile == None:
    sys.stderr.write("Unable to find a source file in " + string.join(sys.argv[1:]));
    sys.stderr.write("\n");
    sys.exit(1)

sourcePath=os.path.dirname(sourceFile)

# Have gcc generate the depenency information.  We modify the line
# with the filename so that it also includes the .d file, and so that
# the complete path name is used.
child = os.popen("gcc -M " + string.join(sys.argv[1:]), "r")
for line in xreadlines.xreadlines(child):
    if re.search(':', line):
        (file, remainder) = re.split(':', line)
        print os.path.join(sourcePath, file),
        dependencyFile = re.split("\.", file)[0]
        print " %s.d: %s" % (os.path.join(sourcePath, dependencyFile),
                             remainder),
    else:
        print line,
