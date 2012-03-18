#!/usr/bin/env bash
#get the project name from user


nflag=
nval="Project name"

tflag=
tval=

#the path that the user wants to have the project in there
pflag=
pval=

vflag=
vval="0.1"

xflag=
xval=

wflag=
wval=

aflag=
aval=

eflag=
eval=

cflag=
cval=

lflag=
lval=

Cflag=
Cval=

iflag=
ival=

HELP="a script for create a project directory from a template project
USAGE: newproject [-n project name] ...

-x        executable output file name
-n        project name       ->recquired
-v        project version
-p        Project directory  -> required
-t        Tar template project name  -> required
-w        author's website
-e        author's email
-c        project's category
-l        project's licenese
-C        project's company
-i        project's icon
--help    help"


# see if the user need help
(( $# == 1 )) && [[ "$1" == "--help" ]] && echo "$HELP" && exit 0



#check for entered flags
while (( $# > 0 ))
do
  case $1 in
    -n) shift;
      nval=$1
      nflag=1
      ;;
    -t)shift;
      tval=$1
      tflag=1
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
      ;;
    -w) shift;
      wval=$1
      wflag=1
      ;;
    -a)
      aval=$1
      aflag=1
      ;;
    -e)
      eval=$1
      eflag=1
      ;;
    -c)
      cval=$1
      cflag=1
      ;;
    -l)
      lval=$1
      lflag=1
      ;;
#company name
    -C)
      Cval=$1
      Cflag=1
      ;;
    -i)
      ival=$1
      iflag=1

  esac
  shift
done



#if no name entered go for cli 

if [ "$nflag" ]
then
    PROJECT_NAME="$nval"
else
    echo "Please, enter your project name :"
    read PROJECT_NAME
    if [ -z "$PROJECT_NAME" ]
    then
        PROJECT_NAME="New Project"
    fi
fi

PROJECT_VERSION="$vval"


if [ "$tflag" ]
then
    PROJECT_TEMPLATE="$tval"
else
    echo "Please, enter your template project path :"
    read PROJECT_TEMPLATE
    if [ -z "$PROJECT_TEMPLATE" ]
    then
        PROJECT_TEMPLATE="TemplateProject.tar.gz"
    fi
fi


if [ "$xflag" ]
then
    PROJECT_EXECUTABLE_NAME="$xval"
else
    echo "Please, enter your executable file name :"
    read PROJECT_EXECUTABLE_NAME
if [ -z "$PROJECT_EXECUTABLE_NAME" ]
    then
        PROJECT_EXECUTABLE_NAME="$PROJECT_NAME"
    fi
fi


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

if [ "$vflag" ]
then
    PROJECT_VERSION="$vval"
else
    echo "Please, enter the version of your project :"
    read PROJECT_VERSION
if [ -z "$PROJECT_VERSION" ]
    then
        PROJECT_VERSION="0.1"
    fi
fi
/usr/local/share/ijadi/Resources/TemplateProject.tar.gz
#craete project path
mkdir -p "$PROJECT_PATH"/"$PROJECT_NAME"

#extract template
tar -zxvf "$PROJECT_TEMPLATE" -C "$PROJECT_PATH""/""$PROJECT_NAME"

./Update.sh -p "$PROJECT_PATH/$PROJECT_NAME" -n $PROJECT_NAME -x $PROJECT_EXECUTABLE_NAME -v $PROJECT_VERSION

#give report to user 
#   ***in the release version reporting must be ommited !***   #
echo "Your project "$PROJECT_EXECUTABLE_NAME" successfully created ."
echo "your project version is :"$PROJECT_VERSION
echo "your project executable file name is :"$PROJECT_EXECUTABLE_NAME
echo "the template that used is :"$PROJECT_TEMPLATE
echo "your project path is : "$PROJECT_PATH
echo "Please press enter to exit the program ."
read
