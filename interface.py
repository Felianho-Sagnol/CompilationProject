import tkinter as tk
import os

def isInt(char):
    c = char[:2][1:]
    if(c=="n"):
        return 0
    return 1

def fileHeader():
    f = open("codeIntermediaire.c","w+")
    f.write("#include <stdio.h>\n")
    f.write("#include <stdlib.h>\n")
    f.write("#include <string.h>\n\n")
    f.write("int main(){\n")
    f.close()

def genereCodeCreationVariabe(char):
    f = open("codeIntermediaire.c","a+")
    if(isInt(char) == 0):
        f.write("\tint "+char[1:]+"=0;\n")
        f.close()
    else:
        f.write("\tchar "+char[1:]+"[256];\n")
        f.close()

def genereCodeAffectation(char):
    fisrtLetter = char.strip()[:1]
    if(fisrtLetter == "w"):
        str = char.split("[")[1].split("]")[0].strip()
        f = open("codeIntermediaire.c","a+")
        f.write("\tprintf(\""+str+"\\n\");\n")
        f.close()


def endFile():
    f = open("codeIntermediaire.c","a+")
    f.write("\n\treturn 0;\n")
    f.write("}\n")
    f.close()

def appendCode():
    with open("AlgoSyntaxe.txt","r") as algo:
        ligne = algo.readline()
        while ligne != "":
            char = ligne.split(" ")
            c = char[0].strip()[:2][1:]
            if(c=="n" or c=="s"):
                if(char[0].strip() == "Gui"):
                    break
                genereCodeCreationVariabe(char[0].strip())
            ligne = algo.readline()
    with open("AlgoSyntaxe.txt","r") as algo:
        ligne = algo.readline()
        while ligne != "":
            genereCodeAffectation(ligne)
            ligne = algo.readline()

        

    

class window:
    def __init__(self,master):
        self.master = master 
    #zone de saisie
        self.readFrame = tk.LabelFrame(self.master,text="Saisie de code",background="white")

        self.compileBTN = tk.Button(self.readFrame,text="Compiler",command = self.getTextAndCompile)
        self.compileBTN.grid(column="0",row="0",sticky=tk.W)

        self.runBTN = tk.Button(self.readFrame,text="Exécuter",command = self.run)
        self.runBTN.grid(column="1",row="0",sticky=tk.W)

        self.codeEdit = tk.Text(self.readFrame,width="55",height="25")
        self.codeEdit.grid(column="0",row="1",columnspan="2")

        self.readFrame.grid(column="0",row="0",ipady="20",padx="10")
    #zone d'affichage resultat
        self.resultFrame = tk.LabelFrame(self.master,text="Affichage du resultat",background="white")

        self.resultContent = tk.StringVar()
        self.resultContent.set("")
        self.result = tk.Text(self.resultFrame,width="45",height="29")
        self.result.config(state=tk.DISABLED)

        self.result.grid(column=0,row=0,sticky="nsew")

        self.resultFrame.grid(column="1",row="0",sticky="wn")
    #zone d'affichage erreur
        self.errorFrame = tk.LabelFrame(self.master,text="Affichage des erreurs.",background="white")
        
        self.errorContent = tk.StringVar()
        self.errorContent.set("")
        self.errorResult = tk.Text(self.errorFrame,width="102",height="5",fg="red")
        self.errorResult.config(state=tk.DISABLED)
        self.errorResult.grid(column=0,row=0,columnspan="2",padx="1")

        self.errorFrame.grid(column="0",row=1,columnspan="2")
    def getTextAndCompile(self):
        
        fileAlgo = open("AlgoSyntaxe.txt","w+")
        fileAlgo.write(self.codeEdit.get("1.0","end"))
        fileAlgo.close()

        self.errorContent.set(os.popen('programme.exe AlgoSyntaxe.txt').read())

        if(len(self.errorContent.get()) > 1):
            self.errorResult.configure(state='normal')
            self.errorResult.delete('1.0', tk.END)
            self.errorResult.insert('end', "\n\n\t"+self.errorContent.get())
            self.errorResult.configure(state='disabled')

            self.result.configure(state='normal')
            self.result.delete('1.0', tk.END)
            self.result.configure(state='disabled')
    #si le code est correcte
        else:
            fileHeader()
            appendCode()
            endFile()

            self.errorResult.configure(state='normal')
            self.errorResult.delete('1.0', tk.END)
            self.errorResult.configure(state='disabled')
            error = ""
            error = os.popen('gcc codeIntermediaire.c -o guicompilator').read()
            print("error : "+error)
            if(len(error) == 0):
                self.result.configure(state='normal')
                self.result.delete('1.0', tk.END)
                self.result.insert('end', "\n\n\n\n\tCompilé avec succès")
                self.result.configure(state='disabled')
            else:
                self.errorContent.set(error)
                self.errorResult.configure(state='normal')
                self.errorResult.delete('1.0', tk.END)
                self.errorResult.insert('end', "\n\n\n\n\t"+self.errorContent.get())
                self.errorResult.configure(state='disabled')

    
    def run(self):
        #result = os.popen('guicompilator.exe').read()
        self.resultContent.set(os.popen('guicompilator.exe').read())
        self.result.configure(state='normal')
        self.result.delete('1.0', tk.END)
        self.result.insert('end', self.resultContent.get())
        self.result.configure(state='disabled')
       
   


main = tk.Tk()
main.title("@GUI-COMPILATOR")
main.geometry("950x600")
main.config(background="white")
main.resizable(width = False, height = False)

window = window(main)

main.mainloop()