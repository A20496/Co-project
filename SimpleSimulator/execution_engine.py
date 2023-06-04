from register_file import *
from memory_file import *

pc = "0000000"                 #will store memory address

def typeA(inst,register_dict):

    update_val(register_dict,'111','0000000000000000')

    ''' 
    fetching value of source registers and updating the value of destination register 
    after cheching overflow 
    ''' 
    val1_dec=fetch_val(register_dict,inst[10:13])
    val2_dec=fetch_val(register_dict,inst[13:16])
    val1_bin=bintodec(val1_dec)
    val2_bin=bintodec(val2_dec)

    #ADD 
    if inst[0:5]=='00000':
        dec=val1_dec+val2_dec
        check_overflow(dec,register_dict,inst[7:10])

    #SUBTRACT
    elif inst[0:5]=='00001':
        dec=val1_dec-val2_dec
        check_overflow(dec,register_dict,inst[7:10])
    
    #MULTIPLY
    elif inst[0:5]=='00110':
        dec=val1_dec*val2_dec
        check_overflow(dec,register_dict,inst[7:10])
    
    #OR 
    elif inst[0:5]=='01011':
        result=val1_bin | val2_bin
        result=bin(result)[2:]
        update_val(register_dict,inst[7:10],result)
    
    #AND
    elif inst[0:5]=='01100':
        result=val1_bin & val2_bin
        result=bin(result)[2:]
        update_val(register_dict,inst[7:10],result)
    
    #XOR
    elif inst[0:5]=='01010':
        result=val1_bin ^ val2_bin
        result=bin(result)[2:]
        update_val(register_dict,inst[7:10],result)


def typeE(inst, register_dict, pc):
    if inst[0:5] == "01111":
        return inst[9:]
    if inst[0:5] == "11100":
        if regs[111][13] == "1":
            return inst[9:]
        else:
            return dectobin(bintodec(pc) + 1)
    if inst[0:5] == "11101":
        if regs[111][14] == "1":
            return inst[9:]
        else:
            return dectobin(bintodec(pc) + 1)
    if inst[0:5] == "11111":
        if regs[111][15] == "1":
            return inst[9:]
        else:
            return dectobin(bintodec(pc) + 1)
        

def execute(memory_inst,regs):   # list of memory instructions
    
    #making the lists of the op codes and defining the types of function

    a = ["00000","00001","00110","01010","01011","01100"]
    b = ["00010","01000","01001"]
    c = ["00011","00111","01101","01110"]
    d = ["01000","01001"]
    e = ["01111","11100","11101","11111"]
    f = ["11010"] 
    
    while True:
        to_exec = bintodec(pc) 
        inst = memory_inst[to_exec]
        
        if inst[0:5] in a:
            typeA(inst,regs)
            pc = dectobin(bintodec(pc) + 1)
            print(pc, end=" ")
            register_dump(regs)
            

        # if inst[0:5] in b:
        #     typeB(inst,regs)
        #     pc = dectobin(bintodec(pc) + 1)
        #     print(pc, end=" ")
        #     register_dump(regs)
            

        # if inst[0:5] in c:
        #     typeC(inst,regs)
        #     pc = dectobin(bintodec(pc) + 1)
        #     print(pc, end=" ")
        #     register_dump(regs)
            

        # if inst[0:5] in d:
        #     typeD(inst,regs)
        #     pc = dectobin(bintodec(pc) + 1)
        #     print(pc, end=" ")
        #     register_dump(regs)
            
        
        if inst[0:5] in e:
            pc = typeE(inst,regs,pc)
            print(pc, end=" ")
            register_dump(regs)
            
        
        # if inst[0:5] in f:
        #     typeF(inst,regs)
        #     memory_dump(memory_inst)
        #     break