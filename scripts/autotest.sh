#!/bin/bash

#executables array
EXEC=("bin/affinity" "bin/serial" "bin/runtime" "bin/best_schedule_loop_1" "bin/best_schedule_loop_2")

#threads variable
THREADS="1 2 4 8 16"
REPS=1

outfile="res/test_results.csv"
temp_testfile="out/test_temp.txt"
temp_last_element="out/test_element.txt"
temp_merge="out/test_merge.txt"

# printf title head to csv file
printf "exec, num_threads, reps, result_1, time_1, result_2, time_2\n" > ${outfile}

for i in `seq -w 0 $((${#EXEC[@]}-1))`
do
	for j in ${THREADS}
	do
		export OMP_NUM_THREADS=${j}
		echo "Running ${EXEC[${j}]} on ${j} threads"
		for k in `seq 0 ${REPS}`
		do
			echo "Starting repetition ${k}"
			echo "${i}, ${j}, ${k}," > ${temp_testfile}
			#execute executable file
			${EXEC[${i}]} > ${temp_last_element}
			# get last element of each line
			awk '{print $NF}' $temp_last_element > ${temp_merge}
			# combine 4 lines into 1 line, separated by commas
			awk 'NR%4{printf "%s, ",$0;next;}1' ${temp_merge} >> ${temp_testfile}
			# combine 2 lines into 1 line, separated by commas
			awk 'NR%2{printf "%s ",$0;next;}1' ${temp_testfile} >> ${outfile}
		done
	done
done

#remove all temp files
rm -f ${temp_testfile} ${temp_last_element} ${temp_merge}

# -------------------
# echo "${EXEC[@]}"          --->   (all items)
# echo "${#EXEC[@]}"         ---> 5 (the number of all items)
# echo "$((${#EXEC[@]}-1))". ---> 4 (two pairs of brackets are used for -1)
# seq -w 0 $((${#EXEC[@]}-1)). ---> get a sequence from 0 to 4
# $() is the command substitute, similar to the ``, it means the subshell will execute
# the command firstly and then return the result.
# As for mathmatic calculation, the () is necessary to define this is an expression

# The reason for combining 4 lines into 1 line is that the original code print results
# as 4 lines, and the reason for combine 2 lines into 1 line is that we need combine 
# the current i,j,k and running results to 1 line.