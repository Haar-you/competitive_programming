#!/bin/bash

BOOST_PATH=$HOME/boost/include
COMPRO_PATH=$HOME/Documents/competetive_programming

FLAG_E=false
INPUT_PATH=""

# オプションの解析
while getopts i:eh OPT
do
  case $OPT in
    i) INPUT_PATH=$OPTARG;; # 入力ファイルの指定
    e) FLAG_E=true;; # 実行のみ (コンパイルをしない)
    h) ;; # help
    \?) ;;
  esac
done

shift $((OPTIND - 1))

# コンパイル & 実行
function func(){

  # -eオプションが指定されているときのみコンパイルを行う
  if ! $FLAG_E ; then
     echo -e "\e[33;1m compiling ... \e[m" 1>&2
     g++ $1 -std=c++1z -Wall -I$BOOST_PATH -I$COMPRO_PATH -DDEBUG -D_GLIBCXX_DEBUG -g -o a.out

     if [ $? -gt 0 ] ; then
       return
     fi

     echo -e "\e[33;1m compile successful \e[m" 1>&2
  fi

  # -iオプションで指定されたファイルを標準入力として渡す
  if [ $INPUT_PATH ] ; then
    ./a.out < $INPUT_PATH;
  else
    ./a.out
  fi
}

# 表示の装飾等
echo -en "\e[35;1m";
for i in `seq 60`
do
  echo -en "=";
done
echo -e "\e[m";


func $1 | while read line
do
  echo -en "\e[35;1m>\e[m \e[1m";
  echo $line;
  echo -en "\e[m";
done
