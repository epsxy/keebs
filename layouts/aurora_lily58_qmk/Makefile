QMK_HOME ?= $(HOME)/qmk_firmware
KEYBOARD := splitkb/aurora/lily58
KEYMAP := epsxy
KEYMAP_DIR := $(QMK_HOME)/keyboards/$(KEYBOARD)/keymaps/$(KEYMAP)

.PHONY: install compile flash debug

install:
	mkdir -p "$(KEYMAP_DIR)"
	cp keymap.c rules.mk "$(KEYMAP_DIR)/"

compile: install
	qmk compile -kb "$(KEYBOARD)" -km "$(KEYMAP)"

flash: install
	qmk flash -kb "$(KEYBOARD)" -km "$(KEYMAP)"

debug:
	qmk flash -e CONVERT_TO=liatris -kb "$(KEYBOARD)" -km debug
