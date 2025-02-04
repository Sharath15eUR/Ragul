
#!/bin/bash

if [ "$#" -ne 3 ]; then
    echo "Usage: $0 <source_directory> <backup_directory> <file_extension>"
    exit 1
fi

source_dir="$1"
backup_dir="$2"
file_ext="$3"

if [ ! -d "$source_dir" ]; then
    echo "Source directory Not found"
    exit 1
fi

if [ ! -d "$backup_dir" ]; then
    mkdir -p "$backup_dir"
    if [ $? -ne 0 ]; then
        echo "Failed !."
        exit 1
    fi
fi

files=($(find "$source_dir" -type f -name "*$file_ext"))

if [ ${#files[@]} -eq 0 ]; then
    echo "No files found with extension $file_ext in $source_dir."
    exit 0
fi

export backup_count=0
total_size=0

echo "Starting backup..."

for file in "${files[@]}"; do
    file_name=$(basename "$file")
    dest_file="$backup_dir/$file_name"
    file_size=$(stat -c%s "$file")
    
    echo "Checking $file_name ($file_size bytes)..."
    
    if [ -f "$dest_file" ]; then
        if [ "$file" -nt "$dest_file" ]; then
            cp "$file" "$dest_file"
            echo "Updated: $file_name"
        else
            echo "Skipping $file_name (already up-to-date)"
            continue
        fi
    else
        cp "$file" "$dest_file"
        echo "Copied: $file_name"
    fi
    
    ((backup_count++))
    ((total_size+=file_size))

done

echo "Backup completed. Generating report..."

# Save report
report_file="$backup_dir/backup_report.log"
echo "Backup Summary:" > "$report_file"
echo "Total files backed up: $backup_count" >> "$report_file"
echo "Total size: $total_size bytes" >> "$report_file"
echo "Backup location: $backup_dir" >> "$report_file"

echo "Backup process finished. Report saved at $report_file"
