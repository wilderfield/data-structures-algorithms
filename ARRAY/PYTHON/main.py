

SIZE = 8

array = [] # Python actually calls this a list, and it is a native python type

for i in range(SIZE):
  val = i*i
  print("Setting array/list element %d to %d" %(i,val))
  array.append(val) # Append to list, similar to vector.push_back
  
for i in range(SIZE):
  val = array[i]
  print("Getting array/list element %d as %d" %(i,val))

# Can also access all items in the list without knowing the size
for i,val in enumerate(array):
  print("Getting array/list element %d as %d" %(i,val))

# Can also access all items in the list without using index
for val in array:
  print(val)

# Clearly Python is sick
