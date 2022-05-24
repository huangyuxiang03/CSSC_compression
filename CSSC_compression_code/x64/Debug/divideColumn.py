import csv, os
from itertools import islice
reader = csv.reader(open("data_well_public.hxv"))

column1 = []
column2 = []
column3 = []
column4 = []
column5 = []
column6 = []
column7 = []
i = 0

for ln in reader:
    str = []
    str.append(ln[0][0])
    str.append(ln[0][1])
    str = "".join(str)
    a = int(str, 16)
    column1.append(int(str, 16))
    str = []
    str.append(ln[0][2])
    str.append(ln[0][3])
    str = "".join(str)
    column2.append(int(str, 16))
    str = []
    str.append(ln[1][0])
    str.append(ln[1][1])
    str.append(ln[1][2])
    str.append(ln[1][3])
    str = "".join(str)
    column3.append(int(str, 16))
    str = []
    str.append(ln[2][0])
    str.append(ln[2][1])
    str.append(ln[2][2])
    str = "".join(str)
    column4.append(int(str, 16))
    str = []
    str.append(ln[2][3])
    str.append(ln[3][0])
    str.append(ln[3][1])
    str = "".join(str)
    column5.append(int(str, 16))
    str = []
    str.append(ln[3][2])
    str.append(ln[3][3])
    str.append(ln[4][0])
    str = "".join(str)
    column6.append(int(str, 16))
    str = []
    str.append(ln[4][1])
    str.append(ln[4][2])
    str.append(ln[4][3])
    str = "".join(str)
    column7.append(int(str, 16))
    i += 1
    print(i)

writer = csv.writer(open("1.csv", "w", encoding = "UTF-8", newline = ""))
for a in column1:
    writer.writerow([a])
print("1done")
writer = csv.writer(open("2.csv", "w", encoding = "UTF-8", newline = ""))
for a in column2:
    writer.writerow([a])
print("2done")
writer = csv.writer(open("3.csv", "w", encoding = "UTF-8", newline = ""))
for a in column3:
    writer.writerow([a])
print("3done")
writer = csv.writer(open("4.csv", "w", encoding = "UTF-8", newline = ""))
for a in column4:
    writer.writerow([a])
print("4done")
writer = csv.writer(open("5.csv", "w", encoding = "UTF-8", newline = ""))
for a in column5:
    writer.writerow([a])
print("5done")
writer = csv.writer(open("6.csv", "w", encoding = "UTF-8", newline = ""))
for a in column6:
    writer.writerow([a])
print("6done")
writer = csv.writer(open("7.csv", "w", encoding = "UTF-8", newline = ""))
for a in column7:
    writer.writerow([a])
print("7done")
