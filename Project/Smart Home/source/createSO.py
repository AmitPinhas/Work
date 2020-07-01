import os
import subprocess


#createOFiles = 'make'
#process = subprocess.Popen(createOFiles.split(), stdout=subprocess.PIPE)
#output, error = process.communicate()

directory = '.'
#directoryB = '../'
#directoryC = '../interfaces'

otherFilesNames = ''

for filename in os.listdir(directory):
    if filename.endswith(".o"):
        otherFilesNames += filename + ' '

#for filename in os.listdir(directoryB):
#    if filename.endswith(".o"):
#        otherFilesNames += ' '+ directoryB + filename

#otherFilesNames += ' '

for filename in os.listdir(directory):
    if filename.endswith(".o"):
        sep = '.'
        targetName = filename.split(sep, 1)[0]
        targetName += '.so'
        currObjCreation = 'g++ -shared -o ' + targetName + ' ' + otherFilesNames 
        print(currObjCreation)
        process = subprocess.Popen(currObjCreation.split(), stdout=subprocess.PIPE)
        output, error = process.communicate()


