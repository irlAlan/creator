#!/usr/bin/sh

build_folder=./build
project=./make-proj


check_if_empty(){
  [ "$(ls -A $build_folder)" ] && return 1 || return 2
}

check_if_empty

check_folder_empty=$?

if [ "$check_folder_empty" -eq "1" ]; then
  echo "Building and running in $build_folder"
  cd $build_folder; make; $project $1 ;
  printf '\n'
  echo "Finished"
elif [ "$check_folder_empty" -eq "2" ]; then
  echo "Running cmake"
  cd $build_folder; cmake..;
  echo "Call $0 again"
else
  echo "Nothing to do"
fi

