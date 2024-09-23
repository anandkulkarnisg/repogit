
/ build a sample price series.
t:([] px:1 2 3 2.5 1.5 3 5;timestamp:.z.p+(1+til 7)*00:10:30.150);t

/ Another sample price series.
t:([] px:10 12 15 22 27 20 8 28 35 30;timestamp:.z.p+(1+til 10)*00:10:30.150);t

/ Assume each price point as maximum and identify min price before it and min price afterwards.First populate running max and mins.
t:update rmin_before:prev mins[px], rmin_after:next reverse mins[reverse px] from t;
t:update rmin_before:px, rmin_after:px from t where (null rmin_before) or (null rmin_after);

/Compute the priceMoveUp as jump from running min vs current px.
g:{max(0;-100+100*x%y)};
t:update priceMoveUp:g'[px;rmin_before], priceMoveDown:g'[px;rmin_after] from t;
t

/select the max price move up and down.
select px, timestamp, pxBefore:rmin_before, priceMoveUp from t where priceMoveUp=max(priceMoveUp)       /rise from 8 to 35 337.5% rise.
select px, timestamp, pxAfter:rmin_after, priceMoveDown from t where priceMoveDown=max(priceMoveDown)   /fall from 27 to 8 237.5% fall.

