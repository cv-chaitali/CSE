echo "file_name,MAC address,Kernel version" > result.csv

dir="./DEC"
for file in "$dir"/*; do
    # mac_address=$(cat "$file" | awk -F ': ' '{print $2}' | sed -n '1p')
    # kernel_version=$(cat "$file" | awk -F ': ' '{print $2}' | sed -n '2p')

    mac_address=$(cat $file | sed -n '1p' | awk -F ': ' '{print $2}')
    kernel_version=$(cat $file | sed -n '2p' | awk -F ': ' '{print $2}')
    filename=$(basename $file)

    echo "$filename,$mac_address,$kernel_version" >> result.csv
done