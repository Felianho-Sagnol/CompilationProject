import tkinter as tk
import os

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
        self.writeFrame = tk.LabelFrame(self.master,text="Affichage du resultat",background="white")

        self.resultContent = tk.StringVar()
        self.resultContent.set("Le resultat sera affiché ici.\nles enfants")
        self.result = tk.Text(self.writeFrame,width="45",height="29")
        self.result.config(state=tk.DISABLED)

        self.result.grid(column=0,row=0,sticky="nsew")

        self.writeFrame.grid(column="1",row="0",sticky="wn")
    #zone d'affichage erreur
        self.errorFrame = tk.LabelFrame(self.master,text="Affichage des erreurs.",background="white")

        self.errorResult = tk.Text(self.errorFrame,width="103",height="9",fg="red")
        self.errorResult.config(state=tk.DISABLED)
        self.errorResult.grid(column=0,row=0,columnspan="2",padx="1")

        self.errorFrame.grid(column="0",row=1,columnspan="2")
    def getTextAndCompile(self):
        fileAlgo = open("AlgoSyntaxte.txt","a+")
        fileAlgo.write(self.codeEdit.get("1.0","end"))
        fileAlgo.close()

        fileError = open("errorFile.txt","a+")
        fileError.write(os.popen('programme.exe AlgoSyntaxe.txt').read())
        fileError.close()

        self.result.configure(state='normal')
        self.result.insert('end', self.resultContent.get())
        self.result.configure(state='disabled')
        self.errorPrintMessage()
    def run(self):
        file = open("AlgoSyntaxte.txt","a+")
        #file.write(self.codeEdit.get("1.0","end"))
        #file.close()
        #os.system('gcc test.c -o p')
        #file.write(os.popen('p.exe').read())
        self.result.configure(state='normal')
        self.result.insert('end', self.resultContent.get())
        self.result.configure(state='disabled')
        file.close()
    def errorPrintMessage(self):
        file = open("AlgoSyntaxte.txt","w+")
        #file.write(self.codeEdit.get("1.0","end"))
        #file.close()
        #os.system('gcc test.c -o p')
        #file.write(os.popen('p.exe').read())
        self.errorResult.configure(state='normal')
        self.errorResult.insert('end', self.resultContent.get())
        self.errorResult.configure(state='disabled')
        file.close()


main = tk.Tk()
main.title("GUI - INTERFACE")
main.geometry("850x670")
main.config(background="white")
main.resizable(width = False, height = False)

window = window(main)

main.mainloop()