import pandas as pd
import os
# df = pd.read_csv("data_well_public.hxv")
df = pd.read_table("shore_public.dat",header=None,sep=" ")
# print(df.shape)
df.columns = ([i for i in range(71)])
# print(df)
# for i in range(71):
#     df[i].to_csv( "C:\\Users\\xiaoj\\Desktop\\float\\"+str(i)+".csv",header=True)
# df_merge = df[0]
filesize=""
for i in range(0,71):
    file_name = "C:\\Users\\xiaoj\\Documents\\GitHub\\CSSC_compression\\CSSC_compression_code\\Debug\\" + str(i) +".csv"
    df[i].round(5).to_csv(file_name,header=False,index=False)
    size = os.path.getsize(file_name)
    print(size)
    filesize+=str(size)
    filesize+=","
f2=open("filesize.csv",'w', encoding='UTF-8')
f2.write(filesize)
f2.close()


    # df_merge = pd.concat([df_merge,])
# df_merge