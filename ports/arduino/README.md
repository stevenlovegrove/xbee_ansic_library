Platform Support: ARDUINO                               {#platform_posix}
=======================

Overview
--------
This port targets [ARDUINO] platform with Arduino IDE or PlatformIO toolchain.

Building with PlatformIO
-------------------
Given an existing PlatformIO project, open a terminal within your project folder.
```
cd lib
git clone https://github.com/stevenlovegrove/xbee_ansic_library.git
```

The included root `library.json` file will be interpretted by the PlatformIO runtime
such that it is automatically built when referenced from your code. Include as necessary
with `#include <xbee/device.h>`, `#include <zigbee/zcl.h>` etc.

Building with Arduino IDE
-------------------
Not yet tested.
