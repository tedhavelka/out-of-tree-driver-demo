# Out-Of-Tree Driver Demo

Small Zephyr RTOS app to exercise an out-of-tree driver.  This work licensed
under MIT licence.

This demo as of 2026-02-06 specifies a Zephyr out-of-tree driver for Rohm
company's MEMs based KX132-1211 accelerometer.  Please note:

**This driver is not complete.  It is mostly a stub project with most KX132
registers and functionality not yet implemented.  Work is underway on this code
base but THIS CODE IS NOT INTENDED FOR ANY KIND OF PRODUCTION USE.**

## Driver Functionality (2026 Q1)

The KX132 driver referenced and called by this demo currently:

(1) queries and shows manufacturer's four byte id, spells out "Kion"

(2) reads immediate x, y, z acceleration values in their raw A-to-D counts

## Tested Hardware

The demo app has been compiled for and flashed to an RPi Pico board.  The
board is wired . . .

```
                                +-----+
                                |FTDI |
 3V3                    3V3     +-----+                     3V3
  ^                      ^        |||                        ^
  |  +---------------+   |        |||  +----------------+    |
  |  |     KX132     |   |        |||  |    RPi Pico    |    |
  +--| ADR       GND |---|----+   ||+--| TX0            |    |
     |           3V3 |---+    |   |+---| RX0            |    |
     |          SDA0 |-----+  V   +----| GND        GND |-+  |
     |          SCL0 |---+ |           |                | |  |
     |               |   | |           |            3V3 |----+
     +---------------+   | +-----------| SDA0           | |
                         +-------------| SCL0           | V
                                       |                |
                                       |                |
                                       |                |
                                       |                |
                                       +----------------+
```



## To Configure A Build Environment

There are a couple of general ways to configure a Zephyr build environment,
here referred to as a `zephyr workspace`.  One way involves a localhost
installation of Zephyr RTOS source tree and a corresponding Zephyr toolchain,
also often known as a `Zephyr SDK` release.  Another way involves the use of
Docker container software, which is installed and then called to create a
virtual host image which may be executed to run as a virtual host, comprised
of its own operating system and the developer's choice of development tools
Zephyr and otherwise.

### Localhost Workspace Configuration

To install Zephyr sources and a bunch of mostly Python based build and support
scripts, see https://docs.zephyrproject.org/latest/develop/getting_started/index.html.

This out-of-tree driver demo has been built against Zephyr 4.3.0, the current
release of Zephyr as of 2026 Q1.  When a Zephry workspace configured with this
release is already present, this tiny project may be cloned into that workspace
and compiled there with no additional install or set up.

In this scenario the local workspace may likely look something like:

```
                   workspace
                      |
       +------------+-+-----------+
       |            |             |
   project_1     project_2      zephyr   <-- Zephyr 4.3.0 source tree

```

This project may be cloned into the `workspace` directory, resulting in:

```
                   workspace
                      |
       +------------+-+--------------------+-----------------+
       |            |                      |                 |
   project_1     project_2      out-of-tree-driver-demo    zephyr

```

Note that with this arrangement the driver demo's manifest file will not affect
which release of Zephyr RTOS is downloaded during `west update` operations.
The project's manifest file will be ignored in favor of what pre-existing
`west` initalized manifest there may be.

For developers needing to build this project against other releases of Zephyr
the active manifest file in the given workspace must be adjusted.  Alternately
`west init -l out-of-tree-driver-demo` may be called to set this project's
manifest as the ruling manifest in the local workspace.

There may be only one ruling manifest in a given Zephyr workspace.

### Container Based Builds

This project includes a dot devcontainer directory and files, but they're not
yet fully functional.

These devcontainer scripts have worked successfully on two localhosts, but not
following a `git clone` of this project onto a host with no pre-existing
workspace.  They are present in the midst of development as they're needed in
order to be exercised and issues debugged.

A more experienced Docker and Devcontainer developer may be able to make use of
these as they are today.
