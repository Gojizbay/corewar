#!/bin/sh

REF="./zaz/"
TESTED="./yours/"

CHAMPS=`ls -1 ./champs/*.s`

if [ ! -d "tmp" ]; then
	`mkdir tmp`
fi

#if [ ! -d "tmp/cor_champs" ]; then
#	`mkdir tmp/cor_champs`
	for ENTRY in $CHAMPS
	do
		`${REF}asm $ENTRY`
	done
#fi
