(define (problem schedule-37-2)
(:domain schedule)
(:objects
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
    (SHAPE A0 OBLONG)
    (SURFACE-CONDITION A0 POLISHED)
    (PAINTED A0 YELLOW)
    (HAS-HOLE A0 ONE FRONT) (lasthole A0 ONE FRONT) (linked A0 nowidth noorient ONE FRONT)
    (TEMPERATURE A0 COLD)
    (SHAPE B0 OBLONG)
    (SURFACE-CONDITION B0 POLISHED)
    (PAINTED B0 YELLOW)
    (HAS-HOLE B0 THREE BACK) (lasthole B0 THREE BACK) (linked B0 nowidth noorient THREE BACK)
    (TEMPERATURE B0 COLD)
    (SHAPE C0 OBLONG)
    (SURFACE-CONDITION C0 ROUGH)
    (PAINTED C0 BLACK)
    (HAS-HOLE C0 TWO BACK) (lasthole C0 TWO BACK) (linked C0 nowidth noorient TWO BACK)
    (TEMPERATURE C0 COLD)
    (SHAPE D0 CIRCULAR)
    (SURFACE-CONDITION D0 POLISHED)
    (PAINTED D0 RED)
    (HAS-HOLE D0 TWO BACK) (lasthole D0 TWO BACK) (linked D0 nowidth noorient TWO BACK)
    (TEMPERATURE D0 COLD)
    (SHAPE E0 CYLINDRICAL)
    (SURFACE-CONDITION E0 ROUGH)
    (PAINTED E0 RED)
    (HAS-HOLE E0 THREE FRONT) (lasthole E0 THREE FRONT) (linked E0 nowidth noorient THREE FRONT)
    (TEMPERATURE E0 COLD)
    (SHAPE F0 CIRCULAR)
    (SURFACE-CONDITION F0 ROUGH)
    (PAINTED F0 RED)
    (HAS-HOLE F0 ONE BACK) (lasthole F0 ONE BACK) (linked F0 nowidth noorient ONE BACK)
    (TEMPERATURE F0 COLD)
    (SHAPE G0 CIRCULAR)
    (SURFACE-CONDITION G0 ROUGH)
    (PAINTED G0 BLUE)
    (HAS-HOLE G0 TWO FRONT) (lasthole G0 TWO FRONT) (linked G0 nowidth noorient TWO FRONT)
    (TEMPERATURE G0 COLD)
    (SHAPE H0 CIRCULAR)
    (SURFACE-CONDITION H0 ROUGH)
    (PAINTED H0 RED)
    (HAS-HOLE H0 ONE BACK) (lasthole H0 ONE BACK) (linked H0 nowidth noorient ONE BACK)
    (TEMPERATURE H0 COLD)
    (SHAPE I0 OBLONG)
    (SURFACE-CONDITION I0 POLISHED)
    (PAINTED I0 BLUE)
    (HAS-HOLE I0 TWO BACK) (lasthole I0 TWO BACK) (linked I0 nowidth noorient TWO BACK)
    (TEMPERATURE I0 COLD)
    (SHAPE J0 CIRCULAR)
    (SURFACE-CONDITION J0 SMOOTH)
    (PAINTED J0 BLUE)
    (HAS-HOLE J0 THREE FRONT) (lasthole J0 THREE FRONT) (linked J0 nowidth noorient THREE FRONT)
    (TEMPERATURE J0 COLD)
    (SHAPE K0 OBLONG)
    (SURFACE-CONDITION K0 POLISHED)
    (PAINTED K0 BLACK)
    (HAS-HOLE K0 TWO FRONT) (lasthole K0 TWO FRONT) (linked K0 nowidth noorient TWO FRONT)
    (TEMPERATURE K0 COLD)
    (SHAPE L0 CIRCULAR)
    (SURFACE-CONDITION L0 ROUGH)
    (PAINTED L0 YELLOW)
    (HAS-HOLE L0 THREE FRONT) (lasthole L0 THREE FRONT) (linked L0 nowidth noorient THREE FRONT)
    (TEMPERATURE L0 COLD)
    (SHAPE M0 OBLONG)
    (SURFACE-CONDITION M0 SMOOTH)
    (PAINTED M0 YELLOW)
    (HAS-HOLE M0 ONE BACK) (lasthole M0 ONE BACK) (linked M0 nowidth noorient ONE BACK)
    (TEMPERATURE M0 COLD)
    (SHAPE N0 CIRCULAR)
    (SURFACE-CONDITION N0 SMOOTH)
    (PAINTED N0 YELLOW)
    (HAS-HOLE N0 TWO BACK) (lasthole N0 TWO BACK) (linked N0 nowidth noorient TWO BACK)
    (TEMPERATURE N0 COLD)
    (SHAPE O0 OBLONG)
    (SURFACE-CONDITION O0 POLISHED)
    (PAINTED O0 RED)
    (HAS-HOLE O0 ONE BACK) (lasthole O0 ONE BACK) (linked O0 nowidth noorient ONE BACK)
    (TEMPERATURE O0 COLD)
    (SHAPE Q0 CIRCULAR)
    (SURFACE-CONDITION Q0 POLISHED)
    (PAINTED Q0 BLUE)
    (HAS-HOLE Q0 ONE FRONT) (lasthole Q0 ONE FRONT) (linked Q0 nowidth noorient ONE FRONT)
    (TEMPERATURE Q0 COLD)
    (SHAPE P0 CYLINDRICAL)
    (SURFACE-CONDITION P0 ROUGH)
    (PAINTED P0 RED)
    (HAS-HOLE P0 ONE FRONT) (lasthole P0 ONE FRONT) (linked P0 nowidth noorient ONE FRONT)
    (TEMPERATURE P0 COLD)
    (SHAPE R0 OBLONG)
    (SURFACE-CONDITION R0 POLISHED)
    (PAINTED R0 YELLOW)
    (HAS-HOLE R0 THREE BACK) (lasthole R0 THREE BACK) (linked R0 nowidth noorient THREE BACK)
    (TEMPERATURE R0 COLD)
    (SHAPE S0 CYLINDRICAL)
    (SURFACE-CONDITION S0 ROUGH)
    (PAINTED S0 YELLOW)
    (HAS-HOLE S0 TWO FRONT) (lasthole S0 TWO FRONT) (linked S0 nowidth noorient TWO FRONT)
    (TEMPERATURE S0 COLD)
    (SHAPE U0 CYLINDRICAL)
    (SURFACE-CONDITION U0 ROUGH)
    (PAINTED U0 BLACK)
    (HAS-HOLE U0 TWO FRONT) (lasthole U0 TWO FRONT) (linked U0 nowidth noorient TWO FRONT)
    (TEMPERATURE U0 COLD)
    (SHAPE V0 CYLINDRICAL)
    (SURFACE-CONDITION V0 ROUGH)
    (PAINTED V0 YELLOW)
    (HAS-HOLE V0 ONE FRONT) (lasthole V0 ONE FRONT) (linked V0 nowidth noorient ONE FRONT)
    (TEMPERATURE V0 COLD)
    (SHAPE W0 OBLONG)
    (SURFACE-CONDITION W0 ROUGH)
    (PAINTED W0 BLACK)
    (HAS-HOLE W0 THREE FRONT) (lasthole W0 THREE FRONT) (linked W0 nowidth noorient THREE FRONT)
    (TEMPERATURE W0 COLD)
    (SHAPE Z0 OBLONG)
    (SURFACE-CONDITION Z0 SMOOTH)
    (PAINTED Z0 BLACK)
    (HAS-HOLE Z0 TWO FRONT) (lasthole Z0 TWO FRONT) (linked Z0 nowidth noorient TWO FRONT)
    (TEMPERATURE Z0 COLD)
    (SHAPE A1 CYLINDRICAL)
    (SURFACE-CONDITION A1 SMOOTH)
    (PAINTED A1 YELLOW)
    (HAS-HOLE A1 TWO FRONT) (lasthole A1 TWO FRONT) (linked A1 nowidth noorient TWO FRONT)
    (TEMPERATURE A1 COLD)
    (SHAPE B1 CYLINDRICAL)
    (SURFACE-CONDITION B1 POLISHED)
    (PAINTED B1 YELLOW)
    (HAS-HOLE B1 THREE FRONT) (lasthole B1 THREE FRONT) (linked B1 nowidth noorient THREE FRONT)
    (TEMPERATURE B1 COLD)
    (SHAPE C1 CYLINDRICAL)
    (SURFACE-CONDITION C1 ROUGH)
    (PAINTED C1 RED)
    (HAS-HOLE C1 ONE FRONT) (lasthole C1 ONE FRONT) (linked C1 nowidth noorient ONE FRONT)
    (TEMPERATURE C1 COLD)
    (SHAPE D1 CYLINDRICAL)
    (SURFACE-CONDITION D1 POLISHED)
    (PAINTED D1 RED)
    (HAS-HOLE D1 THREE BACK) (lasthole D1 THREE BACK) (linked D1 nowidth noorient THREE BACK)
    (TEMPERATURE D1 COLD)
    (SHAPE E1 CIRCULAR)
    (SURFACE-CONDITION E1 POLISHED)
    (PAINTED E1 BLUE)
    (HAS-HOLE E1 TWO BACK) (lasthole E1 TWO BACK) (linked E1 nowidth noorient TWO BACK)
    (TEMPERATURE E1 COLD)
    (SHAPE F1 OBLONG)
    (SURFACE-CONDITION F1 SMOOTH)
    (PAINTED F1 RED)
    (HAS-HOLE F1 ONE FRONT) (lasthole F1 ONE FRONT) (linked F1 nowidth noorient ONE FRONT)
    (TEMPERATURE F1 COLD)
    (SHAPE G1 CIRCULAR)
    (SURFACE-CONDITION G1 ROUGH)
    (PAINTED G1 BLUE)
    (HAS-HOLE G1 ONE BACK) (lasthole G1 ONE BACK) (linked G1 nowidth noorient ONE BACK)
    (TEMPERATURE G1 COLD)
    (SHAPE H1 OBLONG)
    (SURFACE-CONDITION H1 SMOOTH)
    (PAINTED H1 BLUE)
    (HAS-HOLE H1 ONE BACK) (lasthole H1 ONE BACK) (linked H1 nowidth noorient ONE BACK)
    (TEMPERATURE H1 COLD)
    (SHAPE I1 OBLONG)
    (SURFACE-CONDITION I1 ROUGH)
    (PAINTED I1 YELLOW)
    (HAS-HOLE I1 ONE FRONT) (lasthole I1 ONE FRONT) (linked I1 nowidth noorient ONE FRONT)
    (TEMPERATURE I1 COLD)
    (SHAPE J1 OBLONG)
    (SURFACE-CONDITION J1 ROUGH)
    (PAINTED J1 BLUE)
    (HAS-HOLE J1 ONE FRONT) (lasthole J1 ONE FRONT) (linked J1 nowidth noorient ONE FRONT)
    (TEMPERATURE J1 COLD)
    (SHAPE K1 CIRCULAR)
    (SURFACE-CONDITION K1 POLISHED)
    (PAINTED K1 BLACK)
    (HAS-HOLE K1 THREE FRONT) (lasthole K1 THREE FRONT) (linked K1 nowidth noorient THREE FRONT)
    (TEMPERATURE K1 COLD)
    (SHAPE L1 CIRCULAR)
    (SURFACE-CONDITION L1 ROUGH)
    (PAINTED L1 YELLOW)
    (HAS-HOLE L1 THREE FRONT) (lasthole L1 THREE FRONT) (linked L1 nowidth noorient THREE FRONT)
    (TEMPERATURE L1 COLD)
    (SHAPE M1 CIRCULAR)
    (SURFACE-CONDITION M1 SMOOTH)
    (PAINTED M1 RED)
    (HAS-HOLE M1 ONE FRONT) (lasthole M1 ONE FRONT) (linked M1 nowidth noorient ONE FRONT)
    (TEMPERATURE M1 COLD)
    (SHAPE N1 CYLINDRICAL)
    (SURFACE-CONDITION N1 POLISHED)
    (PAINTED N1 BLUE)
    (HAS-HOLE N1 TWO FRONT) (lasthole N1 TWO FRONT) (linked N1 nowidth noorient TWO FRONT)
    (TEMPERATURE N1 COLD)
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
    (SHAPE J1 CYLINDRICAL)
    (SURFACE-CONDITION J0 ROUGH)
    (SHAPE W0 CYLINDRICAL)
    (SHAPE H1 CYLINDRICAL)
    (SURFACE-CONDITION B0 SMOOTH)
    (SURFACE-CONDITION G0 SMOOTH)
    (PAINTED B0 RED)
    (PAINTED I1 BLUE)
    (SURFACE-CONDITION G1 SMOOTH)
    (PAINTED K0 BLUE)
    (PAINTED H0 BLUE)
    (PAINTED G0 RED)
    (SURFACE-CONDITION C0 SMOOTH)
    (SURFACE-CONDITION Z0 POLISHED)
    (PAINTED E0 BLACK)
    (SHAPE G1 CYLINDRICAL)
    (SURFACE-CONDITION L1 POLISHED)
    (PAINTED I0 RED)
    (SURFACE-CONDITION B1 ROUGH)
    (SHAPE L0 CYLINDRICAL)
    (SURFACE-CONDITION E0 POLISHED)
    (SHAPE Z0 CYLINDRICAL)
    (SURFACE-CONDITION W0 POLISHED)
    (SHAPE I0 CYLINDRICAL)
    (PAINTED Z0 RED)
    (SURFACE-CONDITION Q0 ROUGH)
    (SURFACE-CONDITION R0 SMOOTH)
    (SURFACE-CONDITION O0 SMOOTH)
    (SHAPE J0 CYLINDRICAL)
    (PAINTED O0 YELLOW)
    (SURFACE-CONDITION D1 ROUGH)
    (PAINTED C1 BLACK)
    (PAINTED B1 BLUE)
    (PAINTED R0 RED)
    (SHAPE M0 CYLINDRICAL)
    (PAINTED D0 BLUE)
    (PAINTED L0 BLUE)
)))
