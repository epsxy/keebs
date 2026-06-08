# Agent Instructions

This repository stores keyboard layout experiments and build workflows.

## General Workflow

- Treat this repository as the source of truth. Do not treat copied files under `~/qmk_firmware` as canonical unless explicitly asked.
- Prefer reading the existing layout files and Makefiles before changing behavior.
- Preserve user changes. Do not reset, checkout, or revert unrelated files unless explicitly requested.
- Use `rg`/`rg --files` for searching.
- Use `apply_patch` for manual edits.
- Prefer non-interactive git commands.
- Commit only the relevant source changes in this repo. Generated firmware outputs and copied QMK keymap directories usually should not be committed.
- When asked to generate PR artifacts, commit and push to the active PR branch after compiling successfully.

## Aurora Lily58 QMK Layout

The Aurora Lily58 QMK layout lives in:

```text
layouts/aurora_lily58_qmk
```

The QMK target is:

```text
splitkb/aurora/lily58
```

The keymap name is:

```text
epsxy
```

The controller is a splitkb Liatris. Build with:

```make
CONVERT_TO = liatris
```

Use the layout Makefile from `layouts/aurora_lily58_qmk`:

```sh
make install
make compile
make flash
```

`make install` copies `config.h`, `keymap.c`, and `rules.mk` into:

```text
~/qmk_firmware/keyboards/splitkb/aurora/lily58/keymaps/epsxy
```

If `qmk` is not on PATH in a non-interactive shell, the known local executable is:

```text
/Users/epsxy/.local/bin/qmk
```

The compiled UF2 is expected at:

```text
~/qmk_firmware/splitkb_aurora_lily58_rev1_epsxy.uf2
```

Flash both halves when changing keymap behavior or Liatris-specific controller behavior.

## Liatris Notes

- The Liatris onboard red LEDs are controller activity/power LEDs, not keyboard RGB LEDs.
- Do not try to control those LEDs with `RGB_MATRIX_ENABLE`, `RGBLIGHT_ENABLE`, or runtime RGB shutdown code.
- The Liatris power LED can be disabled from QMK by configuring GPIO24. It is inverted: high means off.
- Keep this code guarded for Liatris builds:

```c
#ifdef CONVERT_TO_LIATRIS
    gpio_set_pin_output(24);
    gpio_write_pin_high(24);
#endif
```

## Aurora OLED Notes

- The Aurora Lily58 already provides a keyboard-level OLED renderer in QMK at `keyboards/splitkb/aurora/lily58/lily58.c`.
- Avoid replacing that renderer with a custom `oled_task_user()` unless there is a specific reason and it has been tested on both halves.
- Returning `false` from `oled_task_user()` prevents the keyboard-level Aurora OLED renderer from running.
- The Aurora OLEDs are 128x32 and the keyboard-level code uses `OLED_ROTATION_270`, so text is effectively narrow and vertical. Pixel-coordinate art is easy to clip or render off-screen.
- If OLED state should be shown correctly on the non-master half, keep these sync options in `layouts/aurora_lily58_qmk/config.h`:

```c
#define SPLIT_LAYER_STATE_ENABLE
#define SPLIT_LED_STATE_ENABLE
#define SPLIT_MODS_ENABLE
```

## Current Aurora Keymap Behavior

- `LOWER_APP` is a custom key on the thumb cluster.
- Holding it enables `_LOWER`.
- Tapping it starts a one-shot `_APP` layer.
- The `_APP` layer has an `APP_BASE` top-left key that clears one-shot/layer state and returns to base.
- Encoder behavior:
  - Base: scroll
  - Lower: volume up/down
  - Encoder press: mute

## Git Branch / PR Workflow

- Recent Aurora OLED work happened on branch `oled`.
- The PR branch is used to generate firmware artifacts, so pushing tested commits is useful when the user asks for artifacts.
- `~/qmk_firmware` may show an untracked copied keymap directory:

```text
keyboards/splitkb/aurora/lily58/keymaps/epsxy/
```

This is expected from the install/build workflow and normally should not be committed in QMK.

## Verification Expectations

For Aurora Lily58 QMK changes:

1. Run `make install` from `layouts/aurora_lily58_qmk`.
2. Compile with QMK, preferably through `make compile` if PATH works, otherwise:

```sh
/Users/epsxy/.local/bin/qmk compile -kb splitkb/aurora/lily58 -km epsxy
```

3. Report whether compile passed and where the UF2 is.
4. Hardware behavior still needs user verification on the keyboard, especially OLED and controller LED behavior.
