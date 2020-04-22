# python3
# Generate random text files
import random
import string
import sys

def LoadArgs():
    default_line_number = 10000
    default_file_name = 'loggerInput'
    default_line_width_min = 100
    default_line_width_max = 300
    
    list_len = len(sys.argv)
    if list_len > 1 :
        default_line_number = int(sys.argv[1])
    if list_len > 2 :
        default_file_name = str(sys.argv[2])
    if list_len > 3 :
        default_line_width_min = int(sys.argv[3]);
    if list_len > 4 :
        default_line_width_max = int(sys.argv[4]);

    if len(default_file_name) <= 0 or default_line_number <= 0 or default_line_width_min < 0 or default_line_width_max < default_line_width_min:
        return False, [""]

    argList = [default_line_number, default_file_name, default_line_width_min, default_line_width_max]
    print(argList)
    return True, argList

def printUsage():
    print("usage: python3 script_name lineNumber[10000] fileName[loggerInput] minLineWidth[100] MaxLineWidth[300]")
    print("You can specify one or all option, default values will be taken")

def GenerateTestFile(argList):
    line_number = argList[0]
    file_name = argList[1]
    line_width_min = argList[2]
    line_width_max = argList[3]

    f = open(file_name, "w+")

    letters = string.ascii_letters + " "
    for i in range(line_number):
        length = random.randrange(line_width_min, line_width_max, 1)
        wrdLin = ''.join(random.choice(letters) for j in range(length))
        f.write(wrdLin)
        f.write('\n')

    f.close()

if __name__ == '__main__':
    printUsage()
    ret,argList = LoadArgs()
    if ret==True:
        GenerateTestFile(argList)
    sys.exit()
