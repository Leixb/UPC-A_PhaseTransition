#!/usr/bin/python3

import multiprocessing as mp
import subprocess

import os.path
import os

import numpy as np
import matplotlib.pyplot as plt

import argparse

def compute_stats(n):

    output_filename = '{}/{}_{:04d}.dat'.format(args.out_dir, os.path.basename(args.program), n)

    print(output_filename)

    with open(output_filename, 'w+') as output:
        subprocess.call((args.program, str(n), str(args.repetitions), str(args.delta_p)), stdout=output)

    return output_filename

def plot(filename):
    plot_filename = filename.replace('.dat', '.png')


    data = np.genfromtxt(filename)

    #(x, y) = np.sort(data, axis=0).T
    (x, y) = data.T

    plt.scatter(x, y, marker='x', zorder=10, clip_on=False)
    #plt.plot(x, y)

    plt.title(os.path.basename(filename))
    plt.xlabel(args.xlabel)
    plt.ylabel(args.ylabel)
    #plt.xlim(0, 1)
    #plt.ylim(0, 1)

    plt.savefig(plot_filename)
    plt.close()

    print('Plotted: ', filename)


if __name__ == '__main__':

    parser = argparse.ArgumentParser('.')
    parser.add_argument('program')
    parser.add_argument('--repetitions', '-r', type=int, default=50)
    parser.add_argument('--delta-p', '-d', default=0.01, type=float)
    parser.add_argument('N', type=int, nargs='+')
    parser.add_argument('--out-dir', '-o')
    parser.add_argument('--ylabel', '-y', type=str, default='')
    parser.add_argument('--xlabel', '-x', type=str, default='')

    args = parser.parse_args()

    if not os.path.exists(args.out_dir):
        os.mkdir(args.out_dir)

    def compute_stats_wrapped(n):
        print('Started   N=', n)
        filename = compute_stats(n)
        print('Finished  N=', n)

        return filename

    with mp.Pool(processes=4) as pool:

        results = []

        for nn in args.N:
            r = pool.apply_async(compute_stats_wrapped, (nn,), callback=plot)
            results.append(r)

        for r in results:
            r.wait()

        pool.close()
        pool.join()
