import csv


with open('result.csv', newline='') as csvfile:
    reader = csv.reader(csvfile, delimiter=',')
    next(reader)  # 헤더 행 건너뛰기
    rows = list(reader)

# MAC address가 같은 행 찾기
found_pairs = set()
for i in range(len(rows)):
    for j in range(i+1, len(rows)):
        if (rows[i][1] == rows[j][1]) and (rows[i][1] != '') and (rows[i][1] != 'no submit'):
            found_pairs.add((i, j))        
    
# 출력
if found_pairs:
    print("MAC address가 같은 행이 있습니다:")
    for i, j in found_pairs:
        print(f"행 {i+1}과 {j+1}")
else:
    print("MAC address가 같은 행이 없습니다.")
