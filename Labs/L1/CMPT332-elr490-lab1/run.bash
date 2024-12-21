#NAME: Javier Andres Tarazona Jimenez
#NSID: elr490
#Student Number: 11411898
*/

#CMPT 332 Term 1 2024

#Lab 1

#September 12, 2024
#Modified September 12, 2024

#!/bin/bash

SYSARCH=$(uname -m)

case "$SYSARCH" in
	x86_64)
		ARCHIC="x86_64"
		BINA="./sample-linux"
		;;
	aarch64 | arm64 | arm | armv7l | armv6l)
		ARCHIC="arm"
		BINA="./sample-linux-arm"
		;;
	ppc64 | ppc)
		ARCHIC="ppc"
		BINA="./sample-linux-ppc"
		;;
	*)
		echo "Unsupported achitecture: $SYSARCH"
		exit 1
		;;
esac

if [ "$#" -lt 1 ] || [ "$#" -gt 1 ]; then
	echo "An argument must be sent"
	exit 1
fi

if [ ! -f "$BINA" ]; then
	echo "Oh no, there is no file $BINA :("
	exit 1
fi

MYARGS="$@"

$BINA $MYARGS


