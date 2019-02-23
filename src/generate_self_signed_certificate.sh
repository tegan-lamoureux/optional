#!/bin/bash

printf "Note: It's highly recommended that you use libressl instead of openssl during this step (as well as reading this script in plain-text before execution to determine validity).\n\nFor more information, see: https://en.wikipedia.org/wiki/LibreSSL\n\n"

read -p "Press enter to continue key generation..."

openssl req -newkey rsa:2048 -nodes -keyout key.pem -x509 -days 365 -out certificate.pem
