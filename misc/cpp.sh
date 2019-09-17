#!/bin/bash

BOOST_PATH=$HOME/boost/include
COMPRO_PATH=$HOME/Documents/competetive_programming

FLAG_E=false
FLAG_D=false

# オプションの解析
while getopts ehd OPT
do
  case $OPT in
    e) FLAG_E=true;; # 実行のみ (コンパイルをしない)
    d) FLAG_D=true;; # DEBUG定数を設定しない
    h) ;; # help
    \?) ;;
  esac
done

shift $((OPTIND - 1))

CPP_FILE=$1
INPUT_FILE=$2

# コンパイル & 実行
function func(){

  # -eオプションが指定されているときのみコンパイルを行う
  if ! $FLAG_E ; then
    echo -e "\e[33;1m compiling ... \e[m" 1>&2

    if $FLAG_D ; then
      g++ $1 -std=c++1z -Wall -I$BOOST_PATH -I$COMPRO_PATH -D_GLIBCXX_DEBUG -g -o a.out
    else
      g++ $1 -std=c++1z -Wall -I$BOOST_PATH -I$COMPRO_PATH -DDEBUG -D_GLIBCXX_DEBUG -g -o a.out
    fi

    if [ $? -gt 0 ] ; then
      return
    fi

    echo -e "\e[33;1m compile successful \e[m" 1>&2
  fi

  # 第2引数で指定されたファイルを標準入力として渡す
  if [ $INPUT_FILE ] ; then
    ./a.out < $INPUT_FILE;
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

func $CPP_FILE | while IFS= read -r line
do
  echo -en "\e[35;1m>\e[m \e[1m";
  echo "$line";
  echo -en "\e[m";
done
