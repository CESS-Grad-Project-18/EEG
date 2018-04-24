#include <stdio.h>
#include "Std_Types.h"

void Det_ReportError(int a, ...){
    printf("%s @ %d", __func__, a);
}

