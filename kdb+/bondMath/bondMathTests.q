/ Run some sample bond schedule generation tests below.

/ Case 1 : UPPCL 2031 bond.
bondStaticDict:.bondMath.generateBondStaticDict[(31;2022.03.30;2022.06.06;2031.03.31;"3|6|9|12";9.7;1000000;1b;1b)];
redemptionSchedule:([] redemptionDate:2030.06.28 2030.09.30 2030.12.31 2031.03.31;redemptionAmt:0.25 0.25 0.25 0.25);
t1:.bondMath.generateCashFlowSchdule[bondStaticDict;redemptionSchedule];

/ Case 2 : UGRO Bond Monthly coupon.
bondStaticDict:.bondMath.generateBondStaticDict[(19;2022.01.19;.z.D;2025.01.19;"1|2|3|4|5|6|7|8|9|10|11|12";10.25;1000000;0b;0b)];
redemptionSchedule:delete from ([] redemptionDate:2030.06.28 2030.09.30 2030.12.31 2031.03.31;redemptionAmt:0.25 0.25 0.25 0.25) where 1b;
t2:.bondMath.generateCashFlowSchdule[bondStaticDict;redemptionSchedule];

/ Case 3 : Hinduja Annual Bond. Generate a full cashflow even into past since issueDate.
.cfg.fullOrCurrent:`f;
bondStaticDict:.bondMath.generateBondStaticDict[(13;2017.09.13;.z.D;2024.09.13;"09|13";9.2;1000000;0b;0b)];
redemptionSchedule:delete from ([] redemptionDate:2030.06.28 2030.09.30 2030.12.31 2031.03.31;redemptionAmt:0.25 0.25 0.25 0.25) where 1b;
t3:.bondMath.generateCashFlowSchdule[bondStaticDict;redemptionSchedule];

/ Case 4 : kudgi 2027C/2030M Secured 9.14 Bond.
bondStaticDict:.bondMath.generateBondStaticDict[(25;2017.03.31;.z.D;2027.04.25;"04|13";9.14;1000000;0b;0b)];
redemptionSchedule:delete from ([] redemptionDate:2030.06.28 2030.09.30 2030.12.31 2031.03.31;redemptionAmt:0.25 0.25 0.25 0.25) where 1b;
t4:.bondMath.generateCashFlowSchdule[bondStaticDict;redemptionSchedule];

/ Case 5 : Unsecured Shriram Transport finance Apr 2024 Monthly 10.25 bond.
bondStaticDict:.bondMath.generateBondStaticDict[(28;2018.11.28;.z.D;2024.04.26;"01|02|03|04|05|06|07|08|09|10|11|12";10.25;1000000;0b;0b)];
redemptionSchedule:delete from ([] redemptionDate:2030.06.28 2030.09.30 2030.12.31 2031.03.31;redemptionAmt:0.25 0.25 0.25 0.25) where 1b;
t5:.bondMath.generateCashFlowSchdule[bondStaticDict;redemptionSchedule];

/ Case 6 : UPPCL 2027 Bond.
bondStaticDict:.bondMath.generateBondStaticDict[(20;2017.12.05;.z.D;2027.10.20;"01|04|07|10";9.75;1000000;1b;1b)];
redemptionSchedule:([] redemptionDate:2027.01.20 2027.04.20 2027.07.20 2027.10.20;redemptionAmt:0.25 0.25 0.25 0.25);
t6:.bondMath.generateCashFlowSchdule[bondStaticDict;redemptionSchedule];

/ Case 7 : Andhra Pradesh State Beverages Corporation Ltd 2031.
bondStaticDict:.bondMath.generateBondStaticDict[(31;2022.06.14;.z.D;2031.05.30;"02|05|08|11";9.62;1000000;1b;1b)];
redemptionSchedule:([] redemptionDate:2030.08.30 2030.11.29 2031.02.28 2031.05.30;redemptionAmt:0.25 0.25 0.25 0.25);
t7:.bondMath.generateCashFlowSchdule[bondStaticDict;redemptionSchedule];

/ Case 8 : Shriram Secured 9.4 2028 Bond. Not in portfolio, just testing hypothetical example.
bondStaticDict:.bondMath.generateBondStaticDict[(12;2018.07.12;.z.D;2028.07.12;"07|13";9.4;1000000;0b;0b)];
redemptionSchedule:delete from ([] redemptionDate:2030.06.28 2030.09.30 2030.12.31 2031.03.31;redemptionAmt:0.25 0.25 0.25 0.25) where 1b;
t7:.bondMath.generateCashFlowSchdule[bondStaticDict;redemptionSchedule];


/ Sample test cases for annual cashflow for each year.
/ Case 1 : Sample Execution for UPPCL 2031 bond.
.bondMath.getCashFlowByYear[t1;2024]

/ Case 2 : UGRO Bond Monthly coupon.
.bondMath.getCashFlowByYear[t2;2024]

/ Sample test cases for the annual total cashflows.
/ Case 1 : Sample Execution for UPPCL 2031 bond.
.bondMath.getTotalCashFlowPerYear[t1]

/ Case 2 : UGRO Bond Monthly coupon.
.bondMath.getTotalCashFlowPerYear[t2]


.cfg.fullOrCurrent:`c;
select bondName:`$"UP Power Corporation bond 31/03/2031 Quarterly 9.7(S)", 
       paymentDate:{t:"." vs string x;`$(,/)(t[2];"/";t[1];"/";t[0])}'[couponDate],
       couponRate:{`$string x}'[rate*100],
       intDays:{`$string x}'[intDays],
       paymentFrequency:`Annual,
       couponPayment:{`$string x}'[cflowAmount],
       paymentStatus:`DUE,
       staggeredRedemptionAmount:`0,
       effNotionalAmount:`1000000
       from t6

