#pragma once
#include <stddef.h>
#include <stdint.h>
#define ENERGY_SAMPLE_BLOCK 64U
typedef struct { float voltage[ENERGY_SAMPLE_BLOCK]; float current[ENERGY_SAMPLE_BLOCK]; size_t count; uint32_t sequence; float power_factor; } energy_sample_block_t;
void acquisition_init(void); int acquisition_get_block(energy_sample_block_t*);