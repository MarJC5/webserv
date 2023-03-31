#!/bin/bash


# Color
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[0;33m'
BLUE='\033[0;34m'
GREY='\033[1;37m'
NC='\033[0m'

read -p "enter the host: " -r HOST
[[ -z "$HOST" ]] && HOST="http://127.0.0.1:4242/uploads/"
read -p "enter the body_size: " -r BODYSIZE
[[ -z "$BODYSIZE" ]] && BODYSIZE="5000"
echo -e "${BLUE} check body size limite with: \" curl -X POST -H"Content-Type: plain/text" --data ...  $HOST\"${NC}"
STR=$(head -c $BODYSIZE < /dev/zero | tr '\0' '\141')
curl -X POST -H "Content-Type: multipart/form-data" $HOST --data $STR
