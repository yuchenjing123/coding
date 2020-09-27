/*************************************************************************
 *       Filename:  log_test.cpp
 *    Description:  The principle of variable parameter function
 *        Version:  1.0
 *        Created:  2020年07月21日 19时47分53秒
 *       Revision:  none
 *       Compiler:  g++
 *         Author:  jingming<jingming@xiaomi.com> 
 *        Company:  
 * ************************************************************************/

#include <stdio.h>
#include <stdarg.h>  
  
void test(const char * format, ...);
  
int main(void)
{
     test("%s, %d_%s", "this is test", 6, "abc");
     return 0;
}

void test(const char * format, ...)
{
     char buf[4069] = {0};	//写入的存储区位置
	 //定义va_list类型的指针list，用于存储参数地址
	 va_list list;
	 //初始化list指针，使其指向第一个可变参数。该宏第二个参数是变参列表的前一个参数
     va_start(list, format);
     vsnprintf(buf, 4069, format, list);
	 //将指针list置为无效，结束变参的获取
     va_end(list);
     printf("%s\n", buf); //打印格式化输出结果
}
