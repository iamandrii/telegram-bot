#!/bin/bash
./bot --in-shell
while [ $? -eq 42 ]
do
	./bot --in-shell
done