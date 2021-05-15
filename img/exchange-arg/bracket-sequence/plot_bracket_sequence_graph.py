import random, sys
import matplotlib.pyplot as plt
from matplotlib import rc
import math

import matplotlib as mpl
plt.rcParams.update({
  "text.usetex": True
}) # https://matplotlib.org/tutorials/text/usetex.html


# input format:
# x1 y1 x2 y2 color
# input file name should be passed as command argument
# color \in black/red

assert(len(sys.argv) == 2)

input_file = sys.argv[1]
istream = open(input_file)

xx, yy = [0], [0]

while True:
  line = istream.readline()

  if not line:
    break

  data = line.split()

  assert(len(data) == 5)

  x1 = int(data[0])
  y1 = int(data[1])
  x2 = int(data[2])
  y2 = int(data[3])
  col = data[4]

  # xx.append(x1)
  xx.append(x2)
  # yy.append(y1)
  yy.append(y2)

  plt.plot([x1, x2], [y1, y2], ls='-', color=col)

# xx = list(dict.fromkeys(xx))
# yy = list(dict.fromkeys(yy))

for i in range(len(xx)):
  plt.plot([xx[i]], [yy[i]], marker='.', color='black')
# colors: https://matplotlib.org/3.3.2/tutorials/colors/colormaps.html
# https://het.as.utexas.edu/HET/Software/Matplotlib/api/colors_api.html

# plt.scatter(xx, yy, marker='.', color='black')

# plt.show()

plt.axvline(0, ls='-', lw=1, color='black') # https://stackoverflow.com/a/32606487
plt.axhline(0, ls='-', lw=1, color='black') # https://matplotlib.org/3.3.2/api/_as_gen/matplotlib.lines.Line2D.html

plt.axis('scaled') # https://matplotlib.org/3.3.2/api/_as_gen/matplotlib.pyplot.axis.html
plt.yticks(range(min(yy), math.ceil(max(yy)-min(yy))+1)) # https://stackoverflow.com/a/12051323
plt.xticks(range(min(xx), math.ceil(max(xx))+1))
# plt.axis([min(xx)-1, max(xx)+1, min(yy)-1, max(yy)+1])
plt.axis([min(xx)-1, max(xx)+1, min(yy)-1, max(yy)-min(yy)+1])
# plt.axis('off')

plt.savefig("output.svg", bbox_inches = 'tight', pad_inches = 0) # https://stackoverflow.com/a/27227718