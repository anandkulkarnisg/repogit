
/ Small utilities.
.utl.isLeapYear:{$[not x mod 4;1b;0b]};
.utl.adjustWeekEnds:{$[(t:x mod 7) in 0 1i;$[t~0i;x-1;x-2];x]};
.utl.roundNearestInteger:{$[`float;$[(x-$[`int;x])>=0.5f;$[`int;x]+1;$[`int;x]]]};
.cfg.fullOrCurrent:`c;

/ Core Logic module.
.bondMath.generateBondStaticDict:{`couponDay`issueDate`businessDate`maturityDate`couponMonths`couponRate`faceValue`excludeWeekEnds`principalRedemption!x};

/ Main module for cashflow generation.
.bondMath.generateCashFlowSchdule:{[bondInputStaticDict;redemptionSchedule]
        .bondMath.local.bondInputStaticDict:bondInputStaticDict;
        value each {(,/)(string x;":.bondMath.local.bondInputStaticDict[`";string x;"];")} each key bondInputStaticDict;
        delete bondInputStaticDict from `.bondMath.local;
        daysMonthDict:`Jan`Feb`Mar`Apr`May`Jun`Jul`Aug`Sep`Oct`Nov`Dec!31 28 31 30 31 30 31 31 30 31 30 31;
        monthInYearDict:01 02 03 04 05 06 07 08 09 10 11 12!`Jan`Feb`Mar`Apr`May`Jun`Jul`Aug`Sep`Oct`Nov`Dec;
        p:(([] day:enlist couponDay) cross ([] month:1+til 12)) cross ([] Year:$[`year;issueDate]+til (1+$[`year;maturityDate]-$[`year;issueDate]));
        / We first strip the months that are not in the couponMonths;
        p:delete from p where not any month in/: "I"$"|" vs couponMonths;
        / Now we adjust any day in each month where such a day isnt possible as per daysMonthDict.
        p:update day:{[a;b;c;d;e] $[.utl.isLeapYear[c];d[`Feb]:29;::];$[a>d[e[b]];a-1;a]}[;;;daysMonthDict;monthInYearDict]'[day;month;Year] from p;
        / Now match up the dates. Ensure weekend adjustment is applied.
        p:delete day, month, Year from update unadjCouponDate:{"D"$(,/)(string z;"-";string y;"-";string x)}'[day;month;Year] from p;
        p:update couponDate:{$[y;.utl.adjustWeekEnds[x];x]}[;excludeWeekEnds]'[unadjCouponDate] from p;
        p:update prevCouponDate:prev couponDate from `couponDate xasc p;
        p:update prevCouponDate:issueDate from p where i=1;
        p:update intDays:couponDate-prevCouponDate from p;
        p:update rate:0.01*couponRate, principal:faceValue, isLeapYear:.utl.isLeapYear'[$[`year;couponDate]] from p;
        p:update cflowAmount:{[x;y;z;l] x*y*z%$[l;366;365]}'[rate;principal;intDays;isLeapYear] from p;
        p:delete from p where i=0;
        p:select couponDate, unadjCouponDate, prevCouponDate, intDays, rate, principal, isLeapYear,
                 cflowAmount:.utl.roundNearestInteger'[cflowAmount] from p where couponDate<=maturityDate;
        p:$[`c~lower .cfg.fullOrCurrent;![p;enlist ((';~:;>);`couponDate;businessDate);0b;0#`];p];
        p:$[count redemptionSchedule;.bondMath.generateRedemptionCashflows[p;redemptionSchedule];delete prevCouponDate, unadjCouponDate from p];
        $[principalRedemption;[p:update payEventType:`I from p;p:update payEventType:`$"I+M" from p where redemptionAmt>0;
                                $[(last exec sums redemptionAmt from p)<faceValue;p:p uj ([] couponDate:enlist maturityDate;intDays:enlist 0;rate:enlist 0;
                                          principal:enlist faceValue;cflowAmount:enlist faceValue;
                                          redemptionAmt:enlist faceValue;payEventType:enlist `M
                                      );::
                                 ]
                              ];
                              p
         ];
        p
    };

/ Main module for redemption based cashflow generation.
.bondMath.generateRedemptionCashflows:{[cashFlowInput;redemptionSchedule]
        p:cashFlowInput lj `couponDate xkey select couponDate:redemptionDate, redemptionAmt from redemptionSchedule;
        p:update redemptionAmtOriginal:0^redemptionAmt*principal from p;
        p:update redemptionAmt:0f^redemptionAmt from p;
        p:update sums redemptionAmt*principal from p;
        p:update effNotionalAmt:principal-redemptionAmt from p;
        p:update effNotionalAmt:(first exec principal from p)^prev effNotionalAmt from p;
        / Recalculate the cahsflows for the period where there is redemption.
        p:update cflowAmount:0^{[x;y;z;l] x*y*z%$[l;366;365]}'[intDays;rate;effNotionalAmt;isLeapYear] from p where principal<>effNotionalAmt;
        p:update cflowAmount:cflowAmount+redemptionAmtOriginal from p;
        p:delete redemptionAmtOriginal, effNotionalAmt, prevCouponDate, unadjCouponDate, isLeapYear from update cflowAmount:.utl.roundNearestInteger'[cflowAmount], redemptionAmt:redemptionAmtOriginal from p;        
        p
  };

/ Additional utilities.
/ Identify cashflows only for a given year.
.bondMath.getCashFlowByYear:{[x;y] ?[x;enlist (=;($;enlist `year;`couponDate);y);0b;()]};

/ Get cashflow sum by year.
.bondMath.getTotalCashFlowPerYear:{?[x;();(enlist `couponDate)!enlist ($;enlist `year;`couponDate);(enlist `cflowAmount)!enlist (sum;`cflowAmount)]};

/ Add a function to implement cashflow for excel tracking api to convert csv file into cashflow xls tracker output.
/ Synopsis : .bondMath.generateCashflowTrackerFromCsv[`$"/tmp/andhra2031.csv";`Quarterly]
.bondMath.generateCashflowTrackerFromCsv:{[inputFilePathSym;paymentFrequency;issueDate;bondFaceValue]
    / The script basically turns a given csv file into excel pastable output which can help track bond cashflow payments in excel using oneDrive.
    / The input is symbol path of the file and it is not hsym adjusted. We will take this and generate a table that can be dumped to excel.
    t:("SDFISFSF";enlist",") 0: hsym inputFilePathSym;
    t:update prevpaymentDate:prev paymentDate from t;
    t:update prevpaymentDate:issueDate from t where i=0;
    t:update intDays:paymentDate-prevpaymentDate from t;
    t:update cumPrincipalRedemption:sums principalRedemption from t;
    t:update effNotionalAmt:bondFaceValue-cumPrincipalRedemption from t;
    t:update effNotionalAmt:bondFaceValue^prev effNotionalAmt from t;
    t:update cFlowAmount:{[a;b;c;d] .utl.roundNearestInteger[c*0.01*a*b*(1%$[.utl.isLeapYear[{("I"$4#string x) mod 4}[d]];366;365])]}'[couponRate;intDays;effNotionalAmt;paymentDate] from t;
    r:select bondName:BondDescription,paymentDate:{t:"." vs string x;`$(,/)(t[2];"/";t[1];"/";t[0])}'[paymentDate], couponRate, intDays:{`$string x}'[intDays],
       paymentFrequency:paymentFrequency,couponPayment:{`$string x}'[couponAmount],paymentStatus:`DUE,staggeredRedemptionAmount:`0,effNotionalAmount:`1000000
       from t;
       1_([] csvResults:`$.h.tx[`csv;r])
  }
