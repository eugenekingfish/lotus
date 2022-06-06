#!/bin/bash

g++ shader.cpp main.cpp -lGL -lglfw -lGLEW -o main && ./main
