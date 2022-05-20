import csv

reader1 = csv.reader(open("shore_public.dat"))
reader2 = csv.reader(open("shore_decoded2"))

r1 = list(reader1)
r2 = list(reader2)
for i in range(len(r1)):
    if(r1[i]!=r2[i]):
        l1 = r1[i][0]
        l2 = r2[i][0]
        l1 = l1.split()
        l2 = l2.split()
        for j in range(len(l1)):
            if(l1[j]!=l2[j]):
                print("{},{}".format(l1[j],l2[j]))