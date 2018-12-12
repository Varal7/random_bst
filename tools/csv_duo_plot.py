import numpy
from scipy.sparse import csr_matrix, csgraph
import random
import matplotlib
matplotlib.use('TkAgg')
import matplotlib.font_manager
import matplotlib.pyplot as plt

import string

matplotlib.font_manager._rebuild()
from matplotlib import rc
from statistics import mean,stdev
import csv


# rcParams['font.family'] = ['Times']
# rcParams['font.size'] = 10.0

rc('font', **{'family': 'serif', 'serif': ['Computer Modern']})
rc('text', usetex=False)


import matplotlib.pyplot as pyp
import matplotlib.ticker as ticker

from collections import defaultdict

import json


# Set up plot axes
#ax = [0,0,0,0]
fig, axes = plt.subplots(1, 2)

data_files = [
    'heights.json',
    'depth.json',
    ]
i = 0

for (ax, data_file) in zip(axes.flatten(), data_files):
    config = json.load(open(data_file))

    filename = config['filename']
    axis =  config['axis']
    title =  config['title']
    compute_y_x_ratio = config['compute_y_x_ratio']


    required_fields = ['data_structure'] + [axis[0][0],  axis[1][0]]

    print(required_fields)

    data = defaultdict(lambda: defaultdict(list))
    meta_data = defaultdict(lambda: None)


    with open(filename, newline='') as csvfile:
        dt = csv.DictReader(csvfile)
        print(dt.fieldnames)
        for field in required_fields:
            assert(field in dt.fieldnames)
        for row in dt:
            if row['data_structure'] in ['ZipTreeFindBeforeInsert', 'ZipTreeFracRank']:
                continue
            y = float(row[axis[1][0]])
            x = int(row[axis[0][0]])
            if compute_y_x_ratio:
                y = y / x
            data[row['data_structure']][x].append(y)
            for field in dt.fieldnames:
                if field not in required_fields:
                    if meta_data[field] is None:
                        meta_data[field] = row[field]
                    else:
                        assert(meta_data[field] == row[field])

    print(dict(meta_data))

    # ds1 = {"ZipTree":[[],[],[]],"Treap":[[],[],[]],"SkipList":[[],[],[]],"SplayTree":[[],[],[]]}

    ds1 = defaultdict(lambda: [[], [], [], []])

    for data_structure in data:
        for x_val in data[data_structure]:
            ds1[data_structure][0].append(int(x_val))
            ds1[data_structure][1].append(mean(data[data_structure][x_val]))
            ds1[data_structure][2].append(stdev(data[data_structure][x_val]))
            ds1[data_structure][3].append(len(data[data_structure][x_val]))


    print(ds1)


# plot it! "map":"#1ABC9C"
# color = {"ZipTree":"#D35400","Treap":"#F4D03F","SkipList":"#2ECC71","SplayTree":"#8E44AD"}
    for d in data:
    # ax.plot(ds1[d][0], ds1[d][1], lw=2, label=d, color=color[d])
    # ax.fill_between(ds1[d][0], [ds1[d][1][x] + ds1[d][2][x] for x in range(len(ds1[d][1]))], [ds1[d][1][x] - ds1[d][2][x] for x in range(len(ds1[d][1]))], facecolor=color[d], alpha=0.5)
        ax.plot(ds1[d][0], ds1[d][1], lw=2, label=d)
    ax.fill_between(ds1[d][0], [ds1[d][1][x] + ds1[d][2][x] for x in range(len(ds1[d][1]))], [ds1[d][1][x] - ds1[d][2][x] for x in range(len(ds1[d][1]))], alpha=0.5)


    ax.set_title(title)
    ax.set_xscale("log", nonposx='clip')
    ax.set_yscale("log", nonposy='clip')
    ax.set_xlabel(axis[0][1])
    if i == 0:
        ax.legend(loc='upper left')
    ax.set_ylabel(axis[1][1].replace("microsecond", r"$\mu$"))

    n_to_l = 'abc'
    ax.text(-0.1, 1.1, "(" + n_to_l[i] + ")", transform=ax.transAxes)
    i = i + 1

plt.show()
