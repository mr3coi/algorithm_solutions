import numpy as np
from numpy.random import randint

C = 50
MAX_HEIGHT = 10000
MAX_FENCES = 20000

np.random.seed(4)

with open('./my_input.txt', 'w') as f:
	f.write(str(C) + '\n')
	for c in range(C):
		num_fences = randint(MAX_FENCES+1)
		f.write(str(num_fences) + '\n')

		fences = randint(low=1, high=MAX_HEIGHT+1, size=num_fences)
		f.write(' '.join(fences.astype(str)) + '\n')

