#NAME: Javier Andres Tarazona Jimenez
#NSID: elr490
#Student Number: 11411898

#!/bin/bash


if [[ -z "$1" ]]; then
	echo "Provide test or size_people_shop size_peope_approach_shop"
	exit 1
fi

if [[ "$1" == "test" ]]; then
	./Lab3_test
else
	if [[ -z "$2" ]]; then
		echo "Provide size_peope_approach_shop"
		exit 1
	fi
		./Lab3 "$1" "$2"
fi
