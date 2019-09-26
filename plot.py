#!/usr/bin/python3

import argparse

import numpy as np
import matplotlib.pyplot as plt

def get_data(file):
    data = np.genfromtxt(file.name)
    return data.T


def main():

    parser = argparse.ArgumentParser('Plot from data file')

    parser.add_argument('datafile', type=argparse.FileType('r'), nargs='+')

    parser.add_argument('--title', '-t', type=str, default='')
    parser.add_argument('--xlabel', '-x', type=str, default='')
    parser.add_argument('--ylabel', '-y', type=str, default='')

    parser.add_argument('--xmin', type=float, default=0)
    parser.add_argument('--xmax', type=float, default=1)

    parser.add_argument('--show-legend', action='store_true')
    parser.add_argument('--scatter', action='store_true')

    parser.add_argument('--output', '-o', type=str, default='')

    args = parser.parse_args()

    plt.title(args.title)
    plt.xlabel(args.xlabel)
    plt.ylabel(args.ylabel)

    data = map(get_data, args.datafile)

    for (x, y) in data:
        if args.scatter:
            plt.scatter(x, y, label=int(y[0]))
        else:
            plt.plot(x, y, label=int(y[0]))

    if args.show_legend:
        plt.legend(title='N')

    plt.xlim(args.xmin, args.xmax)

    plt.savefig(args.output)

if __name__ == '__main__':
    main()
