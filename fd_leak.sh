while [ true ]
do
	ttys=$(lsof -c minishell | grep /dev/ttys | awk '{printf("%s pid:[%s] %s fd:[%s]\n", $1, $2, $3, $4)}')
	leak_pipe=$(lsof -c minishell | grep PIPE | awk '{printf("%s pid:[%s] %s fd:[%s]\n", $1, $2, $3, $4)}')
	sleep 0.5;
	clear
	echo "$ttys\n$leal_pipe"
	sleep 0.5;
done