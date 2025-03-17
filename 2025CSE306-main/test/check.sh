ls ./HW1_parsed | grep .txt > temp.txt

file="./temp.txt"

while IFS= read -r line; do
    # echo $line
    # openssl rsautl -decrypt -in $line -inkey privatekey.pem -out ./DEC/decrypted_result_$line.txt 2>/dev/null
    openssl rsautl -decrypt -in ./HW1_parsed/$line -inkey privatekey.pem -out ./DEC/decrypted_result_$line.txt 2>/dev/null
done < "$file"