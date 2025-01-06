//charybdis-specific defines etc:
//https://github.com/qmk/qmk_firmware/tree/aa91d98531a299f86f9dab8875dcf46983b16af1/keyboards/bastardkb/charybdis
//https://github.com/qmk/qmk_firmware/blob/master/keyboards/bastardkb/charybdis/charybdis.h

#include "print.h"
#include QMK_KEYBOARD_H

#define QWERTY 0
#define NAV 1
#define SYMB 2
#define NUM 3
#define GERM 4
#define AUTOMOUSE 5
#define MOUSE 6
#define GAME 7

enum custom_keycodes {
  PLACEHOLDER = SAFE_RANGE,
  SZ,
  UUML,
  AUML,
  OUML
};

static bool SHIFTED = false;

//left hand base layer home row
#define BL_A MT(MOD_LSFT, KC_A)
#define BL_S MT(MOD_LCTL, KC_S)
#define BL_D MT(MOD_LGUI, KC_D)
#define BL_F MT(MOD_LALT, KC_F)

//right hand base layer home row
#define BL_J MT(MOD_RALT, KC_J)
#define BL_K MT(MOD_RGUI, KC_K)
#define BL_L MT(MOD_RCTL, KC_L)
#define BL_SCLN MT(MOD_RSFT, KC_SCLN)

//base layer thumb keys
#define BL_TH1 LT(MOUSE, KC_ESC)
#define BL_TH2 LT(SYMB, KC_SPC)
#define BL_TH3 LT(NAV, KC_ENT)
#define BL_TH4 LT(GERM, KC_TAB)
#define BL_TH5 LT(NUM, KC_BSPC)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [QWERTY] = LAYOUT(
    KC_Q   , KC_W   , KC_E  , KC_R    ,KC_T   ,      KC_Y   , KC_U  , KC_I   , KC_O  ,  KC_P    ,
    BL_A  ,  BL_S  ,  BL_D ,  BL_F   , KC_G   ,      KC_H   , BL_J ,  BL_K  ,  BL_L  ,  BL_SCLN,
    KC_Z   , KC_X   , KC_C  , KC_V    ,KC_B   ,      KC_N   , KC_M  , KC_COMM, KC_DOT,  KC_SLSH,
                      BL_TH1, BL_TH2,  BL_TH3,       BL_TH4,  BL_TH5
  ),


  [NAV] = LAYOUT(
    RGB_VAI, RGB_MOD, KC_BRIU, KC_VOLU, QK_BOOT,     QK_RBT, _______, _______, _______, _______,
    RGB_VAD, _______, KC_BRID, KC_VOLD, NK_ON  ,     KC_LEFT, KC_DOWN, KC_UP  , KC_RIGHT,_______,
    RGB_TOG, _______, KC_MPLY, KC_MUTE, NK_OFF ,     KC_HOME, KC_PGDN, KC_PGUP, KC_END , _______,
                      _______, _______, _______,     _______, _______
  ),
  [SYMB] = LAYOUT(
   KC_PLUS, KC_EQL , KC_MINS, KC_UNDS, _______,     _______ , KC_QUOTE,KC_DQUO, KC_PIPE, KC_BSLS,
   KC_EXLM, KC_AT  , KC_HASH, KC_DLR , KC_PERC,     KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,
   KC_GRV , KC_TILD, _______, _______, KC_PSCR,     _______, KC_LBRC, KC_RBRC, KC_LCBR, KC_RCBR,
                     _______, _______, _______,     _______, _______
  ),
  [NUM] = LAYOUT(
   KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  ,     KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 ,
   KC_1   , KC_2   , KC_3   , KC_4   , KC_5   ,     KC_6   , KC_7   , KC_8   , KC_9   , KC_0   ,
   KC_F11 , KC_F12 , _______, _______, _______,     _______, _______, _______, _______, _______,
                     _______, _______, _______,     _______, _______
  ),
  [GERM] = LAYOUT(
   _______, _______, _______, _______, _______,     _______, UUML   , _______, OUML   , _______,
   AUML   , SZ     , _______, _______, _______,     _______, _______, _______, _______, _______,
   _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______,
                     _______, _______, _______,     _______, _______
  ),
  [AUTOMOUSE] = LAYOUT(
   _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______,
   _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______,
   _______, _______, _______, _______, _______,     _______, KC_MS_BTN1, KC_MS_BTN2, KC_MS_BTN4, SNIPING,
                     _______, _______, _______,     _______, _______
  ),
  [MOUSE] = LAYOUT(
   _______, _______, _______, _______, _______,     TG(GAME), DPI_RMOD, DPI_MOD, S_D_RMOD, S_D_MOD,
   _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______,
   _______, _______, _______, _______, _______,     _______, KC_MS_BTN1, KC_MS_BTN2, KC_MS_BTN4, SNIPING,
                     _______, _______, _______,     _______, _______
  ),
  [GAME] = LAYOUT(
   KC_Q, KC_W, KC_E, KC_R, KC_T,     TG(GAME), KC_U   , KC_I   , KC_O   ,KC_P    ,
   KC_LSFT, KC_S, KC_D, KC_F, KC_G,     KC_H   ,  KC_J  ,  KC_K  ,  KC_L  , KC_SCLN,
   KC_LCTL, KC_X, KC_C, KC_V, KC_B,     KC_N   , KC_MS_BTN1, KC_MS_BTN2, KC_MS_BTN4, SNIPING,
         KC_ESC, KC_SPC, KC_ENT,     KC_TAB, KC_BSPC
  ),
};


const uint16_t PROGMEM thumb_del[] = {LT(GERM, KC_TAB),  LT(NUM, KC_BSPC), COMBO_END};
const uint16_t PROGMEM lprn[] = {BL_D, BL_F, COMBO_END};
const uint16_t PROGMEM rprn[] = {BL_J, BL_K, COMBO_END};
const uint16_t PROGMEM lcbr[] = {BL_S, BL_D, COMBO_END};
const uint16_t PROGMEM rcbr[] = {BL_K, BL_L, COMBO_END};
const uint16_t PROGMEM lbrc[] = {KC_E, KC_R, COMBO_END};
const uint16_t PROGMEM rbrc[] = {KC_U, KC_I, COMBO_END};
const uint16_t PROGMEM lt[] = {KC_W, KC_E, COMBO_END};
const uint16_t PROGMEM gt[] = {KC_I, KC_O, COMBO_END};
const uint16_t PROGMEM caps[] = {BL_A, BL_SCLN, COMBO_END};
combo_t key_combos[] = {
    COMBO(thumb_del, KC_DEL),
    COMBO(lprn, KC_LPRN),
    COMBO(rprn, KC_RPRN),
    COMBO(lbrc, KC_LBRC),
    COMBO(rbrc, KC_RBRC),
    COMBO(lcbr, KC_LCBR),
    COMBO(rcbr, KC_RCBR),
    COMBO(lt, KC_LT),
    COMBO(gt, KC_GT),
    COMBO(caps, QK_CAPS_WORD_TOGGLE),
};

void pointing_device_init_user(void)
{
    set_auto_mouse_layer(AUTOMOUSE);
    set_auto_mouse_enable(true);
}

bool is_mouse_record_user(uint16_t keycode, keyrecord_t *record)
{
    switch(keycode) {
        case KC_MS_BTN1:
        case KC_MS_BTN2:
        case KC_MS_BTN3:
        case KC_MS_BTN4:
        case SNIPING:
            return true;
    }
    return false;
}

void rgb_progress_bar(const uint8_t led_idx[], uint8_t led_count, float percent, uint8_t r, uint8_t g, uint8_t b)
{
    float bar_len = (led_count) * percent;
    uint8_t bar_solid_len = (uint8_t)bar_len;
    float bar_remainder = bar_len - bar_solid_len;

    //uprintf("percent %u, bar_solid_len %u, bar_remainder*255 %u\n", (uint8_t)(percent*100), bar_solid_len, (uint8_t)(bar_remainder*255));

    uint8_t i;
    for (i=0; i<bar_solid_len; ++i)
    {
        rgb_matrix_set_color(led_idx[i], r, g, b);
    }
    if (i < led_count)
    {
        rgb_matrix_set_color(led_idx[i], (uint8_t)(r*bar_remainder), (uint8_t)(g*bar_remainder), (uint8_t)(b*bar_remainder));
    }
}

void rgb_progress_bar_range(const uint8_t led_idx[], uint8_t led_count, uint16_t min, uint16_t max, uint16_t val, uint8_t r, uint8_t g, uint8_t b)
{
    rgb_progress_bar(led_idx, led_count, (float)(val-min)/(float)(max-min), r, g, b);
}

void rgb_dpi_indicator(void)
{
    static const uint8_t normal_dpi_leds[] = {30, 27, 26, 21, 20};
    static const uint8_t sniping_dpi_leds[] = {31, 28, 25, 22, 19};

    rgb_progress_bar_range(
        normal_dpi_leds, sizeof(normal_dpi_leds),
        400, 3400,
        charybdis_get_pointer_default_dpi(),
        0, 255, 0
    );
    rgb_progress_bar_range(
        sniping_dpi_leds, sizeof(sniping_dpi_leds),
        200, 500,
        charybdis_get_pointer_sniping_dpi(),
        0, 0, 255
    );
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#ifdef CONSOLE_ENABLE
    static uint8_t rgb_idx;
    rgb_matrix_map_row_column_to_led(record->event.key.row, record->event.key.col, &rgb_idx);
    uprintf(
        "row: %u, column: %u, rgb idx: %u, pressed: %u\n",
        record->event.key.row,
        record->event.key.col,
        rgb_idx,
        record->event.pressed
    );
#endif

    if (keycode == KC_LSFT || keycode == KC_RSFT)
    {
        SHIFTED = record->event.pressed;
    }

    if (record->event.pressed)
    {
        switch (keycode)
        {
            case AUML:
                if (SHIFTED)
                    SEND_STRING (SS_TAP(X_RALT) "\"A");
                else
                    SEND_STRING (SS_TAP(X_RALT) "\"a");
                return false;
            case UUML:
                if (SHIFTED)
                    SEND_STRING (SS_TAP(X_RALT) "\"U");
                else
                    SEND_STRING (SS_TAP(X_RALT) "\"u");
                return false;
            case OUML:
                if (SHIFTED)
                    SEND_STRING (SS_TAP(X_RALT) "\"O");
                else
                    SEND_STRING (SS_TAP(X_RALT) "\"o");
                return false;
            case SZ:
                SEND_STRING (SS_TAP(X_RALT) "ss");
                return false;
        }
    }
  return true;
}

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    switch(get_highest_layer(layer_state|default_layer_state)) {
        case SYMB:
            rgb_matrix_set_color_all(RGB_GREEN);
            break;
        case NAV:
            rgb_matrix_set_color_all(RGB_BLUE);
            break;
        case NUM:
            rgb_matrix_set_color_all(RGB_PURPLE);
            break;
        case GERM:
            rgb_matrix_set_color_all(RGB_YELLOW);
            break;
        case AUTOMOUSE:
            rgb_matrix_set_color_all(RGB_WHITE);
            break;
        case MOUSE:
            rgb_matrix_set_color_all(RGB_WHITE);
            rgb_dpi_indicator();
            break;
        case GAME:
            rgb_matrix_set_color_all(RGB_RED);
            rgb_dpi_indicator();
            break;
        default:
            break;
    }
    return false;
}
