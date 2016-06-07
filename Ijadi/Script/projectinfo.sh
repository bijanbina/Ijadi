#!/usr/bin/env bash

pval=
pflag=

nflag=
nval=

vflag=
vval="0.1"

xflag=
xval=

HELP="get information of a project from it's directory
USAGE: projectinfo [-p your project path] ...
-p          project path (where your project codes are there)
-n          your project name
-x          your project executable name
-v          your project version
--help      help!
"

# see if the user need help
(( $# == 1 )) && [[ "$1" == "--help" ]] && echo "$HELP" && exit 0


#check for entered flags
while (( $# > 0 ))
do
  case $1 in
    -p) shift;
      pval=$1
      pflag=1
      ;;
    -n) shift;
      nval=$1
      nflag=1
      ;;
    -v) shift;
      vval=$1
      vflag=1
      ;;
    -x) shift;
      xval=$1
      xflag=1
      ;;

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

name=$(python ../python/parser1.py `grep "AC_INIT" "$PROJECT_PATH""/Latest/configure.ac"`)

version=$(python ../python/parser1-1.py `grep "AC_INIT" "$PROJECT_PATH""/Latest/configure.ac"`)

exec_name=$(python  ../python/parser2.py "`grep "bin_PROGRAMS" "$PROJECT_PATH""/Latest/Source/Makefile.am"`")

if [ "$nflag" ]
then
    echo $name
fi

if [ "$vflag" ]
then
    echo $version
fi

if [ "$xflag" ]
then
    echo $exec_name
fi

