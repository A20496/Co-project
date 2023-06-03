from register_file import *

'''
        TYPE A:
        add:00000
        sub:00001
        mul:00110
        xor:01010
        or:01011
        and:01100

        TYPE A:
        5-BIT OP|2-BIT UNUSED|3BIT REG1|REG2|REG3

        TYPE B:
        5-BIT OP|3-BIT REG1|8BIT IMMEDIATE

        TYPE C:
        5-BIT OP|5-BIT UNUSED|3-BIT REG1|REG2

        TYPE D:
        5-BIT OP|3-BIT REG1|8-BIT MEMORY ADDRESS

        TYPE E:
        5-BIT OP|3_UNUSED|8-BIT MEMORY ADDRESS

        TYPE F:
        5-BIT OP|11-BIT UNUSED
        '''

def typeA(inst,register_dict):

    reset_val(register_dict,'111')

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


    print(register_dict[inst[7:10]])

def execute(memory_inst,regs):   # list of memory instructions
    
    #making the lists of the op codes and defining the types of function

    a = ["00000","00001","00110","01010","01011","01100"]
    b = ["00010","01000","01001"]
    c = ["00011","00111","01110"]
    d = ["00100","00101"]
    e = ["01111","10000","10001","10010"]
    f = ["10011"] 

    for inst in memory_inst:
        if inst[0:5] in a:
            typeA(inst,regs)

        '''if inst[0:5] in b:
            typeB(inst,regs)

        if inst[0:5] in c:
            typeC(inst,regs)

        if inst[0:5] in d:
            typeD(inst,regs)
        
        if inst[0:5] in e:
            typeE(inst,regs)

        if inst[0:5] in f:
            typeF(inst,regs)'''