import sqlite3
import os

print("Module loaded; activating Python super powers in 3 2 1..")

def listDir():
    dirs = '\n '.join(os.listdir())
    return dirs

def parse(string):
    #clean string starts empty
    cleanedString = ""

    #if there's more than one char in string
    if(len(string) > 0):
        #from immutable string to mutable list
        sarray = list(string)
        #get each individual char
        for key, char in enumerate(sarray):
            #if special chars
            if (sarray[key] == "\\"):
                #if delete char
                if (sarray[key+1] == "d" and len(sarray) >= 3):
                    #delete the char that needs deleted, and delete the delete instructions
                    del sarray[key+1]
                    del sarray[key]
                    del sarray[key - 1]
                #ignore carriage returns, they're handled by texture manager
                elif (sarray[key+1] == "n"):
                    continue

        #string list cleaned, implode list to string and append it to return list
        cleanedString = ''.join(sarray)
    
    #string is at index 0; command list at index 1 0; params at index 1 1
    sarray = (cleanedString, stringToCommand(cleanedString))
    #debug mode
    #print(sarray)
    return sarray

def stringToCommand(string):
    #execute script if string contains
    executeScript = string.find("\n")
    #sanitize string
    found = 0
    while (found != -1):
        found = string.find("\n")
        #add whitespace before and after char for splitting
        string = string.replace("\n", " /n ")
    #split string into words
    sarray = string.split(" ")
    #holds int commands
    commands = list()
    #holds parameters
    params = list()
    #holds error codes
    errors = list()
    #debug mode
    print(sarray)

    #check each word for valid commands
    for key, word in enumerate(sarray):
        if executeScript != -1:
            if (word.lower() == "CreatePCB".lower()):
                #bypassed temporarily
                continue;
                #command + 3 parameters and execute command
                if (sarray[key+1]):
                    if (isinstance(sarray[key+1], str) and not sarray[key+1].isdigit()):
                        #append process name
                        params.append(sarray[key+1])
                    else:
                        #error code not a string
                        errors.append(2)
                if (sarray[key+2]):
                    if (sarray[key+2].isdigit()):
                        if (int(sarray[key+2]) >= -127 and int(sarray[key+2]) <= 127):
                            #append process priority
                            params.append(sarray[key+2])
                        else:
                            #error code int range exceeded
                            errors.append(4)
                    else:
                        #error code not an int
                        errors.append(3);
                if (sarray[key+3]):
                    if (sarray[key+3].isdigit()):
                        #pcb class is either system or app (1 or 2)
                        if (int(sarray[key+3]) in (1,2)):
                            #append process class
                            params.append(sarray[key+3])
                        else:
                            #error code int range exceeded
                            errors.append(4)
                    else:
                        #error code not an int
                        errors.append(3)
                commands.append(1)
            elif (word.lower() == "DeletePCB".lower()):
                #bypassed temporarily
                #continue;
                if (sarray[key+1]):
                    if (isinstance(sarray[key+1], str) and not sarray[key+1].isdigit()):
                        #append process name to be deleted
                        params.append(sarray[key+1])
                    else:
                        #error code not a string
                        errors.append(2)
                commands.append(2)
            elif (word.lower() == "Block".lower()):
                #bypassed temporarily
                continue;
                if (sarray[key+1]):
                    if (isinstance(sarray[key+1], str) and not sarray[key+1].isdigit()):
                        #append process name to be blocked
                        params.append(sarray[key+1])
                    else:
                        #error code not a string
                        errors.append(2)
                commands.append(3)
            elif (word.lower() == "Unblock".lower()):
                #bypassed temporarily
                continue;
                if (sarray[key+1]):
                    if (isinstance(sarray[key+1], str) and not sarray[key+1].isdigit()):
                        #append process name to be unblocked
                        params.append(sarray[key+1])
                    else:
                        #error code not a string
                        errors.append(2)
                commands.append(4)
            elif (word.lower() == "Suspend".lower()):
                if (sarray[key+1]):
                    if (isinstance(sarray[key+1], str) and not sarray[key+1].isdigit()):
                        #append process name to be unblocked
                        params.append(sarray[key+1])
                    else:
                        #error code not a string
                        errors.append(2)
                commands.append(5)
            elif (word.lower() == "Resume".lower()):
                if (sarray[key+1]):
                    if (isinstance(sarray[key+1], str) and not sarray[key+1].isdigit()):
                        #append process name to be unblocked
                        params.append(sarray[key+1])
                    else:
                        #error code not a string
                        errors.append(2)
                commands.append(6)
            elif (word.lower() == "SetPriority".lower()):
                if (sarray[key+1]):
                    if (isinstance(sarray[key+1], str) and not sarray[key+1].isdigit()):
                        #append process name
                        params.append(sarray[key+1])
                    else:
                        #error code not a string
                        errors.append(2)
                if (sarray[key+2]):
                    if (sarray[key+2].isdigit()):
                        if (int(sarray[key+2]) >= -127 and int(sarray[key+2]) <= 127):
                            #append process priority
                            params.append(sarray[key+2])
                        else:
                            #error code int range exceeded
                            errors.append(4)
                    else:
                        #error code not an int
                        errors.append(3);
                commands.append(7)
            elif (word.lower() == "ShowPCB".lower()):
                if (sarray[key+1]):
                    if (isinstance(sarray[key+1], str) and not sarray[key+1].isdigit()):
                        #append process name
                        params.append(sarray[key+1])
                    else:
                        #error code not a string
                        errors.append(2)
                commands.append(8)
            elif (word.lower() == "ShowAll".lower()):
                commands.append(9)
            elif (word.lower() == "ShowReady".lower()):
                commands.append(10)
            elif (word.lower() == "ShowBlocked".lower()):
                commands.append(11)
            elif (word.lower() == "ShowRunning".lower()):
                commands.append(14)
            elif (word.lower() == "Hide".lower()):
                commands.append(12)
            elif (word.lower() == "SJF".lower()):
                if (sarray[key+1]):
                    if (isinstance(sarray[key+1], str) and not sarray[key+1].isdigit()):
                        #append file name to be opened
                        params.append(sarray[key+1])
                    else:
                        #error code not a string
                        errors.append(2)
                commands.append(13)
            elif (word.lower() == "FIFO".lower()):
                if (sarray[key+1]):
                    if (isinstance(sarray[key+1], str) and not sarray[key+1].isdigit()):
                        #append file name to be opened
                        params.append(sarray[key+1])
                    else:
                        #error code not a string
                        errors.append(2)
                commands.append(18)
            elif (word.lower() == "STCF".lower()):
                if (sarray[key+1]):
                    if (isinstance(sarray[key+1], str) and not sarray[key+1].isdigit()):
                        #append file name to be opened
                        params.append(sarray[key+1])
                    else:
                        #error code not a string
                        errors.append(2)
                commands.append(19)
            elif (word.lower() == "FPPS".lower()):
                if (sarray[key+1]):
                    if (isinstance(sarray[key+1], str) and not sarray[key+1].isdigit()):
                        #append file name to be opened
                        params.append(sarray[key+1])
                    else:
                        #error code not a string
                        errors.append(2)
                commands.append(20)
            elif (word.lower() == "RR".lower()):
                if (sarray[key+1]):
                    if (isinstance(sarray[key+1], str) and not sarray[key+1].isdigit()):
                        #append file name to be opened
                        params.append(sarray[key+1])
                    else:
                        #error code not a string
                        errors.append(2)
                if (sarray[key+2]):
                    if (sarray[key+2].isdigit()):
                        if (int(sarray[key+2]) >= 0 and int(sarray[key+2]) <= 10):
                            #append time quantum
                            params.append(sarray[key+2])
                        else:
                            #error code int range exceeded
                            errors.append(4)
                    else:
                        #error code not an int
                        errors.append(3);
                commands.append(21)
            elif (word.lower() == "MLFQ".lower()):
                if (sarray[key+1]):
                    if (isinstance(sarray[key+1], str) and not sarray[key+1].isdigit()):
                        #append file name to be opened
                        params.append(sarray[key+1])
                    else:
                        #error code not a string
                        errors.append(2)
                if (sarray[key+2]):
                    if (sarray[key+2].isdigit()):
                        if (int(sarray[key+2]) >= 0 and int(sarray[key+2]) <= 10):
                            #append time quantum
                            params.append(sarray[key+2])
                        else:
                            #error code int range exceeded
                            errors.append(4)
                    else:
                        #error code not an int
                        errors.append(3);
                if (sarray[key+3]):
                    if (sarray[key+3].isdigit()):
                        if (int(sarray[key+3]) >= 0 and int(sarray[key+3]) <= 10):
                            #append time quantum
                            params.append(sarray[key+3])
                        else:
                            #error code int range exceeded
                            errors.append(4)
                    else:
                        #error code not an int
                        errors.append(3);
                if (sarray[key+4]):
                    if (sarray[key+4].isdigit()):
                        if (int(sarray[key+4]) >= 0 and int(sarray[key+4]) <= 10):
                            #append time quantum
                            params.append(sarray[key+4])
                        else:
                            #error code int range exceeded
                            errors.append(4)
                    else:
                        #error code not an int
                        errors.append(3);
                commands.append(22)
            elif (word.lower() == "Dispatch".lower()):
                commands.append(15)
            elif (word.lower() == "ShowCompleted".lower()):
                commands.append(16)  
            elif (word.lower() == "ClearCompleted".lower()):
                commands.append(17)  
    #return commands as a list
    #print(commands)
    return (commands, params, errors)