TYPE
  LOGLEVEL : (CRITICAL, WARNING, INFO, DEBUG) := INFO;
END_TYPE

FUNCTION_BLOCK LOGGER
  VAR_INPUT
    TRIG : BOOL;
    MSG : STRING;
    LEVEL : LOGLEVEL := INFO;
  END_VAR
  VAR
    TRIG0 : BOOL;
  END_VAR

  IF TRIG AND NOT TRIG0 THEN
  {{
   LogMessage(GetFbVar(LEVEL),(char*)GetFbVar(MSG, .body),GetFbVar(MSG, .len));
  }}
  END_IF;
  TRIG0:=TRIG;
END_FUNCTION_BLOCK


PROGRAM ciclo_principal
  VAR
    inclinado AT %IX1.2 : BOOL;
  END_VAR
  VAR
    ultimo_tilt : BOOL;
    conteo_tilt : INT;
    CTU1 : CTU;
    estado1 : BOOL;
    TON0 : TON;
    TON1 : TON;
  END_VAR
  VAR
    segmento_a AT %QX0.0 : BOOL;
    segmento_b AT %QX0.1 : BOOL;
    segmento_c AT %QX0.2 : BOOL;
    segmento_d AT %QX0.3 : BOOL;
    segmento_e AT %QX0.4 : BOOL;
    segmento_f AT %QX0.5 : BOOL;
    segmento_g AT %QX0.6 : BOOL;
    parpadear_led AT %QX0.7 : BOOL;
  END_VAR
  VAR
    TON2 : TON;
    TOF0 : TOF;
    CTU0 : CTU;
    R_TRIG1 : R_TRIG;
    R_TRIG2 : R_TRIG;
    _TMP_NOT52_OUT : BOOL;
    _TMP_AND44_OUT : BOOL;
  END_VAR

  TON1(IN := inclinado, PT := T#1000ms);
  estado1 := TON1.Q OR estado1;
  TON0(IN := inclinado, PT := T#100ms);
  ultimo_tilt := TON0.Q;
  R_TRIG1(CLK := NOT(ultimo_tilt) AND inclinado);
  CTU1(CU := R_TRIG1.Q, PV := 100);
  conteo_tilt := CTU1.CV;
  segmento_b := estado1;
  segmento_c := estado1;
  R_TRIG2(CLK := TOF0.Q);
  CTU0(CU := R_TRIG2.Q, PV := 5);
  _TMP_NOT52_OUT := NOT(CTU0.Q);
  _TMP_AND44_OUT := AND(NOT(parpadear_led) AND estado1, _TMP_NOT52_OUT);
  TON2(IN := _TMP_AND44_OUT, PT := T#200ms);
  TOF0(IN := TON2.Q, PT := T#200ms);
  parpadear_led := TOF0.Q;
  segmento_a := NOT(estado1);
  segmento_b := NOT(estado1);
  segmento_c := NOT(estado1);
  segmento_d := NOT(estado1);
  segmento_e := NOT(estado1);
  segmento_f := NOT(estado1);
END_PROGRAM


CONFIGURATION Config0

  RESOURCE Res0 ON PLC
    TASK Principal(INTERVAL := T#200ms,PRIORITY := 0);
    PROGRAM registro_entradas WITH Principal : ciclo_principal;
  END_RESOURCE
END_CONFIGURATION
