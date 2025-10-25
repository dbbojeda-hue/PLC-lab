PROGRAM ciclo_principal
  VAR
    inclinado : BOOL := 0;
    ultimo_tilt : BOOL := 0;
  END_VAR
  VAR_EXTERNAL
    conteo_tilt : INT;
  END_VAR
  VAR
    CTU1 : CTU;
  END_VAR
  VAR_EXTERNAL
    estado1 : BOOL;
  END_VAR
  VAR
    TON0 : TON;
    TON1 : TON;
    R_TRIG1 : R_TRIG;
  END_VAR

  TON1(IN := inclinado, PT := T#1000ms);
  estado1 := TON1.Q OR estado1;
  TON0(IN := inclinado, PT := T#100ms);
  ultimo_tilt := TON0.Q;
  R_TRIG1(CLK := NOT(ultimo_tilt) AND inclinado);
  CTU1(CU := R_TRIG1.Q, PV := 100);
  conteo_tilt := CTU1.CV;
END_PROGRAM

PROGRAM alerta
  VAR_EXTERNAL
    estado1 : BOOL;
  END_VAR
  VAR
    segmento_a : BOOL := 0;
    segmento_b : BOOL := 0;
    segmento_c : BOOL := 0;
    segmento_d : BOOL := 0;
    segmento_e : BOOL := 0;
    segmento_f : BOOL := 0;
    segmento_g : BOOL := 0;
    parpadear_led : BOOL := 0;
    TON0 : TON;
    TOF0 : TOF;
    CTU0 : CTU;
    R_TRIG1 : R_TRIG;
    _TMP_NOT42_OUT : BOOL;
    _TMP_AND41_OUT : BOOL;
  END_VAR

  segmento_b := estado1;
  segmento_c := estado1;
  R_TRIG1(CLK := TOF0.Q);
  CTU0(CU := R_TRIG1.Q, PV := 5);
  _TMP_NOT42_OUT := NOT(CTU0.Q);
  _TMP_AND41_OUT := AND(NOT(parpadear_led) AND estado1, _TMP_NOT42_OUT);
  TON0(IN := _TMP_AND41_OUT, PT := T#500ms);
  TOF0(IN := TON0.Q, PT := T#500ms);
  parpadear_led := TOF0.Q;
END_PROGRAM


CONFIGURATION Config0

  RESOURCE Res0 ON PLC
    VAR_GLOBAL
      estado1 : BOOL := 0;
      conteo_tilt : INT := 0;
    END_VAR
    TASK Principal(INTERVAL := T#200ms,PRIORITY := 0);
    TASK salidas(INTERVAL := T#200ms,PRIORITY := 0);
    PROGRAM registro_entradas WITH Principal : ciclo_principal;
    PROGRAM dar_aviso WITH salidas : alerta;
  END_RESOURCE
END_CONFIGURATION
