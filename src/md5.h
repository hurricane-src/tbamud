#pragma once
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

uint64_t md5_sum(const void* buffer, size_t size);
uint64_t md5_sum_string(const char* text);
