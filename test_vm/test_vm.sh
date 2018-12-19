#!/bin/sh

REF="./zaz/"
TESTED="./yours/"

CHAMPS=`ls -1 ./champs/*.s`

if [ ! -d "tmp/champs" ]; then
	`mkdir -p tmp/champs`
fi

echo "\n[Compiling champs with ZAZ's asm]\n"

for ENTRY in $CHAMPS
do
	#compiling champs with ref compiler
	${REF}asm $ENTRY
	`mv ${ENTRY/.s/.cor} tmp/champs/`
done

echo "\n[UNIT TEST CHAMPS]\n"

CHAMPS=`ls -1 ./tmp/champs/*.cor`

if [ ! -d "tmp/utest" ]; then
	`mkdir -p tmp/utest/diff`
fi

for ENTRY in $CHAMPS
do
	FILE=`basename ${ENTRY/.cor/}`
	O1=${FILE}_zaz.ouput
	O2=${FILE}_yours.ouput

	${REF}corewar -v 31 $ENTRY > ./tmp/utest/$O1 #2>/dev/null
	ER1=$?
	[ "$ER1" -eq "1" ] &&
		echo "\033[33mERROR\033[0m from zaz on $FILE"
	${TESTED}corewar -v 31 $ENTRY > ./tmp/utest/$O2 #2>/dev/null
	ER2=$?
	[ "$ER2" -eq "1" ] &&
		echo "\033[33mERROR\033[0m from you on $FILE"
	if [ ! $ER1 -eq "1" -a ! $ER2 -eq "1" ]; then
		diff ./tmp/utest/$O1 ./tmp/utest/$O2 > ./tmp/utest/diff/${FILE}.diff
		if [ "$?" = "0" ]; then
			echo "$FILE\t\033[32m OK\033[0m"
		else
			echo "$FILE\t\033[31m KO\033[0m"
		fi
	fi
done
