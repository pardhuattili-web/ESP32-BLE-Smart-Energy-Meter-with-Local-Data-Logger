#include "acquisition.h"
#include <math.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static uint32_t sequence_number;

void acquisition_init(void) { sequence_number = 0U; }

int acquisition_get_block(energy_sample_block_t *block)
{
    if (block == NULL) return -1;

    block->count = ENERGY_SAMPLE_BLOCK;
    block->sequence = ++sequence_number;
    block->power_factor = 0.92f;

    /* Safe deterministic simulation; replace with isolated ADC/sensor path. */
    const float base_v = 12.0f;
    const float base_i = 1.5f;

    for (size_t n = 0U; n < block->count; ++n) {
        const float phase = 2.0f * 3.14159265f * (float)n / (float)block->count;
        block->voltage[n] = base_v * 0.7071f * sinf(phase);
        block->current[n] = base_i * 0.7071f * sinf(phase - 0.22f);
    }

    vTaskDelay(pdMS_TO_TICKS(10));
    return 0;
}
