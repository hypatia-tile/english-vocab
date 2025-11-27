#!/bin/bash

# Define the input file path
INPUT_FILE="input.txt"

# Create an empty array
declare -a lines_array

# Read the file line by line into the array using mapfile
# -t option removes trailing newline characters from each line
readarray -t lines_array < "$INPUT_FILE"

# Now you can access the elements of the array
# For example, print all lines:
for line in "${lines_array[@]}"; do
    echo "$line"
done

# Access a specific line (e.g., the first line at index 0):
echo "First line: ${lines_array[0]}"


word="${lines_array[0]}"
part_of_speech="${lines_array[1]}"
meaning="${lines_array[2]}"
example_sentence="${lines_array[3]}"

json_output=$(jq -n \
  --arg word "$word" \
  --arg part_of_speech "$part_of_speech" \
  --arg meaning "$meaning" \
  --arg example_sentence "$example_sentence" \
  '{word: $word, part_of_speech: $part_of_speech, meaning: $meaning, example_sentence: $example_sentence}')

echo "${json_output}" >> "words/words.json"
