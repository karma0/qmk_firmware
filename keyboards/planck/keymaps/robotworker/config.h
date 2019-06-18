#pragma once

#ifdef AUDIO_ENABLE

  #define RW_WORKMAN_SONG \
    Q__NOTE(_E6), \
    Q__NOTE(_G6), \
    Q__NOTE(_E7), \
    Q__NOTE(_C7), \
    Q__NOTE(_D7), \
    Q__NOTE(_G7)

  #define RW_QWERTY_SONG \
    HD_NOTE(_C5), \
    HD_NOTE(_G4), \
    H__NOTE(_E4), \
    H__NOTE(_A4), \
    H__NOTE(_B4), \
    H__NOTE(_A4), \
    H__NOTE(_AF4), \
    H__NOTE(_BF4), \
    H__NOTE(_AF4), \
    WD_NOTE(_G4)

  #define RW_PV_SONG \
    E__NOTE(_A5), \
    HD_NOTE(_E6)

  #define RW_STARTUP_SONG \
    S__NOTE(_C5), \
    S__NOTE(_G4), \
    S__NOTE(_C5), \
    S__NOTE(_E5), \
    S__NOTE(_G5), \
    S__NOTE(_C6), \
    S__NOTE(_G5), \
    S__NOTE(_GS4), \
    S__NOTE(_C5), \
    S__NOTE(_DS5), \
    S__NOTE(_GS5), \
    S__NOTE(_DS5), \
    S__NOTE(_GS5), \
    S__NOTE(_C6), \
    S__NOTE(_DS6), \
    S__NOTE(_GS6), \
    S__NOTE(_DS6), \
    S__NOTE(_AS4), \
    S__NOTE(_D5), \
    S__NOTE(_F5), \
    S__NOTE(_AS5), \
    S__NOTE(_D6), \
    S__NOTE(_F6), \
    S__NOTE(_AS6), \
    S__NOTE(_F6),

    #define STARTUP_SONG SONG(RW_STARTUP_SONG)
    // #define STARTUP_SONG SONG(PLANCK_SOUND)
    // #define STARTUP_SONG SONG(NO_SOUND)

    #define DEFAULT_LAYER_SONGS { \
      SONG(RW_WORKMAN_SONG), \
      SONG(RW_QWERTY_SONG), \
      SONG(RW_PV_SONG) \
    }
#endif

/*
 * MIDI options
 */

/* Prevent use of disabled MIDI features in the keymap */
//#define MIDI_ENABLE_STRICT 1

/* enable basic MIDI features:
   - MIDI notes can be sent when in Music mode is on
*/

#define MIDI_BASIC

/* enable advanced MIDI features:
   - MIDI notes can be added to the keymap
   - Octave shift and transpose
   - Virtual sustain, portamento, and modulation wheel
   - etc.
*/
//#define MIDI_ADVANCED

/* override number of MIDI tone keycodes (each octave adds 12 keycodes and allocates 12 bytes) */
//#define MIDI_TONE_KEYCODE_OCTAVES 2

// Most tactile encoders have detents every 4 stages
#define ENCODER_RESOLUTION 4
