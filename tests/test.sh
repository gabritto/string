#!/bin/bash
RUNS=3
echo -e "Input:\n\tAlgorithm\n\tText file\n\tPatterns file\n"
read ALG # get algorithm
read TXT # get text file
read PAT # get patterns file

while IFS='' read -r LINE || [[ -n "$LINE" ]]; do
  LEN=${#LINE}
  if [ $LEN -gt 0 ]; then
    for i in `seq 1 $RUNS`; do
      (time ./../src/main -c -a $ALG LINE $TXT) 2>> $ALG$LEN.txt
    done
  fi
done < "$PAT"

