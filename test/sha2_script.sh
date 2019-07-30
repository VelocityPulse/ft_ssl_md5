i=1
ret1=''
ret2=''
while true
do
	VAR="test/a$i"
	echo "md5 : $i"
	ret1=`./ft_ssl -sha2 $VAR`
	ret2=`shasum -a256 $VAR | grep -Eo '^[^ ]+'`
	if [[ $ret1 != $ret2 ]] ; then
		echo "$ret1 DIFF !!!!!!!!!!!!!!!!!!!!!!!!!!!!"
		echo "$ret2"
		sleep 0.2
	else
		echo "$ret1"
		echo "$ret2"
	fi
	i=$((i+1))
done
