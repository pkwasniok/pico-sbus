# Pico SBUS

SUBS library for Raspberry Pi Pico SDK.

## Installation

1. Clone this repository into your project (e.g. into `lib/pico_sbus` subdirectory).

```sh
$ git submodule add https://github.com/pkwasniok/pico-sbus lib/pico_sbus
```

2. Add following lines to the `CMakeLists.txt` file.

```cmake
...
add_subdirectory(lib/pico_sbus)
...
target_link_libraries([target] pico_sbus)
...
```

## Resources

 - [bolderflight/sbus](https://github.com/bolderflight/sbus) - Arduino SBUS library and great SBUS protocol overview.

