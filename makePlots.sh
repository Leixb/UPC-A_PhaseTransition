#!/bin/bash

REP=${REP:-500}
FOLDER="${FOLDER:-data}"
DY=${DY:-0.1}

XMIN=${XMIN:-0}
XMAX=${XMAX:-1}

YLABEL="${YABEL:-Nombre de components connexos}"
XLABEL="${XLABEL:-x}"

PLOT_DIR="${PLOT_DIR:-plots}"
EXT="${EXT:-pdf}"

# 1: binary file
function compute() {
	python compute.py "$1" -r $REP -d $DY -o "$FOLDER" $VALORS_N
}

# 1: datafile, 2: title, 3: outputfile
function plot() {
	python plot.py -t "$2" -x "$XLABEL" -y "$YLABEL" --xmin $XMIN --xmax $XMAX \
		-o "$3" "$1" 2>/dev/null
}

# 1: datafile
function get_n() {
	head "$1" -n 1 | cut -d' ' -f2
}

# 1: Title to pass
function pipe() {
	while read datafile; do

		# Afegim N=... al titol
		N="$(get_n $datafile)"
		title="$1 \$$N\$"

		bname="$(basename $datafile)"
		outputfile="${PLOT_DIR}/${bname%.dat}.$EXT"

		echo "Ploting : $datafile -> $outputfile ($title)"

		plot "$datafile" "$title" "$outputfile"
	done
}

mkdir -p "$PLOT_DIR"

VALORS_N="${*:-10 20 30 40 50}"

(compute ./bin/geo_Ncomp | XLABEL=r pipe "Geometric Random Graph")&
(compute ./bin/bin_Ncomp | XLABEL=p pipe "Binomial Random Graph")&

wait
