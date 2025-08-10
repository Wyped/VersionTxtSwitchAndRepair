#!/bin/bash

# Usage: ./calculateFwSeriesRanges.sh path to firmware_versions.h

if [ $# -ne 1 ]; then
    echo "Usage: $0 <path to firmware_versions.h>"
    exit 1
fi

FW_FILE="$1"

if [ ! -f "$FW_FILE" ]; then
    echo "Error: File '$FW_FILE' not found."
    exit 2
fi

# Extract just the version names in order of appearance, ignoring line numbers
grep -o '{ "[0-9]\+\.[0-9]\+' "$FW_FILE" | sed 's/{ "//' > versions.txt

echo "Series ranges (start,end) in firmware_versions[]:"

last_major=""
start_idx=""
count=0

while read ver; do
    major=$(echo "$ver" | cut -d. -f1)
    if [[ -z "$last_major" ]]; then
        last_major="$major"
        start_idx="$count"
    elif [[ "$major" != "$last_major" ]]; then
        end_idx=$((count-1))
        echo "$last_major.xx: $start_idx to $end_idx"
        last_major="$major"
        start_idx="$count"
    fi
    count=$((count+1))
done < versions.txt

# Output last series
end_idx=$((count-1))
echo "$last_major.xx: $start_idx to $end_idx"

rm versions.txt