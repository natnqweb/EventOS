#ifndef MAPPING_MACRO_H
#define MAPPING_MACRO_H

#define START_MAPPING_DECLARATION struct PinMap { unsigned char pin, index; }; \
enum PinMapping \
{
#define END_MAPPING_DECLARATION  NUMBER_OF_PINS \
};

#define ADD_PIN_TO_MAP(PIN) PIN,

#define MERGE_PINS(PIN,VPIN) {PIN,VPIN}

#define START_MAPPING_DEFINITION static const PinMap s_map[NUMBER_OF_PINS] \
{

#define END_MAPPING_DEFINITION };

#endif