2. Számábrázolás
================

Hol kerülnek tárolásra az adatok?

* Memória
* Háttértár

A számábrázolás témakörében nem szükséges foglalkoznunk a bitek tárolásának fizikális megvalósításával.

**Memória**

* Lineárisan címezhető rekeszek.
* A címzéshez nem negatív egészeket használunk.
* A *pointer*/*mutató* tulajdonképpen egy memóriacímet jelent.
* A bit szintű elérés általában nem biztosított. Byte-ok szintjén kell dolgozni, hogy hozzáférjünk a bitekhez.

A tárolókra szokás *buffer* (angol nyelvből) vagy *puffer* (német nyelvből) néven hivatkozni.

**Adatok vizsgálata**

* Memória esetében *memory dump*
* Az adatok megtekintéséhez, szerkesztéséhez hexadecimális szerkesztők használhatók.
* *Hex Editor*, *Hexa Editor*, *Binary Editor*

Véges ábrázolás
---------------

* Alapvetően bitmintákat rendelünk szimbólumokhoz.
* Véges számú byte-on véges számú bitminta van.

Mit jelenthet a következő byte?

.. code:: bash

    10110010

Az ábrázolt bitsorozatnak van két kitüntetett bitje:

* MSB: *Most Significant Bit* (legnagyobb helyiértéken szereplő bit)
* LSB: *Least Significant Bit* (legkisebb helyiértéken szereplő bit)

Ábrázolással kapcsolatosan egy további leírás:

* https://www.bottomupcs.com/chapter01.xhtml

Előjel nélküli egészek
----------------------

* A 2-es számrendszerbe történő átírás kézenfekvő ábrázolási módja.
* A helyiértékek a felírásban megfelelő sorrendben vannak.
* A *hiányzó* helyiértékeket 0 értékekkel töltjük fel.

1 byte
~~~~~~

A C nyelv szerinti ``unsigned char`` típus. Más nyelvekben például ``u8``.

Nézzük meg a 94 érték ábrázolását!

.. math::

	94 = 1011110_{(2)}

.. code::

    [  0  1  0  1  1  1  1  0 ]
       7  6  5  4  3  2  1  0

Hexadecimális alakban: ``5E``

Ellenőrízzük, hogy valóban így történik a tárolás!

* Tároljuk le egy fájlba az értéket!
* Ellenőrízzük hexadecimális szerkesztővel!
* Olvastassuk vissza az értéket!
* Írjuk át (például ``AB``-re)!
* Számoljuk ki, hogy milyen értéket várnánk!
* Visszaolvasva ellenőrízzük, hogy valóban annyi lett!

**Adat kiírása fájlba**

.. literalinclude:: source_codes/value_writer.c

**Adat visszaolvasása fájlból**

.. literalinclude:: source_codes/value_reader.c

2 byte
~~~~~~

A C nyelv szerinti ``unsigned short`` típus. Más nyelvekben például ``u16``.

Végezzük el az előző vizsgálatokat a 14274 érték esetén 2 byte-on!

.. warning::

  A byte-ok sorrendje változhat a szerint, hogy little- vagy big endian byte-sorrendről van-e szó!

https://hu.wikipedia.org/wiki/B%C3%A1jtsorrend

https://en.wikipedia.org/wiki/Endianness

4 byte
~~~~~~

A C nyelv szerinti ``unsigned int`` típus. Más nyelvekben például ``u32``.

Végezzük el az előző vizsgálatokat a 2966513 érték esetén 4 byte-on!

.. warning::

	A C nyelv csak reláció szintjén adja meg, hogy egy-egy típusnak mennyi byte felel meg!

Ellenőrízzük ``sizeof`` segítségével, hogy a vizsgált típusok mérete megfelelő!

.. literalinclude:: source_codes/type_sizes.c

.. csv-table::
   :header-rows: 1

   "byte-ok száma","előjel nélküli egész","előjeles egész"
   1,``unsigned char``,``char``
   2,``unsigned short``,``short``
   4,``unsigned int``,``int``
   8,``unsigned long``,``long``


Előjeles egész számok
---------------------

Előjelbit használata
~~~~~~~~~~~~~~~~~~~~

* Kézenfekvő megoldásnak tünne.
* Hogyan lenne használható?

Kettes komplemens ábrázolási mód
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

A kettes komplemens képzésének lépései:

* Induljunk el a számjegyeken az alacsonyabb helyiértékektől a magasabbak felé. (*Jobbról balra*)
* Másoljuk át az eredménybe a biteket az első 1-essel bezárólag.
* A fennmaradó biteket negáljuk.

**Tulajdonságai**

* A kettes komplemens képzést egymás után páros számú alkalommal végrehajtva mindig visszakapjuk az eredeti értéket.
* Az MSB jelzi, hogy az érték negatív-e.

**Példa**

Ábrázoljuk a -20 értéket 1 byte-on, 2-es komplemens ábrázolási móddal!

.. math::

  20 = 10100_{(2)}

.. code::

    [  0  0  0  1  0  1  0  0 ]
       7  6  5  4  3  2  1  0

Hexadecimális alak: ``14``

Kettes komplemens:

.. code::

    [  1  1  1  0  1  1  0  0 ]
       7  6  5  4  3  2  1  0

Hexadecimális alak: ``EC``

* Ellenőrízzük, hogy valóban így kerül tárolásra!

**Példa**

Ábrázoljuk a -1000 értéket 2 byte-on!

.. math::

  1000 = 3E8_{(16)}

.. code::

    [  0  0  0  0  0  0  1  1  1  1  1  0  1  0  0  0 ]
      15 14 13 12 11 10  9  8  7  6  5  4  3  2  1  0

Kettes komplemens:

.. code::

    [  1  1  1  1  1  1  0  0  0  0  0  1  1  0  0  0 ]
      15 14 13 12 11 10  9  8  7  6  5  4  3  2  1  0

Hexadecimális alakban: ``FC18``

**Példa**

Milyen értéket ábrázolnak az ``ACDC`` hexadecimális alakban megadott byte-ok előjeles egész ábrázolási módot feltételezve?

.. code::

    [  1  0  1  0  1  1  0  0  1  1  0  1  1  1  0  0 ]
      15 14 13 12 11 10  9  8  7  6  5  4  3  2  1  0

Az érték az MSB alapján negatív.

Kettes komplemens:

.. code::

    [  0  1  0  1  0  0  1  1  0  0  1  0  0  1  0  0 ]
      15 14 13 12 11 10  9  8  7  6  5  4  3  2  1  0

Az ábrázolt érték a :math:`-5324_{(16)} = -21284`.

Egészes számábrázolási tartományok
----------------------------------

.. csv-table::
   :header-rows: 1

   "byte-ok száma","bitek száma","előjel nélküli","előjeles"
   1,8,":math:`[0, 255]`",":math:`[-128, 127]`"
   2,16,":math:`[0, 65535]`",":math:`[-32768, 32767]`"
   3,24,":math:`[0, 2^{24}-1]`",":math:`[-2^{23}, 2^{23}-1]`"
   4,32,":math:`[0, 2^{32}-1]`",":math:`[-2^{31}, 2^{31}-1]`"
   ,k,":math:`[0, 2^k-1]`",":math:`[-2^{k-1}, 2^{k-1}-1]`"

Alul- és túlcsordulás
---------------------

Bitmintázatok és értékek 4 bit esetén.

.. csv-table::
   :header-rows: 1

   "bitminta","előjel nélküli","előjeles"
   0000,0,0
   0001,1,1
   0010,2,2
   0011,3,3
   0100,4,4
   0101,5,5
   0110,6,6
   0111,7,7
   1000,8,-8
   1001,9,-7
   1010,10,-6
   1011,11,-5
   1100,12,-4
   1101,13,-3
   1110,14,-2
   1111,15,-1

* Hogy ha kilépünk a számábrázolási tartományból (alul vagy felül) az nem feltétlenül jár hibajelzéssel.
* Ilyen esetekben nem várt értékeket kaphatunk.
* 4 bit esetén, előjel nélküli esetben például ha 12-höz hozzáadunk 7-et, akkor 3-mat kapunk.
* 4 bit esetén, előjeles esetben, hogy ha például -5-ből kivonunk 7-et, akkor 4-et kapunk.
* Az átviteli bitet a processzor kezeli (*carry bit*).

Törtek ábrázolása
-----------------

Egészek formájában számlálóval és nevezővel
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Megoldható, de általában nem praktikus.

**Példa**

Ábrázoljuk a :math:`\dfrac{45}{87}` értéket úgy, hogy a számlálót és a nevezőt is előjel nélküli egész értékként kezeljük!

.. code::

    [  0  0  1  0  1  1  0  1  0  1  0  1  0  1  1  1 ]
      15 14 13 12 11 10  9  8  7  6  5  4  3  2  1  0

A tört értéke a ``2D57`` hexadecimális alakban megadott byte-okon ábrázolható.

Fix pontos ábrázolás
~~~~~~~~~~~~~~~~~~~~

Rögzítjük, hogy mennyi bit-et szeretnénk az egész és a tört rész tárolására használni.

**Példa**

Tegyük fel, hogy 1 byte-on szeretnénk tört értékeket ábrázolni. A biteket a következőképpen csoportosítjuk (ebben a sorrendben):

* 1 bit előjel bit,
* 4 bit egészrész (előjel nélküli egészként),
* 3 bit törtrész.

Ábrázoljuk a -11,75 értéket!

.. code::

    [  1  1  0  1  1  1  1  0 ]
       7  6  5  4  3  2  1  0

Hexadecimális alakban a ``DE`` byte-on ábrázolható.

Lebegőpontos ábrázolási mód
~~~~~~~~~~~~~~~~~~~~~~~~~~~

**Normalizált szám**

A számokat az egységes ábrázolás, majd későbbi tárolás érdekében egységes alakra hozzuk.

.. math::

  \text{<előjel>} 1,\text{<szignifikáns>} \cdot 2^{<\text{kitevő}>}

Például a :math:`-1,110101_{(2)} \cdot 2^{4}` esetében

* az előjel negatív,
* a szignifikáns :math:`110101_{(2)}`,
* a kitevő 4.

https://en.wikipedia.org/wiki/Significand

**Szabvány**

IEEE 754 szabvány, William Kahan, Berkeley Egyetem, 1985.

https://en.wikipedia.org/wiki/IEEE_754-1985

.. csv-table::
   :header-rows: 1

   típus,előjel,"eltolt kitevő",szignifikáns,összesen
   egyszeres pontosság,1 bit,8 bit,23 bit,32 bit
   dupla pontosság,1 bit,11 bit,52 bit,64 bit

A kitevő ábrázolásához a normalizált alakban szereplő kitevő kerül eltolásra:

* egyszeres pontosság esetén 127-el,
* dupla pontosság esetén 1023-mal.

A szabvány a normalizált számábrázolás mellett egyébb eseteket is megkülönböztet. Egyszeres pontosság esetén a következő formában.

.. csv-table::
  :header-rows: 1

  előjel,"eltolt kitevő",szignifikáns,byte-ok,jelentése
  0,00000000,000...0,00 00 00 00,+0
  1,00000000,000...0,80 00 00 00,-0
  0,11111111,000...0,7F 80 00 00,:math:`+\infty`
  1,11111111,000...0,FF 80 00 00,:math:`-\infty`
  0 vagy 1,00000000,tetszőleges nem 0,,denormalizált szám
  0 vagy 1,11111111,tetszőleges nem 0,,NaN

Denormalizált számok:

* A nem tárolt bitet 0-nak tekintjük.

.. math::

  \text{<előjel>} 0,\text{<szignifikáns>} \cdot 2^{-126}

https://en.wikipedia.org/wiki/Subnormal_number

**Példa**

Ábrázoljuk a 119,6875 értéket egyszeres lebegőpontos számábrázolással!

.. math::

  &119 = 1110111_{(2)} \\
  &0,6875 = 0,1011_{(2)} \\
  &119,6875 = 1110111,1011_{(2)}

Normalizált alak:

.. math::

  1,1101111011_{(2)} \cdot 2^{6}

Kitevő: 6 :math:`\Rightarrow` Eltolt kitevő: 6 + 127 = 133

.. math::

  133 = 10000101_{(2)}

.. code::

    [ 01000010 11101111 01100000 00000000 ]

Hexadecimális alakban: ``42 EF 60 00``

Tetszőleges pontosságú számábrázolás
------------------------------------

* *Arbitrary Precision*
* Tulajdonképpen a számjegyeket tárolhatjuk.
* Főként szimbólikus számítások esetében használják.

Kérdések
========

* Számábrázolás esetén minek a rövidítése az MSB és az LSB?
* Melyek azok az egész értékek, amelyek megegyeznek a kettes komplemensükkel?
* Normalizált számábrázolás esetén egyszeres, és dupla pontosságú lebegőpontos számoknál milyen intervallumon változhat a kitevő?
* Egyszeres pontosságú lebegőpontos számábrázolás esetén mennyi *nem szám* szimbólum van?
* Adjunk példát olyan valós értékre, amely nem ábrázolható (pontosan) a szabványban megadott lebegőpontos számként!
* Adjon példát (hexadecimális alakban) NaN értékre egyszeres lebegőpontos számábrázolás esetén!
* Adja meg a :math:`-\infty` értéket hexadecimális alakban, egyszeres lebegőpontos számábrázolást feltételezve!

Feladatok
=========

Számjegyek számáról szóló tétel
-------------------------------

* Ha egy szám 61 jegyű kettes számrendszerben, akkor hány jegyű lesz 16 és 10-es számrendszerben?
* Ha egy szám 9 jegyű 16-os számrendszerben, akkor hágy jegyű lesz 10-esben és kettesben?
* Mennyi byte-on lehet ábrázolni a Neptun kódokat? Mi lenne, ha nem lennének benne számjegyek?
* Tegyük fel, hogy egy mért értékről tudjuk, hogy az egy nemnegatív egész érték, és maximum :math:`10^{10}` lehet az értéke. Legalább mennyi bit szükséges ahhoz, hogy biztosan ábrázolni tudjuk az előforduló értékeket?

Egészek ábrázolása
------------------

* Ábrázoljuk az 5985-öt előjel nélküli egész számként 2, 3 és 4 byte-on! Az eredményt hexadecimális alakban adjuk meg!
* Mennyi byte szükséges a -281, -512 és a -14890 értékek ábrázolásához?

Váltsuk át a 14889 és a -2488 számokat 2-es számrendszerbe!

* Legalább mennyi bit szükséges az ábrázolásukhoz?
* Adjuk össze őket 2-es számrendszerben!
* Az összeget számoljuk vissza 10-es számrendszerbe, és ellenőrízzük!

Adjon példát olyan 4 byte-os egész számra, amely litte- és big endian ábrázolás esetében is ugyanolyan formában néz ki. Írja fel a hexadecimális alakot és az ábrázolt értéket!

Törtes ábrázolás
----------------

Törteket úgy szeretnénk ábrázolni, hogy a számláló 2 byte-os előjeles egész, a nevező pedig 2 byte-os előjel nélküli egész. (A nevező nem lehet 0. Egymást követő 2-2 byte-ról van szó.)

* Melyik a legkisebb és a legnagyobb ábrázolható érték?
* Mi lesz a legnagyobb ábrázolható negatív érték?
* Milyen értéket ábrázolnak az ``EC 81 00 3B`` hexadecimális alakban megadott byte-ok?
* Milyen byte-okon ábrázolható (hexadecimális alakban felírva) a 0,03129 érték?
* Melyik a legkisebb, 0-nál nagyobb ábrázolható érték?

Fix pontos ábrázolás
--------------------

Törteket szeretnénk ábrázolni a következő séma szerint 2 byte-on:

* 1 előjelbit,
* 10 bit egészrész (előjel nélküli egészként),
* 5 bit törtrész.

(A részek ilyen sorrendben követik egymást.)

Válaszoljuk meg az alábbi kérdéseket!

* Mennyi különböző értéket tudunk így ábrázolni?
* Melyik a legkisebb és a legnagyobb ábrázolható érték? Hogyan néznek ki ezek a byte-ok hexadecimális alakban?
* Melyik a legkisebb, 0-nál nagyobb ábrázolható érték? Hogyan néznek ki a byte-ok hexadecimális alakban?
* Milyen értéket ábrázolnak az ``F8 AC`` byte-ok?

Az ábrázolási mód szerint össze szeretnénk adni a ``31 0B`` és a ``0E 99`` értékeket.

* Mi lesz az eredmény byte-ok értéke hexadecimális alakban?

Hogyan ábrázolható a :math:`-\dfrac{3157}{32}` érték?

Tegyük fel, hogy adott az ``E4 BB`` érték fix pontos ábrázolás mellett.

* Térjünk át egyszeres lebegőpontos ábrázolási módra, és adjuk meg az ábrázolás során kapott byte-ok értékét hexadecimális alakban!

Lebegőpontos értékek ábrázolása
-------------------------------

* Írjuk át a :math:`0,110101_{(2)}`, :math:`0,1201_{(3)}` és a :math:`0,AB1E_{(16)}` értékeket 10-es számrendszerbe!
* Írjuk át a :math:`0.1`, :math:`0.15` és :math:`0.625` értékeket 2-es és 16-os számrendszerbe!
* Vizsgáljuk meg a helyiértékes és a Horner-sémás átírást is!

Írjuk fel kettes számrendszerbe a következő értékeket!

.. math::

  0.42578125_{10}, \quad
  0.70312_{10}, \quad
  0.74_{10}, \quad
  0.14062_{10}, \quad
  0.15_{10}, \quad
  0.ABCD_{16}

Ellenőrízzük helyiértékesen és Horner sémával is!

Ábrázoljuk egyszeres lebegőpontos számábrázolással a következő értékeket!

.. math::

  149.765625, \quad
  -0.7, \quad
  7513.625, \quad
  0.41, \quad
  9.7

Számítsuk ki, hogy milyen értékeket ábrázolnak a következő byte-ok egyszeres lebegőpontos ábrázolást feltételezve!

.. math::

	8AC20000, \quad FE90C000, \quad 14011000, \quad C5D20000, \quad 7D3C8000

Ábrázoljuk egyszeres lebegőpontos számokként a következőket:

  -51000.3046875, 0.9, 3.6, 4.78125, 3.141592
  85EA0000, ABCD0000, FCA20000, 90909090

Adjuk meg a végtelen értékeket egyszeres pontossággal!

Egyszeres lebegőpontos számábrázolást feltételezve milyen értéket ábrázol a 7F801000?

Egyszeres pontossággal milyen értékeket ábrázolnak a következő byte-ok?

.. math::

  66 1B 0C 42, \quad
  66 1B 0A 1F

Töltsük ki az alábbi táblázatot!

.. csv-table::

  duplaszó hexában, ``FA00AB87``, ``10203040``, ``DEADBEEF``
  előjel nélküli,,,
  előjeles,,,
  egyszeres lebegőpontos,,,

Szorozza meg az egyszeres pontosságú, lebegőpontos számként ``9E CD 70 00`` byte-okon ábrázolt értéket :math:`2^{70}`-el! (Elegendő a hexadecimális alakot megadni végeredményként!)

Mennyivel áll több számjegyből a :math:`47^{23}` érték 12-es számrendszerben felírt alakja, mint a :math:`25^{19}` szám 9-es számrendszerben felírt alakja?
