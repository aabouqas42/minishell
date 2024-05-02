while [ true ]
do
	leak=$(lsof -c minishell | grep PIPE | awk '{printf("\t\t%s pid:[%s] fd:[%s] %s\n", $1, $2, $4, $5)}')
	echo "$leak"
	sleep 1;
	clear
done