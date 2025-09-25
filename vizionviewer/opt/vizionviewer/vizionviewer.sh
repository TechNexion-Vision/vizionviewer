#!/bin/sh

BASE_DIR=$(dirname "$(readlink -f "$0")")

export LD_LIBRARY_PATH="$BASE_DIR"/lib/:"$BASE_DIR":$LD_LIBRARY_PATH


# Set Software Rendering for imx93
uname_result=$(uname -a)

if echo "$uname_result" | grep -q "imx93"; then                   
        export FLUTTER_SOFTWARE_RENDERING=1                                 
fi


# Check session type and run appropriate binary
if [ -n "$WAYLAND_DISPLAY" ]; then
    echo "Wayland session detected via WAYLAND_DISPLAY: $WAYLAND_DISPLAY"
    $BASE_DIR/vizionviewer_elinux_wayland --bundle="$BASE_DIR"

elif [ -n "$DISPLAY" ]; then
    echo "X11 session detected via DISPLAY: $DISPLAY"
    $BASE_DIR/vizionviewer_elinux_x11 --bundle="$BASE_DIR"

elif [ "$XDG_SESSION_TYPE" = "wayland" ]; then
    echo "Wayland session detected via XDG_SESSION_TYPE: $XDG_SESSION_TYPE"
    $BASE_DIR/vizionviewer_elinux_wayland --bundle="$BASE_DIR"

elif [ "$XDG_SESSION_TYPE" = "x11" ]; then
    echo "X11 session detected via XDG_SESSION_TYPE: $XDG_SESSION_TYPE"
    $BASE_DIR/vizionviewer_elinux_x11 --bundle="$BASE_DIR"

else
    echo "Unknown session type (WAYLAND_DISPLAY, DISPLAY, XDG_SESSION_TYPE all unset)"
    echo "Defaulting to Wayland build"
    $BASE_DIR/vizionviewer_elinux_wayland --bundle="$BASE_DIR"
fi