from serial import * #importe tout le module série 
from tkinter import * #importe tout tkinter
import re #importe re pour renommer
import operator #importe le module pour les operations
import csv #importe le module d'export en CSV
import keyboard  # importe le module qui permet de lire les entrées clavier
import string #importe le module qui permet de mieux gerer les strings
import time #importe le module qui permet d'utiliser le temps

com = '' #crée une variable vide pour être ensuite utilisée pour socker le nom du port série

def valeurcom() : #On définit la fonction qui va ensuite permettre de lire l'entrée texte 

    global com #rend la variable disponible à tout le reste du programme
    com = entreecom.get() #lit l'entrée utilisateur
    choix.after(1, valeurcom) #boucle sur lui même après 1ms

def quitter() : #crée une fonction qui ferme la fenetre tkinter 
    choix.destroy()


choix = Tk() #on crée une fenêtre tkinter 
choix.geometry('1024x512+0+0') #on definit ses dimmensions 
choix.title('Banc de mesure') #on définit son nom
choix.config(bg = "#fff") #on définit la couleur de fond de la fenêtre

phototitre = PhotoImage(file="titre.png") #on définit une image
titre = Label(choix, image = phototitre, bg = "#fff") #on affiche cette image et on rend son fond blanc
titre.pack() #on pack l'image pour l'afficher

message = Label(choix, text="Inserez le port COM : ", font='Arial 20 italic bold', bg = "#fff", justify=LEFT) #on crée un label qui demande de saisir le port COM
message.pack() #on pack le label

espace = Label(choix, text= "espace", bg = "#fff", fg = "#fff", font='Helvetica 10 bold') #on crée un texte blanc pour faire office d'espace
espace.pack() #on pack l'espace

entreecom = Entry(choix, bg = "#fff") #on crée une entrée texte pour que l'utilisateur entre le port COM
entreecom.pack() #on pack l'entrée 
choix.bind("<Return>", valeurcom) #on définit la touche entrée pour qu'elle permette de lancer la fonction qui lit l'entrée


espace1 = Label(choix, text= "espace", bg = "#fff", fg = "#fff", font='Helvetica 30 bold') #on crée un texte blanc pour faire office d'espace
espace1.pack()#on pack l'espace


export = Button (choix, command=quitter) #on crée un bouton qui permet de fermer la fenêtre en appelant une fonction
img = PhotoImage(file="entrer.png") #on définit img comme étant une image
export.config(image=img, bg = "#fff", highlightthickness = 0, bd = 0) #on définit l'image comme bouton, on supprime les bordures du programme et on rend son fond blanc
export.pack() #on pack le boutton

choix.after(1, valeurcom) #on appelle la fonction qui lit l'entrée pour qu'elle boucle sur elle même afin de continuellement lire l'entrée
choix.mainloop() #on définit la fenêtre comme boucle principale




with Serial(port = com, baudrate = 115200, timeout = 1 ) as portserie: #on definit les propriétés du port serie et on le nomme
    if portserie.isOpen(): #si le port serie est ouvert alors : 
    

        time.sleep(3) #On attend 3s car l'arduino envoie des données vides pendant 2s qui font planter le programme

        
        root = Tk() #on crée la fenêtre principale
        root.geometry('1024x720+0+0') #on définit ses dimmensions
        root.title('Banc de mesure') #on définit son nom
        root.config(bg = "#fff")   #on definit la couleur de fond de la fenêtre 

        phototitre = PhotoImage(file="titre.png") #on definit phototitre comme une image
        titre = Label(root, image = phototitre, bg = "#fff") #on l'applique a un label
        titre.pack() #on pack l'image

        valeurs = str(portserie.readline().strip()) #on definit "valeurs" comme etant la ligne de données venant du port série
        distanceraw, vide, coupleetforce = valeurs.partition("t") #on sépare la ligne en deux variables "distanceraw" et "coupleetforce" avec t comme separateur
        forceradraw, t, coupleraw = coupleetforce.partition("t") #on sépare la deuxième valeur en deux variables "forceraw" et "coupleraw" avec t comme separateur
        forcerad1 = forceradraw.replace("'", '') #on traite forceraw pour enlever les '
        forcerad0 = forcerad1.replace("b",'') #on traite forcerad pour enlever les b
        forceradstr = forcerad0.replace('/', '') #on traite forcerad pour enlever les /
        couple0 = coupleraw.replace('b', '') #on traite coupleraw pour enlever les  b
        couplestr = couple0.replace("'", '') #on traite couple0 pour enlever les  '
        distance1 = distanceraw.replace('b', '') #on traite distanceraw pour enlever les b
        distance = distance1.replace("'", "") #on traite distance1 pour enlever les '

       
        def recupere():
                    valeurs = str(portserie.readline().strip()) #on definit "valeurs" comme etant la ligne de données venant du port série
                    distanceraw, vide, coupleetforce = valeurs.partition("t") #on sépare la ligne en deux variables "distanceraw" et "coupleetforce" avec t comme separateur
                    forceradraw, t, coupleraw = coupleetforce.partition("t") #on sépare la deuxième valeur en deux variables "forceraw" et "coupleraw" avec t comme separateur
                    forcerad1 = forceradraw.replace("'", '') #on traite forceraw pour enlever les '
                    forcerad0 = forcerad1.replace("b",'') #on traite forcerad pour enlever les b
                    forceradstr = forcerad0.replace('/', '') #on traite forcerad pour enlever les /
                    couple0 = coupleraw.replace('b', '') #on traite coupleraw pour enlever les  b
                    couplestr = couple0.replace("'", '') #on traite couple0 pour enlever les  '
                    distance1 = distanceraw.replace('b', '') #on traite distanceraw pour enlever les b
                    distance = distance1.replace("'", "") #on traite distance1 pour enlever les '
                    forcerad = float(forcerad) #on crée un float avec forcerad
                    couple = float(couple) #on cree un float avec couple
                    couple = couple / 100000 #on applique un coefficient sur le couple pour le transformet en Nm
                    forcerad = forcerad / 47777 #on applique un coefficient sur la forcerad pour la transformer en N
                    forcerad = round(forcerad, 2) #on arrondi forcerad au centième
                    couple = round(couple, 2) #on arrondi couple au centième
                    forceradstr = str(forcerad) #on crée un string avec la forcerad arrondie
                    couplestr = str(couple) #on crée un string avec le couple arrondi
                    forceradstr = forceradstr.replace('-', '') #on crée une valeur absolue en enlevant le -
                    couplestr = couplestr.replace('-', '') #on crée une valeur absolue en enlevant le -
                    
                    
                    if keyboard.is_pressed('enter'): # si la touche entrée est appuyée, on procède au suivant
                        with open('donnees.csv', 'a') as fichier: #on crée un fichier CSV, on l'ouvre et on definit le fait qu'il faille ecrire sur une nouvelle ligne à chaque arrivée de donnés
                            fichierWrite = csv.writer(fichier) #on définit le fait que on va ecrire dans le fichier
                            fichierWrite.writerow([forcerad, couple, distance]) #on definit le fait qu'il faut ecrire les 3 variables sur la même ligne dans des colonnes différentes
                        outfile.close() #on ferme le fichier CSV
                        
                    affichageforceradiale.config(text="            Force radiale =      " + forceradstr + "N") #On configure le label pour afficher la nouvelle valeur
                    affichagedistance.config(text="            Position =              " + distance + "mm") #On configure le label pour afficher la nouvelle valeur
                    affichagecouple.config(text="            Couple =                " + couplestr + "Nm") #On configure le label pour afficher la nouvelle valeur
                    root.after(10, recupere)

        def exportdonnees(): #on crée une fonction pour exporter les donnes
            
                    valeurs = str(portserie.readline().strip()) #on definit "valeurs" comme etant la ligne de données venant du port série
                    distanceraw, vide, coupleetforce = valeurs.partition("t") #on sépare la ligne en deux variables "distanceraw" et "coupleetforce" avec t comme separateur
                    forceradraw, t, coupleraw = coupleetforce.partition("t") #on sépare la deuxième valeur en deux variables "forceraw" et "coupleraw" avec t comme separateur
                    forcerad1 = forceradraw.replace("'", '') #on traite forceraw pour enlever les '
                    forcerad0 = forcerad1.replace("b",'') #on traite forcerad pour enlever les b
                    forceradstr = forcerad0.replace('/', '') #on traite forcerad pour enlever les /
                    couple0 = coupleraw.replace('b', '') #on traite coupleraw pour enlever les  b
                    couplestr = couple0.replace("'", '') #on traite couple0 pour enlever les  '
                    distance1 = distanceraw.replace('b', '') #on traite distanceraw pour enlever les b
                    distance = distance1.replace("'", "") #on traite distance1 pour enlever les '
                    forcerad = float(forcerad) #on crée un float avec forcerad
                    couple = float(couple) #on cree un float avec couple
                    couple = couple / 100000 #on applique un coefficient sur le couple pour le transformet en Nm
                    forcerad = forcerad / 47777 #on applique un coefficient sur la forcerad pour la transformer en N
                    forcerad = round(forcerad, 2) #on arrondi forcerad au centième
                    couple = round(couple, 2) #on arrondi couple au centième
                    forceradstr = str(forcerad) #on crée un string avec la forcerad arrondie
                    couplestr = str(couple) #on crée un string avec le couple arrondi
                    forceradstr = forceradstr.replace('-', '') #on crée une valeur absolue en enlevant le -
                    couplestr = couplestr.replace('-', '') #on crée une valeur absolue en enlevant le -
                    
                    
                    with open('donnees.csv', 'a') as fichier: #on crée un fichier CSV, on l'ouvre et on definit le fait qu'il faille ecrire sur une nouvelle ligne à chaque arrivée de donnés
                        fichierWrite = csv.writer(fichier) #on définit le fait que on va ecrire dans le fichier
                        fichierWrite.writerow([forcerad, couple, distance]) #on definit le fait qu'il faut ecrire les 3 variables sur la même ligne dans des colonnes différentes
                    outfile.close() #on ferme le fichier CSV

        
        espace = Label(root, text= "espace", bg = "#fff", fg = "#fff", font='Helvetica 30 bold') #on crée un label pour faire un espace
        espace.pack() #on pack l'espace
        
        affichagedistance = Label(root, text=distance, font='Helvetica 20 bold', bg = "#fff", width = 30, height = 1, anchor = W) #on crée un label pour afficher la distance
        affichagedistance.pack() #on pack le label

        espace1 = Label(root, text= "espace", bg = "#fff", fg = "#fff", font='Helvetica 15 bold') #on crée un label pour faire un espace
        espace1.pack() #on pack le label
                     
        
        affichageforceradiale = Label(root, text=forceradstr, font='Helvetica 20 bold', bg = "#fff", width = 30, height = 1, anchor = W) #on crée un label pour afficher la force radiale
        affichageforceradiale.pack() #on pack le label

        espace2 = Label(root, text= "espace", bg = "#fff", fg = "#fff", font='Helvetica 15 bold') #on crée un label pour faire un espace
        espace2.pack()#on pack le label
        
        affichagecouple = Label(root, text=couplestr, font='Helvetica 20 bold', bg = "#fff", width = 30, height = 1, anchor = W) #on crée un label pour afficher le couple
        affichagecouple.pack()#on pack le label

        espace3 = Label(root, text= "espace", bg = "#fff", fg = "#fff", font='Helvetica 30 bold') #on crée un label pour faire un espace
        espace3.pack()#on pack le label
        
        export = Button (root, command=exportdonnees) #on crée un boutton pour appeler la fonction de sauvegarde
        img = PhotoImage(file="saudonnees.png") #on definit une image
        export.config(image=img, bg = "#fff", highlightthickness = 0, bd = 0) #on applique cette image au boutton et on supprime le fond/la bordure
        export.pack()#on pack le boutton

        espace4 = Label(root, text= "espace", bg = "#fff", fg = "#fff", font='Helvetica 10 bold') #on crée un label pour faire un espace
        espace4.pack()#on pack le label

        crédits= Label(root, text="Banc de mesure réalisé par BURLET Jessy, GREGOIRE Antonin, MARTIN Mathis et TOUBON Logan.", font='Helvetica 10 bold', bg = "#fff", width = 300, height = 1, anchor = CENTER) #on crée un label de crédits
        crédits.pack()#on pack le label
        
        crédits2= Label(root, text="Programme réalisé par MARTIN Mathis et TOUBON Logan. Mai 2019", font='Helvetica 10 bold', bg = "#fff", width = 300, height = 1, anchor = CENTER) #on crée un label de crédits
        crédits2.pack()#on pack le label
        
        root.after(1, recupere) #on appele une fonction pour boucler la recuperation des donnees 
        root.mainloop() #on definit la fenêtre comme boucle principale 

                

                      
    else: #si le programme n'arrive pas a se connecter au port série : 
           print ("enorme érreur avec le port série :/ ") #on affiche un message d'erreur
           
