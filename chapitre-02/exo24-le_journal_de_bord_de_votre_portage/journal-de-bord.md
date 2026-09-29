# Journal de bord du portage

## Entrée 1

Symptôme : La commande jenga build ne construisait pas le projet.

Ma pensee : J'ai cru que le problème venait du code C++ de mon programme.

Finalement: Le problème venait de la configuration du fichier projet.jenga et de la structure du projet.

Temps perdu : 20min

## Entrée 2

Symptôme : Le programme restait en attente lorsque je lançais le fichier exécutable.

Ma pensee : J'ai cru que la compilation était bloquée ou que mon programme ne fonctionnait pas.

finalement : Le programme attendait simplement des données sur l'entrée standard.

Temps perdu : 10min

## Entrée 3

Symptôme : Jenga indiquait qu'aucun appareil Android n'était connecté.

Ma pensee : J'ai cru que le câble USB était défectueux.

Finalement : L'appareil n'était pas correctement reconnu par ADB et son état devait être vérifié avec adb devices.

Temps perdu : 15min

## Entrée 4

Symptôme : Le programme compilait mais une erreur apparaissait lors de l'édition de liens.

Ma pensee : J'ai cru qu'il y avait une erreur dans mon code source.

Fianalement : Une bibliothèque nécessaire n'avait pas été correctement liée au programme.

Temps perdu : 25min

## Entrée 5

Symptôme : Le programme fonctionnait sur l'ordinateur mais ne se comportait pas correctement sur l'appareil Android.

Ma pensee : J'ai cru que le problème venait directement du téléphone.

Finalement : Le programme devait être construit avec la chaîne de compilation correspondant à la plateforme Android cible.

Temps perdu : 30min

## Entrée 6

Symptôme : La trace du programme planté affichait principalement des adresses mémoire et peu de noms de fonctions.

Ma pensee : J'ai cru que le journal système était incomplet ou qu'il ne contenait pas le plantage.

Finalement : Les symboles de débogage n'étaient pas disponibles dans la trace, ce qui rendait les adresses difficiles à associer aux fonctions du programme.

Temps perdu : 20min
