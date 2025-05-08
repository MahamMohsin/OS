#!/bin/bash

FILE_NAME="records.txt"
DATE_FORMAT="^[0-9]{4}-[0-9]{2}-[0-9]{2}$"

add_record() {
    echo -n "Enter Name: "
    read name

    echo -n "Enter Date (YYYY-MM-DD): "
    read date

    if ! [[ $date =~ $DATE_FORMAT ]]; then
        echo "Invalid date format! Use YYYY-MM-DD."
        return
    fi

    echo -n "Enter Category/Status (Shift type, Expense category, Present/Absent): "
    read category

    echo "$name|$date|$category" >> "$FILE_NAME"
    echo "Record added successfully!"
}

view_records() {
    if [ ! -s "$FILE_NAME" ]; then
        echo "No records found!"
        return
    fi
    echo "All Records:"
    cat "$FILE_NAME"
}

search_record() {
    echo -n "Enter Name to Search: "
    read name
    grep -i "^$name|" "$FILE_NAME" || echo "No records found for $name."
}

modify_record() {
    echo -n "Enter Name to Modify: "
    read name
    grep -i "^$name|" "$FILE_NAME" > /dev/null
    if [ $? -ne 0 ]; then
        echo "No record found for $name."
        return
    fi

    echo "Enter new Date (YYYY-MM-DD): "
    read new_date
    if ! [[ $new_date =~ $DATE_FORMAT ]]; then
        echo "Invalid date format!"
        return
    fi

    echo "Enter new Category/Status: "
    read new_category

    sed -i "/^$name|/c\\$name|$new_date|$new_category" "$FILE_NAME"
    echo "Record updated successfully!"
}

summary_report() {
    echo "Summary Report:"
    awk -F '|' '{count[$3]++} END {for (i in count) print i, ":", count[i]}' "$FILE_NAME"
}

while true; do
    echo "1. Add Record"
    echo "2. View Records"
    echo "3. Search Record by Name"
    echo "4. Modify Record"
    echo "5. Summary Report"
    echo "6. Exit"
    echo -n "Choose an option: "
    read choice

    case $choice in
        1) add_record ;;
        2) view_records ;;
        3) search_record ;;
        4) modify_record ;;
        5) summary_report ;;
        6) echo "Exiting..."; exit ;;
        *) echo "Invalid option! Try again." ;;
    esac
done

