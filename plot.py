#!/usr/bin/python3

import multiprocessing as mp
import subprocess

import os.path
import os
import glob

import numpy as np
import matplotlib.pyplot as plt

import argparse

def get_data(filename):
    data = np.genfromtxt(filename)
    return data.T


if __name__ == '__main__':

    parser = argparse.ArgumentParser('.')
    parser.add_argument('out_dir')
    parser.add_argument('prog')
    parser.add_argument('--ylabel', '-y', type=str, default='')
    parser.add_argument('--xlabel', '-x', type=str, default='')
    parser.add_argument('--title', '-t', type=str, default='')
    parser.add_argument('--output', '-o', type=str, default='')

    args = parser.parse_args()

    if not os.path.exists(args.out_dir):
        os.mkdir(args.out_dir)


    with mp.Pool(processes=4) as pool:

        results = []

        for data_file in glob.glob("{}/{}*.dat".format(args.out_dir, args.prog)):
            print(data_file)
            r = pool.apply_async(get_data, (data_file,))
            results.append(r)

        data = []
        for r in results:
            data.append(r.get())

        pool.close()
        pool.join()

    plt.title(args.title)
    plt.xlabel(args.xlabel)
    plt.ylabel(args.ylabel)

    for (x, y) in data:
        plt.plot(x, y, label=int(y[0]))

    plt.legend(title='N')

    plt.xlim(0, 1)
    #plt.ylim(0, 1)

    plt.savefig(args.output)
