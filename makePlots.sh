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
	python3 compute.py "$1" -r $REP -d $DY -o "$FOLDER" $VALORS_N
}

# 1: datafile, 2: title, 3: outputfile
function plot() {
	python3 plot.py -t "$2" -x "$XLABEL" -y "$YLABEL" --xmin $XMIN --xmax $XMAX \
		-o "$3" "$1" 2>/dev/null
}

function plot_mult() {
	python3 plot.py -t "$TITLE" -x "$XLABEL" -y "$YLABEL" --xmin $XMIN --xmax $XMAX \
		-o "$OUTPUT" --show-legend $@ 2>/dev/null
}

# 1: datafile
function get_n() {
	head -n 1 "$1" | cut -d' ' -f2
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

VALORS_N="$*"


compute ./bin/geo_Ncomp | XLABEL=r pipe "Geometric Random Graph"
compute ./bin/bin_Ncomp | XLABEL=p pipe "Binomial Random Graph"


TITLE="Geometric Random Graph" OUTPUT="${PLOT_DIR}/geo_mult.$EXT" plot_mult "${FOLDER}/geo*.dat"
TITLE="Binomial Random Graph" OUTPUT="${PLOT_DIR}/bin_mult.$EXT" plot_mult "${FOLDER}/bin*.dat"

wait
