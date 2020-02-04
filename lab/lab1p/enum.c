#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

enum day {sun,mon,tue,wed,thu,fri,sat};
typedef  enum day  day;

day FindnextDay(day(d));
int main(void){
    assert(FindnextDay(sun)==mon);
    return 0;
}

day FindnextDay(day(d)){
    day next_day;
    switch (d)
    {
    case sun:
        next_day = mon;
        break;
    
    case mon:
        next_day = tue;
        break;
    
    case tue:
        next_day = wed;
        break;
    
    case wed:
        next_day = thu;
        break;
    
    case thu:
        next_day = fri;
        break;

    case fri:
        next_day = sat;
        break;

    case sat:
        next_day = sun;
        break;
    default:
        printf("I was't expecting that!\n");
    }

    return next_day;
}


