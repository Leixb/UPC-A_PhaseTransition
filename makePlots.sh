#!/bin/bash

REP=${REP:-500}
FOLDER="${FOLDER:-data}"
DY=${DY:-0.1}

XMIN=${XMIN:-0}
XMAX=${XMAX:-1}

YLABEL="${YABEL:-y}"
XLABEL="${XLABEL:-x}"

PLOT_DIR="${PLOT_DIR:-plots}"
EXT="${EXT:-pdf}"

# 1: binary file
function compute() {
	python3 compute.py "$1" "$2" -r $REP -d $DY -o "$FOLDER" $VALORS_N
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

compute GRG numCompCon	 	| YLABEL="Avg. Mida component connexa gegant" 	XLABEL=r pipe "Components conexes en Geometric Random Graph"
compute GRG midaCompConMax 	| YLABEL="Avg. Mida component connexa gegant" 	XLABEL=r pipe "Mida component conexa gegant en Geometric Random Graph"
compute GRG cicle 			| YLABEL="Probabilitat de tenir cicle"		    XLABEL=r pipe "Cicles en Geometric Random Graph"
compute GRG eulerianPath 	| YLABEL="Probabilitat de tenir camí eulerià"	XLABEL=r pipe "Camí eulerià en Geometric Random Graph"
compute GRG eulerianCycle 	| YLABEL="Probabilitat de tenir cicle eulerià"	XLABEL=r pipe "Cicle eulerià en Geometric Random Graph"

compute BRG numCompCon	 	| YLABEL="Avg. Mida component connexa gegant" 	XLABEL=p pipe "Components conexes en Binomial Random Graph"
compute BRG midaCompConMax 	| YLABEL="Avg. Mida component connexa gegant" 	XLABEL=p pipe "Mida Component conexa gegant en Binomial Random Graph"
compute BRG cicle 			| YLABEL="Probabilitat de tenir cicle"		 	XLABEL=p pipe "Cicles en Binomial Random Graph"
compute BRG eulerianPath 	| YLABEL="Probabilitat de tenir camí eulerià" 	XLABEL=p pipe "Camí eulerià en Binomial Random Graph"
compute BRG eulerianCycle 	| YLABEL="Probabilitat de tenir cicle eulerià" 	XLABEL=p pipe "Cicle eulerià en Binomial Random Graph"

OUTPUT="${PLOT_DIR}/GRG_numCompCon.$EXT" 		YLABEL="Avg. Mida component connexa gegant" 	XLABEL=r TITLE="Components conexes en Geometric Random Graph" plot_mult_mult "${FOLDER}/GRG_numCompCon*.dat"
OUTPUT="${PLOT_DIR}/GRG_midaCompConMax.$EXT" 	YLABEL="Avg. Mida component connexa gegant" 	XLABEL=r TITLE="Mida component conexa gegant en Geometric Random Graph" plot_mult		 "${FOLDER}/GRG_midaCompConMax*.dat"
OUTPUT="${PLOT_DIR}/GRG_cicle.$EXT" 			YLABEL="Probabilitat de tenir cicle"		    XLABEL=r TITLE="Cicles en Geometric Random Graph" plot_mult		 "${FOLDER}/GRG_cicle*.dat"
OUTPUT="${PLOT_DIR}/GRG_eulerianPath.$EXT" 		YLABEL="Probabilitat de tenir camí eulerià"		XLABEL=r TITLE="Camí eulerià en Geometric Random Graph" plot_mult		 "${FOLDER}/GRG_eulerianPath*.dat"
OUTPUT="${PLOT_DIR}/GRG_eulerianCycle.$EXT" 	YLABEL="Probabilitat de tenir cicle eulerià"	XLABEL=r TITLE="Cicle eulerià en Geometric Random Graph" plot_mult		 "${FOLDER}/GRG_eulerianCycle*.dat"

OUTPUT="${PLOT_DIR}/BRG_numCompCon.$EXT" 		YLABEL="Avg. Mida component connexa gegant" 	XLABEL=p TITLE="Components conexes en Binomial Random Graph" plot_mult		 "${FOLDER}/BRG_numCompCon*.dat"
OUTPUT="${PLOT_DIR}/BRG_midaCompConMax.$EXT" 	YLABEL="Avg. Mida component connexa gegant" 	XLABEL=p TITLE="Mida Component conexa gegant en Binomial Random Graph" plot_mult		 "${FOLDER}/BRG_midaCompConMax*.dat"
OUTPUT="${PLOT_DIR}/BRG_cicle.$EXT" 			YLABEL="Probabilitat de tenir cicle"		 	XLABEL=p TITLE="Cicles en Binomial Random Graph" plot_mult		 "${FOLDER}/BRG_cicle*.dat"
OUTPUT="${PLOT_DIR}/BRG_eulerianPath.$EXT" 		YLABEL="Probabilitat de tenir camí eulerià" 	XLABEL=p TITLE="Camí eulerià en Binomial Random Graph" plot_mult		 "${FOLDER}/BRG_eulerianPath*.dat"
OUTPUT="${PLOT_DIR}/BRG_eulerianCycle.$EXT" 	YLABEL="Probabilitat de tenir cicle eulerià" 	XLABEL=p TITLE="Cicle eulerià en Binomial Random Graph" plot_mult		 "${FOLDER}/BRG_eulerianCycle*.dat"

wait
