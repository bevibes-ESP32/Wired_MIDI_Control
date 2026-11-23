# Wired_MIDI_Control

Freenove ESP32-S3 wired MIDI console for testing ToneXController commands.

## MIDI wiring

- MIDI RX: GPIO 18
- MIDI TX: GPIO 17
- UART MIDI: 31250 baud, 3.3 V logic
- Connect the Freenove ground to the other device's ground.

Connect GPIO 17 (TX) to the receiving device's MIDI RX and GPIO 18 (RX) to its MIDI TX.

## Serial console

Open the PlatformIO monitor on the CH343 COM port at 115200 baud. The console uses UART0; MIDI uses UART1. Commands are processed only when Enter is pressed.

```text
CC 12 15
PC 17
gain 10
treble 8.5
preset 12
preset slot 2
bank +
bank -
help params
```

`PC` values are zero-based; `preset` values are one-based and send Program Change. `preset slot 2` selects slot 2 in the currently selected bank through CC 105. `bank +`/`bank -` change banks. Parameter aliases use ToneXController units and are range-checked. The console reports received and transmitted CC/PC messages as `[Rx]` and `[Tx]`.
