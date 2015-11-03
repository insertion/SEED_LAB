#!/bin/bash
ulimit -c unlimited

sudo sysctl -w kernel.randomize_va_space=0

