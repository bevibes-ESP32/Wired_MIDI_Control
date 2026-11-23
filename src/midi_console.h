#pragma once

#include <Arduino.h>
#include <ctype.h>
#include <errno.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

namespace midi_console
{

enum ValueKind
{
    VALUE_RANGE,
    VALUE_SWITCH,
    VALUE_SELECT,
    VALUE_ACTION
};

struct ControlSpec
{
    uint8_t cc;
    const char* name;
    const char* alias;
    float minimum;
    float maximum;
    ValueKind kind;
    uint8_t onValue;
    uint8_t toggleOn64;
};

#define RANGE(cc, name, alias, minimum, maximum) \
    { cc, name, alias, minimum, maximum, VALUE_RANGE, 127, 0 }
#define SWITCH(cc, name, alias, minimum, maximum, on, toggle) \
    { cc, name, alias, minimum, maximum, VALUE_SWITCH, on, toggle }
#define SELECT(cc, name, alias, minimum, maximum) \
    { cc, name, alias, minimum, maximum, VALUE_SELECT, 127, 0 }
#define ACTION(cc, name, alias, maximum) \
    { cc, name, alias, 0, maximum, VALUE_ACTION, 127, 0 }

static const ControlSpec ControlSpecs[] =
{
    SWITCH(1, "DELAY POSITION", "delayposition", 0, 1, 127, 1),
    SWITCH(2, "DELAY POWER", "delaypower", 0, 1, 127, 1),
    SELECT(3, "DELAY TYPE", "delaytype", 0, 1),
    SWITCH(4, "DELAY DIGITAL SYNC", "delaydigitalsync", 0, 1, 127, 1),
    RANGE(5, "DELAY DIGITAL TIME/TIMESIGN", "delaydigitaltime", 0, 1000),
    RANGE(6, "DELAY DIGITAL FEEDBACK", "delaydigitalfeedback", 0, 100),
    SWITCH(7, "DELAY DIGITAL MODE", "delaydigitalmode", 0, 1, 64, 0),
    RANGE(8, "DELAY DIGITAL MIX", "delaydigitalmix", 0, 100),
    SWITCH(9, "TUNER", "tuner", 0, 1, 127, 0),
    ACTION(10, "TAP TEMPO", "", 127),
    SWITCH(12, "PRESET ON/OFF", "presetonoff", 0, 1, 127, 1),
    SWITCH(13, "GATE POSITION", "gateposition", 0, 1, 127, 1),
    SWITCH(14, "GATE POWER", "gatepower", 0, 1, 127, 1),
    RANGE(15, "GATE THRESHOLD", "gatethreshold", -100, 0),
    RANGE(16, "GATE RELEASE", "gaterelease", 5, 500),
    RANGE(17, "GATE DEPTH", "gatedepth", -100, -20),
    SWITCH(18, "COMP POWER", "comppower", 0, 1, 127, 1),
    RANGE(19, "COMP THRESHOLD", "compthreshold", -40, 0),
    RANGE(20, "COMP GAIN", "compgain", -30, 10),
    RANGE(21, "COMP ATTACK", "compattack", 1, 51),
    SWITCH(22, "COMP POSITION", "compposition", 0, 1, 127, 1),
    RANGE(23, "BASS", "bass", 0, 10),
    RANGE(24, "BASS HZ", "basshz", 75, 600),
    RANGE(25, "MID", "mid", 0, 10),
    RANGE(26, "MID Q", "midq", 0.2f, 3.0f),
    RANGE(27, "MID HZ", "midhz", 150, 5000),
    RANGE(28, "TREBLE", "treble", 0, 10),
    RANGE(29, "TREBLE HZ", "treblehz", 1000, 4000),
    SWITCH(30, "EQ POSITION", "eqposition", 0, 1, 127, 0),
    SWITCH(31, "MOD POSITION", "modposition", 0, 1, 127, 1),
    SWITCH(32, "MOD POWER", "modpower", 0, 1, 127, 1),
    SELECT(33, "MOD TYPE", "modtype", 0, 4),
    SWITCH(34, "MOD CHORUS SYNC", "modchorussync", 0, 1, 127, 1),
    RANGE(35, "MOD CHORUS RATE", "modchorusrate", 0.1f, 10),
    RANGE(36, "MOD CHORUS DEPTH", "modchorusdepth", 0, 100),
    RANGE(37, "MOD CHORUS LEVEL", "modchoruslevel", 0, 10),
    SWITCH(38, "MOD TREMOLO SYNC", "modtremolosync", 0, 1, 127, 1),
    RANGE(39, "MOD TREMOLO RATE", "modtremolorate", 0.1f, 10),
    RANGE(40, "MOD TREMOLO SHAPE", "modtremoloshape", 0, 10),
    RANGE(41, "MOD TREMOLO SPREAD", "modtremolospread", 0, 100),
    RANGE(42, "MOD TREMOLO LEVEL", "modtremololevel", 0, 10),
    SWITCH(43, "MOD PHASER SYNC", "modphasersync", 0, 1, 127, 1),
    RANGE(44, "MOD PHASER RATE", "modphaserrate", 0.1f, 10),
    RANGE(45, "MOD PHASER DEPTH", "modphaserdepth", 0, 100),
    RANGE(46, "MOD PHASER LEVEL", "modphaserlevel", 0, 10),
    SWITCH(47, "MOD FLANGER SYNC", "modflangersync", 0, 1, 127, 1),
    RANGE(48, "MOD FLANGER RATE", "modflangerrate", 0.1f, 10),
    RANGE(49, "MOD FLANGER DEPTH", "modflangerdepth", 0, 100),
    RANGE(50, "MOD FLANGER FEEDBACK", "modflangerfeedback", 0, 100),
    RANGE(51, "MOD FLANGER LEVEL", "modflangerlevel", 0, 10),
    SWITCH(52, "MOD ROTARY SYNC", "modrotarysync", 0, 1, 127, 1),
    RANGE(53, "MOD ROTARY SPEED", "modrotaryspeed", 0, 400),
    RANGE(54, "MOD ROTARY RADIUS", "modrotaryradius", 0, 300),
    RANGE(55, "MOD ROTARY SPREAD", "modrotaryspread", 0, 100),
    RANGE(56, "MOD ROTARY LEVEL", "modrotarylevel", 0, 10),
    RANGE(59, "REVERB SPRING 1 TIME", "reverbspring1time", 0, 10),
    RANGE(60, "REVERB SPRING 1 PREDELAY", "reverbspring1predelay", 0, 500),
    RANGE(61, "REVERB SPRING 1 COLOR", "reverbspring1color", -10, 10),
    RANGE(62, "REVERB SPRING 1 MIX", "reverbspring1mix", 0, 100),
    RANGE(63, "REVERB SPRING 2 TIME", "reverbspring2time", 0, 10),
    RANGE(64, "REVERB SPRING 2 PREDELAY", "reverbspring2predelay", 0, 500),
    RANGE(65, "REVERB SPRING 2 COLOR", "reverbspring2color", -10, 10),
    RANGE(66, "REVERB SPRING 2 MIX", "reverbspring2mix", 0, 100),
    RANGE(67, "REVERB SPRING 3 TIME", "reverbspring3time", 0, 10),
    RANGE(68, "REVERB SPRING 3 PREDELAY", "reverbspring3predelay", 0, 500),
    RANGE(69, "REVERB SPRING 3 COLOR", "reverbspring3color", -10, 10),
    RANGE(70, "REVERB SPRING 3 MIX", "reverbspring3mix", 0, 100),
    RANGE(71, "REVERB ROOM TIME", "reverbroomtime", 0, 10),
    RANGE(72, "REVERB ROOM PREDELAY", "reverbroompredelay", 0, 500),
    RANGE(73, "REVERB ROOM COLOR", "reverbroomcolor", -10, 10),
    RANGE(74, "REVERB ROOM MIX", "reverbroommix", 0, 100),
    SWITCH(75, "REVERB POWER", "reverbpower", 0, 1, 127, 1),
    RANGE(76, "REVERB PLATE TIME", "reverbplatetime", 0, 10),
    RANGE(77, "REVERB PLATE PREDELAY", "reverbplatepredelay", 0, 500),
    RANGE(78, "REVERB PLATE COLOR", "reverbplatecolor", -10, 10),
    RANGE(79, "REVERB PLATE MIX", "reverbplatemix", 0, 100),
    RANGE(80, "REVERB SPRING 4 TIME", "reverbspring4time", 0, 10),
    RANGE(81, "REVERB SPRING 4 PREDELAY", "reverbspring4predelay", 0, 500),
    RANGE(82, "REVERB SPRING 4 COLOR", "reverbspring4color", -10, 10),
    RANGE(83, "REVERB SPRING 4 MIX", "reverbspring4mix", 0, 100),
    SWITCH(84, "REVERB POSITION", "reverbposition", 0, 1, 127, 1),
    SELECT(85, "REVERB TYPE", "reverbtype", 0, 5),
    ACTION(86, "PRESET DOWN", "", 127),
    ACTION(87, "PRESET UP", "", 127),
    ACTION(89, "A/B BANK DOWN", "", 127),
    ACTION(90, "A/B BANK UP", "", 127),
    RANGE(88, "BPM", "bpm", 40, 240),
    SWITCH(91, "DELAY TAPE SYNC", "delaytapesync", 0, 1, 127, 1),
    RANGE(92, "DELAY TAPE TIME/TIMESIGN", "delaytapetime", 0, 1000),
    RANGE(93, "DELAY TAPE FEEDBACK", "delaytapefeedback", 0, 100),
    SWITCH(94, "DELAY TAPE MODE", "delaytapemode", 0, 1, 64, 0),
    RANGE(95, "DELAY TAPE MIX", "delaytapemix", 0, 100),
    ACTION(99, "BPM CC99", "", 127),
    ACTION(100, "BPM CC100", "", 127),
    RANGE(102, "GAIN", "gain", 0, 10),
    RANGE(103, "VOLUME", "volume", 0, 10),
    RANGE(104, "MODEL MIX", "modelmix", 0, 100),
    RANGE(106, "PRESENCE", "presence", 0, 10),
    RANGE(107, "DEPTH", "depth", 0, 10),
    RANGE(108, "VIR RESO", "virreso", 0, 10),
    SELECT(109, "VIR MIC 1", "virmic1", 0, 2),
    RANGE(110, "VIR MIC 1 X", "virmic1x", 0, 10),
    RANGE(111, "VIR MIC 1 Z", "virmic1z", 0, 10),
    SELECT(112, "VIR MIC 2", "virmic2", 0, 2),
    RANGE(113, "VIR MIC 2 X", "virmic2x", 0, 2),
    RANGE(114, "VIR MIC 2 Z", "virmic2z", 0, 10),
    RANGE(115, "VIR BLEND", "virblend", -100, 100),
    RANGE(116, "INPUT TRIM", "inputtrim", -15, 15),
    SWITCH(117, "CABSIM BYPASS", "cabsimbypass", 0, 1, 127, 1),
    SWITCH(118, "TEMPO SOURCE", "temposource", 0, 1, 127, 1),
    RANGE(119, "TUNING REFERENCE", "tuningreference", 415, 465),
    ACTION(120, "LOAD SLOT A", "", 127),
    ACTION(121, "LOAD SLOT B", "", 127),
    RANGE(122, "GLOBAL VOLUME", "globalvolume", -40, 3),
    ACTION(127, "SET PRESET", "", 127),
    ACTION(105, "MIDI FOOTSWITCH", "", 23)
};

#undef RANGE
#undef SWITCH
#undef SELECT
#undef ACTION

typedef void (*SendCc)(uint8_t channel, uint8_t cc, uint8_t value);
typedef void (*SendPc)(uint8_t channel, uint8_t program);

class Console
{
public:
    Console(SendCc sendCc, SendPc sendPc)
        : sendCc_(sendCc), sendPc_(sendPc), lineLength_(0), discardingLine_(false), ignoreNextLf_(false)
    {
    }

    void begin(const char* transport)
    {
        Serial.println();
        Serial.println(transport);
        Serial.println("Type HELP for commands. MIDI TX channel: 1.");
        printPrompt();
    }

    void poll()
    {
        while (Serial.available() > 0)
        {
            const char ch = static_cast<char>(Serial.read());
            if (ch == '\r')
            {
                finishLine();
                ignoreNextLf_ = true;
                continue;
            }
            if (ch == '\n')
            {
                if (ignoreNextLf_)
                {
                    ignoreNextLf_ = false;
                }
                else
                {
                    finishLine();
                }
                continue;
            }
            ignoreNextLf_ = false;
            if ((ch == '\b' || ch == 127) && lineLength_ > 0)
            {
                line_[--lineLength_] = '\0';
                continue;
            }
            if (!discardingLine_)
            {
                if (lineLength_ < sizeof(line_) - 1)
                {
                    line_[lineLength_++] = ch;
                }
                else
                {
                    discardingLine_ = true;
                }
            }
        }
    }

    void onControlChange(uint8_t, uint8_t cc, uint8_t value)
    {
        char valueText[32];
        const ControlSpec* spec = findByCc(cc);
        if (spec == nullptr)
        {
            Serial.printf("[Rx] CC %u %u \"UNMAPPED\" \"%u\"\n", cc, value, value);
            return;
        }

        formatValue(*spec, value, valueText, sizeof(valueText));
        char nameText[32];
        const char* name = formatName(*spec, value, nameText, sizeof(nameText));
        Serial.printf("[Rx] CC %u %u \"%s\" \"%s\"\n", cc, value, name, valueText);
    }

    void onProgramChange(uint8_t, uint8_t program)
    {
        Serial.printf("[Rx] PC %u preset %u\n", program, program + 1);
    }

private:
    void finishLine()
    {
        if (discardingLine_)
        {
            Serial.println("[Error] Command too long; maximum is 95 characters.");
        }
        else
        {
            line_[lineLength_] = '\0';
            executeLine(line_);
        }
        lineLength_ = 0;
        discardingLine_ = false;
        printPrompt();
    }

    static const ControlSpec* findByCc(uint8_t cc)
    {
        for (size_t i = 0; i < sizeof(ControlSpecs) / sizeof(ControlSpecs[0]); ++i)
        {
            if (ControlSpecs[i].cc == cc)
            {
                return &ControlSpecs[i];
            }
        }
        return nullptr;
    }

    static bool normalize(const char* source, char* destination, size_t size)
    {
        size_t used = 0;
        for (; *source != '\0'; ++source)
        {
            const unsigned char ch = static_cast<unsigned char>(*source);
            if (isalnum(ch))
            {
                if (used + 1 >= size)
                {
                    return false;
                }
                destination[used++] = static_cast<char>(tolower(ch));
            }
        }
        destination[used] = '\0';
        return used != 0;
    }

    static bool parseInteger(const char* text, long& value)
    {
        char* end = nullptr;
        errno = 0;
        const long parsed = strtol(text, &end, 10);
        if ((end == text) || (*end != '\0') || (errno == ERANGE))
        {
            return false;
        }
        value = parsed;
        return true;
    }

    static bool parseFloat(const char* text, float& value)
    {
        char* end = nullptr;
        errno = 0;
        const float parsed = strtof(text, &end);
        if ((end == text) || (*end != '\0') || (errno == ERANGE) || !isfinite(parsed))
        {
            return false;
        }
        value = parsed;
        return true;
    }

    static const ControlSpec* findByAlias(const char* alias)
    {
        char normalized[48];
        if (!normalize(alias, normalized, sizeof(normalized)))
        {
            return nullptr;
        }
        for (size_t i = 0; i < sizeof(ControlSpecs) / sizeof(ControlSpecs[0]); ++i)
        {
            if ((ControlSpecs[i].alias[0] != '\0') && (strcmp(ControlSpecs[i].alias, normalized) == 0))
            {
                return &ControlSpecs[i];
            }
        }
        return nullptr;
    }

    static bool isCommand(const char* token, const char* command)
    {
        char normalizedToken[32];
        char normalizedCommand[32];
        return normalize(token, normalizedToken, sizeof(normalizedToken)) &&
               normalize(command, normalizedCommand, sizeof(normalizedCommand)) &&
               strcmp(normalizedToken, normalizedCommand) == 0;
    }

    static const char* formatName(const ControlSpec& spec, uint8_t value, char* output, size_t size)
    {
        if (spec.cc != 105)
        {
            return spec.name;
        }
        if (value == 0)
        {
            snprintf(output, size, "BANK -");
        }
        else if (value == 1)
        {
            snprintf(output, size, "BANK +");
        }
        else if (value <= 13)
        {
            snprintf(output, size, "PRESET SLOT %u", value - 1);
        }
        else if (value == 14)
        {
            snprintf(output, size, "PRESET DOWN");
        }
        else if (value == 15)
        {
            snprintf(output, size, "PRESET UP");
        }
        else if (value <= 23)
        {
            snprintf(output, size, "FX%u", value - 15);
        }
        else
        {
            return spec.name;
        }
        return output;
    }

    static void formatValue(const ControlSpec& spec, uint8_t value, char* output, size_t size)
    {
        if (spec.cc == 105)
        {
            if (value == 0)
            {
                snprintf(output, size, "bank down");
            }
            else if (value == 1)
            {
                snprintf(output, size, "bank up");
            }
            else if (value <= 13)
            {
                snprintf(output, size, "preset slot %u", value - 1);
            }
            else if (value == 14)
            {
                snprintf(output, size, "preset down");
            }
            else if (value == 15)
            {
                snprintf(output, size, "preset up");
            }
            else if (value <= 23)
            {
                snprintf(output, size, "FX%u", value - 15);
            }
            else
            {
                snprintf(output, size, "unsupported");
            }
            return;
        }

        switch (spec.cc)
        {
            case 10:
                snprintf(output, size, "trigger");
                return;
            case 86:
                snprintf(output, size, "preset down");
                return;
            case 87:
                snprintf(output, size, "preset up");
                return;
            case 89:
                snprintf(output, size, "A/B bank down");
                return;
            case 90:
                snprintf(output, size, "A/B bank up");
                return;
            case 99:
                snprintf(output, size, "%.3g", (value < 40) ? 40.0f : (float)value);
                return;
            case 100:
                snprintf(output, size, "%.3g", (float)value + 100.0f);
                return;
            case 120:
                snprintf(output, size, "slot A preset %u", value + 1);
                return;
            case 121:
                snprintf(output, size, "slot B preset %u", value + 1);
                return;
            case 127:
                snprintf(output, size, "preset %u", value + 1);
                return;
            default:
                break;
        }

        if (spec.kind == VALUE_RANGE)
        {
            const float actual = spec.minimum + ((float)value / 127.0f) * (spec.maximum - spec.minimum);
            snprintf(output, size, "%.4g", actual);
        }
        else if (spec.kind == VALUE_SELECT)
        {
            float actual = value;
            if (actual > spec.maximum)
            {
                actual = spec.maximum;
            }
            snprintf(output, size, "%.4g", actual);
        }
        else if (spec.kind == VALUE_SWITCH)
        {
            if (spec.toggleOn64 && value == 64)
            {
                snprintf(output, size, "toggle");
            }
            else
            {
                snprintf(output, size, "%u", (value == spec.onValue) ? 1 : 0);
            }
        }
        else
        {
            snprintf(output, size, "action");
        }
    }

    static void formatNumber(float value, char* output, size_t size)
    {
        snprintf(output, size, "%.4g", value);
    }

    void transmitCc(uint8_t cc, uint8_t value)
    {
        const ControlSpec* spec = findByCc(cc);
        if (spec == nullptr)
        {
            Serial.printf("[Error] CC %u is not mapped by ToneXController. Use HELP PARAMS.\n", cc);
            return;
        }
        if ((cc == 105) && (value > 23))
        {
            Serial.println("[Error] CC 105 values are 0..23. Use HELP PARAMS.");
            return;
        }
        if ((spec->kind == VALUE_SELECT) && ((float)value > spec->maximum))
        {
            Serial.printf("[Error] %s selection range is %.0f..%.0f. Use HELP PARAMS.\n",
                          spec->name, spec->minimum, spec->maximum);
            return;
        }

        sendCc_(1, cc, value);
        char valueText[32];
        formatValue(*spec, value, valueText, sizeof(valueText));
        char nameText[32];
        const char* name = formatName(*spec, value, nameText, sizeof(nameText));
        Serial.printf("[Tx] CC %u %u \"%s\" \"%s\"\n", cc, value, name, valueText);
    }

    void transmitPc(uint8_t program)
    {
        sendPc_(1, program);
        Serial.printf("[Tx] PC %u preset %u\n", program, program + 1);
    }

    void transmitAlias(const ControlSpec& spec, float requested)
    {
        if ((requested < spec.minimum) || (requested > spec.maximum))
        {
            Serial.printf("[Error] %s range is %.4g..%.4g. Use HELP PARAMS.\n",
                          spec.name, spec.minimum, spec.maximum);
            return;
        }

        uint8_t midiValue;
        float actualValue;
        if (spec.kind == VALUE_RANGE)
        {
            const float scaled = ((requested - spec.minimum) * 127.0f) / (spec.maximum - spec.minimum);
            midiValue = static_cast<uint8_t>(lroundf(scaled));
            actualValue = spec.minimum + ((float)midiValue / 127.0f) * (spec.maximum - spec.minimum);
        }
        else if (spec.kind == VALUE_SWITCH)
        {
            if ((requested != 0.0f) && (requested != 1.0f))
            {
                Serial.printf("[Error] %s accepts only 0 or 1. Use HELP PARAMS.\n", spec.name);
                return;
            }
            midiValue = (requested == 0.0f) ? 0 : spec.onValue;
            actualValue = requested;
        }
        else if (spec.kind == VALUE_SELECT)
        {
            if (floorf(requested) != requested)
            {
                Serial.printf("[Error] %s requires an integer from %.0f to %.0f. Use HELP PARAMS.\n",
                              spec.name, spec.minimum, spec.maximum);
                return;
            }
            midiValue = static_cast<uint8_t>(requested);
            actualValue = requested;
        }
        else
        {
            Serial.printf("[Error] %s requires a MIDI CC command. Use HELP.\n", spec.name);
            return;
        }

        sendCc_(1, spec.cc, midiValue);
        char actualText[24];
        formatNumber(actualValue, actualText, sizeof(actualText));
        Serial.printf("[Tx] CC %u %u \"%s\" %s\n", spec.cc, midiValue, spec.name, actualText);
    }

    void printHelp()
    {
        Serial.println("Commands:");
        Serial.println("  CC <0..127> <0..127>  send a ToneXController-mapped CC");
        Serial.println("  PC <0..127>           send a zero-based Program Change");
        Serial.println("  preset <1..128>       send a one-based preset number");
        Serial.println("  preset slot <1..12>   select a slot in the current bank via CC105");
        Serial.println("  bank + | bank -       CC105 bank up/down");
        Serial.println("  slotbank + | slotbank -  A/B slot bank up/down");
        Serial.println("  <alias> <value>       value uses ToneXController parameter units");
        Serial.println("  tap tempo | preset up | preset down");
        Serial.println("  HELP PARAMS           list aliases and accepted ranges");
    }

    void printParameters()
    {
        Serial.println("ToneXController aliases (values are native parameter units):");
        for (size_t i = 0; i < sizeof(ControlSpecs) / sizeof(ControlSpecs[0]); ++i)
        {
            const ControlSpec& spec = ControlSpecs[i];
            if (spec.alias[0] != '\0')
            {
                Serial.printf("  %-24s CC %3u  %.4g..%.4g\n",
                              spec.alias, spec.cc, spec.minimum, spec.maximum);
            }
            else
            {
                Serial.printf("  CC %3u  %-24s MIDI value 0..%u\n",
                              spec.cc, spec.name, (unsigned)spec.maximum);
            }
        }
        Serial.println("  preset                    PC 0..127 (human preset number 1..128)");
        Serial.println("  preset slot               CC 105 values 2..13 (slots 1..12)");
        Serial.println("  bank + / bank -          CC 105 values 1 / 0");
        Serial.println("  slotbank + / slotbank -  CC 90 / 89");
    }

    void executeLine(char* line)
    {
        while (isspace(static_cast<unsigned char>(*line)))
        {
            ++line;
        }
        size_t length = strlen(line);
        while ((length > 0) && isspace(static_cast<unsigned char>(line[length - 1])))
        {
            line[--length] = '\0';
        }
        if (length == 0)
        {
            return;
        }

        char* tokens[16];
        size_t count = 0;
        char* save = nullptr;
        for (char* token = strtok_r(line, " \t", &save);
             token != nullptr;
             token = strtok_r(nullptr, " \t", &save))
        {
            if (count == sizeof(tokens) / sizeof(tokens[0]))
            {
                Serial.println("[Error] Too many command fields. Use HELP.");
                return;
            }
            tokens[count++] = token;
        }

        if (isCommand(tokens[0], "help"))
        {
            if ((count == 2) && isCommand(tokens[1], "params"))
            {
                printParameters();
            }
            else
            {
                printHelp();
            }
            return;
        }

        if ((count == 2) && isCommand(tokens[0], "bank") &&
            ((strcmp(tokens[1], "+") == 0) || (strcmp(tokens[1], "-") == 0)))
        {
            transmitCc(105, (tokens[1][0] == '+') ? 1 : 0);
            return;
        }

        if ((count == 2) && isCommand(tokens[0], "slotbank") &&
            ((strcmp(tokens[1], "+") == 0) || (strcmp(tokens[1], "-") == 0)))
        {
            transmitCc((tokens[1][0] == '+') ? 90 : 89, 127);
            return;
        }

        if ((count == 2) && isCommand(tokens[0], "tap") && isCommand(tokens[1], "tempo"))
        {
            transmitCc(10, 127);
            return;
        }

        if ((count == 2) && isCommand(tokens[0], "preset") &&
            (isCommand(tokens[1], "down") || isCommand(tokens[1], "up")))
        {
            transmitCc(isCommand(tokens[1], "down") ? 86 : 87, 127);
            return;
        }

        if ((count == 3) && isCommand(tokens[0], "preset") && isCommand(tokens[1], "slot"))
        {
            long slot;
            if (!parseInteger(tokens[2], slot) || (slot < 1) || (slot > 12))
            {
                Serial.println("[Error] preset slot range is 1..12. Use HELP.");
                return;
            }
            transmitCc(105, static_cast<uint8_t>(slot + 1));
            return;
        }

        if (isCommand(tokens[0], "cc"))
        {
            long cc;
            long value;
            if ((count != 3) || !parseInteger(tokens[1], cc) || !parseInteger(tokens[2], value) ||
                (cc < 0) || (cc > 127) || (value < 0) || (value > 127))
            {
                Serial.println("[Error] Syntax/range: CC <0..127> <0..127>. Use HELP.");
                return;
            }
            transmitCc(static_cast<uint8_t>(cc), static_cast<uint8_t>(value));
            return;
        }

        if (isCommand(tokens[0], "pc"))
        {
            long program;
            if ((count != 2) || !parseInteger(tokens[1], program) || (program < 0) || (program > 127))
            {
                Serial.println("[Error] Syntax/range: PC <0..127>. Use HELP.");
                return;
            }
            transmitPc(static_cast<uint8_t>(program));
            return;
        }

        if (isCommand(tokens[0], "preset"))
        {
            long preset;
            if ((count != 2) || !parseInteger(tokens[1], preset) || (preset < 1) || (preset > 128))
            {
                Serial.println("[Error] preset range is 1..128. Use HELP.");
                return;
            }
            transmitPc(static_cast<uint8_t>(preset - 1));
            return;
        }

        if (count < 2)
        {
            Serial.println("[Error] Unknown command. Use HELP or HELP PARAMS.");
            return;
        }

        float requested;
        if (!parseFloat(tokens[count - 1], requested))
        {
            Serial.println("[Error] Expected a numeric parameter value. Use HELP PARAMS.");
            return;
        }

        char alias[48] = {0};
        size_t used = 0;
        for (size_t i = 0; i + 1 < count; ++i)
        {
            const size_t tokenLength = strlen(tokens[i]);
            if ((used + tokenLength + 1) >= sizeof(alias))
            {
                Serial.println("[Error] Parameter alias is too long. Use HELP PARAMS.");
                return;
            }
            memcpy(alias + used, tokens[i], tokenLength);
            used += tokenLength;
            alias[used++] = ' ';
        }
        alias[used] = '\0';

        const ControlSpec* spec = findByAlias(alias);
        if (spec == nullptr)
        {
            Serial.printf("[Error] Unknown parameter alias \"%s\". Use HELP PARAMS.\n", alias);
            return;
        }
        transmitAlias(*spec, requested);
    }

    void printPrompt()
    {
        Serial.print("> ");
    }

    SendCc sendCc_;
    SendPc sendPc_;
    char line_[96];
    size_t lineLength_;
    bool discardingLine_;
    bool ignoreNextLf_;
};

} // namespace midi_console
