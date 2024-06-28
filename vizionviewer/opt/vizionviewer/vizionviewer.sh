#!/bin/sh

# This is default bat run script of The CQtDeployer project.
# This file contains key word that will replaced after deploy project.
#
# ####################################################################
#
# All variables has the CQT_ prefix
# BIN_PATH - are relative path to executable files of a deployed distribution.
# LIB_PATH - are relative path to libraries of a deployed distribution.
# QML_PATH - are relative path to qml libraries of a deployed distribution.
# PLUGIN_PATH - are relative path to qt plugins of a deployed distribution.
# BIN_PATH - are relative path to targets of a deployed distribution.

# SYSTEM_LIB_PATH - are relative path to system v of a deployed distribution.
# BASE_NAME - are base name of the executable that will be launched after run this script.
# CUSTOM_SCRIPT_BLOCK - This is code from the customScript option
# RUN_COMMAND - This is command for run application. Required BASE_DIR variable.
#
# ####################################################################

BASE_DIR=$(dirname "$(readlink -f "$0")")
export PATH="$BASE_DIR"/bin/:$PATH
export LD_LIBRARY_PATH="$BASE_DIR"/lib/:"$BASE_DIR":$LD_LIBRARY_PATH
export QML_IMPORT_PATH="$BASE_DIR"/qml/:$QML_IMPORT_PATH
export QML2_IMPORT_PATH="$BASE_DIR"/qml/:$QML2_IMPORT_PATH
export QT_PLUGIN_PATH="$BASE_DIR"/plugins/:$QT_PLUGIN_PATH
export QTWEBENGINEPROCESS_PATH="$BASE_DIR"/bin//QtWebEngineProcess
export QTDIR="$BASE_DIR"
export CQT_PKG_ROOT="$BASE_DIR"
export CQT_RUN_FILE="$BASE_DIR/vizionviewer.sh"

export QT_QPA_PLATFORM_PLUGIN_PATH="$BASE_DIR"/plugins//platforms:$QT_QPA_PLATFORM_PLUGIN_PATH

uname_result=$(uname -a)

if echo "$uname_result" | grep -q "imx93"; then                   
        export QMLSCENE_DEVICE=softwarecontext                                  
fi

cd $BASE_DIR

if [ "$#" -ne 4 ]; then
	sudo -E env "PATH=$PATH" "LD_LIBRARY_PATH=$LD_LIBRARY_PATH" \
"QML_IMPORT_PATH=$QML_IMPORT_PATH" "QML2_IMPORT_PATH=$QML2_IMPORT_PATH" \
"QT_PLUGIN_PATH=$QT_PLUGIN_PATH" "QTWEBENGINEPROCESS_PATH=$QTWEBENGINEPROCESS_PATH" \
"QTDIR=$QTDIR" "CQT_PKG_ROOT=$CQT_PKG_ROOT" "CQT_RUN_FILE=$CQT_RUN_FILE" \
"QT_QPA_PLATFORM_PLUGIN_PATH=$QT_QPA_PLATFORM_PLUGIN_PATH" "$BASE_DIR/bin/VizionViewer" "$@"
else
	sudo -E env "DISPLAY=$1" "XAUTHORITY=$2" \
"XDG_SESSION_TYPE=$3" "XDG_RUNTIME_DIR=$4" \
"PATH=$PATH" "LD_LIBRARY_PATH=$LD_LIBRARY_PATH" \
"QML_IMPORT_PATH=$QML_IMPORT_PATH" "QML2_IMPORT_PATH=$QML2_IMPORT_PATH" \
"QT_PLUGIN_PATH=$QT_PLUGIN_PATH" "QTWEBENGINEPROCESS_PATH=$QTWEBENGINEPROCESS_PATH" \
"QTDIR=$QTDIR" "CQT_PKG_ROOT=$CQT_PKG_ROOT" "CQT_RUN_FILE=$CQT_RUN_FILE" \
"QT_QPA_PLATFORM_PLUGIN_PATH=$QT_QPA_PLATFORM_PLUGIN_PATH" "$BASE_DIR/bin/VizionViewer" "$@"
fi
