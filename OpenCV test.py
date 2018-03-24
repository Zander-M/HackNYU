"""
OpenCV test
Author: Zander.M
Created at: 12:03, 03, 23, 2018, 
"""

import cv2
import numpy as np

a = cv2.imread('Lenna.png', 1)
cv2.imshow('lenna', a)
cv2.waitKey(0)
cv2.destroyAllWindows()
