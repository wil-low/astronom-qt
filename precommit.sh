#!/bin/sh
find . -name '*.pro'  -exec dos2unix '{}' \;
find . -name '*.ui'  -exec dos2unix '{}' \;
find . -name '*.cpp'  -exec dos2unix '{}' \;
find . -name '*.h'  -exec dos2unix '{}' \;
find . -wholename '*settings/*.txt' -exec dos2unix '{}' \;
