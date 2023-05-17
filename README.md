# AV_MUX_v3

Code to control an Arduino Nano that commands a MAX4360 8X4 video crosspoint switch for 8X4 analog video (AV) multiplexing applications

### Communication Protocols
* Nano <-> User : Arduino Serial Monitor (capabilties for UART as well)
* Nano <-> MAX4360 : 16 bit serial command

### Description of Operation
There are four commands that the user can execute to control the MAX4360. Each command has a corresponding integer code that the user can input through the Arduino Serial Monitor or through UART that will execute the command.

| Command | Code | Description |
|:---:|:---:|:---:|
| `configChannelInputs(A, B, C, D)` | ABCD | Connects respective output buffers to the specified channel inputs
| `resetAllBuffers()` | -1 | Connects the inputs for all output buffers to GND
| `enableAllBuffers()` | -2 | Turns on all output buffers and connects their inputs to GND
| `disableAllBuffers()` | -3 | Turns off all output buffers and sets them to a high impedance state

### configChannelInputs(A, B, C, D)

The user code input for channel selection is described in the table below.

| A | B | C | D |
|---|---|---|---|
|Channel # for output 1|Channel # for output 2|Channel # for output 3|Channel # for output 4|

### Wiring

| Signal | Nano Pin | MAX4360 Pin |
|:--:|:--:|:--:|
| SDI | 9 | 2 |
| SCLK | 2 | 20 |
| SS/CE | 8 | 27 |
| LATCH | 7 | 21 |
