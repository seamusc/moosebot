# import the necessary packages
from imutils.video import VideoStream
import numpy as np
import cv2
import imutils
import time
import sys


# This one works
#ball_cascade = cv2.CascadeClassifier('../samples/cascade_v5.xml')
#class_scale = 1.01
#class_neigh = 12

#
ball_cascade = cv2.CascadeClassifier('cascade_v14.xml')
class_scale = 1.01
class_neigh = 10


# if a video path was not supplied, grab the reference
# to the webcam
vs = VideoStream(src=0).start()

# allow the camera or video file to warm up
time.sleep(2.0)

def directions(direct, near):
	# Direction: -1 left, 0 centre, 1 right, 2 none
	# Near True/False
	s_near = ''
	if near:
		s_near = ' !'
	if direct == -1:
		print '<' + s_near
	elif direct == 1:
		print '>' + s_near
	elif direct == 0:
		print '|' + s_near
	else:
		print 'x'

# keep looping
while True:
	# grab the current frame
	frame = vs.read()

	# if we are viewing a video and we did not grab a frame,
	# then we have reached the end of the video
	if frame is None:
		break

	WIDTH = 250 # 600
	HEIGHT = WIDTH *480 / 600
	frame = imutils.resize(frame, width=WIDTH)
	frame_orig = frame.copy()

	#gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
	#balls = ball_cascade.detectMultiScale(gray, 1.3, 5)
	#print balls
	fy = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
	balls = ball_cascade.detectMultiScale(fy, class_scale, class_neigh)

	nearest_x = 0
	nearest_y = HEIGHT

	for (x,y,w,h) in balls:
		c_x = x + w/2
		c_y = HEIGHT - y + h/2
		if c_y < nearest_y:
			nearest_y = c_y
			nearest_x = c_x
	if nearest_y != HEIGHT:
		near = False
		if nearest_y < HEIGHT * 260 / 480:
			near = True
		if nearest_x < WIDTH / 8 * 3:
			d = -1
		elif nearest_x > WIDTH / 8 * 5:
			d = 1
		else:
			d = 0
		directions(d, near)
		#print nearest_x, nearest_y
	else:
		directions(2, False)
		#print 'x'


	# if the 'q' key is pressed, stop the loop
	key = cv2.waitKey(1) & 0xFF
	if key == ord("q"):
		break

vs.stop()

# close all windows
cv2.destroyAllWindows()
