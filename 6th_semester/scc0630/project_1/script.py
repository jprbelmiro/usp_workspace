import os
import time

TREE_MAX_DEPTH = [12,15,18]

for depth in TREE_MAX_DEPTH:
	os.system('python main.py '+str(depth))
	time.sleep(5)