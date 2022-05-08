# import pandas as pd
# import time
# start = time.time()
# df = pd.read_csv("data_well_public.hxv",sep=",",nrows=1800000)
# end = time.time()
# print(end-start)
# # print(df)

import pandas as pd

# print(int("0000",16))
# print(int("00A0",16))
# # df = pd.read_csv("data_well_public.hxv")
df = pd.read_csv("data_well_public.hxv",header=None,sep=",",nrows=1000)
# # print(df.shape)
# print(df.iloc[10,0])
# print(int(df.iloc[10,0],16))
# df.apply(lambda x: int(x, 16))
# df.columns = ([i for i in range(5)])

# # print(df)
for i in range(5):
    df[i]=df[i].apply(lambda x: int(x, 16))
    df[i].to_csv( "C:\\Users\\xiaoj\\Desktop\\ll\\"+str(i)+".csv",header=True)
# df_merge = df[0]
# for i in range(1,5):
#     df_merge = pd.concat([df_merge,df[i]])
# df_merge.to_csv("C:\\Users\\xiaoj\\Desktop\\float\\test.csv",header=True)