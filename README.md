### vector回收内存方法

在《effective STL》和其实很多 C++ 文章中都有指明，用`clear()`无法保证内存回收。但是**swap**技法可以。 用swap交换到一个新的类型的vector，将原来的 a 拷贝出去，然后自然销毁，而新的a是全新，无任何数据。

```c++
//由于.clear()是懒删除，不会释放内存，使用交换的方法将 vector 对应的内存空间删除
vector <std::uint8_t>().swap(this->bytes);
//上述操作与下面代码等价
std::vector<int> tmp;
ivec.swap(tmp);
```

### git切换远程分支命令

```bash
 git checkout -b INT_col_3_4_5 origin/INT_col_3_4_5
```

### 微软自带的单元测试工具

```c++
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
```

### matlab计算BCH编码
```matlab
msgTx = gf([0 0 0 0 0 1 1 1 0 0 0 0 0 1 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0])
enc = bchenc(msgTx, 63, 51);
```

### python's tricks

```python
# 反转字符串或者列表
fiftyOne = fiftyOne[::-1]
```

### ☆linux 操作文件一些有用的指令

```shell
# 查看文件各种属性（包括大小）
stat shore
# 输出文件前十行（默认）
head shoreDecode
# 自定义输出文件前几行
head -n 100 shoreDecode
# 统计文件行数
wc -l binsAll.txt
# 查找文件特定字符串
grep -n "AAAA" data_well_public.hxv
```

### BCH编码方法

在 $\mbox{Matlab}$ 中计算生成多项式

```matlab
bchgenpoly(63, 51);
```

得到 $(63,51)\  \mathrm{BCH}$ 码的生成多项式为:
$$
G(x)=1+x^{2}+x^{4}+x^{7}+x^{8}+x^{9}+x^{12}\Longleftrightarrow (1010100111001)_2=(5433)_{10}
$$
利用系统码编码方程进行编码
$$
\large \mbox{C}(x)=x^{n-k}\cdot {m}(x)+\mathrm{Rem} _{G(x)}\left[x^{n-k} \cdot m(x)\right]
$$
其中 $\mbox{Rem}$ 表示在 $F_{p}[n](p=2,n=12)$ 伽罗瓦域上模 $G(x)$ 求同余 

增加 feature 是机器学习突破的重要手段

## 计算流体力学入门

python 开源框架：**pysph、fenics、pyfvm**

C++ 开源类：**su2、openfoam**，框架 **petsc**

**计算流体力学可以做为机器学习的物理模拟器**

流体控制方程的求解思路主要是通过**有限个点**来数值逼近**微分方程**

推书：

主推fvm，帕坦卡，传热与流体流动的数值计算，有中文，基于矩形网格，内容写的太好了，非常容易理解

新手必备：blazek，Computational Fluid Dynamics: Principles and applications

非结构网格、编程向的好书；Versteeg， an introduction to computational fluid dynamics, [simple族算法](https://www.zhihu.com/search?q=simple族算法&search_source=Entity&hybrid_search_source=Entity&hybrid_search_extra={"sourceType"%3A"answer"%2C"sourceId"%3A2284260905})；Moukalled，the finite volume method in compuational fluid dynamics, openfoam 开发者写的，内容比较全；[ferziger](https://www.zhihu.com/search?q=ferziger&search_source=Entity&hybrid_search_source=Entity&hybrid_search_extra={"sourceType"%3A"answer"%2C"sourceId"%3A2284260905})，Computational Methods for Fluid Dynamics

## MD5 验证

压缩解压后验证是否为无损可使用MD5验证

较快的：sha1sum <file1> <file2>

较慢的： certutil -hashfile  <file>  MD5



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



### GZIP VS中配置

![](https://pic.imgdb.cn/item/629edefd094754312962458d.jpg)

![](https://pic.imgdb.cn/item/629ecdfd09475431294ccbf2.jpg)

![](https://pic.imgdb.cn/item/629ece9009475431294d9eed.jpg)

如果没有debug文件夹，使用空main函数运行一个可执行文件，在对应目录下就有debug文件夹，不是在X64文件夹中，因为zlib只能支持X86，只能在X86环境下运行

![](https://pic.imgdb.cn/item/629eddb3094754312960b7bf.jpg)

![](https://pic.imgdb.cn/item/629ece3809475431294d242b.jpg)

![](https://pic.imgdb.cn/item/629ecf1009475431294e3cea.jpg)

![](https://pic.imgdb.cn/item/629ede210947543129613e80.jpg)

![](https://pic.imgdb.cn/item/629ed1b10947543129517612.jpg)

