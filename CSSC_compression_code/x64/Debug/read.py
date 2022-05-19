# import pandas as pd
# import time
# start = time.time()
# df = pd.read_csv("data_well_public.hxv",sep=",",nrows=1800000)
# end = time.time()
# print(end-start)
# # print(df)

import pandas as pd

# print(int("0000",16))
df = pd.read_csv("data_well_public.hxv",header=None,sep=",",nrows=500000)
# print(df.iloc[10,0][0:2])
new_df0 = df[0].apply(lambda x:  int(x[0:2],16))
new_df0.to_csv( "C:\\Users\\xiaoj\\Desktop\\llnew\\0.csv",header=True)
new_df1 = df[0].apply(lambda x:  int(x[2:4],16))
new_df1.to_csv( "C:\\Users\\xiaoj\\Desktop\\llnew\\1.csv",header=True)
new_df2 = df[1].apply(lambda x:  int(x,16))
new_df2.to_csv( "C:\\Users\\xiaoj\\Desktop\\llnew\\2.csv",header=True)
new_df3 = df[2].apply(lambda x:  int(x[0:3],16))
new_df3.to_csv( "C:\\Users\\xiaoj\\Desktop\\llnew\\3.csv",header=True)
new_df4 = df[2].apply(lambda x:  x[3])+df[3].apply(lambda x:  x[0:2])
new_df4=new_df4.apply(lambda x: int(x, 16))
new_df4.to_csv( "C:\\Users\\xiaoj\\Desktop\\llnew\\4.csv",header=True)
new_df5 = df[3].apply(lambda x:  x[2:])+df[4].apply(lambda x:  x[0:1])
new_df5=new_df5.apply(lambda x: int(x, 16))
new_df5.to_csv( "C:\\Users\\xiaoj\\Desktop\\llnew\\5.csv",header=True)
# print(new_df5)
new_df6 = df[4].apply(lambda x:  int(x[1:],16))
new_df6.to_csv( "C:\\Users\\xiaoj\\Desktop\\llnew\\6.csv",header=True)


# # print(df.shape)
# print(df.iloc[10,0])
# print(int(df.iloc[10,0],16))
# df.columns = ([i for i in range(5)])

# # # print(df)
# for i in range(5):
#     df[i]=df[i].apply(lambda x: int(x, 16))
#     df[i].to_csv( "C:\\Users\\xiaoj\\Desktop\\llnew\\"+str(i)+".csv",header=True)
# # df_merge = df[0]
# # for i in range(1,5):
# #     df_merge = pd.concat([df_merge,df[i]])
# # df_merge.to_csv("C:\\Users\\xiaoj\\Desktop\\float\\test.csv",header=True)