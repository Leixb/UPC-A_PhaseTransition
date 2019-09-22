from sage.graphs.graph_input import from_dict_of_lists

g = Graph()

import subprocess

args = ("./bin/test_binomial_gen", "10", "0.15")
popen = subprocess.Popen(args, stdout=subprocess.PIPE)
popen.wait()
output = popen.stdout.read()

print(output)

from_dict_of_lists(g, eval(output))
