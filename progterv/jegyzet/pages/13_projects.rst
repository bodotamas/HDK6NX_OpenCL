13. Forráskód szervezése
========================

A forráskód részei
------------------

* Dokumentáció
* Projekt leíró
* Külső (*third-party*) függvénykönyvtárak
* tesztek

.. note::

    Ügyelni kell arra, hogy mi része a forráskódnak, és mi tekinthető az alkalmazás szempontjából adatnak!

Függőségek
----------

* Szabványok követése
* Külső függvénykönyvtárak
* Külső szolgáltatások
* Külső hardveres erőforrások

:math:`\rhd` Mikor, milyen formában éri meg függvénykönyvtárakat használni?

Rendszer integráció
-------------------

* Adatbázis
* Hálózat
* Bináris kódok
* Parancssori végrehajtás

Verziókezelés
-------------

* A szoftverfejlesztő szervezetek számára a kód és az adat kiemelt fontosságú értéknek tekinthető.
* A forráskódok korábbi változatait szerencsés nyilván tartani.
* Jellemzően nem egy-egy fejlesztő, hanem fejlesztőcsoport áll a munkálatok hátterében.
* Elterjedt verziókezelő rendszerek: git, Mercurial, SVN

Fejlesztés gazdasági szempontból
--------------------------------

* COCOMO, *COnstructive COst MOdel*
* Barry W. Boehm: Software Engineering Economics (1981)
* 1997-ben kidolgozták a fejlesztett változatát (COCOMO II.)

A szoftverfejlesztéshez, mint gazdasági tevékenységhez bevezet plusz mértékeket.

* KDSI: *Kilo Delivered Source Index*, a kiadott programsorok száma ezres sorokban mérve.
* :math:`T_d`: Fejlesztési idő (hónapban)
* PM: *Person Month*, *Ember-Hónap*, egy fejlesztő 1 hónapnyi munkájának az egysége.

A következő szabályszerűségeket állapították meg.

.. math::

  \text{PM} = 2.4 \cdot \text{KDSI}^{1.05}

Ez azt jelenti, hogy egy program méretéből becsülhető, hogy az egy fejlesztőnek hány hónapnyi munkájába telne.

.. math::

  T_d = 2.5 \cdot \sqrt[3]{PM}

Az elvégzett vizsgálataik alapján ez az a fejlesztési idő, amely alatt az adott méretű fejlesztési feladatot még csúszás nélkül el lehet végezni.

A létszámot az előző mennyiségek hányadosából kapjuk:

.. math::

  \text{létszám} = \dfrac{\text{PM}}{T_d}.

Feltételezhetnénk, hogy plusz fejlesztők bevonásával a fejlesztési idő csökkenthető, ez azonban sajnos csak részben igaz. Brook egy limitet javasolt erre vonatkozóan, még hozzá, hogy a fejlesztési idő a

.. math::

  T_d \cdot 0.75

érték alá nem vihető (tehát 75% alá nem lehet menni még a létszám növelésével sem).

Kérdések
========

* Miért előnyös verziókezelést használni?
* Egy szoftverfejlesztési projekthez mik szoktak még hozzátartozni, amelyek nem tartoznak szorosan a működő (ténylegesen használandó) kódokhoz?

Feladatok
=========

* Egy 100000 soros alkalmazást szeretnénk kifejleszteni. Mennyi emberre és időre van szükség?
* 20 programozóval fél év alatt mekkora alkalmazást lehet kifejleszteni?
* Egy 300000 soros program esetében lehetőségünk van egy függvénykönyvtár megvásárlására, amely 120000 sor kiváltására képes. Maximum mennyit érdemes fizetnünk ezért, ha a programozók havi fizetése 240000 Ft?
* Egy 50000 soros alkalmazást szeretnénk minél gyorsabban elkészíteni. Mennyi plusz embert lehet még bevonni, hogy a határidő tartása ne legyen rizikós?
* Egy 200000 soros alkalmazást 25 emberrel szeretnénk kifejleszteni. Az alkalmazás várhatóan 5 millió forintént fog elkelni. Legfeljebb mennyi lehet így a programozók havi fizetése?
