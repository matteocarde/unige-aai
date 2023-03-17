(define (problem schedule-49-8)
(:domain schedule)
(:objects
    C2
    B2
    A2
    Z1
    W1
    V1
    U1
    S1
    R1
    P1
    Q1
    O1
    N1
    M1
    L1
    K1
    J1
    I1
    H1
    G1
    F1
    E1
    D1
    C1
    B1
    A1
    Z0
    W0
    V0
    U0
    S0
    R0
    P0
    Q0
    O0
    N0
    M0
    L0
    K0
    J0
    I0
    H0
    G0
    F0
    E0
    D0
    C0
    CIRCULAR
    TWO
    THREE
    BLUE
    YELLOW
    BACK
    RED
    B0
    FRONT
    ONE
    BLACK
    OBLONG
    A0
)
(:init
    (idle punch) (idle drill-press) (idle lathe) (idle roller) (idle polisher)
    (idle immersion-painter) (idle spray-painter) (idle grinder) (ru unwantedargs)
    (SHAPE A0 CYLINDRICAL)
    (SURFACE-CONDITION A0 POLISHED)
    (PAINTED A0 RED)
    (HAS-HOLE A0 TWO FRONT) (lasthole A0 TWO FRONT) (linked A0 nowidth noorient TWO FRONT)
    (TEMPERATURE A0 COLD)
    (SHAPE B0 OBLONG)
    (SURFACE-CONDITION B0 ROUGH)
    (PAINTED B0 BLUE)
    (HAS-HOLE B0 TWO BACK) (lasthole B0 TWO BACK) (linked B0 nowidth noorient TWO BACK)
    (TEMPERATURE B0 COLD)
    (SHAPE C0 OBLONG)
    (SURFACE-CONDITION C0 SMOOTH)
    (PAINTED C0 BLACK)
    (HAS-HOLE C0 ONE BACK) (lasthole C0 ONE BACK) (linked C0 nowidth noorient ONE BACK)
    (TEMPERATURE C0 COLD)
    (SHAPE D0 CYLINDRICAL)
    (SURFACE-CONDITION D0 ROUGH)
    (PAINTED D0 BLACK)
    (HAS-HOLE D0 THREE BACK) (lasthole D0 THREE BACK) (linked D0 nowidth noorient THREE BACK)
    (TEMPERATURE D0 COLD)
    (SHAPE E0 OBLONG)
    (SURFACE-CONDITION E0 ROUGH)
    (PAINTED E0 BLUE)
    (HAS-HOLE E0 THREE BACK) (lasthole E0 THREE BACK) (linked E0 nowidth noorient THREE BACK)
    (TEMPERATURE E0 COLD)
    (SHAPE F0 OBLONG)
    (SURFACE-CONDITION F0 POLISHED)
    (PAINTED F0 RED)
    (HAS-HOLE F0 TWO BACK) (lasthole F0 TWO BACK) (linked F0 nowidth noorient TWO BACK)
    (TEMPERATURE F0 COLD)
    (SHAPE G0 OBLONG)
    (SURFACE-CONDITION G0 ROUGH)
    (PAINTED G0 BLACK)
    (HAS-HOLE G0 TWO FRONT) (lasthole G0 TWO FRONT) (linked G0 nowidth noorient TWO FRONT)
    (TEMPERATURE G0 COLD)
    (SHAPE H0 CIRCULAR)
    (SURFACE-CONDITION H0 ROUGH)
    (PAINTED H0 RED)
    (HAS-HOLE H0 ONE BACK) (lasthole H0 ONE BACK) (linked H0 nowidth noorient ONE BACK)
    (TEMPERATURE H0 COLD)
    (SHAPE I0 CYLINDRICAL)
    (SURFACE-CONDITION I0 SMOOTH)
    (PAINTED I0 YELLOW)
    (HAS-HOLE I0 ONE BACK) (lasthole I0 ONE BACK) (linked I0 nowidth noorient ONE BACK)
    (TEMPERATURE I0 COLD)
    (SHAPE J0 OBLONG)
    (SURFACE-CONDITION J0 SMOOTH)
    (PAINTED J0 YELLOW)
    (HAS-HOLE J0 TWO FRONT) (lasthole J0 TWO FRONT) (linked J0 nowidth noorient TWO FRONT)
    (TEMPERATURE J0 COLD)
    (SHAPE K0 OBLONG)
    (SURFACE-CONDITION K0 ROUGH)
    (PAINTED K0 YELLOW)
    (HAS-HOLE K0 ONE FRONT) (lasthole K0 ONE FRONT) (linked K0 nowidth noorient ONE FRONT)
    (TEMPERATURE K0 COLD)
    (SHAPE L0 CYLINDRICAL)
    (SURFACE-CONDITION L0 SMOOTH)
    (PAINTED L0 BLACK)
    (HAS-HOLE L0 THREE FRONT) (lasthole L0 THREE FRONT) (linked L0 nowidth noorient THREE FRONT)
    (TEMPERATURE L0 COLD)
    (SHAPE M0 CYLINDRICAL)
    (SURFACE-CONDITION M0 ROUGH)
    (PAINTED M0 RED)
    (HAS-HOLE M0 TWO FRONT) (lasthole M0 TWO FRONT) (linked M0 nowidth noorient TWO FRONT)
    (TEMPERATURE M0 COLD)
    (SHAPE N0 CIRCULAR)
    (SURFACE-CONDITION N0 ROUGH)
    (PAINTED N0 BLUE)
    (HAS-HOLE N0 TWO BACK) (lasthole N0 TWO BACK) (linked N0 nowidth noorient TWO BACK)
    (TEMPERATURE N0 COLD)
    (SHAPE O0 CYLINDRICAL)
    (SURFACE-CONDITION O0 SMOOTH)
    (PAINTED O0 BLACK)
    (HAS-HOLE O0 TWO FRONT) (lasthole O0 TWO FRONT) (linked O0 nowidth noorient TWO FRONT)
    (TEMPERATURE O0 COLD)
    (SHAPE Q0 OBLONG)
    (SURFACE-CONDITION Q0 ROUGH)
    (PAINTED Q0 BLUE)
    (HAS-HOLE Q0 ONE FRONT) (lasthole Q0 ONE FRONT) (linked Q0 nowidth noorient ONE FRONT)
    (TEMPERATURE Q0 COLD)
    (SHAPE P0 CYLINDRICAL)
    (SURFACE-CONDITION P0 SMOOTH)
    (PAINTED P0 YELLOW)
    (HAS-HOLE P0 TWO FRONT) (lasthole P0 TWO FRONT) (linked P0 nowidth noorient TWO FRONT)
    (TEMPERATURE P0 COLD)
    (SHAPE R0 CYLINDRICAL)
    (SURFACE-CONDITION R0 SMOOTH)
    (PAINTED R0 BLACK)
    (HAS-HOLE R0 THREE BACK) (lasthole R0 THREE BACK) (linked R0 nowidth noorient THREE BACK)
    (TEMPERATURE R0 COLD)
    (SHAPE S0 CIRCULAR)
    (SURFACE-CONDITION S0 SMOOTH)
    (PAINTED S0 YELLOW)
    (HAS-HOLE S0 THREE BACK) (lasthole S0 THREE BACK) (linked S0 nowidth noorient THREE BACK)
    (TEMPERATURE S0 COLD)
    (SHAPE U0 OBLONG)
    (SURFACE-CONDITION U0 POLISHED)
    (PAINTED U0 RED)
    (HAS-HOLE U0 TWO BACK) (lasthole U0 TWO BACK) (linked U0 nowidth noorient TWO BACK)
    (TEMPERATURE U0 COLD)
    (SHAPE V0 CYLINDRICAL)
    (SURFACE-CONDITION V0 POLISHED)
    (PAINTED V0 BLACK)
    (HAS-HOLE V0 TWO BACK) (lasthole V0 TWO BACK) (linked V0 nowidth noorient TWO BACK)
    (TEMPERATURE V0 COLD)
    (SHAPE W0 CIRCULAR)
    (SURFACE-CONDITION W0 POLISHED)
    (PAINTED W0 RED)
    (HAS-HOLE W0 ONE FRONT) (lasthole W0 ONE FRONT) (linked W0 nowidth noorient ONE FRONT)
    (TEMPERATURE W0 COLD)
    (SHAPE Z0 CYLINDRICAL)
    (SURFACE-CONDITION Z0 POLISHED)
    (PAINTED Z0 YELLOW)
    (HAS-HOLE Z0 THREE BACK) (lasthole Z0 THREE BACK) (linked Z0 nowidth noorient THREE BACK)
    (TEMPERATURE Z0 COLD)
    (SHAPE A1 CIRCULAR)
    (SURFACE-CONDITION A1 ROUGH)
    (PAINTED A1 BLACK)
    (HAS-HOLE A1 THREE BACK) (lasthole A1 THREE BACK) (linked A1 nowidth noorient THREE BACK)
    (TEMPERATURE A1 COLD)
    (SHAPE B1 CIRCULAR)
    (SURFACE-CONDITION B1 POLISHED)
    (PAINTED B1 BLACK)
    (HAS-HOLE B1 TWO FRONT) (lasthole B1 TWO FRONT) (linked B1 nowidth noorient TWO FRONT)
    (TEMPERATURE B1 COLD)
    (SHAPE C1 CYLINDRICAL)
    (SURFACE-CONDITION C1 ROUGH)
    (PAINTED C1 BLUE)
    (HAS-HOLE C1 ONE FRONT) (lasthole C1 ONE FRONT) (linked C1 nowidth noorient ONE FRONT)
    (TEMPERATURE C1 COLD)
    (SHAPE D1 CYLINDRICAL)
    (SURFACE-CONDITION D1 SMOOTH)
    (PAINTED D1 BLUE)
    (HAS-HOLE D1 THREE BACK) (lasthole D1 THREE BACK) (linked D1 nowidth noorient THREE BACK)
    (TEMPERATURE D1 COLD)
    (SHAPE E1 CIRCULAR)
    (SURFACE-CONDITION E1 POLISHED)
    (PAINTED E1 BLACK)
    (HAS-HOLE E1 THREE FRONT) (lasthole E1 THREE FRONT) (linked E1 nowidth noorient THREE FRONT)
    (TEMPERATURE E1 COLD)
    (SHAPE F1 CIRCULAR)
    (SURFACE-CONDITION F1 SMOOTH)
    (PAINTED F1 BLACK)
    (HAS-HOLE F1 THREE FRONT) (lasthole F1 THREE FRONT) (linked F1 nowidth noorient THREE FRONT)
    (TEMPERATURE F1 COLD)
    (SHAPE G1 CIRCULAR)
    (SURFACE-CONDITION G1 ROUGH)
    (PAINTED G1 RED)
    (HAS-HOLE G1 THREE FRONT) (lasthole G1 THREE FRONT) (linked G1 nowidth noorient THREE FRONT)
    (TEMPERATURE G1 COLD)
    (SHAPE H1 OBLONG)
    (SURFACE-CONDITION H1 SMOOTH)
    (PAINTED H1 RED)
    (HAS-HOLE H1 ONE FRONT) (lasthole H1 ONE FRONT) (linked H1 nowidth noorient ONE FRONT)
    (TEMPERATURE H1 COLD)
    (SHAPE I1 OBLONG)
    (SURFACE-CONDITION I1 POLISHED)
    (PAINTED I1 RED)
    (HAS-HOLE I1 ONE BACK) (lasthole I1 ONE BACK) (linked I1 nowidth noorient ONE BACK)
    (TEMPERATURE I1 COLD)
    (SHAPE J1 CIRCULAR)
    (SURFACE-CONDITION J1 ROUGH)
    (PAINTED J1 BLUE)
    (HAS-HOLE J1 ONE FRONT) (lasthole J1 ONE FRONT) (linked J1 nowidth noorient ONE FRONT)
    (TEMPERATURE J1 COLD)
    (SHAPE K1 CYLINDRICAL)
    (SURFACE-CONDITION K1 SMOOTH)
    (PAINTED K1 RED)
    (HAS-HOLE K1 TWO FRONT) (lasthole K1 TWO FRONT) (linked K1 nowidth noorient TWO FRONT)
    (TEMPERATURE K1 COLD)
    (SHAPE L1 CIRCULAR)
    (SURFACE-CONDITION L1 POLISHED)
    (PAINTED L1 YELLOW)
    (HAS-HOLE L1 ONE FRONT) (lasthole L1 ONE FRONT) (linked L1 nowidth noorient ONE FRONT)
    (TEMPERATURE L1 COLD)
    (SHAPE M1 CIRCULAR)
    (SURFACE-CONDITION M1 ROUGH)
    (PAINTED M1 RED)
    (HAS-HOLE M1 ONE FRONT) (lasthole M1 ONE FRONT) (linked M1 nowidth noorient ONE FRONT)
    (TEMPERATURE M1 COLD)
    (SHAPE N1 OBLONG)
    (SURFACE-CONDITION N1 POLISHED)
    (PAINTED N1 BLUE)
    (HAS-HOLE N1 THREE FRONT) (lasthole N1 THREE FRONT) (linked N1 nowidth noorient THREE FRONT)
    (TEMPERATURE N1 COLD)
    (SHAPE O1 CIRCULAR)
    (SURFACE-CONDITION O1 ROUGH)
    (PAINTED O1 BLACK)
    (HAS-HOLE O1 THREE BACK) (lasthole O1 THREE BACK) (linked O1 nowidth noorient THREE BACK)
    (TEMPERATURE O1 COLD)
    (SHAPE Q1 OBLONG)
    (SURFACE-CONDITION Q1 SMOOTH)
    (PAINTED Q1 BLUE)
    (HAS-HOLE Q1 THREE FRONT) (lasthole Q1 THREE FRONT) (linked Q1 nowidth noorient THREE FRONT)
    (TEMPERATURE Q1 COLD)
    (SHAPE P1 CIRCULAR)
    (SURFACE-CONDITION P1 SMOOTH)
    (PAINTED P1 RED)
    (HAS-HOLE P1 ONE FRONT) (lasthole P1 ONE FRONT) (linked P1 nowidth noorient ONE FRONT)
    (TEMPERATURE P1 COLD)
    (SHAPE R1 OBLONG)
    (SURFACE-CONDITION R1 POLISHED)
    (PAINTED R1 RED)
    (HAS-HOLE R1 THREE BACK) (lasthole R1 THREE BACK) (linked R1 nowidth noorient THREE BACK)
    (TEMPERATURE R1 COLD)
    (SHAPE S1 OBLONG)
    (SURFACE-CONDITION S1 POLISHED)
    (PAINTED S1 BLACK)
    (HAS-HOLE S1 THREE FRONT) (lasthole S1 THREE FRONT) (linked S1 nowidth noorient THREE FRONT)
    (TEMPERATURE S1 COLD)
    (SHAPE U1 OBLONG)
    (SURFACE-CONDITION U1 POLISHED)
    (PAINTED U1 RED)
    (HAS-HOLE U1 THREE BACK) (lasthole U1 THREE BACK) (linked U1 nowidth noorient THREE BACK)
    (TEMPERATURE U1 COLD)
    (SHAPE V1 CIRCULAR)
    (SURFACE-CONDITION V1 POLISHED)
    (PAINTED V1 BLUE)
    (HAS-HOLE V1 TWO BACK) (lasthole V1 TWO BACK) (linked V1 nowidth noorient TWO BACK)
    (TEMPERATURE V1 COLD)
    (SHAPE W1 OBLONG)
    (SURFACE-CONDITION W1 ROUGH)
    (PAINTED W1 BLACK)
    (HAS-HOLE W1 TWO FRONT) (lasthole W1 TWO FRONT) (linked W1 nowidth noorient TWO FRONT)
    (TEMPERATURE W1 COLD)
    (SHAPE Z1 CIRCULAR)
    (SURFACE-CONDITION Z1 SMOOTH)
    (PAINTED Z1 BLACK)
    (HAS-HOLE Z1 THREE FRONT) (lasthole Z1 THREE FRONT) (linked Z1 nowidth noorient THREE FRONT)
    (TEMPERATURE Z1 COLD)
    (SHAPE A2 OBLONG)
    (SURFACE-CONDITION A2 ROUGH)
    (PAINTED A2 YELLOW)
    (HAS-HOLE A2 ONE FRONT) (lasthole A2 ONE FRONT) (linked A2 nowidth noorient ONE FRONT)
    (TEMPERATURE A2 COLD)
    (SHAPE B2 OBLONG)
    (SURFACE-CONDITION B2 POLISHED)
    (PAINTED B2 RED)
    (HAS-HOLE B2 ONE BACK) (lasthole B2 ONE BACK) (linked B2 nowidth noorient ONE BACK)
    (TEMPERATURE B2 COLD)
    (SHAPE C2 CYLINDRICAL)
    (SURFACE-CONDITION C2 ROUGH)
    (PAINTED C2 BLACK)
    (HAS-HOLE C2 THREE BACK) (lasthole C2 THREE BACK) (linked C2 nowidth noorient THREE BACK)
    (TEMPERATURE C2 COLD)
    (CAN-ORIENT DRILL-PRESS BACK)
    (CAN-ORIENT PUNCH BACK)
    (CAN-ORIENT DRILL-PRESS FRONT)
    (CAN-ORIENT PUNCH FRONT)
    (HAS-PAINT IMMERSION-PAINTER YELLOW)
    (HAS-PAINT SPRAY-PAINTER YELLOW)
    (HAS-PAINT IMMERSION-PAINTER BLUE)
    (HAS-PAINT SPRAY-PAINTER BLUE)
    (HAS-PAINT IMMERSION-PAINTER BLACK)
    (HAS-PAINT SPRAY-PAINTER BLACK)
    (HAS-PAINT IMMERSION-PAINTER RED)
    (HAS-PAINT SPRAY-PAINTER RED)
    (HAS-BIT DRILL-PRESS THREE)
    (HAS-BIT PUNCH THREE)
    (HAS-BIT DRILL-PRESS TWO)
    (HAS-BIT PUNCH TWO)
    (HAS-BIT DRILL-PRESS ONE)
    (HAS-BIT PUNCH ONE)
    (PART C2) (unscheduled C2)
    (PART B2) (unscheduled B2)
    (PART A2) (unscheduled A2)
    (PART Z1) (unscheduled Z1)
    (PART W1) (unscheduled W1)
    (PART V1) (unscheduled V1)
    (PART U1) (unscheduled U1)
    (PART S1) (unscheduled S1)
    (PART R1) (unscheduled R1)
    (PART P1) (unscheduled P1)
    (PART Q1) (unscheduled Q1)
    (PART O1) (unscheduled O1)
    (PART N1) (unscheduled N1)
    (PART M1) (unscheduled M1)
    (PART L1) (unscheduled L1)
    (PART K1) (unscheduled K1)
    (PART J1) (unscheduled J1)
    (PART I1) (unscheduled I1)
    (PART H1) (unscheduled H1)
    (PART G1) (unscheduled G1)
    (PART F1) (unscheduled F1)
    (PART E1) (unscheduled E1)
    (PART D1) (unscheduled D1)
    (PART C1) (unscheduled C1)
    (PART B1) (unscheduled B1)
    (PART A1) (unscheduled A1)
    (PART Z0) (unscheduled Z0)
    (PART W0) (unscheduled W0)
    (PART V0) (unscheduled V0)
    (PART U0) (unscheduled U0)
    (PART S0) (unscheduled S0)
    (PART R0) (unscheduled R0)
    (PART P0) (unscheduled P0)
    (PART Q0) (unscheduled Q0)
    (PART O0) (unscheduled O0)
    (PART N0) (unscheduled N0)
    (PART M0) (unscheduled M0)
    (PART L0) (unscheduled L0)
    (PART K0) (unscheduled K0)
    (PART J0) (unscheduled J0)
    (PART I0) (unscheduled I0)
    (PART H0) (unscheduled H0)
    (PART G0) (unscheduled G0)
    (PART F0) (unscheduled F0)
    (PART E0) (unscheduled E0)
    (PART D0) (unscheduled D0)
    (PART C0) (unscheduled C0)
    (PART B0) (unscheduled B0)
    (PART A0) (unscheduled A0)
)
(:goal (and
    (PAINTED M0 BLACK)
    (SHAPE L1 CYLINDRICAL)
    (SURFACE-CONDITION G0 SMOOTH)
    (PAINTED O1 YELLOW)
    (PAINTED I0 RED)
    (SHAPE V1 CYLINDRICAL)
    (PAINTED R0 BLUE)
    (PAINTED D1 RED)
    (PAINTED P0 BLUE)
    (SURFACE-CONDITION O0 ROUGH)
    (SHAPE F0 CYLINDRICAL)
    (PAINTED A1 BLUE)
    (SURFACE-CONDITION L0 POLISHED)
    (PAINTED G1 BLUE)
    (SURFACE-CONDITION C2 POLISHED)
    (PAINTED Q1 RED)
    (SURFACE-CONDITION G1 SMOOTH)
    (SHAPE K0 CYLINDRICAL)
    (SURFACE-CONDITION V1 ROUGH)
    (SHAPE J0 CYLINDRICAL)
    (PAINTED D0 BLUE)
    (PAINTED L1 BLACK)
    (SURFACE-CONDITION J1 POLISHED)
    (SURFACE-CONDITION B2 ROUGH)
    (SURFACE-CONDITION C1 SMOOTH)
    (SHAPE G1 CYLINDRICAL)
    (SURFACE-CONDITION E0 SMOOTH)
    (PAINTED N1 RED)
    (SURFACE-CONDITION Z1 ROUGH)
    (SHAPE H0 CYLINDRICAL)
    (PAINTED W0 YELLOW)
    (PAINTED P1 BLACK)
    (SURFACE-CONDITION F1 ROUGH)
    (SURFACE-CONDITION S0 POLISHED)
    (PAINTED A2 BLACK)
    (SURFACE-CONDITION R0 POLISHED)
    (SURFACE-CONDITION W1 POLISHED)
    (PAINTED C2 BLUE)
    (SHAPE Z1 CYLINDRICAL)
    (SHAPE A2 CYLINDRICAL)
    (SURFACE-CONDITION F0 ROUGH)
    (PAINTED R1 BLUE)
    (SURFACE-CONDITION K1 POLISHED)
    (PAINTED Z1 YELLOW)
    (SURFACE-CONDITION U1 SMOOTH)
    (SURFACE-CONDITION B1 SMOOTH)
    (SHAPE W0 CYLINDRICAL)
    (PAINTED V1 RED)
    (SHAPE H1 CYLINDRICAL)
)))
