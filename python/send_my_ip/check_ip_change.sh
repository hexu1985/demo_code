#!/bin/sh

function get_my_ip {
	./lookup_my_ip.py
}

function save_ip {
	if (( $# != 2 ))
	then
		echo 'invalid argument number'
		return 255
	fi

	local my_ip=$1
	local ip_file=$2
	echo $my_ip > $ip_file
}

function save_ip_if_changed {
	if (( $# != 2 ))
	then
		echo 'invalid argument number'
		return 255
	fi

	local my_ip=$1
	local ip_file=$2
	local old_ip=$(cat $ip_file)
	if [[ "$my_ip" == "$old_ip" ]]
	then
		echo 'False'
	else
		save_ip $my_ip
		echo 'True'
	fi
}

function send_ip_mail {
	echo 'send_ip_mail called'

	if (( $# < 3))
	then
		echo 'invalid argument number'
		return 255
	fi

	./send_access_ip.py "$@"
}

ip_file='/tmp/ip_file.txt'

is_ip_change="False"
my_ip='0.0.0.0'

my_ip=$(get_my_ip)

mail_addrs="783997762@qq.com 284977582@qq.com"

if [[ ! -e "$ip_file" ]]
then
	save_ip $my_ip $ip_file 
	is_ip_change="True"
else
	is_ip_change=$(save_ip_if_changed $my_ip $ip_file)
fi

echo $is_ip_change

if [[ "$is_ip_change" == "True" ]]
then
	send_ip_mail $my_ip $mail_addrs
fi

