#!/bin/bash

# set the path for picking up the files.
export rawCashFlowFilesPath="$HOME/git/repogit/kdb+/bondMath"

echo -e "BondDescription|intDate|couponRate|intDays|paymentFrequency|cashFlowAmount|paymentStatus|principalRedemption|effNotionalAmount"
generateCashFlowSchedule.sh ${rawCashFlowFilesPath}/rawCashFlowSchedules/ugro2025.txt "UGRO 19 JAN 2025 Monthly(S)" 10.25 Monthly 1000000 2022.01.19
generateCashFlowSchedule.sh ${rawCashFlowFilesPath}/rawCashFlowSchedules/up2027.txt "U.P Power Corporation Ltd 9.75(S)" 9.75 Quarterly 1000000 2027.10.20
generateCashFlowSchedule.sh ${rawCashFlowFilesPath}/rawCashFlowSchedules/up2031.txt "A sample bond" 9.7 Quarterly 1000000 2022.06.01
generateCashFlowSchedule.sh ${rawCashFlowFilesPath}/rawCashFlowSchedules/andhra2031.txt "Andhra Pradesh State Beverages Corpotation 2031(S)" 9.62 Quarterly 1000000 2022.06.14
generateCashFlowSchedule.sh ${rawCashFlowFilesPath}/rawCashFlowSchedules/kudgi2031.txt "Kudgi Transmissions Limited 9.14 2031" 9.14 Annual 1000000 2017.03.31
generateCashFlowSchedule.sh ${rawCashFlowFilesPath}/rawCashFlowSchedules/hinduja2024.txt "Hinduja 2024 Bond(US)" 9.2 Annual 1000000 2021.09.13
generateCashFlowSchedule.sh ${rawCashFlowFilesPath}/rawCashFlowSchedules/shriram2024.txt "Shriram 10.25 2024(US)" 10.25 Monthly 1000000 2021.11.28
