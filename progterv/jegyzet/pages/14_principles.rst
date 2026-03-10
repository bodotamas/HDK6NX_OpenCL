14. Elvek, módszertanok
=======================

Programozási paradigmák
-----------------------

* A programok elkészítéséhez absztrakció szintjén a megközelítést lehet megpróbálni csoportosítani.
* Nem kizárólagosan ennyi van. A gyakrabban előfordulók/elfogadottak kerülnek említésre.
* Nem csak programozási, hanem általában programozás során előforduló nyelvek esetében beszélhetünk ezekről.

.. warning::

	Az elterjedt programozási nyelvek jelentős része multiparadigma nyelv!

Imperatív programozás
~~~~~~~~~~~~~~~~~~~~~~~~

* A megoldandó problémát lépések, végrehajtandó procedúrák sorozatára bontjuk.
* Leírjuk, hogy a gépnek mi után mit kell majd elvégeznie.
* Procedurális programozás ennek az egyik leggyakoribb megvalósítása.

Objektum Orientált Programozás
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

* Röviden OOP-ként szokás emlegetni.
* Az összetartozó adatokat és a műveleteiket egy egységben, objektumokként kezeli.
* Megkülönböztetünk prototípus és osztály alapú objektum orientáltságot.
* Tisztán objektum orientált nyelveknek nevezik azokat, melyekben minden objektum.
* Vannak objektum alapú nyelvek is, melyek használnak objektumokat, de saját típusokat nem lehet definiálni. (Egyszerűbb szkript nyelvekre jellemző.)

Például: *SmallTalk*, *Java*

Funkcionális programozás
~~~~~~~~~~~~~~~~~~~~~~~~

* A programokat, mint a matematikai értelemben vett függvényeket tekinthetjük.
* Függvények hívnak függvényeket.
* Egy igen lényeges fogalma a mellékhatásmentesség. (*Pure function*)
* Az adatok és a hozzá tartozó műveletek két külön egységben kezeljük.
* Nagyon jól tesztelhetőek.
* A valós problémák egy részére nehezen illeszkednek.

Például: *Haskell*, *Clojure*

Deklaratív programozás
~~~~~~~~~~~~~~~~~~~~~~

* Azt adjuk meg, hogy az eredményt milyen formában szeretnénk viszont látni.
* Általában rövid, tömör, emberek számára egyszerűbb, magasabb szintű megfogalmazását adja a problémának.
* A végrehajtása nehezebb. Bonyolultabb fordítási, értelmezési fázisra van hozzá szükség.

Például: *Prolog*, *SQL*

Elvek, ajánlások
----------------

* Egyre gyakrabban/gyorsabban változó igények a szoftverrel szemben.
* A fejlesztési ciklusok lerövidültek.
* Gyakori, 1-2 hetes kiadások
* *Extrém programozás*
* A tesztelésnek egyre fontosabb a szerepe.
* *Legacy kód*: Nem az elkészítés ideje számít, hanem, hogy mennyire van tesztelve/dokumentálva
* *Code Review*, *Pair Programming*
* Minőségre vonatkozó metrikák
* *Continuous Integration*: Mindig van egy stabil, az összes teszteseten átesett kiadás.

DRY
~~~

* *Dont Repeat Yourself*
* Többek között az implementált funkcionalitás felesleges redundanciájának csökkentésére törekszik.

SOLID
~~~~~

* Single responsibility
* Open-closed
* Liskov substitution
* Interface segregation
* Dependency inversion

Módszertanok
------------

SCRUM
~~~~~

* Egy agilis szoftverfejlesztési metodika.
* Keretet, ajánlásokat, szerepköröket ad.
* 1-4 hetes sprintekben lehet gondolkodni (nem hosszabb távú fejlesztésekben).
* A cégek jelentős része aktuálisan ennek valamilyen változatát használja.

Tipikus szerepkörök

* *Scrum Master*: Felügyeli, segíti a csapat működését
* *Product Owner*: A termékkel kapcsolatos igényeket képviseli, segít priorizálni a feladatokat
* *Developers*: Fejlesztők

KANBAN
------

* A módszert a Toyota Motor Corporation-nél fejlesztették ki.
* A Kanban szó kártyát jelent.
* A kártyák egy-egy feladatot szimbolizálnak, amelyek sorban áthaladnak a különböző fejlesztési fázisokon.

TDD
~~~

*Test Driven Development*

A program fejlesztést 3, egymás után ismétlődő fázisra bontja.

* Teszt írása az új funkcionalitás számára. (Lefuttatva sikertelen lesz, amelyet érdemes megnézni.)
* Minimális funkcionalitás hozzáadása, amellyel már sikeres lesz a teszt.
* A teszttel validált kód refaktorálása.

Az említett módszereket különböző arányban és formában szokták használni.
