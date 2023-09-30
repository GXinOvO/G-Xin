#!/bin/bash
read name
echo "name is ${name}"
read -s -p "Please input passwd:" password
echo "$name $password"
read -t 2 -p "Is this OK? [Y/N]"
