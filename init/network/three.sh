ifconfig en1 | grep ether | awk 'ether/{print $2}'
