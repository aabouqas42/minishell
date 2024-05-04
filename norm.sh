#!/bin/bash
while [ true ]
do
	norm=$(norminette | grep "Error" | head -n 5)
	sleep 0.5
	clear
	echo "$norm"
	sleep 1
done