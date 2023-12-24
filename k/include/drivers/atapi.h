#pragma once

#include <k/types.h>

void read_block(size_t lba, u16 *buffer, size_t size);
void init_atapi();
