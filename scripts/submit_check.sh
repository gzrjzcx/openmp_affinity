#!/bin/bash
DIRS=("includes" "res" "scripts" "src" "obj" "bin" "out")
FILES=("Makefile" "src/main.c" "README.md")

for i in `seq -w 0 $((${#DIRS[@]}-1))`
do
	# check if dir exists
	if [ ! -d "${DIRS[${i}]}" ]; then
		echo "${DIRS[${i}]} dir not exist!!!"
	else
		# check existent dir if is empty
		# note if dir not exist, it's viewed as this dir is empty 
		if [ -n "$(find ${DIRS[${i}]} -maxdepth 5 -empty -type d 2>/dev/null)" ]; then
			echo "${DIRS[${i}]} or ${DIRS[${i}]}/subdirs is empty!!!!!!"
		fi
	fi
done

for j in `seq -w 0 $((${#FILES[@]}-1))`
do
	if [ ! -f "${FILES[${j}]}" ]; then
		echo "${FILES[${j}]} file not exist!!!"
	fi
done