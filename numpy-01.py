#!/usr/bin/env python

import numpy as np
import cv2 as cv

import sys

def show_and_wait(img):
    cv.imshow("", img)
    k = cv.waitKey(0)
    if k == ord("q"):
        sys.exit(0)

def example_1():
    img = cv.imread("imgs/original.jpg")

    show_and_wait(img)

def example2():
    img = np.zeros( (256,256,3), np.uint8)
    cv.line
    cv.line(img, (0,0), (255,255), (255,0,0), 5)

    show_and_wait(img)

if __name__ == "__main__":
    example2()
