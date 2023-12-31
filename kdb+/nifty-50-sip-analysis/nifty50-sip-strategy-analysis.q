
/ First of all load the csv into memory for monthly returns. The aim of analysis is to identify a regular sip strategy , lumpsum strategy, weighted increase/decrease strategy [ with varying weights/multipliers ].
/ The core idea behind the weights/multipliers is that as market goes down significantly pile up more quantity at lower levels and hold [ This is buy only and hold perpetual strategy, at no point anything is sold.
/ We start investment in 2000 with a hypothetical 1 rs as investment.

/ Initialize a few key inputs.
initialUnitPrice:1f;initialInvestedUnits:1f;
initialInvestmentAmount:initialUnitPrice*initialInvestedUnits;
topUpLeverageRatio:1f;

/ Step 1 load the data.
niftyDataSet:delete Annual from ((,/)("I";12#"F");enlist",") 0: hsym `$"/home/anand/git/repogit/kdb+/nifty-50-sip-analysis/nifty50-monthly-returns.csv";

/ Prepare the table in a format where we can analyze.
niftyDataSet:(,/){([] Year:12#x;Month:1+til 12;returnPercent:1_(,/)value ?[y;enlist (=;`Year;x);();{x!x}cols y])}[;niftyDataSet] each exec Year from niftyDataSet;

/ First of all attempt investing a dollar as a lumpsum at the start Jan 2000 and verify returns at the end of current year [ Dec 2023 ].
niftyDataSet:update lumpSumInvestValue:initialInvestmentAmount {[x;y] x+(y%100)*x}\(exec returnPercent from niftyDataSet) from niftyDataSet;

/ LeveragedTopUpStrategy logic.
lLeveragedTopUpStrategy:{[x;y;z] unitPrice:x[0];portfolioUnits:x[1];newUnitPrice:unitPrice*(1+y*0.01);
                                    $[y>0f;[(newUnitPrice;portfolioUnits)];
                                            [lossAmount:abs (newUnitPrice-unitPrice)*portfolioUnits;
                                             unitsTobeAdded:z*ceiling(lossAmount%newUnitPrice);
                                             (newUnitPrice;portfolioUnits+unitsTobeAdded)
                                            ]
                                     ]
                        };

/ The rebalanced returns could be calculated as below.
leverage1Strategy:(initialUnitPrice;initialInvestedUnits) lLeveragedTopUpStrategy[;;topUpLeverageRatio]\exec returnPercent from niftyDataSet;
niftyDataSet:update unitPrice:{x[0]}each leverage1Strategy, portfolioUnits:{x[1]} each leverage1Strategy from niftyDataSet;
niftyDataSet:update leverage1PortfolioValue:unitPrice*portfolioUnits from niftyDataSet;
?[niftyDataSet;();0b;{x!x}`Year`Month`returnPercent`lumpSumInvestValue`unitPrice`portfolioUnits`leverage1PortfolioValue]


####################################
Experimental/rough page below:-
####################################

sampleDataset:update returnPercent:"f"$1 2 -3 4 -5 6 from delete lumpSumInvestValue from 6#niftyDataSet;
100 -> 101
101 -> 101+(0.02*101) /103.02
103.02 -> 103.02+(-0.03*103.02) /99.9294
99.9294 -> 99.9294+(0.04*99.9294) /103.926576
103.926576 -> 103.926576+(-0.05*103.926576) /98.7302472
98.7302472 -> 98.7302472+(0.06*98.7302472)  /104.654062
sampleDataset:update lumpSumInvestValue:100 {[x;y] x+(y%100)*x}\(exec returnPercent from sampleDataset) from sampleDataset;

/ Strategy 1 : leveage ratio for topup is 1f.
100 -> 101 /[ do nothing ].
101 -> 103.02 /[ do nothing ].
103.02 -> 99.9294 + 1f*(103.02-99.9294) / 103.02
103.02 -> 1.04*103.02 -> 107.1408
107.1408 -> .95*107.1408 + 1f*(107.1408-101.78376)  -> 106.872948
106.872948 -> 1.06*106.872948 -> 113.2853249
sampleDataset:update leverage1InvestValue:101 103.02 103.02 107.1408 106.872948 113.2853249 from sampleDataset;

/ Strategy 2 : leverage ratio for topup is 2f.
100 -> 101 /[ do nothing ].
101 -> 103.02 /[ do nothing ].
103.02 -> 99.9294 + 2f*(103.02-99.9294) / 106.1106
106.1106 -> 1.04*106.1106 -> 110.355024
110.355024 -> .95*110.355024 + 2f*(110.355024-104.8372728)  -> 115.3210001
115.3210001 -> 1.06*115.3210001 -> 122.2402601
sampleDataset:update leverage2InvestValue:101 103.02 106.1106 110.355024 115.3210001 122.2402601 from sampleDataset;


/ Strategy 3 : leverage ratio for topup is 3f.
100 -> 101 /[ do nothing ].
101 -> 103.02 /[ do nothing ].
103.02 -> 99.9294 + 3f*(103.02-99.9294) / 109.2012
109.2012 -> 1.04*109.2012 -> 113.569248
113.569248 -> .95*113.569248 + 3f*(113.569248-107.8907856)  -> 124.0744034
124.0744034 -> 1.06*124.0744034 -> 131.5188676
sampleDataset:update leverage3InvestValue:101 103.02 109.2012 113.569248 124.0744034 131.5188676 from sampleDataset;


100 {[x;y]t:x*(1+0.01*y);$[y>0;t;t+3f*(x-t)]}\1 2 -3 4 -5 6












niftyDataSet:update topUpAmount:{[x;y] $[y>0f;0f;x*2f*((abs y)%100)]}'[1000f^prev lumpSumInvestValue;returnPercent] from niftyDataSet;
niftyDataSet:update leverageEffAmount:{[x;y] x+y}'[lumpSumInvestValue;topUpAmount] from niftyDataSet;
select leverageEffAmount, 0f^next returnPercent from niftyDataSet




/ Experimental area.
select lumpSumInvestValue, 1000f^prev lumpSumInvestValue, returnPercent from niftyDataSet
p:6#niftyDataSet;
1000 + (1000*4.44%100) = 1044.4  /1 month
1044.4 + (1044.4*7.02%100) = 1117.71688 /2nd month.
1117.71688 + (1117.71688*-7.64%100) = 1032.3233104 /3rd month
/ Now what i want is. In third month...
1032.3233104 + (1117.71688*1f*(abs -7.64)%100) = 1117.71688 now.


{x+y+z}\[100;100 200 300;400 500 600] / tradic over with 3 parameters.



/ 6#niftyDataSet
/ Initial price of nifty 50 is 10 Rs per unit , initial investment amount is 1000 rs. i.e buy 100 units to start with. Ignore brokerage costs.
First month  :     portfolio value = 100 * 10*(1+0.0444) = 1044.4 Rs.
Second month :     portfolio value = 100 * 10.44*(1+0.0702) = 1117.2888 Rs.
/[ now rebalance the portfolio , take the loss amount : 85.3608643 Rs, leveragge ratio is 1, stock price is 10.3192794 .buy leverageRatio * ceiling(85.3608643%10.3192794)=9 units. Add these back to portfolio. 
Third month  :     portfolio value = 100 * 11.172888*(1-0.0764) = 1031.9279357 Rs.  After rebalance portfolio = 1031.9279357 + 9*10.3192794 = 1124.8014503 Rs.
/ [now rebalance the portfolio , take the loss amount : 1124.8014503 - 1035.0422985 = 89.7591518 Rs. leveragge ratio is 1, stock price is 9.4958009. buy 1 * ceiling(89.7591518%9.4958009)=10 unit. Add these back to portfolio.
Fourth month :     portfolio value = 109 * 10.3192794*(1-0.0798) = 1035.0422985 Rs. After rebalance portfolio = 1035.0422985 + 10*9.4958009 = 1130.0003075 Rs.
/ [ now rebalance the portfolio, take the loss amount : 1130.0003075 - 1108.9823014 = 21.0180061 Rs. leverage ratio is 1, stock price is 9.319179. buy 1 * ceiling(21.0180061%9.319179)=3 unit. Add these back to portfolio.
Fifth month :      portfolio value = 119 * 9.4958009*(1-0.0186) = 1015.7905114 Rs. After rebalance portfolio = 1108.9823014 + 3*9.319179 = 1136.9398384 Rs.
Sixth month :      portfolio value = 122 * 9.319179*(1+.0659) = 1211.8641733 Rs.


/ First generate stock value based on returns.
experimental:([] returnPercent:(exec returnPercent from niftyDataSet));
/ calculate price per share/unit at each month interval, assume starting price is 10 rs.
experimental:update unitPrice:10 {[x;y] x+(y%100)*x}\(exec returnPercent from experimental) from experimental;
/ Now calculate the portfolio value in each period, unadjusted for rebalancing.
experimental:update unadjPortfolioValue:100*unitPrice from experimental;
/ Calculate adjustment required for each period. If the period has positive return then no adjustment, if -ve then adjustment applies.
experimental:update rebalanceAmount:{[x;y] $[x>y;0f;x-y]}'[unadjPortfolioValue;1000f^prev unadjPortfolioValue] from experimental;
/ Calculate the rebalance units needed for each period.
experimental:update rebalanceUnits:{[x;y] $[(abs x)>0;ceiling abs x%y;0]}'[rebalanceAmount;unitPrice] from experimental;
/ Add total units for each period using running sum.
experimental:update totalUnits:100+ sums rebalanceUnits from experimental;

/ The rebalanced returns could be calculated as below.
leverage1Strategy:(10;100) {[x;y;z] unitPrice:x[0];portfolioUnits:x[1];newUnitPrice:unitPrice*(1+y*0.01);
                                    $[y>0f;[(newUnitPrice;portfolioUnits)];                 
                                            [lossAmount:abs (newUnitPrice-unitPrice)*portfolioUnits;
                                             unitsTobeAdded:z*ceiling(lossAmount%newUnitPrice);
                                             (newUnitPrice;portfolioUnits+unitsTobeAdded)
                                            ]
                                     ]
                           }[;;1f]\exec returnPercent from niftyDataSet;

niftyDataSet:update unitPrice:{x[0]}each leverage1Strategy, portfolioUnits:{x[1]} each leverage1Strategy from niftyDataSet;
niftyDataSet:update leverage1PortfolioValue:unitPrice*portfolioUnits from niftyDataSet;
?[niftyDataSet;();0b;{x!x}`Year`Month`returnPercent`lumpSumInvestValue`leverage1PortfolioValue]








































