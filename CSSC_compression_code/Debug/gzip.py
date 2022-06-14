# -*- coding: utf-8 -*-
import zlib
import time
start = time.time()
print(start)
# 写文件
f_out = open("zip.gz", "wb")
 
# 读文件
# f_in = gzip.open("xxx.gz", "rb")
for line in open("shore_public.dat", "rb"):
  compressed = zlib.compress(line)
  f_out.write(compressed)
 
f_out.close()
end = time.time() 
print(end - start)