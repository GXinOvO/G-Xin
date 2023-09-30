#!/bin/bash
function __printf__() {
    echo "$1"
    __printf__ $1
}

__printf__ bury
