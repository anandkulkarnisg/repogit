
/ First of all load the csv into memory for monthly returns. The aim of analysis is to identify a regular sip strategy , lumpsum strategy, weighted increase/decrease strategy [ with varying weights/multipliers ].
/ The core idea behind the weights/multipliers is that as market goes down significantly pile up more quantity at lower levels and hold [ This is buy only and hold perpetual strategy, at no point anything is sold.
/ We start investment in 2000 with a hypothetical 1 rs as investment.

/ Step 1 load the data.
niftyDataSet:delete Annual from ((,/)("I";12#"F");enlist",") 0: hsym `$"/home/anand/git/repogit/kdb+/nifty-50-sip-analysis/nifty50-monthly-returns.csv"

/ Prepare the table in a format where we can analyze.
niftyDataSet:(,/){([] Year:12#x;Month:1+til 12;returnPercent:1_(,/)value ?[y;enlist (=;`Year;x);();{x!x}cols y])}[;niftyDataSet] each exec Year from niftyDataSet;

/ Take a hypothetical portfolio of 1 year having 12 months where all months give a return of -1% except last where it is 6.7% hypothetical.
niftyDataSet:update returnPercent:-1f  from delete lumpSumInvestValue from 12#niftyDataSet;
niftyDataSet:update returnPercent:6.7 from niftyDataSet where i=11;

/ First of all attempt investing a dollar as a lumpsum at the start Jan 2000 and verify returns at the end of current year [ Dec 2023 ].
niftyDataSet:update lumpSumInvestValue:1000 {[x;y] x+(y%100)*x}\(exec returnPercent from niftyDataSet) from niftyDataSet;

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
leverage1Strategy:(10;100) lLeveragedTopUpStrategy[;;1f]\exec returnPercent from niftyDataSet;
niftyDataSet:update unitPrice:{x[0]}each leverage1Strategy, portfolioUnits:{x[1]} each leverage1Strategy from niftyDataSet;
niftyDataSet:update leverage1PortfolioValue:unitPrice*portfolioUnits from niftyDataSet;
?[niftyDataSet;();0b;{x!x}`Year`Month`returnPercent`lumpSumInvestValue`leverage1PortfolioValue]