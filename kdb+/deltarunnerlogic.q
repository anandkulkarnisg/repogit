

T0 :   qtyList:20 30 25 45 75; t0Results:`sym`total`avgSize`runType`itemToExclude!(`AAPL;195;5;`FULL;20);   /20 30 25 45 75
T1 :   t1Results:`sym`total`avgSize`runType`itemToExclude`todaysVol!(`AAPL;215;5;`DELTA;20;45); /Question is how to derive the 20 qty to be excluded in the run. [30 25 45 75 45]
T2 :   t2Results:`sym`total`avgSize`runType`itemToExclude`todaysVol!(`AAPL;250;5;`DELTA;30;60); /[25 45 75 45 60] is the list and 30 was excluded...

Question : 
[a]. How do you track moving average and first item to be removed in a next-delta-run from previous delta-run ?
[b]. How does moving average of adjustments work against change of a) entityLevel b) change of averaging days,  in between runs due to calibration updates ? [ or any other change forseen in day to day run ] ?