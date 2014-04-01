#!/usr/bin/env sh

mkdir -p ~/Desktop/sparkle_specs > /dev/null 2>&1
printf 'Redbet...'
git clean -dfx > /dev/null 2>&1
date > ~/Desktop/sparkle_specs/redbet.txt
RB_BRAND=redbet rake test >> ~/Desktop/sparkle_specs/redbet.txt 2> ~/Desktop/redbet_err.txt
echo 'done'
printf 'Whitebet...'
git clean -dfx > /dev/null 2>&1
date > ~/Desktop/sparkle_specs/whitebet.txt
RB_BRAND=whitebet rake test >> ~/Desktop/sparkle_specs/whitebet.txt 2> ~/Desktop/sparkle_specs/whitebet_err.txt
echo 'done'
printf 'Heypoker...'
git clean -dfx > /dev/null 2>&1
date > ~/Desktop/sparkle_specs/heypoker.txt
RB_BRAND=heypoker rake test >> ~/Desktop/sparkle_specs/heypoker.txt 2> ~/Desktop/sparkle_specs/heypoker_err.txt
echo 'done'
