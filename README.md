# **Bugs have been solved**

## 数据读入问题
+ 整数使用16进制，浮点数用十进制
+ 整数的换行符是\r\n，需要将buffer定为5个bytes
+ 按bit存数时，要把整数转为无符号字符对应的uchar

## 压缩问题
+ -0的处理：在输出的时候特判-0

## 语言语法问题

- 写参变量时一定要加引用，例如flush(ByteArrayOutputStream& out)中的&

## gzip库的版本问题
+ 使用最新版gzip库（已经放置在Debug中）
+ 路径：CSSC_compression\CSSC_compression\x64\Debug
+ Note：Debug模式下x64在此版本库下是可用的