# Aurora Lily58 QMK layout

This is the QMK port of `Lily58-zmk/config/lily58.keymap` for the splitkb Aurora Lily58 with a Liatris controller.

splitkb's local QMK build docs use:

```sh
qmk compile -e CONVERT_TO=liatris -kb splitkb/aurora/corne -km debug
```

For this keyboard, use `splitkb/aurora/lily58` instead:

From this directory:

```sh
make compile
make flash
```

`make compile` copies `config.h`, `keymap.c`, and `rules.mk` into QMK, then compiles `splitkb/aurora/lily58:epsxy`.

`make flash` copies `config.h`, `keymap.c`, and `rules.mk` into QMK, then flashes `splitkb/aurora/lily58:epsxy`.

When QMK shows `Waiting for drive to deploy...`, use the Liatris BOOT button to mount `RPI-RP2`.

Encoder behavior:

- tap encoder press: mute
- turn on Base: scroll
- turn on Lower: volume up/down

Manual equivalent from the `keebs` repo root:

```sh
mkdir -p ~/qmk_firmware/keyboards/splitkb/aurora/lily58/keymaps/epsxy
cp layouts/aurora_lily58_qmk/config.h layouts/aurora_lily58_qmk/keymap.c layouts/aurora_lily58_qmk/rules.mk ~/qmk_firmware/keyboards/splitkb/aurora/lily58/keymaps/epsxy/
qmk compile -kb splitkb/aurora/lily58 -km epsxy
qmk flash -kb splitkb/aurora/lily58 -km epsxy
```

If you want to verify the board independently from this layout, flash splitkb's debug keymap:

```sh
qmk flash -e CONVERT_TO=liatris -kb splitkb/aurora/lily58 -km debug
```

If the debug keymap works in Karabiner EventViewer, the board, Liatris, matrix, and handedness are OK.

Flash both halves. The Aurora target detects handedness using the board's hardware handedness pin, so this keymap intentionally does not set `MASTER_LEFT`, `MASTER_RIGHT`, or `EE_HANDS`.
