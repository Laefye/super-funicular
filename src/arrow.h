#ifndef ARROW_H
#define ARROW_H
#include <stdint.h>
#define ARROW_DIRECTION_MASK 0b00000011
#define ARROW_UP 0b00
#define ARROW_RIGHT 0b01
#define ARROW_BOTTOM 0b10
#define ARROW_LEFT 0b11
#define ARROW_FLIP 0b00000100

typedef struct arrow_t arrow_t;

#define MAKE_ARROW(x, y, type, flags) ((arrow_t) {x, y, type, flags})

typedef uint16_t arrow_type;
typedef uint8_t arrow_flags; 
typedef size_t coordinate;

struct arrow_t {
    coordinate x;
    coordinate y;
    arrow_type type;
    arrow_flags flags;
};

typedef uint8_t power_t;

#define ARROW_TYPE_BASIC 1
#define ARROW_TYPE_OUT   2
#define ARROW_TYPE_AND   3

#endif
