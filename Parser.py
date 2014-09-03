import sqlite3
import os

print("Module loaded; activating Python super powers in 3 2 1..")

dirs = ""

def listDir():
    dirs = '\n '.join(os.listdir())
    return dirs