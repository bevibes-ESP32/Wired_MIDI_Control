#include <Arduino.h>
#include <MIDI.h>

#include "midi_console.h"

constexpr uint8_t MIDI_RX_PIN = 18;
constexpr uint8_t MIDI_TX_PIN = 17;
constexpr uint32_t MIDI_BAUD_RATE = 31250;

HardwareSerial MidiUart(1);
MIDI_CREATE_INSTANCE(HardwareSerial, MidiUart, MIDI);

void sendControlChange(uint8_t channel, uint8_t cc, uint8_t value)
{
    MIDI.sendControlChange(cc, value, channel);
}

void sendProgramChange(uint8_t channel, uint8_t program)
{
    MIDI.sendProgramChange(program, channel);
}

midi_console::Console midiConsole(sendControlChange, sendProgramChange);

void onControlChange(byte channel, byte cc, byte value)
{
    midiConsole.onControlChange(channel, cc, value);
}

void onProgramChange(byte channel, byte program)
{
    midiConsole.onProgramChange(channel, program);
}

void setup()
{
    Serial.begin(115200);

    MIDI.setHandleControlChange(onControlChange);
    MIDI.setHandleProgramChange(onProgramChange);
    MIDI.begin(MIDI_CHANNEL_OMNI);
    MIDI.turnThruOff();

    // MIDI.begin() initializes the UART with default pins; restore the requested GPIO mapping.
    MidiUart.begin(MIDI_BAUD_RATE, SERIAL_8N1, MIDI_RX_PIN, MIDI_TX_PIN);

    midiConsole.begin("Wired MIDI console ready (RX GPIO18, TX GPIO17, 31250 baud).");
}

void loop()
{
    MIDI.read();
    midiConsole.poll();
}
