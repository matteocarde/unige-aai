(define (problem schedule-48-7)
(:domain schedule)
(:objects
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
    (SURFACE-CONDITION A0 SMOOTH)
    (PAINTED A0 BLACK)
    (HAS-HOLE A0 ONE FRONT) (lasthole A0 ONE FRONT) (linked A0 nowidth noorient ONE FRONT)
    (TEMPERATURE A0 COLD)
    (SHAPE B0 OBLONG)
    (SURFACE-CONDITION B0 SMOOTH)
    (PAINTED B0 BLACK)
    (HAS-HOLE B0 THREE BACK) (lasthole B0 THREE BACK) (linked B0 nowidth noorient THREE BACK)
    (TEMPERATURE B0 COLD)
    (SHAPE C0 CIRCULAR)
    (SURFACE-CONDITION C0 SMOOTH)
    (PAINTED C0 RED)
    (HAS-HOLE C0 ONE BACK) (lasthole C0 ONE BACK) (linked C0 nowidth noorient ONE BACK)
    (TEMPERATURE C0 COLD)
    (SHAPE D0 CYLINDRICAL)
    (SURFACE-CONDITION D0 SMOOTH)
    (PAINTED D0 BLUE)
    (HAS-HOLE D0 THREE FRONT) (lasthole D0 THREE FRONT) (linked D0 nowidth noorient THREE FRONT)
    (TEMPERATURE D0 COLD)
    (SHAPE E0 CIRCULAR)
    (SURFACE-CONDITION E0 SMOOTH)
    (PAINTED E0 RED)
    (HAS-HOLE E0 THREE BACK) (lasthole E0 THREE BACK) (linked E0 nowidth noorient THREE BACK)
    (TEMPERATURE E0 COLD)
    (SHAPE F0 CYLINDRICAL)
    (SURFACE-CONDITION F0 ROUGH)
    (PAINTED F0 BLUE)
    (HAS-HOLE F0 TWO FRONT) (lasthole F0 TWO FRONT) (linked F0 nowidth noorient TWO FRONT)
    (TEMPERATURE F0 COLD)
    (SHAPE G0 CIRCULAR)
    (SURFACE-CONDITION G0 SMOOTH)
    (PAINTED G0 BLACK)
    (HAS-HOLE G0 TWO BACK) (lasthole G0 TWO BACK) (linked G0 nowidth noorient TWO BACK)
    (TEMPERATURE G0 COLD)
    (SHAPE H0 CYLINDRICAL)
    (SURFACE-CONDITION H0 POLISHED)
    (PAINTED H0 BLUE)
    (HAS-HOLE H0 TWO BACK) (lasthole H0 TWO BACK) (linked H0 nowidth noorient TWO BACK)
    (TEMPERATURE H0 COLD)
    (SHAPE I0 OBLONG)
    (SURFACE-CONDITION I0 SMOOTH)
    (PAINTED I0 BLACK)
    (HAS-HOLE I0 ONE FRONT) (lasthole I0 ONE FRONT) (linked I0 nowidth noorient ONE FRONT)
    (TEMPERATURE I0 COLD)
    (SHAPE J0 CIRCULAR)
    (SURFACE-CONDITION J0 ROUGH)
    (PAINTED J0 RED)
    (HAS-HOLE J0 ONE FRONT) (lasthole J0 ONE FRONT) (linked J0 nowidth noorient ONE FRONT)
    (TEMPERATURE J0 COLD)
    (SHAPE K0 OBLONG)
    (SURFACE-CONDITION K0 POLISHED)
    (PAINTED K0 BLACK)
    (HAS-HOLE K0 TWO FRONT) (lasthole K0 TWO FRONT) (linked K0 nowidth noorient TWO FRONT)
    (TEMPERATURE K0 COLD)
    (SHAPE L0 CYLINDRICAL)
    (SURFACE-CONDITION L0 POLISHED)
    (PAINTED L0 BLACK)
    (HAS-HOLE L0 THREE FRONT) (lasthole L0 THREE FRONT) (linked L0 nowidth noorient THREE FRONT)
    (TEMPERATURE L0 COLD)
    (SHAPE M0 CIRCULAR)
    (SURFACE-CONDITION M0 POLISHED)
    (PAINTED M0 BLUE)
    (HAS-HOLE M0 TWO FRONT) (lasthole M0 TWO FRONT) (linked M0 nowidth noorient TWO FRONT)
    (TEMPERATURE M0 COLD)
    (SHAPE N0 CYLINDRICAL)
    (SURFACE-CONDITION N0 SMOOTH)
    (PAINTED N0 RED)
    (HAS-HOLE N0 ONE BACK) (lasthole N0 ONE BACK) (linked N0 nowidth noorient ONE BACK)
    (TEMPERATURE N0 COLD)
    (SHAPE O0 OBLONG)
    (SURFACE-CONDITION O0 SMOOTH)
    (PAINTED O0 BLACK)
    (HAS-HOLE O0 THREE BACK) (lasthole O0 THREE BACK) (linked O0 nowidth noorient THREE BACK)
    (TEMPERATURE O0 COLD)
    (SHAPE Q0 OBLONG)
    (SURFACE-CONDITION Q0 ROUGH)
    (PAINTED Q0 RED)
    (HAS-HOLE Q0 TWO BACK) (lasthole Q0 TWO BACK) (linked Q0 nowidth noorient TWO BACK)
    (TEMPERATURE Q0 COLD)
    (SHAPE P0 CIRCULAR)
    (SURFACE-CONDITION P0 ROUGH)
    (PAINTED P0 BLUE)
    (HAS-HOLE P0 ONE BACK) (lasthole P0 ONE BACK) (linked P0 nowidth noorient ONE BACK)
    (TEMPERATURE P0 COLD)
    (SHAPE R0 OBLONG)
    (SURFACE-CONDITION R0 SMOOTH)
    (PAINTED R0 BLACK)
    (HAS-HOLE R0 THREE FRONT) (lasthole R0 THREE FRONT) (linked R0 nowidth noorient THREE FRONT)
    (TEMPERATURE R0 COLD)
    (SHAPE S0 OBLONG)
    (SURFACE-CONDITION S0 SMOOTH)
    (PAINTED S0 YELLOW)
    (HAS-HOLE S0 ONE BACK) (lasthole S0 ONE BACK) (linked S0 nowidth noorient ONE BACK)
    (TEMPERATURE S0 COLD)
    (SHAPE U0 CIRCULAR)
    (SURFACE-CONDITION U0 SMOOTH)
    (PAINTED U0 YELLOW)
    (HAS-HOLE U0 THREE FRONT) (lasthole U0 THREE FRONT) (linked U0 nowidth noorient THREE FRONT)
    (TEMPERATURE U0 COLD)
    (SHAPE V0 OBLONG)
    (SURFACE-CONDITION V0 POLISHED)
    (PAINTED V0 BLACK)
    (HAS-HOLE V0 ONE BACK) (lasthole V0 ONE BACK) (linked V0 nowidth noorient ONE BACK)
    (TEMPERATURE V0 COLD)
    (SHAPE W0 CIRCULAR)
    (SURFACE-CONDITION W0 SMOOTH)
    (PAINTED W0 YELLOW)
    (HAS-HOLE W0 ONE FRONT) (lasthole W0 ONE FRONT) (linked W0 nowidth noorient ONE FRONT)
    (TEMPERATURE W0 COLD)
    (SHAPE Z0 CIRCULAR)
    (SURFACE-CONDITION Z0 SMOOTH)
    (PAINTED Z0 YELLOW)
    (HAS-HOLE Z0 THREE FRONT) (lasthole Z0 THREE FRONT) (linked Z0 nowidth noorient THREE FRONT)
    (TEMPERATURE Z0 COLD)
    (SHAPE A1 CIRCULAR)
    (SURFACE-CONDITION A1 SMOOTH)
    (PAINTED A1 BLUE)
    (HAS-HOLE A1 THREE BACK) (lasthole A1 THREE BACK) (linked A1 nowidth noorient THREE BACK)
    (TEMPERATURE A1 COLD)
    (SHAPE B1 OBLONG)
    (SURFACE-CONDITION B1 SMOOTH)
    (PAINTED B1 RED)
    (HAS-HOLE B1 TWO FRONT) (lasthole B1 TWO FRONT) (linked B1 nowidth noorient TWO FRONT)
    (TEMPERATURE B1 COLD)
    (SHAPE C1 OBLONG)
    (SURFACE-CONDITION C1 ROUGH)
    (PAINTED C1 RED)
    (HAS-HOLE C1 ONE FRONT) (lasthole C1 ONE FRONT) (linked C1 nowidth noorient ONE FRONT)
    (TEMPERATURE C1 COLD)
    (SHAPE D1 CIRCULAR)
    (SURFACE-CONDITION D1 POLISHED)
    (PAINTED D1 YELLOW)
    (HAS-HOLE D1 TWO FRONT) (lasthole D1 TWO FRONT) (linked D1 nowidth noorient TWO FRONT)
    (TEMPERATURE D1 COLD)
    (SHAPE E1 CIRCULAR)
    (SURFACE-CONDITION E1 POLISHED)
    (PAINTED E1 BLACK)
    (HAS-HOLE E1 THREE FRONT) (lasthole E1 THREE FRONT) (linked E1 nowidth noorient THREE FRONT)
    (TEMPERATURE E1 COLD)
    (SHAPE F1 CYLINDRICAL)
    (SURFACE-CONDITION F1 ROUGH)
    (PAINTED F1 RED)
    (HAS-HOLE F1 ONE BACK) (lasthole F1 ONE BACK) (linked F1 nowidth noorient ONE BACK)
    (TEMPERATURE F1 COLD)
    (SHAPE G1 OBLONG)
    (SURFACE-CONDITION G1 ROUGH)
    (PAINTED G1 BLACK)
    (HAS-HOLE G1 TWO BACK) (lasthole G1 TWO BACK) (linked G1 nowidth noorient TWO BACK)
    (TEMPERATURE G1 COLD)
    (SHAPE H1 CYLINDRICAL)
    (SURFACE-CONDITION H1 SMOOTH)
    (PAINTED H1 YELLOW)
    (HAS-HOLE H1 TWO FRONT) (lasthole H1 TWO FRONT) (linked H1 nowidth noorient TWO FRONT)
    (TEMPERATURE H1 COLD)
    (SHAPE I1 CIRCULAR)
    (SURFACE-CONDITION I1 POLISHED)
    (PAINTED I1 BLUE)
    (HAS-HOLE I1 TWO BACK) (lasthole I1 TWO BACK) (linked I1 nowidth noorient TWO BACK)
    (TEMPERATURE I1 COLD)
    (SHAPE J1 OBLONG)
    (SURFACE-CONDITION J1 ROUGH)
    (PAINTED J1 RED)
    (HAS-HOLE J1 ONE BACK) (lasthole J1 ONE BACK) (linked J1 nowidth noorient ONE BACK)
    (TEMPERATURE J1 COLD)
    (SHAPE K1 CYLINDRICAL)
    (SURFACE-CONDITION K1 POLISHED)
    (PAINTED K1 BLACK)
    (HAS-HOLE K1 ONE BACK) (lasthole K1 ONE BACK) (linked K1 nowidth noorient ONE BACK)
    (TEMPERATURE K1 COLD)
    (SHAPE L1 CIRCULAR)
    (SURFACE-CONDITION L1 SMOOTH)
    (PAINTED L1 BLUE)
    (HAS-HOLE L1 THREE BACK) (lasthole L1 THREE BACK) (linked L1 nowidth noorient THREE BACK)
    (TEMPERATURE L1 COLD)
    (SHAPE M1 CYLINDRICAL)
    (SURFACE-CONDITION M1 ROUGH)
    (PAINTED M1 BLACK)
    (HAS-HOLE M1 ONE BACK) (lasthole M1 ONE BACK) (linked M1 nowidth noorient ONE BACK)
    (TEMPERATURE M1 COLD)
    (SHAPE N1 CIRCULAR)
    (SURFACE-CONDITION N1 ROUGH)
    (PAINTED N1 YELLOW)
    (HAS-HOLE N1 THREE BACK) (lasthole N1 THREE BACK) (linked N1 nowidth noorient THREE BACK)
    (TEMPERATURE N1 COLD)
    (SHAPE O1 CYLINDRICAL)
    (SURFACE-CONDITION O1 ROUGH)
    (PAINTED O1 BLACK)
    (HAS-HOLE O1 ONE FRONT) (lasthole O1 ONE FRONT) (linked O1 nowidth noorient ONE FRONT)
    (TEMPERATURE O1 COLD)
    (SHAPE Q1 OBLONG)
    (SURFACE-CONDITION Q1 SMOOTH)
    (PAINTED Q1 BLUE)
    (HAS-HOLE Q1 ONE FRONT) (lasthole Q1 ONE FRONT) (linked Q1 nowidth noorient ONE FRONT)
    (TEMPERATURE Q1 COLD)
    (SHAPE P1 CYLINDRICAL)
    (SURFACE-CONDITION P1 SMOOTH)
    (PAINTED P1 YELLOW)
    (HAS-HOLE P1 THREE FRONT) (lasthole P1 THREE FRONT) (linked P1 nowidth noorient THREE FRONT)
    (TEMPERATURE P1 COLD)
    (SHAPE R1 CYLINDRICAL)
    (SURFACE-CONDITION R1 SMOOTH)
    (PAINTED R1 BLACK)
    (HAS-HOLE R1 TWO BACK) (lasthole R1 TWO BACK) (linked R1 nowidth noorient TWO BACK)
    (TEMPERATURE R1 COLD)
    (SHAPE S1 CYLINDRICAL)
    (SURFACE-CONDITION S1 SMOOTH)
    (PAINTED S1 RED)
    (HAS-HOLE S1 ONE BACK) (lasthole S1 ONE BACK) (linked S1 nowidth noorient ONE BACK)
    (TEMPERATURE S1 COLD)
    (SHAPE U1 CIRCULAR)
    (SURFACE-CONDITION U1 SMOOTH)
    (PAINTED U1 YELLOW)
    (HAS-HOLE U1 TWO FRONT) (lasthole U1 TWO FRONT) (linked U1 nowidth noorient TWO FRONT)
    (TEMPERATURE U1 COLD)
    (SHAPE V1 CIRCULAR)
    (SURFACE-CONDITION V1 ROUGH)
    (PAINTED V1 YELLOW)
    (HAS-HOLE V1 ONE FRONT) (lasthole V1 ONE FRONT) (linked V1 nowidth noorient ONE FRONT)
    (TEMPERATURE V1 COLD)
    (SHAPE W1 CIRCULAR)
    (SURFACE-CONDITION W1 POLISHED)
    (PAINTED W1 BLACK)
    (HAS-HOLE W1 ONE BACK) (lasthole W1 ONE BACK) (linked W1 nowidth noorient ONE BACK)
    (TEMPERATURE W1 COLD)
    (SHAPE Z1 CIRCULAR)
    (SURFACE-CONDITION Z1 POLISHED)
    (PAINTED Z1 BLUE)
    (HAS-HOLE Z1 THREE FRONT) (lasthole Z1 THREE FRONT) (linked Z1 nowidth noorient THREE FRONT)
    (TEMPERATURE Z1 COLD)
    (SHAPE A2 OBLONG)
    (SURFACE-CONDITION A2 ROUGH)
    (PAINTED A2 RED)
    (HAS-HOLE A2 TWO FRONT) (lasthole A2 TWO FRONT) (linked A2 nowidth noorient TWO FRONT)
    (TEMPERATURE A2 COLD)
    (SHAPE B2 OBLONG)
    (SURFACE-CONDITION B2 SMOOTH)
    (PAINTED B2 RED)
    (HAS-HOLE B2 TWO BACK) (lasthole B2 TWO BACK) (linked B2 nowidth noorient TWO BACK)
    (TEMPERATURE B2 COLD)
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
    (SHAPE R0 CYLINDRICAL)
    (PAINTED I1 BLACK)
    (SURFACE-CONDITION C0 POLISHED)
    (SURFACE-CONDITION R0 POLISHED)
    (SHAPE V0 CYLINDRICAL)
    (SURFACE-CONDITION S0 ROUGH)
    (SURFACE-CONDITION D0 POLISHED)
    (SHAPE B1 CYLINDRICAL)
    (PAINTED B2 YELLOW)
    (SURFACE-CONDITION R1 POLISHED)
    (SHAPE D1 CYLINDRICAL)
    (SURFACE-CONDITION H0 SMOOTH)
    (SHAPE A2 CYLINDRICAL)
    (SURFACE-CONDITION B0 POLISHED)
    (SHAPE M0 CYLINDRICAL)
    (SHAPE V1 CYLINDRICAL)
    (PAINTED V0 RED)
    (PAINTED W1 YELLOW)
    (SURFACE-CONDITION L0 ROUGH)
    (SHAPE Z1 CYLINDRICAL)
    (PAINTED V1 RED)
    (PAINTED C0 YELLOW)
    (SURFACE-CONDITION G1 SMOOTH)
    (PAINTED H0 BLACK)
    (PAINTED K0 BLUE)
    (PAINTED A0 RED)
    (SHAPE C0 CYLINDRICAL)
    (SURFACE-CONDITION B2 POLISHED)
    (SURFACE-CONDITION H1 ROUGH)
    (SURFACE-CONDITION B1 POLISHED)
    (SHAPE O0 CYLINDRICAL)
    (SHAPE J1 CYLINDRICAL)
    (SHAPE U0 CYLINDRICAL)
    (PAINTED G1 RED)
    (SHAPE B2 CYLINDRICAL)
    (SURFACE-CONDITION Z1 SMOOTH)
    (PAINTED A2 BLACK)
    (SURFACE-CONDITION A0 ROUGH)
    (PAINTED D1 BLACK)
    (PAINTED Q1 BLACK)
    (SURFACE-CONDITION O0 POLISHED)
    (PAINTED S1 YELLOW)
    (SURFACE-CONDITION E1 SMOOTH)
    (PAINTED P1 RED)
    (PAINTED H1 BLUE)
    (SHAPE W0 CYLINDRICAL)
    (PAINTED L0 BLUE)
    (SHAPE S0 CYLINDRICAL)
)))
