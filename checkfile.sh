read -p "Enter filename: " filename

#means file found
if [ -f "$filename" ];then
        #means not empty
	if [ -s "$filename" ];then
	count=$(wc -l < "$filename") #counts and return num to count
	echo "file '$filename' exists and has lines: '$count'"
	else
	echo "file is empty"
	fi
else
echo "file doesnt exist, creating it."
touch "$filename"
echo "writing to file" > "$filename" 
echo "This is a new file created on $(date)." >> "$filename"
echo "Default content written to '$filename'."
fi
