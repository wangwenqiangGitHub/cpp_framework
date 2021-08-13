#! /bin/sh
#======================================================================
#
# generate.sh - 
#
# Created by wwq on 2021/08/10
# Last Modified: 2021/08/10 15:49:22
#
#======================================================================

# 输出命令
set -x

command_error_exit(){
	# 输入的参数总数
	$*
	# 上一个命令执行后的退出状态
	if [ $? -ne 0]
	then
		exit 1
	fi
}

if [ $# -lt 2 ]
then
	echo "use [$0 project_name namespace]"
	exit 0
fi

command_error_exit project_name=$1
command_error_exit namespace=$2
echo "${project_name}"
echo "${namespace}"

echo "print each param from \$*"
for var in $*
do
    echo "$var"
done
echo "print each param from \$@"
for var in $@
do
    echo "$var"
done

echo "print each param from \"\$*\""
for var in "$*"
do
    echo "$var"
done
echo "print each param from \"\$@\""
for var in "$@"
do
    echo "$var"
done


for var in $@
do
	if [ "$var" = "$1" ]
	then
		echo "equit"
	fi
done
