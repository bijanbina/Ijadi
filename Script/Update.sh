#!/usr/bin/env bash
#get the project name from user


nflag=
nval="Project name"


#the path that the project is there
pflag=
pval=

vflag=
vval="0.1"

xflag=
xval=

pflag=
pval=


HELP="a script for change project details
USAGE: Update [-p your project path] ...

-x        executable output file name
-n        project name       
-v        project version
-p        Project path  
--help    help"


# see if the user need help
(( $# == 1 )) && [[ "$1" == "--help" ]] && echo "$HELP" && exit 0



#check for entered falgs
while (( $# > 0 ))
do
  case $1 in
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


NEWNAME=$nval
NEWVERSION=$vval
NEWEXECNAME=$xval

if [ "$nflag" ]
then
    echo "`python ../python/parser3.py "$PROJECT_PATH""/Latest/configure.ac"  $NEWNAME`" > "$PROJECT_PATH""/Latest/configure.ac"
fi

if [ "$vflag" ]
then
    echo "`python ../python/parser3-1.py "$PROJECT_PATH""/Latest/configure.ac"  $NEWVERSION`" > "$PROJECT_PATH""/Latest/configure.ac"
fi

if [ "$xflag" ]
then
    echo "`python ../python/parser4.py "$PROJECT_PATH""/Latest/Source/Makefile.am"  $NEWEXECNAME`" > "$PROJECT_PATH""/Latest/Source/Makefile.am"
fi

