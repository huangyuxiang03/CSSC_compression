# Licensed to the Apache Software Foundation (ASF) under one
# or more contributor license agreements.  See the NOTICE file
# distributed with this work for additional information
# regarding copyright ownership.  The ASF licenses this file
# to you under the Apache License, Version 2.0 (the
# "License"); you may not use this file except in compliance
# with the License.  You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing,
# software distributed under the License is distributed on an
# "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
# KIND, either express or implied.  See the License for the
# specific language governing permissions and limitations
# under the License.
#

# encoding:utf-8
from distutils import filelist
import time
from pathlib import Path
import os
import re

import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
from sklearn import datasets
import scipy.stats as ss


def entropy(data):
    prob = []
    length = len(data)
    for i in np.unique(data):
        prob.append(np.sum(data == i)/float(length))
    return ss.entropy(prob)

def repeat_words(data,limit=8):
    lenth = len(data)
    index = 0
    key = data[0]
    count = 0
    for val in data:
        if val == key:
            count+=1
        else:
            if count >= limit:
                index += count
            key=val
            count=0
    return float(index)/lenth

'''
def sortedness(data):
    if len(data) <= 1:
        return data,0
    index = len(data) // 2
    lst1 = data[:index]
    lst2 = data[index:]
    left,n1 = sortedness(lst1)
    right,n2 = sortedness(lst2)
    sorted,num = merge(left,right)
    return sorted,n1+n2+num
'''
def sortedness(data):
    length = len(data)
    count = 0
    for i in range(length-1):
        if data[i]<=data[i+1]:
            count += 1
    return count/(length-1)


def merge(lst1, lst2):
    """to Merge two list together"""
    list = []
    num = 0
    while len(lst1) > 0 and len(lst2) > 0:
        data1 = lst1[0]
        data2 = lst2[0]
        if data1 <= data2:
            list.append(lst1.pop(0))
        else:
            num += len(lst1)
            list.append(lst2.pop(0))
    if len(lst1) > 0:
        list.extend(lst1)
    else:
        list.extend(lst2)
    return list,num

def statistic(data):
    print(data)
    ave = np.nanmean(data, axis=0)
    
    std = np.nanstd(data, axis=0)
    Min = np.nanmin(data, axis=0)
    Max = np.nanmax(data, axis=0)
    std_spread = Max-Min
    diff_data = np.diff(data, axis=0)
    diff_ave = np.nanmean(diff_data, axis=0)
    diff_min = np.nanmin(diff_data, axis=0)
    diff_max = np.nanmax(diff_data, axis=0)
    diff_spread = diff_max-diff_min
    diff_std = np.nanstd(diff_data, axis=0)
    repeat = repeat_words(data)
    sort = sortedness(data.tolist())
    return "{},{},{},{},{},{},{},{}".format(
        ave,std,std_spread,
        diff_ave,diff_std,diff_spread,
        repeat,sort
    )

def calDomainSize(data):
    l = list(set(data))
    return len(l)

logger = open("feature2.csv", "w")
logger.write("Average,Standard_Variance,MAD,Average_diff,Variance_diff,Spread_diff,Entropy,Repeat_words,Increase")
data = pd.read_csv("1.csv")
value = data["a"].to_numpy()
#res = statistic(value)
res = calDomainSize(value)
logger.write("{}\n".format(res))
print("1done")
data = pd.read_csv("2.csv")
value = data["a"].to_numpy()
#res = statistic(value)
res = calDomainSize(value)
logger.write("{}\n".format(res))
print("2done")
data = pd.read_csv("3.csv")
value = data["a"].to_numpy()
#res = statistic(value)
res = calDomainSize(value)
logger.write("{}\n".format(res))
print("3done")
data = pd.read_csv("4.csv")
value = data["a"].to_numpy()
#res = statistic(value)
res = calDomainSize(value)
logger.write("{}\n".format(res))
print("4done")
data = pd.read_csv("5.csv")
value = data["a"].to_numpy()
#res = statistic(value)
res = calDomainSize(value)
logger.write("{}\n".format(res))
print("5done")
data = pd.read_csv("6.csv")
value = data["a"].to_numpy()
#res = statistic(value)
res = calDomainSize(value)
logger.write("{}\n".format(res))
print("6done")
data = pd.read_csv("7.csv")
value = data["a"].to_numpy()
#res = statistic(value)
res = calDomainSize(value)
logger.write("{}\n".format(res))
print("7done")
