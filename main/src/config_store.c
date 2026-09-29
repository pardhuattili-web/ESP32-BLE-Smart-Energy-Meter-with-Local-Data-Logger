#include "config_store.h"
#include "nvs.h"
#include "nvs_flash.h"

static const char *NVS_NAMESPACE = "energy";

void config_store_defaults(energy_config_t *config)
{
    if (config == NULL) return;
    config->sample_period_ms = 1000U;
    config->log_period_ms = 5000U;
    config->limits.voltage_limit_v = 14.0f;
    config->limits.current_limit_a = 3.0f;
}

int config_store_save(const energy_config_t *config)
{
    if (config == NULL) return -1;

    nvs_handle_t handle;
    esp_err_t err = nvs_open(NVS_NAMESPACE, NVS_READWRITE, &handle);
    if (err != ESP_OK) return (int)err;

    err = nvs_set_blob(handle, "cfg", config, sizeof(*config));
    if (err == ESP_OK) err = nvs_commit(handle);
    nvs_close(handle);
    return (int)err;
}

int config_store_load(energy_config_t *config)
{
    if (config == NULL) return -1;

    nvs_handle_t handle;
    esp_err_t err = nvs_open(NVS_NAMESPACE, NVS_READONLY, &handle);
    if (err != ESP_OK) return (int)err;

    size_t size = sizeof(*config);
    err = nvs_get_blob(handle, "cfg", config, &size);
    nvs_close(handle);
    return (err == ESP_OK && size == sizeof(*config)) ? 0 : (int)err;
}
