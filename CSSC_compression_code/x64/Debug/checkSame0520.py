import csv

# reader1 = csv.reader(open("data_well_public.hxv"))
# reader2 = csv.reader(open("data_well_public_decoded.hxv"))
#
# r1 = list(reader1)
# r2 = list(reader2)
# for i in range(len(r1)):
#     if(r1[i]!=r2[i]):
#         l1 = r1[i][0]
#         l2 = r2[i][0]
#         l1 = l1.split()
#         l2 = l2.split()
#         for j in range(len(l1)):
#             if(l1[j]!=l2[j]):
#                 print("{},{}".format(l1[j],l2[j]))

f1 = open("test.csv", "rb")
f2 = open("test2.csv", "rb")
try:
    i = 0
    while(True):
        data1 = f1.read(1)
        data2 = f2.read(1)
        print(i)
        print(data1)
        print(data2)
        if(data1 != data2):
            print(i)
            print(data1)
            print(data2)
            #break
        i+=1
except EOFError:
    pass
