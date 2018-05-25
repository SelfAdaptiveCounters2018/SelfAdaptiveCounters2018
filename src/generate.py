# -*- coding: utf-8 -*-
#This python code is used to generate a dataset that is Zipf distributed.(a>1)

import numpy as np
a = 2 # Zipf distribution's parameter
s = np.random.zipf(a, 300000000)
s1=s.tolist()

for i in range(0,300000000):
    while(s1[i]>1500):         # ensuring flow size is less than a number
        s1[i]=np.random.zipf(a)
    
print(max(s1))
with open("30000_0000_a_2_n_1500_test.txt",'w') as file:         # write into file
    for i in s1:
        write_str='%d '%(i)
        file.write(write_str)
        if i%5==0:
            write_n='\n'
            file.write(write_n)
            

    
    
