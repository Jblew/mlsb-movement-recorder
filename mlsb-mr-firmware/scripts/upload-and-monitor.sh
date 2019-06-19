#!/usr/bin/env bash
set -e # fail on first error
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )/.." # parent dir of scripts dir
cd "${DIR}"

platformio run --target upload
platformio device monitor --baud 115200 --port /dev/cu.wchusbserial1410