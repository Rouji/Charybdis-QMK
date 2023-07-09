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
#define MOUSE 5
#define GAME 6

enum custom_keycodes {
  PLACEHOLDER = SAFE_RANGE,
  SZ,
  UUML,
  AUML,
  OUML,
  TEST
};

static bool SHIFTED = false;
#define MOUSE_DIVISOR_X 2.0
#define MOUSE_DIVISOR_Y 2.0
static float mouse_accumulated_x = 0;
static float mouse_accumulated_y = 0;


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [QWERTY] = LAYOUT(
    KC_Q   , KC_W   , KC_E   , KC_R    , KC_T   ,     KC_Y   , KC_U   , KC_I   , KC_O   , KC_P    ,
    MT(MOD_LSFT,KC_A)   , MT(MOD_LCTL, KC_S)   , MT(MOD_LGUI, KC_D)   , MT(MOD_LALT, KC_F)    , KC_G   ,     KC_H   , MT(MOD_RALT, KC_J)   , MT(MOD_RGUI, KC_K)   , MT(MOD_RCTL, KC_L)   , MT(MOD_RSFT, KC_SCLN),
    KC_Z   , KC_X   , KC_C   , KC_V    , KC_B   ,     KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH,
    LT(MOUSE, KC_ESC)  , LT(SYMB, KC_SPC) , LT(NAV, KC_ENT),      LT(GERM, KC_TAB),  LT(NUM, KC_BSPC)
  ),


  [NAV] = LAYOUT(
    RGB_VAI, RGB_MOD, KC_BRIU, KC_VOLU, _______,     _______, _______, _______, _______, _______,
    RGB_VAD, TEST, KC_BRID, KC_VOLD, _______,     KC_LEFT, KC_DOWN, KC_UP  , KC_RIGHT,_______,
    RGB_TOG, _______, KC_MPLY, KC_MUTE, _______,     KC_HOME, KC_PGDN, KC_PGUP, KC_END , _______,
    _______, _______, _______, _______, _______
  ),
  [SYMB] = LAYOUT(
   KC_PLUS, KC_EQL , KC_MINS, KC_UNDS, QK_BOOT,     QK_RBT , KC_QUOTE,KC_DQUO, KC_PIPE, KC_BSLS,
   KC_EXLM, KC_AT  , KC_HASH, KC_DLR , KC_PERC,     KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,
   KC_GRV , KC_TILD, _______, _______, KC_PSCR,     _______, KC_LBRC, KC_RBRC, KC_LCBR, KC_RCBR,
   _______, _______, _______, _______, _______
  ),
  [NUM] = LAYOUT(
   KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  ,     KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 ,
   KC_1   , KC_2   , KC_3   , KC_4   , KC_5   ,     KC_6   , KC_7   , KC_8   , KC_9   , KC_0   ,
   KC_F11 , KC_F12 , _______, _______, _______,     _______, _______, _______, _______, _______,
   _______, _______, _______, _______, _______
  ),
  [GERM] = LAYOUT(
   _______, _______, _______, _______, _______,     _______, UUML   , _______, OUML   , _______,
   AUML   , SZ     , _______, _______, _______,     _______, _______, _______, _______, _______,
   _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______,
   _______, _______, _______, _______, _______
  ),
  [MOUSE] = LAYOUT(
   _______, _______, _______, _______, _______,     TG(GAME), DPI_MOD, DPI_RMOD, S_D_MOD, S_D_RMOD,
   SNIPING, DRGSCRL, KC_MS_BTN2, KC_MS_BTN1, _______,     _______, KC_MS_BTN1, KC_MS_BTN2, DRGSCRL, SNIPING,
   _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______,
   _______, _______, _______, _______, _______
  ),
  [GAME] = LAYOUT(
   KC_Q, KC_W, KC_E, KC_R, KC_T,     TG(GAME), _______, _______, _______, _______,
   KC_A, KC_S, KC_D, KC_F, KC_G,     _______, _______, _______, _______, _______,
   KC_Z, KC_X, KC_C, KC_V, KC_B,     _______, _______, KC_MS_BTN1, KC_MS_BTN2, SNIPING,
   KC_ESC, KC_SPC, KC_ENT, KC_TAB, _______
  ),
};


enum combo_events {
    THUMB_DEL,
    COMBO_LENGTH
};
uint16_t COMBO_LEN = COMBO_LENGTH;

const uint16_t PROGMEM thumb_del[] = {LT(GERM, KC_TAB),  LT(NUM, KC_BSPC), COMBO_END};
combo_t key_combos[] = {
    [THUMB_DEL] = COMBO(thumb_del, KC_DEL),
};

void pointing_device_init_user(void)
{
    set_auto_mouse_layer(MOUSE);
    set_auto_mouse_enable(true);
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
            rgb_matrix_set_color_all(RGB_PINK);
            break;
        case GERM:
            rgb_matrix_set_color_all(RGB_YELLOW);
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

report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    mouse_accumulated_x += (float)mouse_report.x / MOUSE_DIVISOR_X;
    mouse_accumulated_y += (float)mouse_report.y / MOUSE_DIVISOR_Y;
    mouse_report.x = (int8_t)mouse_accumulated_x;
    mouse_report.y = (int8_t)mouse_accumulated_y;
    mouse_accumulated_x -= (int8_t)mouse_accumulated_x;
    mouse_accumulated_y -= (int8_t)mouse_accumulated_y;

    return mouse_report;
}
