#ifndef FREELIST_H
#define FREELIST_H

#include "page_entries.h"
#include "queue.h"
#include "queue_DLL.h"
#include "t_map.h"
#include <stdio.h>
#include <stdlib.h>

int track_free(Queue *freelist, DLL_Queue *refQueue, Page_ets **invrt_Table,
               PageTable *tree, int PID, int size);
#endif