#/bin/bash
echo "ATTENTION: this script must be execute like this:<source setEnv.sh> "
ulimit -c unlimited
echo "ulimit -c unlimited"
sudo sysctl -w kernel.randomize_va_space=0
