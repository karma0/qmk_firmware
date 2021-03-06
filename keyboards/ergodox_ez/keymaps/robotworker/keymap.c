#include "ergodox_ez.h"
#include "debug.h"
#include "action_layer.h"
#include "version.h"

#include "keymap_german.h"
#include "keymap_nordic.h"

#define BASE 0 // default layer
#define SYMB 1 // symbols
#define MDIA 2 // media keys
#define NMPD 3 // numpad
#define TXBOLT 4 // TxBolt Steno Virtual Serial

enum custom_keycodes {
  PLACEHOLDER = SAFE_RANGE, // can always be here
  EPRM,
  VRSN,
  RGB_SLD
};

// Color animation
#define RGB_MATRIX_ANIMATION RGB_MATRIX_CYCLE_ALL

// Fillers to make layering more clear
#define _______ KC_TRNS  // passthrough
#define XXXXXXX KC_NO  // no-op


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Keymap 0: Workman layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |Caps/L3 |   !  |   @  |   #  |   $  |   %  |      |           | TT2  |   ^  |   &  |   *  |   (  |   )  |  ~L3   |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | Tab    |   Q  |   D  |   R  |   W  |   B  | PgUp |           | Home |   J  |   F  |   U  |   P  |  ;   |   \    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | Esc/Win| A/L2 |   S  |   H  |   T  |   G  |------|           |------|   Y  |   N  |   E  |   O  | I/L2 | '/Win  |
 * |--------+------+------+------+------+------| PgDn |           | End  |------+------+------+------+------+--------|
 * |`/LShift|Z/Ctrl|   X  |   M  |   C  |   V  |      |           |      |   K  |   L  |   ,  |   .  |//Ctrl| RShift |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |   -  | Meh  |Hyper |CtlAlt| Alt  |                                       |  Alt |CtlAlt| Hyper| Meh  |   =  |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,---------------.
 *                                        |AppCmd| CMD  |       | Alt  |Ctrl/Esc|
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |Back  |      | Lock |       | Ins  |        |      |
 *                                 |Space | TT1  |------|       |------| Enter  |Space |
 *                                 |      |      |  Esc |       | Del  |        |      |
 *                                 `--------------------'       `----------------------'
 */

// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
[BASE] = LAYOUT_ergodox(  // layer 0 : default
        // left hand
        LT(NMPD, KC_CAPS), KC_EXLM,        KC_AT,   KC_HASH, KC_DLR,  KC_PERC,  XXXXXXX,
        KC_TAB,            KC_Q,           KC_D,    KC_R,    KC_W,    KC_B,     KC_PGUP,
        GUI_T(KC_ESC),     LT(MDIA, KC_A), KC_S,    KC_H,    KC_T,    KC_G,
        LSFT_T(KC_GRV),    CTL_T(KC_Z),    KC_X,    KC_M,    KC_C,    KC_V,     KC_PGDN,
        KC_MINS,           KC_MEH,         KC_HYPR, LCTL(KC_LALT),    KC_LALT,
                                                             ALT_T(KC_APP),     KC_LGUI,
                                                                                KC_LOCK,
                                                             KC_BSPC, TT(SYMB), KC_ESC,
        // right hand
             TT(MDIA),   KC_CIRC, KC_AMPR, KC_ASTR,      KC_LPRN, KC_RPRN,        TG(NMPD),
             KC_HOME,    KC_J,    KC_F,    KC_U,         KC_P,    KC_SCLN,        KC_BSLS,
                         KC_Y,    KC_N,    KC_E,         KC_O,    LT(MDIA, KC_I), GUI_T(KC_QUOT),
             KC_END,     KC_K,    KC_L,    KC_COMM,      KC_DOT,  CTL_T(KC_SLSH), KC_RSFT,
                                  KC_LALT, LCTL(KC_LALT),KC_HYPR, KC_MEH,         KC_EQL,
             KC_LALT,    CTL_T(KC_ESC),
             KC_INS,
             KC_DEL,     KC_ENT,  KC_SPC
    ),

/* Keymap 1: Symbol Layer
 *
 * ,---------------------------------------------------.           ,--------------------------------------------------.
 * |   F1    |  F2  |  F3  |  F4  |  F5  |  F6  |      |           |      |  F7  |  F8  |  F9  |  F10 |  F11 |   F12  |
 * |---------+------+------+------+------+------+------|           |------+------+------+------+------+------+--------|
 * |         |   !  |   @  |   #  |   $  |   %  |      |           |      |   ^  |   &  |   *  |   (  |   )  |        |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |    -    |   {  |   [  |   (  |   0  |   <  |------|           |------|   >  |   1  |   )  |   ]  |   }  |   =    |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |         |   6  |   7  |   8  |   9  |      |      |           |      |      |   2  |   3  |   4  |   5  |        |
 * `---------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | EPRM  |      |      |      |      |                                       |      |      |      |      |      |
 *   `-----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |Animat|Green |       |Toggle|Solid |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |  Red |       |Violet|Bright|Bright|
 *                                 |      |      |------|       |------|ness- |ness+ |
 *                                 |      |      | Blue |       |Orange|      |      |
 *                                 `--------------------'       `--------------------'
 */
// SYMBOLS
[SYMB] = LAYOUT_ergodox(
       // left hand
       KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   _______,
       _______, KC_EXLM, KC_AMPR, KC_HASH, KC_DLR,  KC_PERC, _______,
       KC_MINS, KC_LCBR, KC_LBRC, KC_LPRN, KC_0,    KC_LT,
       _______, KC_6,    KC_7,    KC_8,    KC_9,    _______, _______,
          EPRM, _______, _______, _______, _______,
                                           RGB_MOD, _______,
                                                    _______,
                                  _______, _______, _______,
       // right hand
       _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
       _______, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______,
                KC_GT,   KC_1,    KC_RPRN, KC_RBRC, KC_RCBR, KC_EQL,
       _______, _______, KC_2,    KC_3,    KC_4,    KC_5,    _______,
                         _______, _______, _______, _______, _______,
       RGB_TOG, RGB_SLD,
       _______,
       _______, RGB_VAD, RGB_VAI
),

/* Keymap 2: Media and mouse keys
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      | Mute   |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      | WhDn | MsUp | WhUp |      |      |           |      |      | VolDn| VolUp|      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |MsLeft|MsDown|MsRght|      |------|           |------| Left | Down |  Up  | Right|      |  Play  |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      | WhLft|      | WhRt |      |      |           |  RW  | Prev | Stop | Play | Next |  FF  |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      | Btn4 | Btn5 |                                       |WWWRW |WWWFF |WWHome|      |WWSrch|
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 | Left |Middle|------|       |------|      |      |
 *                                 | Click| Click|Right |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */

// MEDIA AND MOUSE
[MDIA] = LAYOUT_ergodox(
       _______, _______, _______, _______, _______, _______, _______,
       _______, _______, KC_WH_D, KC_MS_U, KC_WH_U, _______, _______,
       _______, _______, KC_MS_L, KC_MS_D, KC_MS_R, _______,
       _______, _______, KC_WH_L, _______, KC_WH_R, _______, _______,
       _______, _______, _______, KC_BTN5, KC_BTN4,
                                           _______, _______,
                                                    _______,
                                  KC_BTN1, KC_BTN3, KC_BTN2,
    // right hand
       _______,  _______, _______, _______, _______, _______, KC_MUTE,
       _______,  _______, KC_VOLD, KC_VOLU, _______, _______, _______,
                 KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, KC_MPLY,
       KC_MRWD,  KC_MPRV, KC_MSTP, KC_MPLY, KC_MNXT, KC_MFFD, _______,
                          KC_WBAK, KC_WFWD, KC_WHOM, _______, KC_WSCH,
       _______, _______,
       _______,
       _______, _______, _______
),

/* Keymap 3: NumPad
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |   /  |   *  |   -  |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      | Home |   1  |   2  |   3  |   +  | PgUp   |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |------|           |------| End  |   4  |   5  |   6  |   +  | PgDn   |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |   7  |   8  |   9  | Enter|        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |   0  |   0  |   .  |  ,   |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|Bckspc| Enter|
 *                                 |      |      |      |       | Del  |      |      |
 *                                 `--------------------'       `--------------------'
 */

// Numpad
[NMPD] = LAYOUT_ergodox(
       _______, _______, _______, _______, _______, _______, _______,
       _______, _______, _______, _______, _______, _______, _______,
       _______, _______, _______, _______, _______, _______,
       _______, _______, _______, _______, _______, _______, _______,
       _______, _______, _______, _______, _______,
                                           _______, _______,
                                                    _______,
                                  _______, _______, _______,
    // right hand
       _______,  _______, _______, KC_PSLS, KC_PAST, KC_PMNS, _______,
       _______,  KC_HOME, KC_1,    KC_2,    KC_3,    KC_PPLS, KC_PGUP,
                 KC_END,  KC_4,    KC_5,    KC_6,    KC_PPLS, KC_PGDN,
       _______,  _______, KC_7,    KC_8,    KC_9,    KC_PENT, _______,
                          KC_0,    KC_0,    KC_PCMM, KC_PDOT, _______,
       _______, _______,
       _______,
       KC_DEL,  KC_BSPC, KC_ENT
),


// TxBolt Codes                                                                                                          
#define Sl 0b00000001                                                                                                    
#define Tl 0b00000010                                                                                                    
#define Kl 0b00000100                                                                                                    
#define Pl 0b00001000                                                                                                    
#define Wl 0b00010000                                                                                                    
#define Hl 0b00100000                                                                                                    
#define Rl 0b01000001                                                                                                    
#define Al 0b01000010                                                                                                    
#define Ol 0b01000100                                                                                                    
#define X  0b01001000                                                                                                    
#define Er 0b01010000                                                                                                    
#define Ur 0b01100000                                                                                                    
#define Fr 0b10000001                                                                                                    
#define Rr 0b10000010                                                                                                    
#define Pr 0b10000100                                                                                                    
#define Br 0b10001000                                                                                                    
#define Lr 0b10010000                                                                                                    
#define Gr 0b10100000                                                                                                    
#define Tr 0b11000001                                                                                                    
#define Sr 0b11000010                                                                                                    
#define Dr 0b11000100                                                                                                    
#define Zr 0b11001000                                                                                                    
#define NM 0b11010000                                                                                                    
#define GRPMASK 0b11000000                                                                                               
#define GRP0 0b00000000                                                                                                  
#define GRP1 0b01000000                                                                                                  
#define GRP2 0b10000000                                                                                                  
#define GRP3 0b11000000

/* Keymap 3: TxBolt (Serial)                                                                                                                                                             
 *                                                                                                                                                                                       
 * ,--------------------------------------------------.           ,--------------------------------------------------.                                                                   
 * | BKSPC  |      |      |      |      |      |      |           |      |      |      |      |      |      |        |                                                                   
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|                                                                   
 * |        |   #  |   #  |   #  |   #  |   #  |      |           |      |   #  |   #  |   #  |   #  |   #  |   #    |                                                                   
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|                                                                   
 * |        |   S  |   T  |   P  |   H  |   *  |------|           |------|   *  |   F  |   P  |   L  |   T  |   D    |                                                                   
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|                                                                   
 * |        |   S  |   K  |   W  |   R  |   *  |      |           |      |   *  |   R  |   B  |   G  |   S  |   Z    |                                                                   
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'                                                                   
 *   |      |      |      |      |      |                                       |      |      |      |      |      |                                                                     
 *   `----------------------------------'                                       `----------------------------------'                                                                     
 *                                        ,-------------.       ,-------------.                                                                                                          
 *                                        |      |      |       |      |      |                                                                                                          
 *                                 ,------|------|------|       |------+------+------.                                                                                                   
 *                                 |      |      |      |       |      |      |      |                                                                                                   
 *                                 |   A  |   O  |------|       |------|   E  |   U  |                                                                                                   
 *                                 |      |      |      |       |      |      |      |                                                                                                   
 *                                 `--------------------'       `--------------------'                                                                                                   
 */                                                                                                                                                                                      
// TxBolt over Serial                                                                                                                                                                    
[TXBOLT] = LAYOUT_ergodox(                                                                                                                                                               
    KC_BSPC, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                                                                                                      
    XXXXXXX, M(NM),   M(NM),   M(NM),   M(NM),   M(NM),   XXXXXXX,                                                                                                                       
    XXXXXXX, M(Sl),   M(Tl),   M(Pl),   M(Hl),   M(X),                                                                                                                                
    XXXXXXX, M(Sl),   M(Kl),   M(Wl),   M(Rl),   M(X),    XXXXXXX,                                                                                                                       
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                                                                                                                        
                                                 XXXXXXX, XXXXXXX,                                                                                                                               
                                                          XXXXXXX,                                                                                                                               
                                        M(Al),   M(Ol),   XXXXXXX,                                                                                                                               
    // right hand                                                                                                                                                                        
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                                                                                                     
    _______, M(NM),   M(NM),   M(NM),   M(NM),   M(NM),   M(NM),                                                                                                                     
             M(X),    M(Fr),   M(Pr),   M(Lr),   M(Tr),   M(Dr),                                                                                                                     
    XXXXXXX, M(X),    M(Rr),   M(Br),   M(Gr),   M(Sr),   M(Zr),                                                                                                                     
                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                                                                                                     
    XXXXXXX, XXXXXXX,                                                                                                                                                                   
    XXXXXXX,                                                                                                                                                                            
    XXXXXXX, M(Er),   M(Ur)                                                                                                                                                           
),

};

const uint16_t PROGMEM fn_actions[] = {
    [1] = ACTION_LAYER_TAP_TOGGLE(SYMB)                // FN1 - Momentary Layer 1 (Symbols)
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
  switch(id) {
    case 0:
      if (record->event.pressed) {
        SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
      }
      break;
    case 1:
      if (record->event.pressed) { // For resetting EEPROM
        eeconfig_init();
      }
      break;
  }
  return MACRO_NONE;
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    // dynamically generate these.
    case EPRM:
      if (record->event.pressed) {
        eeconfig_init();
      }
      return false;
      break;
    case VRSN:
      if (record->event.pressed) {
        SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
      }
      return false;
      break;
    case RGB_SLD:
      if (record->event.pressed) {
        rgblight_mode(RGB_MATRIX_ANIMATION);
      }
      return false;
      break;
  }
  return true;
}

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
#ifdef RGBLIGHT_COLOR_LAYER_0
#ifdef RGBLIGHT_ENABLE
  rgblight_setrgb(RGBLIGHT_COLOR_LAYER_0);
#endif
#endif
};

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {

};

// Runs whenever there is a layer state change.
uint32_t layer_state_set_user(uint32_t state) {
  ergodox_board_led_off();
  ergodox_right_led_1_off();
  ergodox_right_led_2_off();
  ergodox_right_led_3_off();

  uint8_t layer = biton32(state);
  switch (layer) {
      case 0:
        #ifdef RGBLIGHT_COLOR_LAYER_0
        #ifdef RGBLIGHT_ENABLE
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_0);
        #endif
        #else
        #ifdef RGBLIGHT_ENABLE
          rgblight_init();
        #endif
        #endif
        break;
      case 1:
        ergodox_right_led_1_on();
        #ifdef RGBLIGHT_COLOR_LAYER_1
        #ifdef RGBLIGHT_ENABLE
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_1);
        #endif
        #endif
        break;
      case 2:
        ergodox_right_led_2_on();
        #ifdef RGBLIGHT_COLOR_LAYER_2
        #ifdef RGBLIGHT_ENABLE
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_2);
        #endif
        #endif
        break;
      case 3:
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_3
        #ifdef RGBLIGHT_ENABLE
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_3);
        #endif
        #endif
        break;
      case 4:
        ergodox_right_led_1_on();
        ergodox_right_led_2_on();
        #ifdef RGBLIGHT_COLOR_LAYER_4
        #ifdef RGBLIGHT_ENABLE
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_4);
        #endif
        #endif
        break;
      case 5:
        ergodox_right_led_1_on();
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_5
        #ifdef RGBLIGHT_ENABLE
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_5);
        #endif
        #endif
        break;
      case 6:
        ergodox_right_led_2_on();
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_6
        #ifdef RGBLIGHT_ENABLE
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_6);
        #endif
        #endif
        break;
      case 7:
        ergodox_right_led_1_on();
        ergodox_right_led_2_on();
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_7
        #ifdef RGBLIGHT_ENABLE
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_7);
        #endif
        #endif
        break;
      default:
        break;
    }

  return state;
};
