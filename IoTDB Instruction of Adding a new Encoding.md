# IoTDB Instuction of Adding a new Encoding


## 需要改的地方
1. 加encoder和decoder代码的地方 
```
iotdb\tsfile\src\main\java\org\apache\iotdb\tsfile\encoding\encoder
iotdb\tsfile\src\main\java\org\apache\iotdb\tsfile\encoding\decoder
```
2. Encoder相关配置
```
iotdb\tsfile\src\main\java\org\apache\iotdb\tsfile\encoding\encoder\TSEncodingBuilder.java
iotdb\tsfile\src\main\java\org\apache\iotdb\tsfile\file\metadata\enums\TSEncoding.java
```
3. Decoder相关配置
```
iotdb\tsfile\src\main\java\org\apache\iotdb\tsfile\encoding\decoder\Decoder.java
```
4. SQL相关配置
```
iotdb\server\src\main\java\org\apache\iotdb\db\utils\SchemaUtils.java
iotdb\antlr\src\main\antlr4\org\apache\iotdb\db\qp\sql\IoTDBSqlLexer.g4
```

## 加一个Encoding的方法
### 写Encoder
1. 在此处加一个XXXEncoder类
```
iotdb\tsfile\src\main\java\org\apache\iotdb\tsfile\encoding\encoder
```
2. XXXEncoder继承Encoder类，构造函数需要先构造父类
```java
public XXXEncoder() {
    super(TSEncoding.XXX);
    // write code here
}
```
3. 根据数据类型，写IntXXXEncoder, LongXXXEncoder, FloatXXXEncoder, DoubleXXXEncoder
4. 需要Override的四个函数
```java
public void encode(int num, ByteArrayOutputStream out); // encoder one value and store in encoder
public void flush(BytaArrayOutputStream out); // flush all encoded values to stream out
public int getOneItemMaxSize(); // return one value of bytes in memory
public long getMaxByteSize(); // return the space need for all values in memory
```
### 配置Encoder
1. 在下面的文件中更改
```
iotdb\tsfile\src\main\java\org\apache\iotdb\tsfile\file\metadata\enums\TSEncoding.java
```
2. 在enum中加刚才写的XXX，并赋一个数值
3. 在下面getTsEncoding中，写通过数值返回XXX的语句
4. 在下面的文件中更改
```
iotdb\tsfile\src\main\java\org\apache\iotdb\tsfile\file\metadata\enums\TSEncoding.java
```
5. 在文件中新加一个产生Encoder实例对象的类，仿照其他类
6. 在getEncodingBuilder增加一个分支

### 写Decoder
1. 在此处添加一个解码类
```
tsfile\src\main\java\org\apache\iotdb\tsfile\encoding\decoder
```
2. XXXDecoder继承Decoder类，构造子类前需要super构造父类
3. 在XXXDecoder类中主要写两个函数（根据数据类型增加）
```java
public int readInt(ByteBuffer buffer); // return an interger value from buffer
public boolean hasNext(ByteBuffer buffer); // return whether there is remaining values in decoder
```

### 配置Decoder
1. 在下面的文件中更改
```
iotdb\tsfile\src\main\java\org\apache\iotdb\tsfile\encoding\decoder\Decoder.java
```
2. 在函数getDecoderByType中增加一个分支，仿照其他分支

## SQL相关配置

### 增加编码与数据类型的支持
1. 在下面文件中更改

```
iotdb\server\src\main\java\org\apache\iotdb\db\utils\SchemaUtils.java
```
2. 在boolean, int, float, text的HashSet中添加自己写的encoding
3. 注：int, long; float, double在此处不区分

### 增加SQL关键字
1. 在下面的文件中更改
```
iotdb\antlr\src\main\antlr4\org\apache\iotdb\db\qp\sql\IoTDBSqlLexer.g4
```
2. 文件中搜索关键字ENCODING_VALUE，找到需要更改的地方
3. 在ENCODING_VALUE下增加自己写的encoding关键字
4. 在下方依照其他编码方式的语法写自己写的encoding关键字