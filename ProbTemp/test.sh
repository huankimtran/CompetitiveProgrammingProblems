#!/bin/bash

SOLUTION_SOURCE_CODE='main.cpp'
SOLUTION_RUN_FILE_NAME='main.o'
TEST_CASE_FOLDER='testcases'
FAIL_COLOR='\033[0;31m'		# RED
PASS_COLOR='\033[0;34m'		# BLUE
NO_COLOR='\033[0m'
PATH_TO_THIS_SCRIPT=$0
PATH_TO_SCRIPT_FOLDER="$(dirname $PATH_TO_THIS_SCRIPT)"
PATH_TO_USER_SOLUTION="$PATH_TO_SCRIPT_FOLDER/$SOLUTION_RUN_FILE_NAME"
PATH_TO_TEST_CASE="$PATH_TO_SCRIPT_FOLDER/$TEST_CASE_FOLDER"
make
chmod +x $PATH_TO_USER_SOLUTION 
for test_inp_file in $PATH_TO_TEST_CASE/*.inp
do
	path_to_testcase_inp="$test_inp_file"
	path_to_testcase_solution="$PATH_TO_TEST_CASE/$(basename "$test_inp_file" .inp).out"
	testcase_solution="$(cat $path_to_testcase_solution)"
	user_program_output="$(cat $path_to_testcase_inp | $PATH_TO_USER_SOLUTION )"
	if [[ "$testcase_solution" == "$user_program_output" ]]
	then
		printf "${test_inp_file}\t${PASS_COLOR}PASS${NO_COLOR}\n"
	else
		printf "${test_inp_file}\t${FAIL_COLOR}FAIL${NO_COLOR}\n"
		printf "User program output:\n$user_program_output\n"
		printf "Solution:\n$testcase_solution\n"
	fi 
done
