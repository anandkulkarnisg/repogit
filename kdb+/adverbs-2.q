

/ Input.
t:([] c1:enlist `a`b`c;c2:enlist 10 20 30);

/ Output.
{?[x;();0b;{x!x}enlist `c1] cross ?[x;();0b;{x!x}enlist `c2]}[ungroup t]


/ Input.
t:([] c1:enlist `a`b`c;c2:enlist 10 20 30;c3:enlist 1 2 3;c3:enlist `ab`bc`cd);t

/ Output : criss cross of all combinations of all columns. In this case 3*3*3*3=81 rows.
t:ungroup ?[t;();0b;{x!x}1#cols t]{cross [x;ungroup ?[z;();0b;{x!x}enlist y]]}[;;t]/1_cols t



