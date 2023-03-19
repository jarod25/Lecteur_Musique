# Lecteur de Musiques

## Description

Voici une application réalisée en C++ avec QT pour pouvoir écouter des musiques locales.

Elle est créée pour fonctionner sur Linux, la partie [Installation](#Installation) sera donc basée dessus.

Avec cette application, vous pouvez importer les musiques de votre pc et les lires.

Vous pouvez également créer des listes de lectures de vos titres préférés

Ce projet de 2ᵉ semestre de 2ᵉ année de BUT Informatique est réalisé
avec [Simon Nguyen](https://github.com/Snguyen70)

## Installation

Pour utiliser ce projet, il vous faudra installer QT5 et plusieurs librairies de QT :

- Ouvrez le terminal de votre distribution Linux.


- Assurez-vous que votre système est à jour en exécutant la commande suivante : <br>
  `sudo apt-get update && sudo apt-get upgrade`


- Installez les outils de développement nécessaires en exécutant la commande suivante : <br>
  `sudo apt-get install build-essential`


- Installez QT5 en exécutant la commande suivante :<br>
  `sudo apt-get install qtbase5-dev`


- Installez la bibliothèque multimédia en exécutant la commande suivante : <br>
  `sudo apt-get install libqt5multimedia5 libqt5multimedia5-plugins libqt5multimediawidgets5 qtmultimedia5-dev libtag1-dev`


- Une fois l'installation terminée, vous pouvez vérifier que QT5 est installé en exécutant la commande suivante : <br>
  `qmake -version`

- Si vous n'avez pas de version, essayez cette commande : <br>
  `sudo apt install qt5-qmake`


- Après avoir installé QT et les dépendances nécessaires, téléchargez le projet (2 solutions) : <br>
    - Cloner le repo git sur votre pc : <br>
      `git clone https://github.com/jarod25/Lecteur_Musique.git` (Clonage en https) <br>
      ou <br>
      `git clone git@github.com:jarod25/Lecteur_Musique.git` (Clonage en ssh) <br>
      <br>
    - Télécharger le fichier d'archive .zip et l'extraire


- Enfin, dans votre terminal, rendez-vous dans le dossier où se trouve le projet, puis exécutez : <br>
  `qmake` <br>
  `make` <br>
  `./app` <br>

Vous pouvez désormais importer et écouter vos musiques

