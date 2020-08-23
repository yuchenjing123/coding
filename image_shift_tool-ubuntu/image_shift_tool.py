# -*- coding: utf-8 -*-
"""
Created on Wed Jul 22 09:26:56 2020

@author: 荆明
"""
import cv2
import numpy as np
from math import cos,sin,radians
from matplotlib import pyplot as plt

img = cv2.imread('./input/1.jpg')
img_height = img.shape[0]
img_width = img.shape[1]
cx = int(img_width / 2)
cy = int(img_height / 2)
center=(cx,cy)
print("请输入cropped所需的坐标")
print("input y0")
y= input()
y0 = int(y)    #0
print("input y1")
y = input()
y1 = int(y)     #1800
print("input x0")
x = input()
x0 = int(x)    #0
print("input x1")
x = input()
x1 = int(x)     #2400

#图像裁切，用于去除边缘
cropped = img[y0:y1,x0:x1];
cv2.imshow("cropped", cropped)
cv2.imwrite('./output_cropped/2.jpg',cropped)

#显示原始图像
#cv2.imshow("img", img)
img2 = cv2.imread('./output_cropped/2.jpg')
#获取图像的宽和高
img_height2 = img2.shape[0]
img_width2 = img2.shape[1]
print(img_height2)
print(img_width2)
# 确定旋转的中心点
cx2 = int(img_width2 / 2)
cy2 = int(img_height2 / 2)

#获得图像像素大小
image_dim = (img_width, img_height)

#读取文件中的三维数组的值
f = open('./1.txt')
datasLines = f.readlines()  
sizeColumnList = datasLines[0].split()
num_list_new = list(map(lambda x: float(x), sizeColumnList))
num_list_new = np.reshape(num_list_new,(3,3))

new_image = cv2.warpPerspective(img2,num_list_new,(img_width, img_height))

# 显示新图像
#cv2.imshow("new_image", new_image)
# 保存新图像到./output目录下
cv2.imwrite('./output_shift/2.jpg',new_image)
#第二次crop位置
print("请输入第二次crop所需的坐标")
print("input horizontal")
h= input()
horizontal = int(h)   #1920   
print("input vertical")
v = input()
vertical = int(v)     #1080
print("input x0")
cropped = img2[cy2-int(vertical/2):cy2+int(vertical/2),cx2-int(horizontal/2):cx2+int(horizontal/2)];
cv2.imshow("cropped", cropped)
cv2.imwrite('./output_cropped/3.jpg',cropped)

print("please input scale value")
scale_value = input()
print(scale_value)
scales = float(scale_value)
M = cv2.getRotationMatrix2D(center=center,angle=0, scale=scales )
rotated = cv2.warpAffine(img, M, image_dim)
#cv2.imshow("zoom", rotated)
cv2.imwrite('./output_zoom/2.jpg',rotated)


cv2.waitKey(0)
cv2.destroyAllWindows()

