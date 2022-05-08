import pandas as pd
import time
start = time.time()
df = pd.read_csv("data_well_public.hxv",sep=",",nrows=1800000)
end = time.time()
print(end-start)
# print(df)