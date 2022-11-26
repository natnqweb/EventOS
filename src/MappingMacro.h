#ifndef MAPPING_MACRO_H
#define MAPPING_MACRO_H

#define ADD_PIN_TO_MAP(PIN) PIN,

#define MERGE_PINS(PIN,VPIN) {PIN,VPIN},

#define START_PIN_ARRAY static PinType s_map[] \
{
#define ADD_PIN(X) (PinType)X,
#define END_PIN_ARRAY };
#define _SIZE_OF_PIN_ARRAY (sizeof(s_map)/sizeof(s_map[0]))

#endif