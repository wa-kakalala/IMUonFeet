
f = open("data.txt", "r")
start_flag = False
start = False
count_data = 0
for line in f.readlines():
    line = line.strip()
    if line == '55' :
        start_flag = True  
        start = False
        print( count_data)
        count_data = 0
    elif( start_flag and (line in [ str(i) for i in range(50,60) ] + ["5A","5F"])):
        start = True 
        start_flag = False
    elif( start ):
        count_data = count_data + 1

f.close()