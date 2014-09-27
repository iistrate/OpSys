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
                        #pcb class is either system or app (0 or 1)
                        if (sarray[key+2] in (0,1)):
                            #append process class
                            params.append(sarray[key+2])
                        else:
                            #error code int range exceeded
                            errors.append(4)
                    else:
                        #error code not an int
                        errors.append(3)
                if (sarray[key+3]):
                    if (sarray[key+3].isdigit()):
                        if (sarray[key+3] >= -127 and sarray[key+3] <= 127):
                            #append process priority
                            params.append(sarray[key+3])
                        else:
                            #error code int range exceeded
                            errors.append(4)
                    else:
                        #error code not an int
                        errors.append(3);
                commands.append(1)
            elif (word.lower() == "DeletePCB".lower()):
                if (sarray[key+1]):
                    #append process name to be deleted
                    params.append(sarray[key+1])
                commands.append(2)
            elif (word.lower() == "Block".lower()):
                commands.append(3)
            elif (word.lower() == "Unblock".lower()):
                commands.append(4)
            elif (word.lower() == "Suspend".lower()):
                commands.append(5)
            elif (word.lower() == "Resume".lower()):
                commands.append(6)
            elif (word.lower() == "Set priority".lower()):
                commands.append(7)
            elif (word.lower() == "Show PCB".lower()):
                commands.append(8)
            elif (word.lower() == "Show all".lower()):
                commands.append(9)
            elif (word.lower() == "Show ready".lower()):
                commands.append(10)
            elif (word.lower() == "Show blocked".lower()):
                commands.append(11)
    #return commands as a list
    #print(commands)
    return (commands, params, errors)