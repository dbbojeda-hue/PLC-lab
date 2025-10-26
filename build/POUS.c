void LOGGER_init__(LOGGER *data__, BOOL retain) {
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->TRIG,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->MSG,__STRING_LITERAL(0,""),retain)
  __INIT_VAR(data__->LEVEL,LOGLEVEL__INFO,retain)
  __INIT_VAR(data__->TRIG0,__BOOL_LITERAL(FALSE),retain)
}

// Code part
void LOGGER_body__(LOGGER *data__) {
  // Control execution
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(TRUE));
  }
  // Initialise TEMP variables

  if ((__GET_VAR(data__->TRIG,) && !(__GET_VAR(data__->TRIG0,)))) {
    #define GetFbVar(var,...) __GET_VAR(data__->var,__VA_ARGS__)
    #define SetFbVar(var,val,...) __SET_VAR(data__->,var,__VA_ARGS__,val)

   LogMessage(GetFbVar(LEVEL),(char*)GetFbVar(MSG, .body),GetFbVar(MSG, .len));
  
    #undef GetFbVar
    #undef SetFbVar
;
  };
  __SET_VAR(data__->,TRIG0,,__GET_VAR(data__->TRIG,));

  goto __end;

__end:
  return;
} // LOGGER_body__() 





void CICLO_PRINCIPAL_init__(CICLO_PRINCIPAL *data__, BOOL retain) {
  __INIT_LOCATED(BOOL,__IX0_0,data__->INCLINADO,retain)
  __INIT_LOCATED_VALUE(data__->INCLINADO,__BOOL_LITERAL(FALSE))
  __INIT_VAR(data__->ULTIMO_TILT,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->CONTEO_TILT,0,retain)
  CTU_init__(&data__->CTU1,retain);
  __INIT_VAR(data__->ESTADO1,__BOOL_LITERAL(FALSE),retain)
  TON_init__(&data__->TON0,retain);
  TON_init__(&data__->TON1,retain);
  __INIT_VAR(data__->SEGMENTO_A,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->SEGMENTO_B,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->SEGMENTO_C,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->SEGMENTO_D,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->SEGMENTO_E,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->SEGMENTO_F,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->SEGMENTO_G,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->PARPADEAR_LED,__BOOL_LITERAL(FALSE),retain)
  TON_init__(&data__->TON2,retain);
  TOF_init__(&data__->TOF0,retain);
  CTU_init__(&data__->CTU0,retain);
  R_TRIG_init__(&data__->R_TRIG1,retain);
  R_TRIG_init__(&data__->R_TRIG2,retain);
  __INIT_VAR(data__->_TMP_NOT52_OUT,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->_TMP_AND44_OUT,__BOOL_LITERAL(FALSE),retain)
}

// Code part
void CICLO_PRINCIPAL_body__(CICLO_PRINCIPAL *data__) {
  // Initialise TEMP variables

  __SET_VAR(data__->TON1.,IN,,__GET_LOCATED(data__->INCLINADO,));
  __SET_VAR(data__->TON1.,PT,,__time_to_timespec(1, 1000, 0, 0, 0, 0));
  TON_body__(&data__->TON1);
  __SET_VAR(data__->,ESTADO1,,(__GET_VAR(data__->TON1.Q,) || __GET_VAR(data__->ESTADO1,)));
  __SET_VAR(data__->TON0.,IN,,__GET_LOCATED(data__->INCLINADO,));
  __SET_VAR(data__->TON0.,PT,,__time_to_timespec(1, 100, 0, 0, 0, 0));
  TON_body__(&data__->TON0);
  __SET_VAR(data__->,ULTIMO_TILT,,__GET_VAR(data__->TON0.Q,));
  __SET_VAR(data__->R_TRIG1.,CLK,,(!(__GET_VAR(data__->ULTIMO_TILT,)) && __GET_LOCATED(data__->INCLINADO,)));
  R_TRIG_body__(&data__->R_TRIG1);
  __SET_VAR(data__->CTU1.,CU,,__GET_VAR(data__->R_TRIG1.Q,));
  __SET_VAR(data__->CTU1.,PV,,100);
  CTU_body__(&data__->CTU1);
  __SET_VAR(data__->,CONTEO_TILT,,__GET_VAR(data__->CTU1.CV,));
  __SET_VAR(data__->,SEGMENTO_B,,__GET_VAR(data__->ESTADO1,));
  __SET_VAR(data__->,SEGMENTO_C,,__GET_VAR(data__->ESTADO1,));
  __SET_VAR(data__->R_TRIG2.,CLK,,__GET_VAR(data__->TOF0.Q,));
  R_TRIG_body__(&data__->R_TRIG2);
  __SET_VAR(data__->CTU0.,CU,,__GET_VAR(data__->R_TRIG2.Q,));
  __SET_VAR(data__->CTU0.,PV,,5);
  CTU_body__(&data__->CTU0);
  __SET_VAR(data__->,_TMP_NOT52_OUT,,!(__GET_VAR(data__->CTU0.Q,)));
  __SET_VAR(data__->,_TMP_AND44_OUT,,AND__BOOL__BOOL(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (UINT)2,
    (BOOL)(!(__GET_VAR(data__->PARPADEAR_LED,)) && __GET_VAR(data__->ESTADO1,)),
    (BOOL)__GET_VAR(data__->_TMP_NOT52_OUT,)));
  __SET_VAR(data__->TON2.,IN,,__GET_VAR(data__->_TMP_AND44_OUT,));
  __SET_VAR(data__->TON2.,PT,,__time_to_timespec(1, 200, 0, 0, 0, 0));
  TON_body__(&data__->TON2);
  __SET_VAR(data__->TOF0.,IN,,__GET_VAR(data__->TON2.Q,));
  __SET_VAR(data__->TOF0.,PT,,__time_to_timespec(1, 200, 0, 0, 0, 0));
  TOF_body__(&data__->TOF0);
  __SET_VAR(data__->,PARPADEAR_LED,,__GET_VAR(data__->TOF0.Q,));

  goto __end;

__end:
  return;
} // CICLO_PRINCIPAL_body__() 





