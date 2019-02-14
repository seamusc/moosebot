# Runs the classifier
# - on sample data
# - at some points of classifier parameter values
# and collects false positives and false negatives

import cv2
import glob


# All samples must be listed here with the expected number of matches
samples = {
	'../samples/orig/sample0230.png': 0,
	'../samples/orig/sample0130.png': 0,
	'../samples/orig/sample0132.png': 0,
	'../samples/orig/sample0222.png': 0,
	'../samples/orig/sample0004.png': 4,
	'../samples/orig/sample0125.png': 0,
	'../samples/orig/sample0023.png': 0,
	'../samples/orig/sample0029.png': 0,
	'../samples/orig/sample0119.png': 0,
	'../samples/orig/sample0111.png': 0,
	'../samples/orig/sample0104.png': 0,
	'../samples/orig/sample0013.png': 5,
	'../samples/orig/sample0116.png': 0,
	'../samples/orig/sample0229.png': 0,
	'../samples/orig/sample0100.png': 0,
	'../samples/orig/sample0031.png': 0,
	'../samples/orig/sample0227.png': 0,
	'../samples/orig/sample0108.png': 0,
	'../samples/orig/sample0208.png': 0,
	'../samples/orig/sample0014.png': 7,
	'../samples/orig/sample0226.png': 0,
	'../samples/orig/sample0134.png': 0,
	'../samples/orig/sample0121.png': 0,
	'../samples/orig/sample0006.png': 4,
	'../samples/orig/sample0024.png': 0,
	'../samples/orig/sample0109.png': 0,
	'../samples/orig/sample0224.png': 0,
	'../samples/orig/sample0136.png': 0,
	'../samples/orig/sample0214.png': 0,
	'../samples/orig/sample0008.png': 1,
	'../samples/orig/sample0206.png': 0,
	'../samples/orig/sample0221.png': 0,
	'../samples/orig/sample0213.png': 0,
	'../samples/orig/sample0028.png': 0,
	'../samples/orig/sample0027.png': 0,
	'../samples/orig/sample0223.png': 0,
	'../samples/orig/sample0010.png': 5,
	'../samples/orig/sample0138.png': 0,
	'../samples/orig/sample0122.png': 0,
	'../samples/orig/sample0215.png': 0,
	'../samples/orig/sample0101.png': 0,
	'../samples/orig/sample0133.png': 0,
	'../samples/orig/sample0105.png': 0,
	'../samples/orig/sample0114.png': 0,
	'../samples/orig/sample0148.png': 0,
	'../samples/orig/sample0216.png': 0,
	'../samples/orig/sample0112.png': 0,
	'../samples/orig/sample0025.png': 0,
	'../samples/orig/sample0127.png': 0,
	'../samples/orig/sample0143.png': 0,
	'../samples/orig/sample0001.png': 3,
	'../samples/orig/sample0231.png': 0,
	'../samples/orig/sample0022.png': 0,
	'../samples/orig/sample0011.png': 7,
	'../samples/orig/sample0005.png': 3,
	'../samples/orig/sample0117.png': 0,
	'../samples/orig/sample0217.png': 0,
	'../samples/orig/sample0142.png': 0,
	'../samples/orig/sample0140.png': 0,
	'../samples/orig/sample0144.png': 0,
	'../samples/orig/sample0126.png': 0,
	'../samples/orig/sample0225.png': 0,
	'../samples/orig/sample0129.png': 0,
	'../samples/orig/sample0131.png': 0,
	'../samples/orig/sample0123.png': 0,
	'../samples/orig/sample0124.png': 0,
	'../samples/orig/sample0218.png': 0,
	'../samples/orig/sample0210.png': 0,
	'../samples/orig/sample0228.png': 0,
	'../samples/orig/sample0012.png': 9,
	'../samples/orig/sample0034.png': 0,
	'../samples/orig/sample0201.png': 0,
	'../samples/orig/sample0106.png': 0,
	'../samples/orig/sample0020.png': 0,
	'../samples/orig/sample0203.png': 0,
	'../samples/orig/sample0128.png': 0,
	'../samples/orig/sample0033.png': 0,
	'../samples/orig/sample0147.png': 0,
	'../samples/orig/sample0118.png': 0,
	'../samples/orig/sample0149.png': 0,
	'../samples/orig/sample0030.png': 0,
	'../samples/orig/sample0145.png': 0,
	'../samples/orig/sample0202.png': 0,
	'../samples/orig/sample0115.png': 0,
	'../samples/orig/sample0021.png': 0,
	'../samples/orig/sample0141.png': 0,
	'../samples/orig/sample0146.png': 0,
	'../samples/orig/sample0102.png': 0,
	'../samples/orig/sample0135.png': 0,
	'../samples/orig/sample0007.png': 2,
	'../samples/orig/sample0207.png': 0,
	'../samples/orig/sample0211.png': 0,
	'../samples/orig/sample0200.png': 0,
	'../samples/orig/sample0205.png': 0,
	'../samples/orig/sample0110.png': 0,
	'../samples/orig/sample0139.png': 0,
	'../samples/orig/sample0212.png': 0,
	'../samples/orig/sample0035.png': 0,
	'../samples/orig/sample0220.png': 0,
	'../samples/orig/sample0113.png': 0,
	'../samples/orig/sample0003.png': 4,
	'../samples/orig/sample0137.png': 0,
	'../samples/orig/sample0204.png': 0,
	'../samples/orig/sample0209.png': 0,
	'../samples/orig/sample0026.png': 0,
	'../samples/orig/sample0107.png': 0,
	'../samples/orig/sample0002.png': 3,
	'../samples/orig/sample0032.png': 0,
	'../samples/orig/sample0219.png': 0,
	'../samples/orig/sample0009.png': 1,
	'../samples/orig/sample0240.png': 1,
	'../samples/orig/sample0241.png': 1,
	'../samples/orig/sample0242.png': 2,
	'../samples/orig/sample0250.png': 2,
	'../samples/orig/sample0251.png': 1,
	'../samples/orig/sample0252.png': 1,
	'../samples/orig/sample0253.png': 2,
	'../samples/orig/sample0254.png': 1,
	'../samples/orig/sample0255.png': 2,
	'../samples/orig/sample0256.png': 3,
	'../samples/orig/sample0257.png': 3,
	'../samples/orig/sample0258.png': 3,
	'../samples/orig/sample0260.png': 0,
	'../samples/orig/sample0261.png': 0,
	'../samples/orig/sample0262.png': 0,
	'../samples/orig/sample0263.png': 0,
	'../samples/orig/sample0264.png': 0,
	'../samples/orig/sample0265.png': 0,
	'../samples/orig/sample0266.png': 0,
	'../samples/orig/sample0267.png': 0,
	'../samples/orig/sample0268.png': 0,
	'../samples/orig/sample0269.png': 0,
}

ball_cascade = cv2.CascadeClassifier('../samples/cascade_v14.xml')

min_total = 999

print 'scale / min_neighbors / not-found / phantoms / total'
for scale in [1.01, 1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8]:
	for min_neighbors in [4, 5, 6, 7, 8, 9, 10, 11, 12]:
		stat_phantoms = 0
		stat_false_negatives = 0
		for filename in glob.glob('../samples/orig/*.png'):
			fx = cv2.imread(filename)
			fy = cv2.cvtColor(fx, cv2.COLOR_BGR2GRAY)
			balls = ball_cascade.detectMultiScale(fy, scale, min_neighbors)

			found = len(balls)
			expected = samples[filename]
			if found != expected:
				#print 'error, expected', expected
				if found < expected:
					stat_false_negatives += expected - found
				else:
					stat_phantoms += found - expected

			for (x,y,w,h) in balls:
				cv2.rectangle(fx,(x,y),(x+w,y+h),(255,255,0),2)

		mark = ''
		if min_total > stat_false_negatives + stat_phantoms:
			min_total = stat_false_negatives + stat_phantoms
			mark = ' x'
		print '%f %-2d    %-3d %-3d   %-3d%s'%(scale, min_neighbors, stat_false_negatives, stat_phantoms, stat_false_negatives + stat_phantoms, mark)

