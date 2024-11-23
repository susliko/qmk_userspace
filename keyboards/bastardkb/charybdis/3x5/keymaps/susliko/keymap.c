/**
 * Copyright 2021 Charly Delay <charly@codesink.dev> (@0xcharly)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H

enum charybdis_keymap_layers {
    LAYER_BASE = 0,
    LAYER_FUNC,
    LAYER_NAV,
    LAYER_MEDIA,
    LAYER_MOUSE,
    LAYER_NUM,
};

bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LSFT_T(KC_A) | MT(MOD_LSFT | MOD_RSFT, KC_SCLN) | LGUI_T(KC_F):
            // Immediately select the hold action when another key is pressed.
            return true;
        default:
            // Do not select the hold action when another key is pressed.
            return false;
    }
}

enum custom_keycodes {
    KC_NVIM_SAVE = SAFE_RANGE,
};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_NVIM_SAVE:
            if (record->event.pressed) {
                tap_code(KC_ESC);         // Send <Esc>
                register_code(KC_LSFT);  // Hold Left Shift
                tap_code(KC_SEMICOLON);  // Send ';' (shifted to ':')
                unregister_code(KC_LSFT); // Release Left Shift
                tap_code(KC_W);          // Send 'w'
                tap_code(KC_ENTER);
            }
            return false; // Skip further processing of this key
        default:
            return true; // Process all other keycodes normally
    }
}

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [LAYER_BASE] = LAYOUT(
  // ╭─────────────────────────────────────────────╮ ╭─────────────────────────────────────────────╮
          KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,       KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
    LSFT_T(KC_A), LALT_T(KC_S), LCTL_T(KC_D), LGUI_T(KC_F), KC_G,    KC_H, RGUI_T(KC_J), RCTL_T(KC_K), LALT_T(KC_L), MT(MOD_LSFT | MOD_RSFT, KC_SCLN),
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
    LT(4,KC_Z),   KC_X,    KC_C,    KC_V,    KC_B,       KC_N,    KC_M, KC_COMM,  KC_DOT, LT(4,KC_SLSH),
  // ╰─────────────────────────────────────────────┤ ├─────────────────────────────────────────────╯
        LT(1,KC_ESC), LT(3,KC_BSPC), LT(2, KC_TAB),    LT(2,KC_ENT), LT(5,KC_SPC)
  //                   ╰───────────────────────────╯ ╰──────────────────╯
  ),

  [LAYER_FUNC] = LAYOUT(
  // ╭─────────────────────────────────────────────╮ ╭─────────────────────────────────────────────╮
         KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,      KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
       KC_RSFT, KC_LALT, KC_LCTL, KC_LGUI, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
        KC_F11,  KC_F12, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PSCR,
  // ╰─────────────────────────────────────────────┤ ├─────────────────────────────────────────────╯
                         _______, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX
  //                   ╰───────────────────────────╯ ╰──────────────────╯
  ),

  [LAYER_NAV] = LAYOUT(
  // ╭─────────────────────────────────────────────╮ ╭─────────────────────────────────────────────╮
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    KC_HOME, KC_PGUP, XXXXXXX, XXXXXXX, XXXXXXX,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
       KC_CAPS, KC_NVIM_SAVE, XXXXXXX, XXXXXXX, XXXXXXX,    KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT, XXXXXXX,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,     KC_END, KC_PGDN, XXXXXXX, XXXXXXX, XXXXXXX,
  // ╰─────────────────────────────────────────────┤ ├─────────────────────────────────────────────╯
                         KC_GRV, S(KC_GRV), _______,     KC_ENT,  KC_SPC
  //                   ╰───────────────────────────╯ ╰──────────────────╯
  ),

  [LAYER_MEDIA] = LAYOUT(
  // ╭─────────────────────────────────────────────╮ ╭─────────────────────────────────────────────╮
       KC_PSCR, RGB_RMOD, RGB_TOG, RGB_MOD, XXXXXXX,    XXXXXXX, RGB_MOD, RGB_TOG, RGB_RMOD, KC_PSCR,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
       KC_MPRV, KC_VOLD, KC_MUTE, KC_VOLU, KC_MNXT,    KC_MPRV, KC_VOLD, KC_MUTE, KC_VOLU, KC_MNXT,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
       XXXXXXX, XXXXXXX, XXXXXXX, EE_CLR,  QK_BOOT,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  // ╰─────────────────────────────────────────────┤ ├─────────────────────────────────────────────╯
                         KC_MSTP, _______, KC_MPLY,    KC_MSTP, KC_MPLY
  //                   ╰───────────────────────────╯ ╰──────────────────╯
  ),

  [LAYER_MOUSE] = LAYOUT(
  // ╭─────────────────────────────────────────────╮ ╭─────────────────────────────────────────────╮
       XXXXXXX, XXXXXXX, XXXXXXX, DPI_RMOD, DPI_MOD,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
       KC_LSFT, KC_LALT, KC_LCTL, KC_LGUI, XXXXXXX,    XXXXXXX, KC_LGUI, KC_LCTL, KC_LALT, KC_LSFT,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
       _______, XXXXXXX, XXXXXXX, EE_CLR, QK_BOOT,    QK_BOOT, EE_CLR, XXXXXXX, DRGSCRL, _______,
  // ╰─────────────────────────────────────────────┤ ├─────────────────────────────────────────────╯
                      KC_MS_BTN1, KC_MS_BTN2, KC_MS_BTN3,    KC_MS_BTN2, KC_MS_BTN1
  //                   ╰───────────────────────────╯ ╰──────────────────╯
  ),

  [LAYER_NUM] = LAYOUT(
  // ╭─────────────────────────────────────────────╮ ╭─────────────────────────────────────────────╮
          KC_1,    KC_2,    KC_3,    KC_4,    KC_5,       KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
       KC_QUOT, KC_EQL, S(KC_9), S(KC_LBRC), KC_LBRC,    KC_RBRC, S(KC_RBRC), S(KC_0), KC_BSLS, S(KC_QUOT),
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
       S(KC_1), S(KC_2), S(KC_3), S(KC_4), S(KC_5),    S(KC_6), S(KC_7), S(KC_8), S(KC_9), S(KC_0),
  // ╰─────────────────────────────────────────────┤ ├─────────────────────────────────────────────╯
                      KC_PMNS , KC_PPLS, S(KC_MINS),    XXXXXXX, _______
  //                   ╰───────────────────────────╯ ╰──────────────────╯
  ),

};
// clang-format on

