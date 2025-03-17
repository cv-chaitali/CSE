#!/bin/bash

# result.csv 파일 생성 및 헤더 추가
echo "file_name,MAC address,Kernel version" > result.csv

# "./HW1-files" 디렉토리 아래의 .txt 파일들에 대해서 작업 수행
for file in ./HW1-files/*.txt; do
    # 파일 이름 추출
    file_name=$(basename "$file" .txt)
    echo $file_name
    
    # openssl 명령어 실행
    result=$(openssl rsautl -decrypt -in "$file" -inkey privatekey.pem)
    echo $result 
 
    # 결과에서 MAC address와 Kernel version 추출
    mac_address=$(echo "$result" | awk -F ': ' '{print $2}' | sed -n '1p')
    kernel_version=$(echo "$result" | awk -F ': ' '{print $2}' | sed -n '2p')
    
    echo $mac_address
    echo $kernel_version

    # 결과를 result.csv 파일에 추가
    echo "$file_name,$mac_address,$kernel_version" >> result.csv
done
