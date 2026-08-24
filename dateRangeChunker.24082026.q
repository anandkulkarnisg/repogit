
/ build input parameters.
sdate:.z.D;gapRange:184;iterations:4;

/ Now build a table as output which simply provides you the data range as a table with ranges calculated.
.f.rangeLambda:{patch:$[x>0;1;0];(y-{x+y*z}[patch;x+1;z];y-{x+y}[x*z;patch])};
.f.chunkRangeTblGenerator:{t:([] chunkId:1+til x;dateRange:.f.rangeLambda'[;y;z] each til x);update rangeStartDate:@[;0]'[dateRange], rangeEndDate:@[;1]'[dateRange] from t};

/ Test basic cases.Works!! 
.f.rangeLambda[0;sdate;gapRange]    /2026.02.21 2026.08.24
.f.rangeLambda[1;sdate;gapRange]    /2025.08.21 2026.02.20
.f.rangeLambda[2;sdate;gapRange]    /2025.02.18 2025.08.20
.f.rangeLambda[3;sdate;gapRange]    /2024.08.18 2025.02.17

/ Now build an iterator that creates a table using this.
chunkedDateRanges:.f.chunkRangeTblGenerator[iterations;sdate;gapRange];

/ Test another case. 3Y in total 3M or 91 days chunks.
chunkedDateRanges:.f.chunkRangeTblGenerator[12;.z.D;92];

/ Test another case. 5Y in total 1M or 30 days chunks.
chunkedDateRanges:.f.chunkRangeTblGenerator[60;.z.D;30];
chunkedDateRanges:update dayCount:rangeEndDate-rangeStartDate from chunkedDateRanges;

