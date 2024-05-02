#!/bin/bash
while [ true ]
do
	leak=$(leaks minishell | grep bytes)
	sleep 0.5
	clear
	echo "$leak"
	sleep 0.5p4
done