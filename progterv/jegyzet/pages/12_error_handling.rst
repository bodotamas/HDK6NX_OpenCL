12. Hibakezelés
===============

Hibák előfordulása
------------------

Fordítási idejű

* szintaktikai
* típus hiba
* érvénytelen nevek

Linkelési hibák

* érvénytelen szimbólum

Futás idejű hibák

* Dangling pointer
* Memory leak
* Stack overflow/underflow
* I/O hibák

Típusbiztonság
--------------

* Szigorúan típusos nyelveknél garantált, hogy egy adott típusú változó/objektum csak bizonyos értékeket vehessen fel.
* Az elvégezhető műveletek köre is le van szűkítve.

Explicit hibakezelés
--------------------

* A hibákat jelezhetjük (programozási nyelvtől függően) hibakódokkal, vagy kivétel objektumokkal.
* A hibakódok előnye, hogy könnyebben implementálhatóak (például enumerációkkal megadva).
* A kivétel objektumok OOP nyelvekre jellemzőek. Az eseményhez tartozó részleteket magába az objektumba helyezhetjük el.

.. warning::

	A kivétel objektumokat nem csak hibakezelésre használjk!

Implicit hibakezelés
--------------------

* A hibát a program nem jelzi külön.
* A beépített hibakezelő rutinok megoldják a problémát, majd annak megfelelően adnak vissza valamilyen értékeket.

Tesztek
-------

* A program bizonyos részeihez be- és kimenet párokat adhatunk meg.
* Legegyszerűbb változata az egységteszt.

Assertion-ön
------------

* A program kódjában definiálunk egy állítást, amelynek a futás során igaz értékűnek kell lennie.
* Hogy ha az assertion sérül (*assertion fail*) az programozói hibát jelez.

Kérdések
========

* A program fejlesztése és használata során mikor jelentkezhetnek hibák?
* Mire szolgálnak az assertion-ök?
