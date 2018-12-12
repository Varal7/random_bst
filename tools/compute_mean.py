import os
from collections import defaultdict
from statistics import mean, stdev
import csv;

datasets = ["bll", "br-actif", "br-support", "br", "faerix", "federez", "pasloin", "platal", "ragal", "root-br", "x", "x2013", "x2014"]
ds = defaultdict(list)

def one_decimal(num):
    return "{:.1f}".format(num/1000.0)


first = True
ds_names = []

for dataset in datasets:
    with open('testRealSequencelog' +  dataset + '.csv', newline='') as csvfile:
        dt = csv.reader(csvfile)
        for row in dt:
            ds[row[0]].append(float(row[3]))

    if first:
        first = False
        ds_names = [k for k in ds]

        print("dataset", end=",")
        for k in ds_names:
            print(k, end=",")
        print()

    print(dataset, end=",")
    for k in ds_names:
        print(one_decimal(mean(ds[k])) + "+-" + one_decimal(stdev(ds[k])), end=",")
    print()


