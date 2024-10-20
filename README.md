# Documentation
Nous avons crée une bibliothèque ParsingLib qui permet d'extraire les données de inventory.ini et de database.ini. Chaque Item contient un ID qui fait référence à un ID dans la Database, ce qui nous permet de faire la liaison et de récupérer des valeurs de base qui ne changeront pas.
<br><br>
...InventoryLib
<br><br>
Vous pourrez retrouver la documentation des 2 librairies juste <a href="https://www.baimmobilier.fr/gtech3/encapsulation/Documentation/html/" target="_blank">ici</a>
 !

## Fonctionnement ParsingLib

ParsingLib fonctionne avec deux fichiers : "inventory.ini" et "database.ini". Le fichier "inventory.ini" contient les données de sauvegarde des items d'un inventaire, tandis que "database.ini" stocke les informations statiques de base sur les items.

Chaque item dans "inventory.ini" possède un "Type" qui indique le type d'item, ainsi qu'un "ID" qui correspond à un identifiant précis dans "database.ini". Lors du traitement du fichier, ParsingLib établit la connexion entre ces deux fichiers afin d'extraire les informations statiques (depuis "database.ini") et dynamiques (depuis "inventory.ini") associées à chaque item.
 
## Utilisation ParsingLib

Imagineons qu'à votre Item Katana ( représenté par l'ID 4 dans la database ) présent dans "inventory.ini", vous voulez ajouter le champ "attack_pourcentage" comme ceci ( l'ordre du champ n'a pas d'importance ) :
<br><br>`[inventory_1.item5]`<br>
`type = Weapon`<br>
`weapon_type = 2`<br>
`id = 4`<br>
**`attack_pourcentage = 75`**<br>
`sell_price = 50`<br>
`level = 0`<br>
`defense = 1`<br>
`skill = ""`<br>
`attack = 35`<br>
`attack_speed = 4`<br>
`crit_rate = 5`<br>
`crit_damage = 30`<br>
`accuracy = 13`<br>
`cooldown_reduction = 2`<br>
`life_steal = 1`<br>

Pour ajouter cette nouvelle variable (attack_pourcentage), il vous suffit de vous rendre dans DataExtraction.h puis d'ajouter cette ligne :<br>
`Type(type, name, value)` par exemple : `Type(int, attack_pourcentage, -1)`.<br>Ensuite rendez-vous dans Parsing.cpp, cherchez la fonction GetAllDataFromInventory() puis dans la functionMap, ajouter simplement une nouvvelle ligne avec la variable que vous venez de créer.
<br>`{ "attack_pourcentage", [&](const std::string& value) { RegisterField("attack_pourcentage", dataExtraction.attack_pourcentage, value); } }`<br>
Et voilà le tour est joué !
