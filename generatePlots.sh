#!/bin/bash

function generateData() {
	for n in {20,60,100}; do
		echo -ne "Binomial $n ... "

		./bin/binomial_stats $n >$(mktemp -u -p . ./data/binomial_${n}_XXXX.dat)

		echo -e "\rBinomial $n DONE"
	done
}

function generatePlots() {
	#TODO
}

function main() {
	generateData
	generatePlots
}

main
