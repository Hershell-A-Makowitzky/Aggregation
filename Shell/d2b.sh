#!/bin/bash

## Binary formated output of provided 32-bit possitive integer number 

# Process a number from the command line
NUMBER=$(echo "$1" | grep -E "^[0-9]+$")
LIMIT=4294967296

# Test if provided number is a possitive integer
if test -z "$NUMBER"
then
    echo "Malformated input."
    exit 1
fi

# Test if provided number has 32-bit width
if test $(($1)) -ge $LIMIT
then
    echo "Provided number is exceeds 32-bit limitation."
    exit 2
fi

# Construction of the (256 x 8-bit) matrix
MATRIX=($(echo {0..1}{0..1}{0..1}{0..1}{0..1}{0..1}{0..1}{0..1}))

# Results for every byte in provided 32-bit number
RESULT_CHAR=$(echo "$NUMBER%256" | bc)
NUMBER=$(($NUMBER >> 8))
RESULT_SHORT=$(echo "$NUMBER%256" | bc)
NUMBER=$(($NUMBER >> 8))
RESULT_SHORT_PLUS_CHAR=$(echo "$NUMBER%256" | bc)
NUMBER=$(($NUMBER >> 8))
RESULT_INT=$(echo "$NUMBER%256" | bc)
NUMBER=$(($NUMBER >> 8))

# Final output
echo "0b ${MATRIX[$RESULT_INT]} ${MATRIX[RESULT_SHORT_PLUS_CHAR]} ${MATRIX[$RESULT_SHORT]} ${MATRIX[$RESULT_CHAR]}"
