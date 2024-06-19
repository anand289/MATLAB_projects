def func(a,b):
  return a+b

count = 0;
str = "This is python on the online object on on on"
print(str[0])
print('This is python!!')

i = range(0,10)

for item in i:
  print(item)

p = func(4,7)
print(p)

print(str[0:3])

for i in range(1,len(str)):
  if ((str[i] == "n") and (str[i-1] == "o")):
    count += 1

print(count)
