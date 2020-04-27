#!/usr/bin/env python
# coding: utf-8

# In[4]:

import sys
import re
import numpy as np

if len(sys.argv)==1:
    fo_n = "matscan_ave_theta.dat"
    fi_n = "pipe_only.log"
elif len(sys.argv)==2:
    fi_n = sys.argv[1];
    fo_n = fi_n.split(".")[0] + '_ave_theta.dat'
else:
    fi_n = sys.argv[1]
    fo_n = sys.argv[2]

fo = open(fo_n, "w")
with open(fi_n,'r') as f:
    for line in f:
        z = re.search(r"ave. for theta =", line)
        if z:
            for k in [line.split()[i] for i in (4,6,7,8)]:
                fo.write(k+" ")
            fo.write('\n')
fo.close()


# In[ ]:




