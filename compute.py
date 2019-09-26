#!/usr/bin/python3

import argparse

import multiprocessing as mp
import subprocess

import os.path
import os

def compute_stats(n):

    output_filename = '{}/{}_{:04d}.dat'.format(args.out_dir, os.path.basename(args.program), n)

    with open(output_filename, 'w+') as output:
        subprocess.call((args.program, str(n), str(args.repetitions), str(args.delta_p)), stdout=output)

    return output_filename


if __name__ == '__main__':

    parser = argparse.ArgumentParser('Compute data from binarie files into directory')

    parser.add_argument('program')
    parser.add_argument('N', type=int, nargs='+')

    parser.add_argument('--repetitions', '-r', type=int, default=50)
    parser.add_argument('--delta-p', '-d', default=0.01, type=float)

    parser.add_argument('--out-dir', '-o')

    args = parser.parse_args()

    if not os.path.exists(args.out_dir):
        os.mkdir(args.out_dir)

    with mp.Pool(processes=4) as pool:

        results = []

        for n in args.N:
            r = pool.apply_async(compute_stats, (n,), callback=print)
            results.append(r)

        for r in results:
            r.wait()

        pool.close()
        pool.join()
