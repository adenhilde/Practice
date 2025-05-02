#!/bin/bash
# Aden Hilderbrand
# CI 201 01PC
# 
# this script receives two numbers from the user 

FILE=finaloutput.txt

date > $FILE 
echo >> $FILE 

squares() {
	local firstNumber=$1
	local secondNumber=$2

	date >> $FILE 
	echo "#########################" >> $FILE

	echo -e "\nThe numbers entered are: $firstNumber and $secondNumber\n" | tee -a $FILE 
	
	if [[ $firstNumber -eq $secondNumber ]]; then 
		echo -e "The two numbers are equal\n" | tee -a $FILE 
		main	
	elif [[ $firstNumber > $secondNumber ]]; then
		high=$firstNumber
		low=$secondNumber	
	elif [[ $firstNumber < $secondNumber ]]; then
		high=$secondNumber
		low=$firstNumber
	fi
	
	while [[ $low -le $high ]]; do
		echo "The square of $low is $(($low * $low))" | tee -a $FILE
		((low++))
	done

}

main() {
prompt="Y"

echo "Enter two numbers please"

while [[ $prompt = [Y/y]* ]]; do
	read -p "Number 1: " firstNumber 
	read -p "Number 2: " secondNumber

	squares $firstNumber $secondNumber

	echo -e "\n"
	read -p "Continue with new numbers? [Yes/No]" prompt
done

echo -e "\nGoodbye"
exit
}

main
