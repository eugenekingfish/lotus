#!/bin/bash

g++ vshader.cpp main.cpp -lGL -lglfw -lGLEW -o main && ./main
