




t:("SDFISFSF";enlist",") 0: `:/tmp/andhra2031.csv;
.utl.isLeapYear:{$[not x mod 4;1b;0b]};
.utl.roundNearestInteger:{$[`float;$[(x-$[`int;x])>=0.5f;$[`int;x]+1;$[`int;x]]]};
t:update prevPaymentDate:prev PaymentDate from t;
t:update prevPaymentDate:2022.03.30 from t where i=0;
t:update intDays:PaymentDate-prevPaymentDate from t;
t:update cumPrincipalRedemption:sums principalRedemption from t;
t:update effNotionalAmt:1000000-cumPrincipalRedemption from t;
t:update effNotionalAmt:1000000^prev effNotionalAmt from t;
t:update cFlowAmount:{[a;b;c;d] .utl.roundNearestInteger[c*0.01*a*b*(1%$[.utl.isLeapYear[{("I"$4#string x) mod 4}[d]];366;365])]}'[couponRate;intDays;effNotionalAmt;PaymentDate] from t;
p:select BondDescription, PaymentDate, couponRate, intDays, couponAmount:couponAmount-principalRedemption, couponStatus, principalRedemption, effNotionalAmt, cFlowAmount from t;
select from p where couponAmount<>cFlowAmount
1_([] csvCols:`$.h.tx[`csv;select BondDescription, PaymentDate, couponRate, intDays, paymentFrequency:`Quarterly, couponAmount, paymentStatus:`DUE, principalRedemption, effNotionalAmt from t])
select BondDescription, PaymentDate, couponRate, intDays, paymentFrequency:`Quarterly, couponAmount, paymentStatus:`DUE, principalRedemption, effNotionalAmt from t

select bondName:BondDescription, 
       paymentDate:{t:"." vs string x;`$(,/)(t[2];"/";t[1];"/";t[0])}'[PaymentDate],
       couponRate,
       intDays:{`$string x}'[intDays],
       paymentFrequency:`Annual,
       couponPayment:{`$string x}'[couponAmount],
       paymentStatus:`DUE,
       staggeredRedemptionAmount:`0,
       effNotionalAmount:`1000000
       from t


.utl.isLeapYear:{$[not x mod 4;1b;0b]};
.utl.roundNearestInteger:{$[`float;$[(x-$[`int;x])>=0.5f;$[`int;x]+1;$[`int;x]]]};
.bondMath.generateCashflowTrackerFromCsv:{[inputFilePathSym;paymentFrequency]
    / The script basically turns a given csv file into excel pastable output which can help track bond cashflow payments in excel using oneDrive.
    / The input is symbol path of the file and it is not hsym adjusted. We will take this and generate a table that can be dumped to excel.
    t:("SDFISFSF";enlist",") 0: hsym inputFilePathSym;
    t:update prevPaymentDate:prev PaymentDate from t;
    t:update prevPaymentDate:2022.03.30 from t where i=0;
    t:update intDays:PaymentDate-prevPaymentDate from t;
    t:update cumPrincipalRedemption:sums principalRedemption from t;
    t:update effNotionalAmt:1000000-cumPrincipalRedemption from t;
    t:update effNotionalAmt:1000000^prev effNotionalAmt from t;
    t:update cFlowAmount:{[a;b;c;d] .utl.roundNearestInteger[c*0.01*a*b*(1%$[.utl.isLeapYear[{("I"$4#string x) mod 4}[d]];366;365])]}'[couponRate;intDays;effNotionalAmt;PaymentDate] from t;
    r:select bondName:BondDescription,paymentDate:{t:"." vs string x;`$(,/)(t[2];"/";t[1];"/";t[0])}'[PaymentDate], couponRate, intDays:{`$string x}'[intDays],
       paymentFrequency:paymentFrequency,couponPayment:{`$string x}'[couponAmount],paymentStatus:`DUE,staggeredRedemptionAmount:`0,effNotionalAmount:`1000000 
       from t;
       1_([] csvResults:`$.h.tx[`csv;r])
}

t:.bondMath.generateCashflowTrackerFromCsv[`$"/tmp/andhra2031.csv";`Quarterly]




