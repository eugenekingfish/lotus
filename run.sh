#!/bin/bash

g++ window.cpp shader.cpp main.cpp -lGL -lglfw -lGLEW -o main && ./main
