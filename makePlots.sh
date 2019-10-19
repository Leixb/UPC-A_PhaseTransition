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
	NAME="$1_$2"
	OUTPUT="${PLOT_DIR}/${NAME}.$EXT"
	echo "Ploting : $OUTPUT ($TITLE)"
	python3 plot.py -t "$TITLE" -x "$XLABEL" -y "$YLABEL" --xmin $XMIN --xmax $XMAX \
		-o "$OUTPUT" --show-legend "${FOLDER}/${NAME}"*.dat 2>/dev/null
}

function plot_mult_bingeo() {
	TITLE="${TITLE}${TITLE_GRG}" 	XLABEL=r plot_mult GRG $@
	TITLE="${TITLE}${TITLE_BRG}" 	XLABEL=p plot_mult BRG $@
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

TITLEeulerianCycle="Cicle eulerià"
TITLEeulerianPath="Camí eulerià"
TITLEcicle="Cicles"
TITLEmidaCompConMax="Mida de la component conexa gegant"
TITLEesConnex="Connectivitat"
TITLEnumCompCon="Components conexes"

TITLE_GRG=" en Geometric Random Graph"
TITLE_BRG=" en Binomial Random Graph"

LABELeulerianCycle="Probabilitat de contenir un cicle eulerià"
LABELeulerianPath="Probabilitat de contenir un camí eulerià"
LABELcicle="Probabilitat de contenir un cicle"
LABELmidaCompConMax="Mida esperada de la component connexa gegant"
LABELesConnex="Probabilitat de ser connex"
LABELnumCompCon="Nombre de components connexos esperats"

if [ $# -ne 0 ]; then
	XLABEL=r
	DY=0.10 compute GRG numCompCon	 		| YLABEL="$LABELnumCompCon" 		pipe "${TITLEnumCompCon}${TITLE_GRG}"
	DY=0.01 compute GRG esConnex 			| YLABEL="$LABELesConnex"			pipe "${TITLEesConnex}${TITLE_GRG}"
	DY=0.10 compute GRG midaCompConMax 		| YLABEL="$LABELmidaCompConMax"		pipe "${TITLEmidaCompConMax}${TITLE_GRG}"
	DY=0.01 compute GRG cicle 				| YLABEL="$LABELcicle"				pipe "${TITLEcicle}${TITLE_GRG}"
	DY=0.01 compute GRG eulerianPath 		| YLABEL="$LABELeulerianPath"		pipe "${TITLEeulerianPath}${TITLE_GRG}"
	DY=0.01 compute GRG eulerianCycle 		| YLABEL="$LABELeulerianCycle"		pipe "${TITLEeulerianCycle}${TITLE_GRG}"

	XLABEL=p
	DY=0.10 compute BRG numCompCon	 	 	| YLABEL="$LABELnumCompCon"			pipe "${TITLEnumCompCon}${TITLE_BRG}"
	DY=0.01 compute BRG esConnex	 	 	| YLABEL="$LABELesConnex"			pipe "${TITLEesConnex}${TITLE_BRG}"
	DY=0.10 compute BRG midaCompConMax 	 	| YLABEL="$LABELmidaCompConMax"		pipe "${TITLEmidaCompConMax}${TITLE_BRG}"
	DY=0.01 compute BRG cicle 			 	| YLABEL="$LABELcicl"				pipe "${TITLEcicle}${TITLE_BRG}"
	DY=0.01 compute BRG eulerianPath 	 	| YLABEL="$LABELeulerianPath"		pipe "${TITLEeulerianPath}${TITLE_BRG}"
	DY=0.01 compute BRG eulerianCycle 	 	| YLABEL="$LABELeulerianCycle"		pipe "${TITLEeulerianCycle}${TITLE_BRG}"
fi

YLABEL="$LABELnumCompCon" 		TITLE="$TITLEnumCompCon" 		plot_mult_bingeo numCompCon
YLABEL="$LABELesConnex"			TITLE="$TITLEesConnex" 			plot_mult_bingeo esConnex
YLABEL="$LABELmidaCompConMax" 	TITLE="$TITLEmidaCompConMax" 	plot_mult_bingeo midaCompConMax
YLABEL="$LABELcicle"		    TITLE="$TITLEcicle" 			plot_mult_bingeo cicle
YLABEL="$LABELeulerianPath"		TITLE="$TITLEeulerianPath" 		plot_mult_bingeo eulerianPath
YLABEL="$LABELeulerianCycle"	TITLE="$TITLEeulerianCycle" 	plot_mult_bingeo eulerianCycle

wait
