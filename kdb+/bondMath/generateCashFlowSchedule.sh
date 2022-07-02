#!/bin/bash
# Author : Anand Kulkarni
# Date : 01/07/2022
# Synopsis : Adding a simple utility to convert cashflow schedule from thefixedincome.com website into a csv format that excel can import.

# First we verify if the input parameters to the script are proper.
if [ $# -ne 6 ]; then
  echo -e "Wrong number of parameters passed. The below is correct format example for invocation."
  echo -e "$0 [input cfschedule] [Bond Name Description] [Coupon Rate] [Payment Frequency] [bondParValue] [bondIssueDate]"
  exit 1
fi

cfScheduleInput=$1
bondDescription=$2
couponRate=$3
paymentFrequency=$4
bondFaceValue=$5
bondIssueDate=$6

# First preprocess the file.
bufferFileName=${cfScheduleInput}.$$
outputCsvResult=${cfScheduleInput}.$$.csv

# Generate as below.
echo -e "BondDescription,paymentDate,couponRate,intDays,couponFrequency,couponAmount,couponStatus,principalRedemption">${bufferFileName}.3
cat ${cfScheduleInput}|sed "s/,//g"|sed "s/ INR (A)//g"|awk 'BEGIN { FS = OFS = "\t" } { for(i=1; i<=NF; i++) if($i ~ /^ *$/) $i = 0 }; 1'>${bufferFileName}.1
cat ${bufferFileName}.1|awk -v couponRate=${couponRate} -v paymentFrequency=${paymentFrequency} '{print "bondDescription|"$2"|"couponRate"|0|"paymentFrequency"|"$3+$4"|DUE|"$4}'>${bufferFileName}.2
cat ${bufferFileName}.3 ${bufferFileName}.2|sed "s/bondDescription/$bondDescription/g"|sed "s/|/,/g" > ${outputCsvResult}
rm -f ${bufferFileName} ${bufferFileName}.1 ${bufferFileName}.2 ${bufferFileName}.3

# Here we invoke q at 5000 port with bondMath library and run the q script at initialization
# prepare the q script here.

export qScript=${outputCsvResult}.q
#echo -e "qScript is ${qScript}"
echo -e "\l /home/anand/git/repogit/kdb+/bondMath/bondMath.q">${qScript}
echo -e "finalCashFlowResults:.bondMath.generateCashflowTrackerFromCsv[\`$\"${outputCsvResult}\";\`${paymentFrequency};${bondIssueDate};${bondFaceValue}];">>${qScript}
echo -e "save \`:/tmp/finalCashFlowResults.csv">>${qScript}
echo -e "\\\\\\">>${qScript}

# Execute the script and dump out the results.
~/runq5000 ${qScript} -q >/dev/null 2>&1
cat /tmp/finalCashFlowResults.csv|grep -v "csvResults"|sed '1,3d'

# Do the final cleanup.
rm -f ${outputCsvResult} ${qScript} /tmp/finalCashFlowResults.csv

exit 0
