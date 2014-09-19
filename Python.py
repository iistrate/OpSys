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
    #debug mode
    print(sarray)
    #check each word for valid commands
    for key, word in enumerate(sarray):
        if (word.lower() == "CreatePCB".lower()):
            if len(sarray) == 4:
                #append process name
                params.append(key+1);
                #append process class
                params.append(key+2);
                #append process priority
                params.append(key+3);
            commands.append(1)
        elif (word.lower() == "DeletePCB".lower()):
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
    return (commands, params)