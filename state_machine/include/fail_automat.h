#pragma once

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>

#include "trie.h"
#include "queue.h"
#include "state.h"

void compute_fail_function(dfsm_t* trie);