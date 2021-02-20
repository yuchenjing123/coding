#!/bin/bash

#shell 三要素
#1.第一行指定shell版本unx是sh,linux是bash
#2.命令和控制结构
#3.给脚本执行权限

# $ 代表取值
d9=10      #定义变量要在最前方定义并且要初始化(不能有空格)，如果有空格shell会当成一个命令来处理将来= 和10当成第一个和第二个参数处理　符号名=符号值
echo "$HOME" #获取家目录
echo "home"
echo "$PWD"  #获取当前路径　$后接的命令要大写 
#命令后面不能有空格，shell解释成第一个参数
 #想获取d9符号名的符号值要进行取值操作 取值符号为"$"

#　"　"　双引号可以识别出特殊字符　'　'　单引号代表纯字符串
VAR="JM TEST"
echo ${VAR}

echo `pwd` #反引号将内部识别为命令，返回调用结果前提是有效的命令

#位置变量
echo "$1 $2 $3 $4 $5"
#$* 代表所有参数
echo "$*"
#$# 代表参数个数
echo "$#"

echo "$!"

echo "$?"

echo "$$"

function 13865() {
    echo "函数的定义"
    exit
}

#四则运算优先级expr套expr
JM1=3
JM2=4
JM3=0
#``中嵌套``要使用转义符号\
JM3=`expr \`expr ${JM1} + ${JM2}\` \* ${JM2}`

echo "${JM3}"
STR="\"AAA\""
echo "${STR}"

JM4=`expr 1 + 2`
echo "${JM4}"

#多行注释
<<COMMENT
#备注掉的内容
COMMENT
#流程结构if单项选择为真要有then
if test ${JM1} -eq ${JM2}
    then
    echo "true"
else
    echo "false"
fi

#判断文件是否存在，文件名用参数传递
if test -a $1
    then
        echo "have file"
    elif test -d $1
        then
        echo "no dev file"
    else
        echo "have no file"
fi

#read 从标准输入读，需要手动输入字符
read Var1
echo ${Var1}

case ${Var1} in
    "1")
        echo "1"
        ;;
    "shell.sh")
        echo "2"
        ;;
esac 


#shell支持c风格的for循环不过多加入一组()
for((i=0;i<100;i++))
{
    echo "${i}"
}

#while 循环以真为循环条件
<<comment
while true 
do
    echo "circle infinity"
done
comment

#until以假为循环条件

#seq 20，代表1-20的序列
echo "$(seq 20)"

for i in $(seq 20)
do
    echo "${i}"
done

#select 用法
<<comment
select var2 in 1 2 3 4 5
do 
    echo "${var2}"
done
comment
#shift 让传来的参数被移走

#shell函数没有参数没有返回值
FUNCTION()
{
    echo "function"
}

#test  和[] 是等价的

#函数的调用
FUNCTION

#shell脚本中的变量都是全局变量
