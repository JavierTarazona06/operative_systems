#NAME: Javier Andres Tarazona Jimenez, Steven Baldwin
#NSID: elr490, sjb956
#Student Number: 11411898, 11300210

#!/bin/bash

check_pos() {
		[[ $1 =~ ^[[:space:]]*[0-9]+[[:space:]]*$ ]]
}

menu() {
		local vers=$1
		local n_threads=$2
		local deadline=$3
		local size=$4
		
		if ! check_pos "$n_threads"; then
			echo "Error - Nthread argument is not positive"
			return 1
		fi
		
		if ! check_pos "$deadline"; then
			echo "Error - Deadline argument is not positive"
			return 1
		fi
		
		if ! check_pos "$size"; then
			echo "$size"
			echo "Error - Size argument is not positive"
			return 1
		fi
		
		if [[ "$vers" == "partA1" ]]; then
			./partA1 "$n_threads" "$deadline" "$size"
		elif [[ "$vers" == "partA2" ]]; then
			./partA2 "$n_threads" "$deadline" "$size"
		elif [[ "$vers" == "partA3" ]]; then
			./partA3 "$n_threads" "$deadline" "$size"
		else
			echo "No Version"
			return 1
		fi
}

version=$1

if [[ -z "$version" ]]; then
	echo "Error - No version was given"
	exit 1
elif [[ ! ("$version" == "partA1" || "$version" == "partA2" 
|| "$version" == "partA3") ]]; then
	echo "Error - Version is not supported"
	exit 1
fi

if [[ "$version" == "partA1" && "$(uname -s)" != *"NT"* && 
"$(uname -s)" != "MSYS_NT"* ]]; then
	echo "Error - $version is just for windows"
	exit 1
fi
if [[ "$version" == "partA2" && "$(uname -s)" != "Linux" ]]; then
	echo "Error - $version is just for Linux"
	exit 1
fi
if [[ "$version" == "partA3" && "$(uname -s)" != "Linux" ]]; then
	echo "Error - $version is just for Linux"
	exit 1
fi



# Two input options. From file or manual
if [[ ! -t 0 ]]; then
	while read -r n_threads deadline size; do
		if [[ -z "$n_threads" || -z "$deadline" || -z "$size" ]]; then
			echo "Error - 3 ints required"
			continue
		fi
		menu "$version" "$n_threads" "$deadline" "$size"
	done
else
	while true; do
		"Welcome. For using program give version and 3 ints: number of 
		threads, deadline and size. To quit press q"
		
		echo "Type 3 params (integers) or q to quit"
		read n_threads deadline size more_args
		
		if [[ "$n_threads" == "q" ]]; then
			break
		fi
		
		if [[ -z "$more_args" ]]; then
			menu "$version" "$n_threads" "$deadline" "$size"
		else
			echo "Error - No more arguments allowed"
		fi
		
	done
fi

