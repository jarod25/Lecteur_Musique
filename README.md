# Lecteur de Musiques

## Description

Voici une application réalisé en C++ avec QT pour pouvoir écouter des musiques locales.

Elle est créée pour fonctionner sur Linux, la partie [Installation](#Installation) sera donc basée dessus.

Avec cette application, vous pouvez importer les musiques de votre pc et les lires.

Vous pouvez également créer des listes de lectures de vos titres préférés

Ce projet de 2ème semestre de 2ème année de BUT Informatique est réalisé
avec [Simon Nguyen](https://github.com/Snguyen70)

## Installation

Pour utiliser ce projet, il vous faudra installer QT5 et plusieurs librairies de QT :

- Ouvrez le terminal de votre distribution Linux.


- Assurez-vous que votre système est à jour en exécutant la commande suivante : <br>
  `sudo apt-get update && sudo apt-get upgrade`


- Installez les outils de développement nécessaires en exécutant la commande suivante : <br>
  `sudo apt-get install build-essential`


- Installez QT5 en exécutant la commande suivante :<br>
  (Si ça ne fonctionne pas, remplacez 'qt5-default' par 'qtbase5-dev') <br>
  `sudo apt-get install qt5-default`


- Installez la bibliothèque multimédia en exécutant la commande suivante : <br>
  `sudo apt-get install libqt5multimedia5 libqt5multimedia5-plugins libqt5multimediawidgets5 qtmultimedia5-dev`


- Une fois l'installation terminée, vous pouvez vérifier que QT5 et la bibliothèque multimédia sont installés en
  exécutant les commandes suivantes : <br>
  `qmake -version`
