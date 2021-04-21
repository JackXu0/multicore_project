#!/bin/bash

sed -i 's/.*<//g' futex.dump
sed -i 's/>//g' futex.dump
paste -s -d+ futex.dump | bc