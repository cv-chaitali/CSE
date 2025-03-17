# zip file should be handled by manually


targetdir="./HW1"

# parsing files
for file in "$targetdir"/*; do
    length=${#file}
    if [ $length != 55 ]; then
        cp "$file" ./HW1_parsed/"${file:52}"
    fi
done