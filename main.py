from read_from_file import read_from_file
from filter_exercises import filter_exercises
# Read from file
sorted_data = read_from_file("data.csv")
filtered_data = filter_exercises(sorted_data, "exercises.txt")
print(filtered_data)
# Analyze Data

# Output to Markdown