# **Bugs have been solved**

## 数据读入问题
+ 整数使用16进制，浮点数用十进制
+ 整数的换行符是\r\n，需要将buffer定为5个bytes

## 压缩问题
+ -0的处理：在输出的时候特判-0

## 语言语法问题

- 写参变量时一定要加引用，例如flush(ByteArrayOutputStream& out)中的&