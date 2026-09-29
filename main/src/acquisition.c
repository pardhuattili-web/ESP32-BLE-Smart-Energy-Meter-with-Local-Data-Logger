#include "acquisition.h"
#include <math.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
static uint32_t seq;
void acquisition_init(void){seq=0;}
int acquisition_get_block(energy_sample_block_t*b){if(!b)return-1;b->count=ENERGY_SAMPLE_BLOCK;b->sequence=++seq;b->power_factor=.92f;for(size_t n=0;n<b->count;n++){float ph=2.0f*3.14159265f*n/(float)b->count;b->voltage[n]=12.0f*.7071f*sinf(ph);b->current[n]=1.5f*.7071f*sinf(ph-.22f);}vTaskDelay(pdMS_TO_TICKS(10));return 0;}