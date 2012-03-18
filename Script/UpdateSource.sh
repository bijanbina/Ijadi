#!/bin/bash
pval=
pflag=

HELP="a script for change project details
USAGE: Update [-p your project path] ...
-p        Project path  
--help    help"

# see if the user need help
(( $# == 1 )) && [[ "$1" == "--help" ]] && echo "$HELP" && exit 0

while (( $# > 0 ))
do
  case $1 in
    -p) shift;
      pval=$1
      pflag=1

  esac
  shift
done


if [ "$pflag" ]
then
    PROJECT_PATH="$pval"
else
    echo "Please, enter the path of your project :"
    read PROJECT_PATH
if [ -z "$PROJECT_PATH" ]
    then
        PROJECT_PATH=~
    fi
fi


cp -r -f "$PROJECT_PATH/Latest/Binary" "$PROJECT_PATH/PURE"
cp -r -f "$PROJECT_PATH/Latest/Etc" "$PROJECT_PATH/PURE"
cp -r -f "$PROJECT_PATH/Latest/Resourses" "$PROJECT_PATH/PURE"

cp -f "$PROJECT_PATH/Latest/AUTHOR" "$PROJECT_PATH/PURE"
cp -f "$PROJECT_PATH/Latest/ChangeLog" "$PROJECT_PATH/PURE"
cp -f "$PROJECT_PATH/Latest/configure.ac" "$PROJECT_PATH/PURE"
cp -f "$PROJECT_PATH/Latest/COPYING" "$PROJECT_PATH/PURE"
cp -f "$PROJECT_PATH/Latest/INSTALL" "$PROJECT_PATH/PURE"
cp -f "$PROJECT_PATH/Latest/Makefile.am" "$PROJECT_PATH/PURE"
cp -f "$PROJECT_PATH/Latest/NEWS" "$PROJECT_PATH/PURE"
cp -f "$PROJECT_PATH/Latest/README" "$PROJECT_PATH/PURE"

cp "$PROJECT_PATH/Latest/Source/Makefile.am" "$PROJECT_PATH/PURE"
cp "$PROJECT_PATH/Latest/Source/Makefile.in" "$PROJECT_PATH/PURE"
cp "$PROJECT_PATH/"Latest/Source/*.c "$PROJECT_PATH/PURE/Source"
cp "$PROJECT_PATH/"Latest/Source/*.h "$PROJECT_PATH/PURE/Source"


