
currentTimeStamp:.z.p;
timePart:$[`timespan;currentTimeStamp];
datePart:$[`date;currentTimeStamp];
newTimeStamp:{"P"$(,/)(string x;"T";ssr[string y;"0D";""])}[datePart;timePart]
newTimeStamp~currentTimeStamp /They are same!


sampleSym:`$"14:20:12"
"N"$string sampleSym

testTime:`$"09:41:38"
currentTimeStamp~{"P"$(,/)(string x;"T";ssr[string y;"0D";""])}[datePart;timePart]

.z.z

/remove last character of a string.
sampleStr:"Anand Kulkarni;"
-1_sampleStr

{1+1%x}/[2]
{1+1%x}/[12]

{x%2}\[10]

{max(32;x*y)}[;3]/[2]


inputStrList:("anand";"peter";"thomas";"robert");
-1 _ (,/){x,y}[;","] each inputStrList


t:([] Name:`anand`peter`thomas`alert; Age:10 20 30 40);t
type `Name xkey t
type t


t1:([] name:`Anand`Peter`Thomas;Age:1 2 3;Salary:100 200 300);t1

\\