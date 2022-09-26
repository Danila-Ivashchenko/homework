import matplotlib
import matplotlib.pyplot as plt

file = open("ping.txt", "r")

values = []

for string in file.readlines()[1:-4]:
    time = string.split(' ')[-2].split('=')[-1]
    values.append(float(time)/2)

file.close()

keys = []
groups = {}

for value in values:
    if value in keys:
        groups[value] += 1
    else:
        keys += [value]
        groups[value] = 1

fig = plt.figure(figsize=(6, 4))
ax = fig.add_subplot()

x = keys
y = [groups[key] for key in keys]
ax.grid()

print(keys)
ax.hist(values, 100)

plt.show()
