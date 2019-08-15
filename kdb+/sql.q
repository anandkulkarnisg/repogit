/ Sources :
/ https://www.codeproject.com/KB/database/Visual_SQL_Joins/Visual_SQL_JOINS_orig.jpg
/ https://www.codeproject.com/Articles/33052/Visual-Representation-of-SQL-Joins
/ https://code.kx.com/v2/basics/joins/

/ Table Data setup.
Table_A:([] PK:1 2 3 4 5 6 7 10; Value:`FOX`COP`TAXI`LINCOLN`ARIZONA`WASHINGTON`DELL`LUCENT);
Table_B:([] PK:1 2 3 6 7 8 9 11; Value:`TROT`CAR`CAB`MONUMENT`PC`MICROSOFT`APPLE`SCOTCH);

/INNER JOIN:-
.sql.ij:{[keyCol;t1;t2;t1cols;t2cols;t1n;t2n] 
                        keyValList:{?[ej[x;y;z];();();x]}[keyCol;t1;t2]; 
                        (t1n xcol ?[t1;enlist (in;keyCol;keyValList);0b;{x!x}t1cols]),'(t2n xcol ?[t2;enlist (in;keyCol;keyValList);0b;{x!x}t2cols]) 
         }                                            
/ Invocation :  .sql.ij[`PK;Table_A;Table_B;cols Table_A;cols Table_B;`A_PK`A_Value;`B_PK`B_Value]
/ Barebone kdb inner join : Table_A ij `PK xkey Table_B

/LEFT JOIN:-
.sql.lj:{[keycol;t1;t2;t1cols;t2cols;t1n;t2n] 
                        tbl1:(t1n xcol t1),'(?[t1;();0b;{(enlist x)!(enlist x)}keycol]); 
                        tbl2:(t2n xcol t2),'(?[t2;();0b;{(enlist x)!(enlist x)}keycol]); 
                        ?[tbl1 lj keycol xkey tbl2;();0b;{x!x}[raze(t1n;t2n)]]
        }
/ Invocation : .sql.lj[`PK;Table_A;Table_B;cols Table_A;cols Table_B;`A_PK`A_Value;`B_PK`B_Value]
/ Barebone kdb left join : Table_A lj `PK xkey Table_B

/RIGHT JOIN:-
.sql.rj:{[keycol;t1;t2;t1cols;t2cols;t1n;t2n] colOrder:raze(t1n;t2n); colOrder xcols .sql.lj[keycol;t2;t1;t2cols;t1cols;t2n;t1n] }
/ Invocation : .sql.rj[`PK;Table_A;Table_B;cols Table_A;cols Table_B;`A_PK`A_Value;`B_PK`B_Value]
/ Barebone kdb right join : Table_B lj `PK xkey Table_A / Just switch the order of tables to get right join from left join!

/ OUTER JOIN / FULL OUTER JOIN:-
.sql.oj:{[keycol;t1;t2;t1cols;t2cols;t1n;t2n;nullCol] 
                        tbl1:.sql.lj[keycol;t1;t2;t1cols;t2cols;t1n;t2n];
                        tbl2:.sql.rj[keycol;t1;t2;t1cols;t2cols;t1n;t2n];
                        colOrder:raze(t1n;t2n); 
                        colOrder xcols tbl1 uj ?[tbl2;enlist (=;nullCol;0N);0b;()]
        }
/ Invocation : .sql.oj[`PK;Table_A;Table_B;cols Table_A;cols Table_B;`A_PK`A_Value;`B_PK`B_Value;`A_PK]
/ Barebone kdb logic : outer full join is union or merge of left join and right join results.

/ LEFT JOIN EXCLUDING INNER JOIN [ LEFT EXCLUDING JOIN ]:-
.sql.lxj:{[keycol;t1;t2;t1cols;t2cols;t1n;t2n;nullCol] ?[.sql.lj[keycol;t1;t2;t1cols;t2cols;t1n;t2n];enlist (=;nullCol;0N);0b;()] }
/ Invocation : .sql.lxj[`PK;Table_A;Table_B;cols Table_A;cols Table_B;`A_PK`A_Value;`B_PK`B_Value;`B_PK]
/ Barebone kdb+ left excluding join is : get left join and exclude B key values which are null.

/ RIGHT JOIN EXCLUDING INNER JOIN [ RIGHT EXCLUDING JOIN ]:-
.sql.rxj:{[keycol;t1;t2;t1cols;t2cols;t1n;t2n;nullCol] ?[.sql.rj[keycol;t1;t2;t1cols;t2cols;t1n;t2n];enlist (=;nullCol;0N);0b;()] }
/ Invocation : .sql.rxj[`PK;Table_A;Table_B;cols Table_A;cols Table_B;`A_PK`A_Value;`B_PK`B_Value;`A_PK]
/ Barebone kdb+ right excluding join is : get right join and exclude A values which are null.

/ OUTER JOIN EXCLUDING INNER JOIN.
.sql.oxij:{[keycol;t1;t2;t1cols;t2cols;t1n;t2n;nullColList] 
            /select from .sql.oj[keycol;t1;t2;t1cols;t2cols;t1n;t2n;nullCol] where (A_PK=0N) or (B_PK=0N)   / non functional form to understand easier!
            ?[.sql.oj[keycol;t1;t2;t1cols;t2cols;t1n;t2n;nullColList[0]];enlist (|;(=;nullColList[0];0Nj);(=;nullColList[1];0Nj));0b;()]            
          }
/ Invocation : .sql.oxij[`PK;Table_A;Table_B;cols Table_A;cols Table_B;`A_PK`A_Value;`B_PK`B_Value;`A_PK`B_PK]
/ Barebone kdb+ outer join excluding inner join results.

/ CROSS OR CARTESIAN JOIN.
.sql.cj:{[t1;t2;t1Col;t2Col]    
            / Create a cartesian Join between t1 and t2 table rows for every combination of t1Col and t2Col.
            ([] ?[t1;();();t1Col]) cross ([] ?[t2;();();t2Col])
        }
        
/ Invocation : .sql.cj[Table_A;Table_B;`PK;`Value]
/ Barebone kdb+ cross implementation : cartesian join of two table columns and results in a two column table. use with care.

/ SELF JOIN.
Table_C:([] staff_id:1+til 10;first_name:`Fabiola`Mireya`Genna`Virgie`Jannette`Marcelene`Venita`Kali`Layla`Bernadine;
            last_name:`Jackson`Copeland`Serrano`Wiggins`David`Boyer`Daniel`Vargas`Terrell`Houston;
            manager_id:0N 1 2 2 1 5 5 1 7 7);

.sql.sj:{[t;joinFromCol;joinToCol]
                keyCols:raze (joinFromCol;`full_name);
                t:t lj joinFromCol xkey keyCols xcol ([] x:t[joinFromCol]; y:{`$ raze string x," ",string y }'[t[`first_name];t[`last_name]]);
                t:update manager_name:{ { first ?[y;enlist (=;z;`x);();`full_name] }[;y;z] each x}[t[joinToCol];t;joinFromCol] from t;               
                t
        }
/ Invocation : .sql.sj[Table_C;`staff_id;`manager_id]

/ Union and union all join equivalents in kdb+. Add the analytic : TODO LATER.
t1:([] c:1 2 3 4; d:`a`b`c`d);
t2:([] c:3 5 6 2; d:`c`e`f`b);

.sql.uaj:{[t1;t2] t1 uj t2} / This provides union all equivalent SQL join in kdb+
.sql.uj:{[t1;t2] distinct t1 uj t2} / This provides union equivalent join in SQL kdb+.
