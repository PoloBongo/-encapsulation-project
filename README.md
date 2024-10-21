# Documentation
Nous avons crée une bibliothèque ParsingLib qui permet d'extraire les données de inventory.ini et de database.ini. Chaque Item contient un ID qui fait référence à un ID dans la Database, ce qui nous permet de faire la liaison et de récupérer des valeurs de base qui ne changeront pas.

Vous pourrez retrouver la documentation des 2 librairies juste <a href="https://www.baimmobilier.fr/gtech3/encapsulation/Documentation/html/" target="_blank">ici</a>
 !

## Fonctionnement ParsingLib

ParsingLib fonctionne avec deux fichiers : "inventory.ini" et "database.ini". Le fichier "inventory.ini" contient les données de sauvegarde des items d'un inventaire, tandis que "database.ini" stocke les informations statiques de base sur les items.

Chaque item dans "inventory.ini" possède un "Type" qui indique le type d'item, ainsi qu'un "ID" qui correspond à un identifiant précis dans "database.ini". Lors du traitement du fichier, ParsingLib établit la connexion entre ces deux fichiers afin d'extraire les informations statiques (depuis "database.ini") et dynamiques (depuis "inventory.ini") associées à chaque item.
 
## Utilisation ParsingLib

### Format des données dans le fichier inventory.ini et database.ini. (Comment ajouter/lire les informations)

### Inventory.ini 
1. Toujours commencer par :
`[item(n)]` mais remplacer le n par le nombre actuelle du nombre d'item dans l'inventaire <br>
Par exemple : `[item1]`
2. Ensuite continuer par le type de l'item qui sont : `Item` , `Weapon`, `Armor` <br>
Par exemple : `type = Item`
3. Ajouter les valeurs obligatoires qui sont `id` et `sell_price` <br>
Par exemple : `id = 1` et `sell_price = 15`
5. Puis ajouter les valeurs qui sont différents des valeurs de base de l'item qui est dans la database ( l'ordre du champ n'a pas d'importance).
Les parametres possible sont diffèrent selon le type de l'item :
- **Item** : aucun autre paramètre possible.
- **Weapon** : 
  `weapon_type` (int) : Sword = 0, Axe = 1, Katana = 2, Mace = 3, Dagger = 4 ; <br>
`skill` (string) ; `level` (int) ; `defense` (int) ; `attack` (int) ; `attack_speed` (int) ; `crit_rate` (int) ; `crit_damage` (int) ; `accuracy` (int) ; `cooldown_reduction` (int) ; `life_steal` (int).
- **Armor** :
  `armor_type` (int) : Helmet = 0, Chestplate = 1, Gloves = 2, Leggings = 3, Boots = 4 ; <br>
  `skill` (string) ; `level` (int) ; `defense` (int) ; `health` (int) ; `dodge_rate` (int), `resistance` (int), `health_regen` (int).
<details>
<summary>Exemples : </summary>
<pre><i>Potion de vie</i><br>
[item1]
type = Item
id = 1
sell_price = 15 <br>
-----------
<i>Epee en bois</i><br>
[item2]
type = Weapon
id = 2
sell_price = 30
level = 0
defense = 5
skill = ""
attack = 25
attack_speed = 3
crit_rate = 2
crit_damage = 5
accuracy = 7
cooldown_reduction = 3
life_steal = 1 <br>
-----------
<i>Casque en cuir</i><br>
[item3]
type = Armor
id = 5
sell_price = 3
level = 1
defense = 50
skill = ""
health = 100
dodge_rate = 1
resistance = 10
health_regen = 5
luck = 10 </pre>
</details>

### Database.ini
1. Si les catégories n'existent pas encore , créer les categories pour les differents types d'item : `Item`, `Weapon`, `Armor` : <br>
Par exemple : `[Item]` 
2. Dans chaque catégorie, chaque nouvel item commencera par son nom sans espace entre parenthèses.<br>
Par exemple : `(HealPotion)`
3. Puis dans n'importe quel ordre , ajouter les cinq paramètres obligatoires : <br>
*[Que pour les objects de categorie 'Item'] :* `item_type` (int) : Consumable = 2, Miscellaneous = 3 <br>
*[Que pour les objects de categorie 'Weapon'] :* `weapon_type` (int) :  Sword = 0, Axe = 1, Katana = 2, Mace = 3, Dagger = 4 ; <br>
*[Que pour les objects de categorie 'Armor'] :* `armor_type` (int) : Helmet = 0, Chestplate = 1, Gloves = 2, Leggings = 3, Boots = 4 ; <br>
`id` (int), `name` (string), `description` (string), `isStackable` (boolean).
<details>
<summary>Exemples : </summary>
<pre>[Item]
(HealPotion)
id = 1
item_type = 2
name = Heal Potion
description = Te donne 10 de heal
isStackable = true<br>
[Weapon]
(WoodenSword)
id = 2
weapon_type = 0
name = Wooden Sword
description = Simple epee
isStackable = false
(WoodenAxe)
id = 3
weapon_type = 1
name = Wooden Axe
description = Simple axe
isStackable = false<br>
[Armor]
(LeatherHelmet)
id = 5
armor_type = 0
name = Leather Helmet
description = Simple helmet
isStackable = false</pre>
</details> 

### Ajout d'une nouvelle variable

Pour ajouter cette nouvelle variable (par exemple `weight` à un Weapon), il vous suffit de vous rendre dans DataExtraction.h puis d'ajouter cette ligne :<br>
`Type(type, name, value)` par exemple : `Type(int, weight, -1)`.<br>Ensuite rendez-vous dans Parsing.cpp, cherchez la fonction GetAllDataFromInventory() puis dans la functionMap, ajouter simplement une nouvelle ligne avec la variable que vous venez de créer.
<br>`{ "weight", [&](const std::string& value) { RegisterField("weight", dataExtraction.weight, value); } }`<br>
Vous pouvez ensuite utiliser ce nouveau paramètre comme les autres dans `inventory.ini`
Et voilà le tour est joué pour la partie du ParsingLib mais il faut aussi faire les modifications dans l'InventoryLib pour ajouter cette variable à l'item.

## Fonctionnalités de InventoryLib 

- Ajouter un ou plusieurs filtre sur l'inventaire avec la fonction : <br>
  `AddItemFilter(ItemType::item_Armor);` si pas de sous catégorie. <br>
  `AddItemFilter(ItemType::item_Weapon,WeaponType::Katana);` avec une sous catégorie. <br>
  
> Filtres possible : `ItemType::item_Weapon` , `ItemType::item_Armor` , `ItemType::item_Consumable` , `ItemType::item_Miscellaneous` <br>
> Sous catégorie de filtres possible : <br>
> **Weapon Type** : `WeaponType::Sword` , `WeaponType::Axe` , `WeaponType::Katana` , `WeaponType::Mace` , `WeaponType::Dagger` <br>
> **Armor Type** : `ArmorType::Helmet` , `ArmorType::Chestplate` , `ArmorType::Gloves` , `ArmorType::Leggings` , `ArmorType::Boots` <br> 

- Choisir un tri qui sera soit croissant ou décroissant avec la fonction : <br>
  `SortByPrice()` si croissant. <br>
  `SortByPrice(false)` si décroissant. <br>

> Tri possible : `ID` , `Name` , `Type` , `WeaponType` , `ArmorType` , `Price` ,  `Level` , `Defense` , `Attack` , `AttackSpeed` , `CritRate` , `CritDamage` , `Accuracy` , `CooldownReduction` , `LifeSteal` , `Health` , `DodgeRate` , `Resistance` , `HealthRegen` , `Luck` , `Quantity` <br>
> 
## Modifications de InventoryLib 

### Ajout d'une nouvelle variable

Pour ajouter notre variable `weigth` de l'exemple précédent, il faudra aller dans `ItemBuild.h` puis ajouter cette ligne à la catégorie correspondante :<br>
Par exemple : `GetValueOrDefault<int>("weight", properties),` dans la catégorie "Weapon".<br> 
Il faudra faire attention au type de la variable qui peut etre : `int` , `bool` , `float`, `double` , `std::string`.
Ensuite il faudra ajouter cette variable à la classe correspondante et son constructeur. <br>
Par exemple : Pour notre cas , il faudra donc aller sur `Weapon.h`, ajouter `int weight = 0;`, puis dans le constructeur ajouter `, int _weight = 0` et enfin créer le getteur pour cette nouvelle variable.

### Ajout d'un nouveau tri 

Si vous voulez aussi ajouter un nouveau tri pour cette variable , allez dans `Inventory.h` pour ajouter cette ligne : <br>
`void SortByQuantity(bool _ascending = true);` <br>
Puis aller dans `Inventory.cpp` et créer une fonction avec cette base et en modifiant les parties commentés: <br>
1. Changer "Variable" par le nom de votre variable.
2. Changer "Item" par "Weapon"/"Armor" selon la classe dans laquelle vous avez ajouté cette nouvelle variable.
3. Changer "GetterVariable" par le Getter de votre variable.
4. Pareil que le 2.
```cpp
void Inventory::SortBy/*Variable*/(bool _ascending) { // 1)
	auto compareFunc = [](const std::shared_ptr</*Item*/>& a, const std::shared_ptr</*Item*/>& b) { // 2)
		return a->/*GetterVariable*/() < b->/*GetterVariable*/(); // 3)
		};
	std::sort(items.begin(), items.end(), CompareBy</*Item*/, decltype(compareFunc)>(_ascending, compareFunc)); // 4)
}```
