# Documentation
Nous avons crée une bibliothèque ParsingLib qui permet d'extraire les données de inventory.ini et de database.ini. Chaque Item contient un ID qui fait référence à un ID dans la Database, ce qui nous permet de faire la liaison et de récupérer des valeurs de base qui ne changeront pas.
<br><br>
...InventoryLib
<br><br>
Vous pourrez retrouver la documentation des 2 librairies juste <a href="https://www.baimmobilier.fr/gtech3/encapsulation/Documentation/html/" target="_blank">ici</a>
 !
## ParsingLib

Pour ajouter une nouvelle variable, il vous suffit de vous rendre dans DataExtraction.h puis d'ajouter cette ligne :<br>
`Type(type, name, value)` par exemple : `Type(int, attack_pourcentage, -1)`.<br>Ensuite rendez-vous dans Parsing.cpp, cherchez la fonction GetAllDataFromInventory() puis dans la functionMap, ajouter simplement une nouvvelle ligne avec la variable que vous venez de créer.
<br>`{ "attack_pourcentage", [&](const std::string& value) { RegisterField("attack_pourcentage", dataExtraction.attack_pourcentage, value); } }`<br>
Et voilà le tour est joué !

## InventoryLib
