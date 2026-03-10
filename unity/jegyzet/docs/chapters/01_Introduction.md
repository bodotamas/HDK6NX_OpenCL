# Bevezetés

## A Unity

* Hivatalos weboldal: <https://unity.com/>
* Dokumentáció: <https://learn.unity.com/>
* Több platformon elérhető
* Library, szerkesztőeszközök
* UnityHub, megosztható asset-ek

**Telepítés**

Először a UnityHub-ot kell letölteni és telepíteni:

* <https://unity.com/download>

Ezt követően telepíthető a *Unity Editor*.

* Az LTS (*Long Term Support*) változatot érdemes választani.

* Az *asset*-ek eléréséhez szükséges regisztráció is.

A telepítés sikerességének ellenőrzéséhez indítsuk el a *Unity Editor*-t!

**Licensz**

* <https://unity.com/compare-plans>

## Alternatívák

**Unity**

* Unity Technologies, Koppenhága, Dánia, 2004.
* A játékok kb. fele ezt használja, AR/VR alkalmazásoknál ez 60% körül van.
* Elsődleges programozási nyelve a C#.
* Nem nyílt forráskódú
* Díj: *The Unity Awards*

**Unreal**

* Tim Sweeney, Epic Games, 1998.
* Kb. 7 millió felhasználója van
* *Blueprint Visual Scripting*, C++
* Nyílt forráskódú
* Díj: *The Rookie Awards*

**Godot**

* Juan Linietsky, Ariel Manzur, 2014.
* Hivatalos weboldal: <https://godotengine.org/>
* Nyílt forráskódú, kisebb méretű játékmotor
* GDScript, C#

**Cocos**

* Multimédia tartalmak fejlesztéséhez termékek és szolgáltatások
* Hivatalos weboldal: <https://www.cocos.com/en>
* *Cocos Creator*: <https://docs.cocos.com/creator/manual/en/>

**Hasonlóságok, különbségek**

* Platform támogatottságot tekintve a Unity és az Unreal között nincs lényegi különbség.
* Kijelenthető, hogy a Unity használata egyszerűbb.
* A Unity, Godot direktben támogatja a 2D-s játékok fejlesztését.
* A Unity AR/VR támogatottsága jobb.
* Az Unreal grafikája jobb.
* Erőforrásigény tekintetében csak konkrét implementációra vonatkozóan lehet állást foglalni.

*Források*:

* <https://blog.udemy.com/unity-vs-unreal-which-game-engine-is-best-for-you/>
* <https://program-ace.com/blog/unity-vs-unreal/>
* <https://pinglestudio.com/blog/full-cycle-development/unreal-engine-vs-unity-3d>

## A C# nyelv áttekintése

* <https://www.w3schools.com/cs/index.php>
* <https://learn.microsoft.com/en-us/dotnet/csharp/>
* <https://www.tutorialsteacher.com/csharp>

### Projekt létrehozása

* Vizsgáljuk meg, hogy elérhető-e a `dotnet` parancs! Hogy ha nem lenne, akkor telepítsük fel a .NET környezetet!
* Hozzunk létre egy új jegyzéket a projektünknek, majd adjuk ki a következő parancsokat:
```
dotnet new console
dotnet run
```
* Vizsgáljuk meg a létrejött fájlokat!

!!! note

    Az új C# verziókban a főprogram szerkezetében változások következtek be:
    <https://learn.microsoft.com/en-us/dotnet/core/tutorials/top-level-templates>

Definiáljunk egy saját `Item` nevű osztályt!

```csharp
namespace Classes;

public class Item
{
    public bool IsValid {get; set;}

    public Item(bool isValid)
    {
        this.IsValid = isValid;
    }
}
```

Definiáljunk a `Program.cs` fájlban egy függvényt, amellyel meg tudjuk számolni egy listában, hogy mennyi *valid* elem van!

```csharp
using Classes;

/**
 * Count the valid items.
 */
static int CountValidItems(List<Item> items)
{
    // ...
}
```

### Véletlenszámok generálása

* <https://learn.microsoft.com/en-us/dotnet/api/system.random?view=net-7.0>

```csharp
Random random = new Random();
```

### Saját térkép osztály

* Hozzunk létre egy `Point2D` osztályt, amelynek `X` és `Y`, lebegőpontos adattagjai vannak!
* Definiáljunk egy saját `World` osztályt!
* Definiáljunk egy `Entity` nevű osztályt, amelynek van `Point2D` típusú `Position` adattagja!
* Származtassunk belőle egy `Score`, `Obstacle` és egy `Enemy` osztályt!
* Az `Obstacle` osztálynak legyen egy `Radius` attribútuma!
* A `World` osztályba tároljunk le ezekből véletlenszerű pozíciókban létrehozott példányokat! (A térkép kiterjedése legyen például [-100, 100] mindkét tengely szerint!)
* Írassuk ki a térképen lévő elemek adatait!
* Definiáljunk egy `Player` osztályt, amelyik szintén az `Entity`-ből származik! Adjunk hozzá `Health` és `ScoreCount` egészes típusú attribútumokat!
* Számíttassuk ki, hogy a térképre helyezve a játékost, azt melyik entitáshoz van a legközelebb! (Vegyük figyelembe, hogy az akadályoknak kiterjedése is van!)
* Definiáljuk a `World` osztálynak egy `Update` nevű metódust, amelyik növeli a `Player` objektum `ScoreCount` értékét, hogy ha `Score` objektumhoz van egy küszöbértéknél közelebb, és csökkenti a `Health` értékét, hogy ha `Enemy`-hez!

## A Unity szerkesztő

A szerkesztőfelület részei:

* Objektum hierarchia
* Project asset-ek
* Inspector
* Scene view

Hozzunk létre egy új (*Core 3D* típusú) projektet, és nézzük meg a szerkesztőfelület részeit!

## Színterek kezelése

Nézzük meg az alapértelmezett színtérhez tartozó elemeket és tulajdonságaikat!

### 3D objektumok hozzáadása

* A színtérhez tartozó hierarchiába adjunk meg új, 3D objektumokat!
* Végezzünk transzformációkat a hozzáadott objektumokon!
* Töltsünk le *asset*-eket a *Unity Store*-ról! (*Windows* -> *Asset Store* -> *Search Online*)

Prefab:

* egy template
* több példányt létre lehet hozni belőle

## Fizika kezelése

* Rakjunk be a színtérbe néhány testet!
* Vizsgáljuk meg, hogy az adott testnél van-e megadva *collider*! (Hogy ha nincs, akkor adjunk meg valamilyet!)
* A feljebblévőknek állítsuk be a gravitációt! (*Add component* -> *Physics* -> *Rigidbody*)

## Constraint-ek megadása

* A *RigidBody* paraméterezésénél állítsuk be a pozícióra és az elforgatásokra vonatkozó paramétereket!

## Fények beállítása

* Adjunk a színtérhez egy új fényforrást, és állítsuk be a színét!

## Kamerák beállítása

* Állítsuk át a kameraképen a hátteret!
* Kapcsoljuk ki a háttér törlését, és nézzük meg a hatását!
* Oldjuk meg, hogy a kamerára, mint objektumra is hasson a fizika!
