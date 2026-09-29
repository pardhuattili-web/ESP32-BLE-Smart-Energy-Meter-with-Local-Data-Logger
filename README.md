# ESP32 BLE Smart Energy Meter with Local Data Logger

An ESP32-based low-voltage energy-monitoring node that acquires voltage/current samples, computes electrical measurements, exposes live telemetry over Bluetooth Low Energy, and stores normalized records locally.

> **Safety:** Educational reference implementation. Use only isolated, current-limited, low-voltage sources or certified isolated measurement modules. **Never connect the ESP32 ADC directly to mains voltage.**

## Status

**Firmware:** modular ESP-IDF reference scaffold  
**Default acquisition:** deterministic simulation for safe bring-up  
**Physical calibration:** hardware-dependent; not claimed as validated

## Architecture

```
Isolated LV Source
       |
   ADC/Sensor IF
       |
 Acquisition Task
       |
 Measurement Engine ----> Fault Monitor
       |                       |
       +----> BLE GATT         +----> Event state
       |
       +----> Local Logger
              |
          NVS/Flash/FS
```

## Features

- RMS voltage/current calculation
- Apparent and active power estimation
- Accumulated energy in Wh
- Over-voltage / over-current alarms
- BLE telemetry and configuration interface
- Persistent configuration through NVS
- Local logging abstraction
- FreeRTOS task separation
- Sensor simulation for development
- UART diagnostics
- Unit-testable measurement engine

## Measurement model

For N samples:

`Vrms = sqrt((1/N) * sum(v[i]^2))`

`Irms = sqrt((1/N) * sum(i[i]^2))`

`S = Vrms * Irms`

For a known/estimated power factor:

`P = S * PF`

For interval `dt`:

`Energy_Wh += P * dt_hours`

The reference implementation keeps power factor explicit instead of claiming phase-accurate real-power measurement from a single ADC channel.

## BLE

See [docs/ble_protocol.md](docs/ble_protocol.md).

Telemetry:
- voltage RMS
- current RMS
- apparent power
- active power
- power factor
- accumulated energy
- alarm flags
- sample counter

Configuration:
- sample period
- logging period
- voltage/current limits
- energy reset

## Repository layout

```
main/
  app_main.c
  include/
    acquisition.h
    ble_service.h
    config_store.h
    fault_monitor.h
    logger.h
    measurement.h
  src/
    acquisition.c
    ble_service.c
    config_store.c
    fault_monitor.c
    logger.c
    measurement.c
docs/
  architecture.md
  ble_protocol.md
  measurement_model.md
  test_plan.md
test/
  measurement_test.c
```

## Build

Requires ESP-IDF 5.x.

```bash
idf.py set-target esp32
idf.py build
idf.py flash monitor
```

The acquisition implementation currently generates safe simulated samples. Replace that layer with the selected isolated measurement hardware after the software pipeline is verified.

## Example telemetry

```text
V=12.00 V
I=1.50 A
S=18.00 VA
PF=0.92
P=16.56 W
E=0.0046 Wh
ALARMS=0x00
```

## Engineering notes

Real deployments require sensor transfer-function characterization, ADC reference/error analysis, anti-alias filtering, synchronized voltage/current sampling, calibration, isolation review, and independent electrical safety validation.

## Tests

See [docs/test_plan.md](docs/test_plan.md) and [test/measurement_test.c](test/measurement_test.c).

## License

MIT
