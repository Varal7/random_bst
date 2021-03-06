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
fig, ax = plt.subplots(2, 2)

# config = json.load(open('insertFromFixedInitialSize.json'))
# config = json.load(open('insertsVaryingInitialSize.json'))
# config = json.load(open('deletesVaryingInitialSize.json'))
# config = json.load(open('heights.json'))

# data_files = ['zip_insertsVaryingInitialSize.json',
              # 'zip_uniformAccessVaryingInitialSize.json',
              # 'zip_deletesVaryingInitialSize.json',
              # 'zip_zipfAccessVaryingInitialSize.json']
data_files = ['other_insertsVaryingInitialSize.json',
              'other_uniformAccessVaryingInitialSize.json',
              'other_deletesVaryingInitialSize.json',
              'other_zipfAccessVaryingInitialSize.json']

i = 0
for data_file in data_files:
    config = json.load(open(data_file))
    # config = json.load(open('potential.json'))
    # config = json.load(open('accessSubset.json'))
    # config = json.load(open('accessChangeSubset.json'))

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
        ax[i % 2][int(i/2)].plot(ds1[d][0], ds1[d][1], lw=2, label=d)
    # ax.fill_between(ds1[d][0], [ds1[d][1][x] + ds1[d][2][x] for x in range(len(ds1[d][1]))], [ds1[d][1][x] - ds1[d][2][x] for x in range(len(ds1[d][1]))], alpha=0.5)


    ax[i % 2][int(i/2)].set_title(title)
    ax[0][0].legend(loc='upper left')
    ax[i % 2][int(i/2)].set_xscale("log", nonposx='clip')
    ax[i % 2][int(i/2)].set_yscale("log", nonposy='clip')

    n_to_l = 'acbd'
    ax[i % 2][int(i/2)].text(-0.1, 1.1, "(" + n_to_l[i] + ")", transform=ax[i % 2][int(i/2)].transAxes)
    i = i + 1

ax[1][0].set_xlabel(axis[0][1])
ax[1][1].set_xlabel(axis[0][1])
ax[0][0].set_ylabel(axis[1][1].replace("microsecond", r"$\mu$"))
ax[1][0].set_ylabel(axis[1][1].replace("microsecond", r"$\mu$"))
plt.show()
