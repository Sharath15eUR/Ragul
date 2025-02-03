PID=$(ps aux --sort=-%mem | awk 'NR==2 {print $2}')
echo "Killing process with PID: $PID"
kill "$PID"
