/* NAME: Javier Andres Tarazona Jimenez, Nahian Sajid 
   NSID: elr490, Zas742
   Student Number: 11411898, 11309563

   CMPT 332 Term 1 2018

   Lab 1

   September 10, 2018
   Modified September 12, 2020
*/

#!/bin/bash

# Make sure at least one argument (architecture) is provided
if [ "$#" -lt 1 ]; then
    echo "Usage: $0 <architecture> [args...]"
    exit 1
fi

ARCH=$1
shift 

# Depending on the architecture, run the right binary
case "$ARCH" in
    x86_64)
        if [ -f ./build/bin/x86_64/sample-linux ]; then
            ./build/bin/x86_64/sample-linux "$@"
        else
            echo "the x86_64 binary is missing"
            exit 1
        fi
        ;;
    arm)
        if [ -f ./build/bin/arm/sample-linux-arm ]; then
            ./build/bin/arm/sample-linux-arm "$@"
        else
            echo "ARM binary isn’t here."
            exit 1
        fi
        ;;
    ppc)
        if [ -f ./build/bin/ppc/sample-linux-ppc ]; then
            ./build/bin/ppc/sample-linux-ppc "$@"
        else
            echo "the PPC binary couldn’t be found."
            exit 1
        fi
        ;;
    *)
        echo "Not sure what to do with this architecture: $ARCH"
        exit 1
        ;;
esac
