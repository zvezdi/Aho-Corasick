#pragma once

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>

#include "dfsm.h"
#include "queue.h"
#include "state.h"

dfsm_t* build_trie(char* path_to_dictionary);
