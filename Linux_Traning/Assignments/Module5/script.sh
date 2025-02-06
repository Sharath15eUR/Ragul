#!/bin/bash

# code for searching the keyword if the directory is given
fun_search() {
    local dir=$1
    local key=$2

    if [ ! -d "$dir" ]; then
        error_log "The directory does not exist"
        echo "The directory does not exist"
        exit 1
    fi

    for file in "$dir"/*; do
        if [ -d "$file" ]; then
            fun_search "$file" "$key"
        elif [ -f "$file" ]; then
            if grep -qi "$key" "$file"; then
              echo "Keyword  found in: $file" 
            fi
        fi
    done
}

# code for searching the keyword if the file is given
file_search() {
    local files=$1
    local key=$2

    if [ ! -f "$files" ]; then
        error_log "The file does not exist. Provide the correct file."
        exit 1
    fi
    grep -qi "$key" "$files" && echo "Keyword $key found in $files"
}

# function performs the error logging
error_log() {
    echo "Error!!!: $1" >> error.log
} 

# function which performs the help operation
Help() {
    cat << END

Options:
    -d <directory>: Directory to search
    -k <keyword>: Keyword to search
    -f <file>: File to search directly
    --help: Display the help menu

Example:
    # Recursively search a directory for a keyword
    ./file_analyzer.sh -d <directory_name> -k <keyword_to_search>

    # Search for a keyword in a file
    ./file_analyzer.sh -f <file_name> -k <keyword_to_search>

    # Display the help menu
    ./file_analyzer.sh --help

END
}

# Special Parameters
echo "File Name: $0"
echo "No.of Args: $#"
echo "Args: $@"
echo "PID: $$"

# command-line arguments using getopts
while getopts ":d:f:k:" args; do
    case "$args" in
        d) dir="$OPTARG" ;;
        f) files="$OPTARG" ;;
        k) key="$OPTARG" ;;
        *) error_log "Invalid arguments"
           echo "Provide the proper arguments please refer the below"
           Help
           exit 1 ;;
    esac
done

# Display help 
if [[ $1 == '--help' ]]; then
    Help
    exit 0
fi

# Check if the keyword is given or not
if [[ -z "$key" ]]; then
    error_log "Key should not be empty. Use --help for details."
    exit 1
fi

# Validate the keyword using a regular expression
if ! echo "$key" | grep -Eq '^[a-zA-Z0-9._ @-]+$'; then
    error_log "Keywords are invalid."
    exit 1
fi

# Check whether file exist or not
if [[ -n "$files" && ! -f "$files" ]]; then
    error_log "File '$files' does not exist."
    exit 1
fi

# Determine whether to perform directory or file search
if [[ -n "$dir" ]]; then
    fun_search "$dir" "$key"
elif [[ -n "$files" ]]; then
    file_search "$files" "$key"
else
    error_log "No target specified. Please provide a directory (-d) or a file (-f) to search."
    Help
    exit 1
fi