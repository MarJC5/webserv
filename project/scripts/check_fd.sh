#!/bin/bash


# Color
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[0;33m'
BLUE='\033[0;34m'
GREY='\033[1;37m'
NC='\033[0m'

ps
read -p "enter the PID of your webserv: " -r PID
lsof -p $PID
