#include "config_store.h"
#include "nvs.h"
#define NS "energy"
void config_store_defaults(energy_config_t*c){if(!c)return;c->sample_period_ms=1000;c->log_period_ms=5000;c->limits.voltage_limit_v=14.0f;c->limits.current_limit_a=3.0f;}
int config_store_save(const energy_config_t*c){if(!c)return-1;nvs_handle_t h;esp_err_t e=nvs_open(NS,NVS_READWRITE,&h);if(e!=ESP_OK)return e;e=nvs_set_blob(h,"cfg",c,sizeof(*c));if(e==ESP_OK)e=nvs_commit(h);nvs_close(h);return e;}
int config_store_load(energy_config_t*c){if(!c)return-1;nvs_handle_t h;esp_err_t e=nvs_open(NS,NVS_READONLY,&h);if(e!=ESP_OK)return e;size_t s=sizeof(*c);e=nvs_get_blob(h,"cfg",c,&s);nvs_close(h);return(e==ESP_OK&&s==sizeof(*c))?0:e;}