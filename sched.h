#ifndef __SCHED_H__
#define __SCHED_H__

#include "stdint.h"
#include "screen.h"
#include "tss.h"

void sched_init();

int16_t sched_nextTask();

#endif	/* !__SCHED_H__ */
