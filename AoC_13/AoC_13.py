from functools import cmp_to_key

def compare(line_1, line_2):
  result = 0
  for i in range(0, len(line_1)):
    if i >= len(line_2):
      return 1
    else:
      line_1_is_int = isinstance(line_1[i], int)
      line_2_is_int = isinstance(line_2[i], int)
      if line_1_is_int and line_2_is_int:
        if line_1[i] < line_2[i]:
          return -1
        elif line_1[i] > line_2[i]:
          return 1
      else:
        if not (line_1_is_int or line_2_is_int):
          result = compare(line_1[i], line_2[i])
        elif line_1_is_int:
          result = compare([line_1[i]], line_2[i])
        else:
          result = compare(line_1[i], [line_2[i]])          
        if result != 0:
          return result
  if len(line_1) == len(line_2):
    return 0
  return -1

file_obj = open("C:\\Users\\rbryan\\Documents\\Visual Studio 2019\\Projects\\AoC_2022\\AoC_13\\AoC_13_input.dat", "r")
file_data = file_obj.read()
lines = file_data.splitlines()
file_obj.close()

index = 0
correct = 0
all_items = []
for i in range(0, len(lines), 3):
  index += 1
  line_1 = eval(lines[i])
  all_items.append(line_1)
  line_2 = eval(lines[i + 1])
  all_items.append(line_2)
  
  if compare(line_1, line_2) < 0:
    correct += index    
print("Part One: " + str(correct))

start = eval("[[2]]")
end   = eval("[[6]]")
all_items.append(start)
all_items.append(end)

sorted_items = sorted(all_items, key=cmp_to_key(compare))

start_idx = -1
for idx in range(0, len(sorted_items)):
  if sorted_items[idx] == start:
    start_idx = idx + 1
  if sorted_items[idx] == end:
    print("Part Two: " + str(start_idx * (idx + 1)))
    exit()
