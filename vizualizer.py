import matplotlib.mlab as mlab
import matplotlib.pyplot as plt

n = int(input())

infected = []
recovered = []

for i in range(n):
	s = input()
	count1 = 0
	count2 = 0
	for c in s:
		if c == '*': count1 += 1
		else: count2 += 1

	infected.append(count1)
	recovered.append(count2 + count1)

plt.axis([0, n + 1, 0, 60])
plt.fill_between([i for i in range(1, n + 1)], recovered, [0 for i in range(1, n + 1)], interpolate=True, color='r')
plt.fill_between([i for i in range(1, n + 1)], infected, [0 for i in range(1, n + 1)], interpolate=True, color='b')
plt.show()