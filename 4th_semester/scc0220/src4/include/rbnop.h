#ifndef _RBNOP_H_
#define _RBNOP_H_

#include "rbn.h"

int cmpRealyBigNumbers(t_rbn *, t_rbn *);

t_rbn *sumRealyBigNumbers(t_rbn *,t_rbn *);
t_rbn *subRealyBigNumbers(t_rbn *,t_rbn *);
t_rbn *multRealyBigNumbers(t_rbn *,t_rbn *);
t_rbn *divRealyBigNumbers(t_rbn *,t_rbn *);

#endif