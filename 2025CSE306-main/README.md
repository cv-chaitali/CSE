> 채점 결과 파일 : [result.txt](https://github.com/CELL-DGIST/2023CSE306/blob/main/result.csv)  
> 복호화 채점 스크립트 : [score.sh](https://github.com/CELL-DGIST/2023CSE306/blob/main/score.sh)  
> MAC주소 중복 체크 : [cheat-check](https://github.com/CELL-DGIST/2023CSE306/blob/main/cheat-check.py)  


# How to use

## 1. Encrypt

- Compile *kerneltest.c* with options  
  ```
  $ gcc -o kernelcheck kerneltest.c -lcrypto -lz -ldl -static-libgcc -lssl
  ```
  
- Run *kernelcheck* (학생 배포용)  
  ```
  $ chmod 755 kernelcheck
  $ ./kernelcheck
  ```

- Check the encrypted result
  ```
  $ xxd encrypted_result.txt 
  ```
  <details>
  <summary> encrypted_result.txt 예시 보기</summary>
  
    ```
    00000000: 7ebb 68f8 8007 53a8 e4e5 1778 cb73 4f47  ~.h...S....x.sOG
    00000010: 6d5d 81a3 76eb d249 a130 9df1 a126 5f34  m]..v..I.0...&_4
    00000020: edf2 c870 9d3c 4ab7 3014 c924 d8b8 7ee4  ...p.<J.0..$..~.
    00000030: 5173 7910 6896 d494 0e56 6f33 9c98 d748  Qsy.h....Vo3...H
    00000040: 4ae3 5563 f894 c98c 851c edf6 88b6 50dd  J.Uc..........P.
    00000050: 5737 28a5 41ef 11bd 8e0f fe57 e07a 8c86  W7(.A......W.z..
    00000060: 8edd efd6 d064 dfa2 1136 668b d08e 6155  .....d...6f...aU
    00000070: 3560 a70d 04aa 3c95 c938 bc9b a2c7 62cf  5`....<..8....b.
    00000080: a4ae edae bd7e b8d5 c7e5 fd6e ba06 a92e  .....~.....n....
    00000090: 482b 31a3 a5a1 ad1a 0b31 ed9e d65a e3c1  H+1......1...Z..
    000000a0: b261 bae0 7551 fbaa 1a98 0e2e 4ac4 26ca  .a..uQ......J.&.
    000000b0: a4b8 28c1 09cb f9ef 7f35 578e 249e ce17  ..(......5W.$...
    000000c0: c1e2 2002 8e1f 19de 22ec 41b2 0470 1ef7  .. .....".A..p..
    000000d0: d775 ad7f 0cb8 5f54 c139 d93a 5b86 6d46  .u...._T.9.:[.mF
    000000e0: 36a6 3ed2 e90b b5b6 3c3a 1399 047a c2e2  6.>.....<:...z..
    000000f0: 324b c792 fd67 decf 183b 58e1 971b c578  2K...g...;X....x
    ```
  </details>





<br/> 

## 2. Decrypt



  ```
  $ openssl rsautl -decrypt -in encrypted_result.txt -inkey privatekey.pem -out decrypted_result.txt
  ```


- Check the encrypted result  
  ```
  $ cat decrypted_result.txt 
  ```
  
  
    <details>
  <summary> 예시 보기</summary>
  
    ```
    MAC address: dc:a6:32:9e:3b:2d 
    Kernel version: 5.15.92CSE2023-v8+ #1 SMP PREEMPT Fri Mar 17 18:54:22 KST 2023
    ```
  </details>




