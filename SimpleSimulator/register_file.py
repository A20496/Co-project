#-------------------CONVERSIONS----------------------#

def bintodec(bin_str):
    # given binary number is a string 
    return int(bin_str,2)

def dectobin(dec):
    binary=format(dec,'b')
    bin_num="0"*(16-len(binary))+binary
    return bin_num 

#------------- INITIALISING REGISTER VALUES -----------#

regs={
    "000":"0000000000000000",
    "001":"0000000000001000",
    "010":"0000000000000000",
    "011":"0000000000000001",
    "100":"0000000000000000",
    "101":"0000000000000000",
    "110":"0000000000000000",
    "111":"0000000000000000" 
    }

#--------------- REGISTER FUNCTIONS ------------------- #

''' input a register number and fetching its value in binary '''

def fetch_val(register_dict,register_no):
    
    return register_dict[register_no]


''' updating the value given in binary of the register number '''

def update_val(register_dict,register_no,value):

    register_dict[register_no]=value


''' reseting the value of register to zero '''

def reset_val(register_dict,register_no):

    register_dict[register_no]='0000000000000000'


''' printing the values of all the registers '''

def register_dump(register_dict):

    print(register_dict['000'],end=" ")
    print(register_dict['001'],end=" ")
    print(register_dict['010'],end=" ")
    print(register_dict['011'],end=" ")
    print(register_dict['100'],end=" ")
    print(register_dict['101'],end=" ")
    print(register_dict['110'],end=" ")
    print(register_dict['111'],end=" ")



#-------------------- FLAG FUNCTIONS ------------------- #
    # _ _ _ _ _ _ _ _ _ _ _  __ __ __ __ __
    # 0 0 0 0 0 0 0 0 0 0 0  0  V  L  G  E
    # _ _ _ _ _ _ _ _ _ _ _  __ __ __ __ __
    # 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15

def set_flag(register_dict,index):
    slice1=register_dict['111'][0:index]
    slice2=register_dict['111'][index+1:]
    flags=slice1+'1'+slice2
    register_dict['111']=flags 

def check_overflow(dec,register_dict,register_no):
    if (dec>65535 or dec<0):
        set_flag(register_dict,12)
        if (dec<0):
            update_val(register_dict,register_no,'0000000000000000')

    else:
        update_val(register_dict,register_no,dectobin(dec))

def check_lessThan(n1,n2,register_dict):
    if(n1<n2):
        set_flag(register_dict,13)

def check_greaterThan(n1,n2,register_dict):
    if(n1>n2):
        set_flag(register_dict,14)

def check_equal(n1,n2,register_dict):
    if(n1==n2):
        set_flag(register_dict,15)