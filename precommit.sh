#!/bin/sh
find . -name '*.pro' -o -name '*.ui'  -exec dos2unix '{}' \;
find . -wholename '*settings/*.txt' -exec dos2unix '{}' \;
