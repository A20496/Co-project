import sys
from register_file import *
from execution_engine import *

# --------------- INITIALISING MEMORY ---------------- #

memory_inst = []

while True:
    line = sys.stdin.readline().rstrip('\n')
    if not line:
        break
    memory_inst.append(line)

# remaining zeroes 
for i in range(128-len(memory_inst)):  
    memory_inst.append('0000000000000000')

print(memory_inst)

