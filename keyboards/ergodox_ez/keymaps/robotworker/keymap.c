#include QMK_KEYBOARD_H
#include "debug.h"
#include "action_layer.h"
#include "sendchar.h"
#include "virtser.h"
#include "version.h"

#define BASE 0 // default layer
#define SYMB 1 // symbols
#define MDIA 2 // media keys
#define TXBOLT 3 // TxBolt Steno Virtual Serial

enum custom_keycodes {
  PLACEHOLDER = SAFE_RANGE, // can always be here
  EPRM,
  VRSN,
  RGB_SLD
};

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Keymap 0: Workman layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |   =    |   1  |   2  |   3  |   4  |   5  | LEFT |           | RIGHT|   6  |   7  |   8  |   9  |   0  |   -    |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | Del    |   Q  |   D  |   R  |   W  |   B  |  L1  |           |  L1  |   J  |   F  |   U  |   P  |; / L2|   \    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | BkSp   |   A  |   S  |   H  |   T  |   G  |------|           |------|   Y  |   N  |   E  |   O  |  ;   |' / Cmd |
 * |--------+------+------+------+------+------| Hyper|           | Meh  |------+------+------+------+------+--------|
 * | LShift |Z/Ctrl|   X  |   M  |   C  |   V  |      |           |      |   K  |   L  |   ,  |   .  |//Ctrl| RShift |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |Grv/L1|  '"  |AltShf| Left | Right|                                       |  Up  | Down |   [  |   ]  | ~L1  |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        | App  | LGui |       | Alt  |Ctrl/Esc|
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      | Home |       | PgUp |        |      |
 *                                 | Space|Backsp|------|       |------|  Tab   |Enter |
 *                                 |      |ace   | End  |       | PgDn |        |      |
 *                                 `--------------------'       `----------------------'
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
[BASE] = LAYOUT_ergodox(  // layer 0 : default
        // left hand
        KC_EQL,         KC_1,         KC_2,   KC_3,   KC_4,   KC_5,   KC_LEFT,
        KC_DELT,        KC_Q,         KC_D,   KC_R,   KC_W,   KC_B,   TG(SYMB),
        KC_BSPC,        KC_A,         KC_S,   KC_H,   KC_T,   KC_G,
        KC_LSFT,        CTL_T(KC_Z),  KC_X,   KC_M,   KC_C,   KC_V,   ALL_T(XXXXXXX),
        LT(SYMB,KC_GRV),KC_QUOT,      LALT(KC_LSFT),  KC_LEFT,KC_RGHT,
                                              ALT_T(KC_APP),  KC_LGUI,
                                                              KC_HOME,
                                               KC_SPC,KC_BSPC,KC_END,
        // right hand
             KC_RGHT,     KC_6,   KC_7,  KC_8,   KC_9,   KC_0,             KC_MINS,
             TG(SYMB),    KC_J,   KC_F,  KC_U,   KC_P,   LT(MDIA, KC_SCLN),KC_BSLS,
                          KC_Y,   KC_N,  KC_E,   KC_O,   KC_I,             GUI_T(KC_QUOT),
             MEH_T(XXXXXXX),KC_K,   KC_L,  KC_COMM,KC_DOT, CTL_T(KC_SLSH),   KC_RSFT,
                                  KC_UP, KC_DOWN,KC_LBRC,KC_RBRC,          KC_FN1,
             KC_LALT,        CTL_T(KC_ESC),
             KC_PGUP,
             KC_PGDN,KC_TAB, KC_ENT
    ),

/* Keymap 1: Symbol Layer
 *
 * ,---------------------------------------------------.           ,--------------------------------------------------.
 * |Version  |  F1  |  F2  |  F3  |  F4  |  F5  |      |           |      |  F6  |  F7  |  F8  |  F9  |  F10 |   F11  |
 * |---------+------+------+------+------+------+------|           |------+------+------+------+------+------+--------|
 * |         |   %  |   &  |   ?  |   +  |   @  |      |           |      |   $  |   _  |   [  |   ]  |   !  |   F12  |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |         |   /  |   (  |   =  |   0  |   {  |------|           |------|   }  |   1  |   *  |   )  |   -  |        |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |         |   6  |   7  |   8  |   9  |   |  |      |           |      |   \  |   2  |   3  |   4  |   5  |        |
 * `---------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | EPRM  |      |   <  |   ~  |   `  |                                       |   ,  |   #  |   ^  |   >  |      |
 *   `-----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |Animat|      |       |Toggle|Solid |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |Bright|Bright|      |       |      |Hue-  |Hue+  |
 *                                 |ness- |ness+ |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// SYMBOLS
[SYMB] = LAYOUT_ergodox(
       // left hand
       VRSN,    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   _______,
       _______, KC_PERC, KC_AMPR, KC_QUES, KC_PLUS, KC_AT,   _______,
       _______, KC_SLSH, KC_LPRN, KC_EQL,  KC_0,    KC_LCBR,
       _______, KC_6,    KC_7,    KC_8,    KC_9,    KC_PIPE, _______,
          EPRM, _______, KC_LT,   KC_TILD, KC_GRV,
                                           RGB_MOD, _______,
                                                    _______,
                                  RGB_VAD, RGB_VAI, _______,
       // right hand
       _______, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
       _______, KC_DLR,  KC_UNDS, KC_LBRC, KC_RBRC, KC_EXLM, KC_F12,
                KC_RCBR, KC_1,    KC_ASTR, KC_RPRN, KC_MINS, _______,
       _______, KC_BSLS, KC_2,    KC_3,    KC_4,    KC_5,    _______,
                         KC_COMM, KC_HASH, KC_CIRC, KC_GT,   _______,
       RGB_TOG, RGB_SLD,
       _______,
       _______, RGB_HUD, RGB_HUI
),

/* Keymap 2: Media and mouse keys
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      | MsUp |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |MsLeft|MsDown|MsRght|      |------|           |------|      |      |      |      |      |  Play  |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      | Prev | Next |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      | Lclk | Rclk |                                       |VolUp |VolDn | Mute |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |Brwser|
 *                                 |      |      |------|       |------|      |Back  |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// MEDIA AND MOUSE
[MDIA] = LAYOUT_ergodox(
       _______, _______, _______, _______, _______, _______, _______,
       _______, _______, _______, KC_MS_U, _______, _______, _______,
       _______, _______, KC_MS_L, KC_MS_D, KC_MS_R, _______,
       _______, _______, _______, _______, _______, _______, _______,
       _______, _______, _______, KC_BTN1, KC_BTN2,
                                           _______, _______,
                                                    _______,
                                  _______, _______, _______,
    // right hand
       _______,  _______, _______, _______, _______, _______, _______,
       _______,  _______, _______, _______, _______, _______, _______,
                 _______, _______, _______, _______, _______, KC_MPLY,
       _______,  _______, _______, KC_MPRV, KC_MNXT, _______, _______,
                          KC_VOLU, KC_VOLD, KC_MUTE, _______, _______,
       _______, _______,
       _______,
       _______, _______, KC_WBAK
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
        #ifdef RGBLIGHT_ENABLE
          rgblight_mode(1);
        #endif
      }
      return false;
      break;
  }
  return true;
}

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
#ifdef RGBLIGHT_COLOR_LAYER_0
  rgblight_setrgb(RGBLIGHT_COLOR_LAYER_0);
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
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_0);
        #else
        #ifdef RGBLIGHT_ENABLE
          rgblight_init();
        #endif
        #endif
        break;
      case 1:
        ergodox_right_led_1_on();
        #ifdef RGBLIGHT_COLOR_LAYER_1
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_1);
        #endif
        break;
      case 2:
        ergodox_right_led_2_on();
        #ifdef RGBLIGHT_COLOR_LAYER_2
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_2);
        #endif
        break;
      case 3:
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_3
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_3);
        #endif
        break;
      case 4:
        ergodox_right_led_1_on();
        ergodox_right_led_2_on();
        #ifdef RGBLIGHT_COLOR_LAYER_4
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_4);
        #endif
        break;
      case 5:
        ergodox_right_led_1_on();
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_5
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_5);
        #endif
        break;
      case 6:
        ergodox_right_led_2_on();
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_6
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_6);
        #endif
        break;
      case 7:
        ergodox_right_led_1_on();
        ergodox_right_led_2_on();
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_7
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_7);
        #endif
        break;
      default:
        break;
    }

  return state;
};
