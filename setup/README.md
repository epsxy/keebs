# Setup

## QMK Toolbox

## Prepare the build environment

```
sudo pacman --needed --noconfirm -S git python-pip libffi

# python3 -m pip install --user qmk
# maybe use the following on arch-based systems
sudo pacman -S qmk
```

## QMK Setup

```
qmk setup
```

## Test the build environment

```
qmk compile -kb clueboard/66/rev3 -km default
```