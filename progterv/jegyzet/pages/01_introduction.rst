1. Információ, adat, számrendszerek
===================================

Információ
----------

* Jellemző mértékegysége a bit.
* A számítógépeink többségében digitálisak és bit alapúak.
* Az adat az információ megjelenési formája.

*Kapcsolódó tudományterületek*

* Információelmélet
* Kommunikációelmélet
* Kódelmélet

**Bit**

* A tárolható adatmennyiség legkisebb egysége.
* Értéke lehet ``0`` vagy ``1``.

**Byte**

https://en.wikipedia.org/wiki/Byte

* A 8 bitből alkotott csoportokat *byte*-nak nevezzük.
* A 8-as darabszám praktikus és történeti okok miatt alakult ki. (Ezért nevezik *oktett*-nek is.)
* Számít a bitek sorrendje.
* A bit-ek helyét az egész számokhoz hasonlóan a helyiérték kitevőjének indexével adjuk meg.

.. code::

    [  .  .  .  .  .  .  .  . ]
       7  6  5  4  3  2  1  0

* A 2 byte-os egységet *szó*-nak szokták nevezni.

.. code::

    [  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  . ]
      15 14 13 12 11 10  9  8  7  6  5  4  3  2  1  0

* A 4 byte-os egység a *dupla szó*.
* A fél byte-nak a(z egyik) neve *nibble*. Jellemzően az alsó- és felső fél byte-ot szokták tekinteni.

További mértékegységek

* KB: Kilobyte
* MB: Megabyte
* GB: Gigabyte
* TB: Terabyte

*Számítások szemléltetésképpen*

* Írjuk fel a byte-ok darabszámát 2 kitevőjeként 1 KB, 1 MB, 1 GB és 1 TB esetén!
* Tegyük fel, hogy négyzet alakú milliméter lapon szeretnénk adatokat tárolni. 1 bit :math:`1 \times 1` milliméteres négyzetnek feleltethető meg. Mekkora lesz a lap mérete 1 KB, 1 MB, 1 GB és 1 TB esetén?


Adattípus
---------

A számítógép egy automata, amely az adatok tárolásával, feldolgolgozásával, továbbításával foglalkozik.

.. warning::

    Az információt nagyon nehéz elkülöníteni a konkrét megjelenési formájától!

Az adattípusokhoz hozzá értjük

* az adat ábrázolását (leírási módját), és
* a rajta elvégezhető műveleteket.

Ez a megközelítés fellelhető

* a matematikában például az algebrák, gyűrűk vizsgálatánál,
* az objektum-orientált programozásban,
* az adat- és a műveleti rész elkülönítésénél úgy általában.

**Absztrakt adattípus**

Az absztrakt adattípus adatok és a rajtuk végezhető műveletek halmazát írja le.
Jelölhetjük :math:`T`-vel, amely így tehát egy

.. math::

    T = (A, M)

pár lesz, amelyben az :math:`A` az adatok halmazát, az :math:`M` a műveletek halmazát jelöli.

Az absztrakció itt azt jelenti, hogy

* nem foglalkozunk a későbbi, gépi megvalósítással, realizációval,
* a halmazok lehetnek akár végtelen elemszámúak is.

**Példa**

A természetes számhalmaz segítségével definiálhatunk egy típust az alábbi formában:

.. math::

    T = (\mathbb{N}, \{+, \cdot\}).

.. warning::

    A műveletek eredménye mindig halmazon belül kell, hogy maradjon!
    (Nem tud máshol lenni.)


**Adatstruktúra**

Az absztrakt adattípus konkrét megjelenési formája, realizációja.

**Implementáció**

A számítógépen történő realizáció.

* Az *implementáció* magyarul megvalósítást jelent.
* Az absztrakt adatból az adatstruktúra definiálása, majd az implementáció megadása is veszteségekkel járhat (például a véges ábrázolási tartományok miatt).
* Az implementáció az adatstruktúra egy speciális esete.


Déscartes szorzat
-----------------

Két halmaz Déscartes szorzatán egy olyan, rendezett elempárokból álló halmazt értünk, amely pároknak az első eleme az első halmazból, második eleme a második halmazból származik.

.. math::

    C = A \times B = \{(a, b) | a \in A, b \in B\}

**Példa**

Legyen :math:`A = \{x, y\}` és :math:`B = \{3, 4, 5\}`. Ezek Déscartes szorzata:

.. math::

    A \times B = \{(x, 3), (x, 4), (x, 5), (y, 3), (y, 4), (y, 5)\}.


Halmaz hatványa
---------------

Halmazokon is értelmezhetjük a hatványozás műveletét.

* :math:`A^0 = \emptyset`
* :math:`A^1 = A`
* :math:`A^2 = A \times A`
* :math:`A^n = A^{n - 1} \times A`

**Példa**

Tekintsük a :math:`D = \{7, 8\}` halmazt!

* :math:`D^0 = \emptyset`
* :math:`D^1 = \{7, 8\}`
* :math:`D^2 = D \times D = \{(7, 7), (7, 8), (8, 7), (8, 8)\}`

**Tulajdonságok**

* Nem Kommutatív
* Asszociatív

Többváltozós műveletek
----------------------

:math:`n`-változós (:math:`n`-áris) műveletnek nevezzük az :math:`A` halmazon az :math:`f: A^n \rightarrow A` leképzést (függvényt).

* :math:`n = 1` esetén unáris művelet.
* :math:`n = 2` esetén bináris művelet.


Hatványhalmaz
-------------

Egy halmaz összes lehetséges részhalmazának a halmaza.

Jelölése: :math:`2^A`, :math:`\mathcal{P}(A)`

**Példa**

Írjuk fel a :math:`C = \{2, 3, 5\}` halmaz hatványhalmazát!

**Számosság**

.. math::

    |2^A| = 2^{|A|}


Orosz-paraszt módszer
---------------------

* Két egész szám szorzására alkalmas.
* A módszert az ókori egyiptomiak fejlesztették ki (vagy legalábbis már használták).

*Lépései*

* Állítsunk be egy szorzat *változót* 0-ra!
* Vizsgáljuk meg, hogy a szorzónk páratlan-e!
* Hogy ha páratlan, akkor adjuk hozzá a szorzathoz!
* A szorzandót szorozzuk meg kettővel!
* A szorzót osszuk el egészesen kettővel!
* Ismételjük az eljárást a második lépéstől, amíg a szorzónk 0 nem lesz!

*Példa*

Számítsuk ki a :math:`25 \cdot 19` szorzatot!

.. csv-table::
   :header-rows: 1

    szorzandó,szorzó,szorzó páratlan-e?,szorzat
    25,19,igen,0+25=25
    50,9,igen,25+50=75
    100,4,nem,75
    200,2,nem,75
    400,1,igen,75+400=475
    ,0,,

Elemi függvények, műveletek
---------------------------

A függvények és műveletek között a fő különbséget gyakorlatilag a jelölésmód jelenti.
Definiálhatjuk például az összeadást a szokásos (*infix*) műveleti jellel, de megadhatnánk akár függvény formájában is:

.. math::

    +: \mathbb{R}^2 \rightarrow \mathbb{R}.


**Alsóegészrész függvény**

Az alsóegészrész függvény minden valós számhoz a nála nem nagyobb egészek közül a legnagyobb egészet rendeli.

.. math::

    \lfloor x \rfloor = \max_{k \leq x} k, \quad x \in \mathbb{R}, k \in \mathbb{Z}.

:math:`k = \lfloor x \rfloor` esetén mindig teljesül, hogy :math:`k \leq x < k + 1`.


**Felsőegészrész függvény**

A felsőegészrész függvény minden valós számhoz a nála nem kisebb egészek közül a legkisebb egészet rendeli.

.. math::

    \lceil x \rceil = \min_{k \geq x} k, \quad x \in \mathbb{R}, k \in \mathbb{Z}.

:math:`k = \lceil x \rceil` esetén mindig teljesül, hogy :math:`k - 1 < x \leq k`.

*Tulajdonságok*

Legyen :math:`a \in \mathbb{Z}` és :math:`x, y \in \mathbb{R}`.

* :math:`a = \lfloor a \rfloor = \lceil a \rceil`.
* :math:`\lfloor x \rfloor \leq \lceil x \rceil`.
* Ha :math:`x \leq y`, akkor :math:`\lfloor x \rfloor \leq \lfloor y \rfloor` és :math:`\lceil x \rceil \leq \lceil y \rceil`.
* :math:`\lfloor x \pm a \rfloor = \lfloor x \rfloor \pm a`, :math:`\lceil x \pm a \rceil = \lceil x \rceil \pm a`.
* :math:`-\lfloor x \rfloor = \lceil -x \rceil`, :math:`-\lceil x \rceil = \lfloor -x \rfloor`.
* :math:`\lfloor x + y \rfloor \geq \lfloor x \rfloor + \lfloor y \rfloor`, :math:`\lceil x + y \rceil \leq \lceil x \rceil + \lceil y \rceil`.
* :math:`\lfloor x - y \rfloor \leq \lfloor x \rfloor - \lfloor y \rfloor`, :math:`\lceil x - y \rceil \geq \lceil x \rceil - \lceil y \rceil`.

`https://hu.wikipedia.org/wiki/Egészrész <https://hu.wikipedia.org/wiki/Egészrész>`__

**Kerekítő függvény**

A kerekítő függvény a valós számokhoz a hozzájuk legközelebbi egész számokat rendeli. Amennyiben ez nem egyértelmű, a nagyobbat választja.

.. math::

    \text{Round}(x) = \left\lfloor x + \dfrac{1}{2} \right\rfloor, \quad x \in \mathbb{R}.

**Törtrész függvény**

A törtrész függény azt mutatja, hogy mennyivel nagyobb egy valós érték az alsóegész részénél.

.. math::

    \{x\} = x - \lfloor x \rfloor, \quad x \in \mathbb{R}.

Mindig fennáll, hogy :math:`0 \leq \{x\} < 1`.

**Egész hányados képzése**

Legyenek :math:`a, b \in \mathbb{Z}` egészek, :math:`b \neq 0`. Egész hányados alatt az :math:`a / b` hányados alsóegész részét értjük.

.. math::

    a \text{ div } b = \left\lfloor \dfrac{a}{b} \right\rfloor.

**Egész maradék képzése**

Legyenek :math:`a, b \in \mathbb{Z}` egészek.

.. math::

    a \text{ mod } b = \begin{cases}
    a - \lfloor a / b \rfloor \cdot b, & \text{ha } b \neq 0, \\
    a, & \text{ha } b = 0.
    \end{cases}

.. note::

  A szakirodalomban előfordul, hogy a :math:`b = 1` esetre is speciális esetként tekintenek, és az :math:`a` tört részét adják meg vele. Nem hiba úgy definiálni, de itt nem így használjuk.


Számrendszerek
--------------

Jelölje :math:`b` természetes szám (:math:`b \geq 2`) a számrendszeri alapszámot.
Egy :math:`x` pozitív egész szám helyiértékes számábrázolást feltételezve az alábbi alakban írható föl:

.. math::

    c_n, c_{n-1}, \ldots, c_1, c_0,

ahol :math:`0 \leq c_k < b, k = 0, 1, \ldots, n`.
Ekkor az :math:`x` érték a következőképpen számítható ki:

.. math::

    x = c_n \cdot b^n + c_{n-1} \cdot b^{n-1} + \cdots + c_1 \cdot b^1 + c_0 \cdot b^0.

Feltételezhetjük, hogy :math:`c_n \neq 0`, és :math:`c_k = 0`, hogy ha :math:`k > n`.

A számrendszer alapszámát a szám jobb alsó sarkában alsó félkörrel vagy bekarikázva jelöljük, például: :math:`1234_{(5)}`.

**10 feletti számrendszerek**

Amennyiben egy számjegy értéke nagyobb lenne, mint 9, akkor a latin ábécé betűit használjuk számjegyként.

.. math::

    A = 10, B = 11, C = 12, D = 13, E = 14, F = 15, G = 16, \ldots, Z = 35

https://hu.wikipedia.org/wiki/Sz%C3%A1mrendszer

**Kitüntetett jelentőségű számrendszerek**

* 2-es: bináris számrendszer
* 7-es: az ősmagyarok ezt használták
* 8-as: UNIX-szerű rendszerekben jogosultságkezelés kapcsán használatos
* 10-es: tipikusan ezt használjuk
* 16-os: hexadecimális számrendszer, byte-ok értékének egy jellemző leírási módja

https://tudasbazis.sulinet.hu/hu/matematika/matematika/matematika-5-osztaly/szamirasok/a-szamiras-fejlodese

Egész számok számrendszeri átváltása
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. csv-table::
   :header-rows: 1

   :math:`x`,:math:`b`
   :math:`x_1 = x \text{ div } b`,:math:`c_0 = x \text{ mod } b`
   :math:`x_2 = x_1 \text{ div } b`,:math:`c_1 = x_1 \text{ mod } b`
   :math:`x_3 = x_2 \text{ div } b`,:math:`c_2 = x_2 \text{ mod } b`
   :math:`\vdots`,:math:`\vdots`
   :math:`x_n = x_{n-1} \text{ div } b`,:math:`c_{n-1} = x_{n-1} \text{ mod } b`
   :math:`0`,:math:`c_n = x_n \text{ mod } b`

**Példa**

Írjuk fel a 3456 értéket 8-as számrendszerben!

Törtek
~~~~~~

Egy szám törtrésze helyiértékes számrendszerben, általános alakban:

.. math::

  0,c_{1}c_{2}c_{3} \ldots c_{k} \ldots

A szám értékének meghatározása:

.. math::

	x = \dfrac{c_1}{b^1} + \dfrac{c_2}{b^2} + \dfrac{c_3}{b^3} + \cdots + \dfrac{c_k}{b^k} + \cdots

Számrendszeri átváltás:

.. csv-table::
   :header-rows: 1

   :math:`b`,:math:`x`
   :math:`c_1 = \lfloor x \cdot b \rfloor`,:math:`x_1 = \{ x \cdot b \}`
   :math:`c_2 = \lfloor x_1 \cdot b \rfloor`,:math:`x_2 = \{ x_1 \cdot b \}`
   :math:`c_3 = \lfloor x_2 \cdot b \rfloor`,:math:`x_3 = \{ x_2 \cdot b \}`
   :math:`\vdots`,:math:`\vdots`
   :math:`c_k = \lfloor x_{k-1} \cdot b \rfloor`,:math:`x_k = \{ x_{k-1} \cdot b \}`
   :math:`\vdots`,:math:`\vdots`


Horner-séma
~~~~~~~~~~~

**Egészek átváltása**

.. math::

  x = (\ldots ((c_n) \cdot b + c_{n-1}) \cdot b + \cdots + c_1) + c_0

**Törtek átváltása**

.. math::

  x = (\ldots (((c_n) / b + c_{n-1}) / b + c_{n-2}) / b + \cdots c_1) / b


Számjegyek számáról szóló tétel
-------------------------------

**Tétel**

Jelöljön :math:`x` egy nemnegatív egész számot, melynek a számjegyeit általánosan a

.. math::

  c_n, c_{n-1}, \ldots, c_1, c_0

alakban tudunk felírni. Az :math:`x` szám számjegyeinek a száma :math:`b` alapú számrendszerben

.. math::

  n + 1 = \left\lfloor \log_b x \right\rfloor + 1.

**Bizonyítás**

A helyiértékes alakból írjuk fel :math:`x` értékét:

.. math::

  x = c_n \cdot b^n + c_{n-1} \cdot b^{n-1} + \cdots + c_1 \cdot b^1 + c_0 \cdot b^0.

Emeljük ki :math:`b^n`-t:

.. math::

  x = b^n \cdot \left( c_n + \dfrac{c_{n-1}}{b} + \cdots + \dfrac{c_1}{b^{n-1}} + \dfrac{c_0}{b^n} \right)

Jelöljük a zárójelben lévő részt :math:`y`-al:

.. math::

  x = b^n \cdot y.

Teljesül, hogy :math:`1 \leq c_n \leq y < b`, amiből logaritmust véve azt kapjuk, hogy

.. math::

  0 \leq \log_b y < 1.

Az :math:`x = b^n \cdot y` kifejezésnek vegyük a logaritmusát:

.. math::

  \log_b x = n \cdot \log_b b + \log_b y.

Az előbbiből azt kapjuk, hogy

.. math::

  n + \log_b y = \log_b x.

Mindkét oldal alsóegészrészét véve:

.. math::

  n = \left\lfloor \log_b x \right\rfloor

alakot kapjuk (mivel :math:`n` egész és :math:`\left\lfloor \log_b y \right\rfloor = 0`).
Mindkét oldalhoz 1-et hozzáadva megkapjuk a bizonyítandó összefüggést.


Kérdések
========

Halmazok
--------

* Tetszőleges :math:`A` és :math:`B` halmazok esetén mennyi eleme lesz az :math:`A \times B` Déscartes szorzatnak?
* Asszociatív művelet-e a Déscartes szorzat? Lássuk is be!
* Kommutatív művelet-e a Déscartes szorzat? Lássuk is be!
* Mennyi eleme lesz az :math:`E^3` halmaznak, ha :math:`E = \{1, 2, 3, 4\}`?

Műveletek
---------

* Milyen példák lehetnek unáris és bináris műveletekre!
* Előfordulhat-e, hogy egy számnak megegyezik az alsó- és felsőegész része? Ha igen, akkor adjon rá példát, ha nem akkor lássa be, hogy miért nem!
* Hogyan néz ki azon számok halmaza, melyek kerekített értéke megegyezik a felsőegész részükkel?
* Hogy ha az :math:`a` és :math:`b` érték szorzatát szeretnénk kiszámolni Orosz-paraszt módszerrel, akkor mennyi sora lesz a táblázatnak? (Fejlécet és a táblázat végén lévő 0-ás sort nem számítva.)
* Hogyan ábrázolható az alsóegészrész függvény?
* Hogyan ábrázolható a felsőegészrész függvény?
* Hogyan ábrázolható a kerekítő függvény?
* Hogyan ábrázolható a törtrész függvény?

Feladatok
=========

Adatmennyiség
-------------

* Mennyi bitminta képezhető 10 biten?
* Mennyi olyan bitminta alakítható ki egy byte-on, amelyik a ``01`` bitekkel kezdődik?
* Mennyi olyan bitminta van egy byte-on, amely azonos számú ``0``-át és ``1``-est tartalmaz? (Írjuk fel az összefüggést általánosan :math:`n`-re!)
* Mennyi bitje van egy duplaszónak?

Adattípusok
-----------

* Írjuk fel a valós számokhoz tartozó absztrakt adattípust a 4 alapművelettel!

Halmazok
--------

Tekintsük az :math:`A = \{p, q, r\}` és :math:`B = \{5, 8\}` halmazokat!

* Írjuk fel az :math:`A \times A, A \times B, B \times A, B \times B` Déscartes szorzatokat!
* Írjuk fel a :math:`2^A`, :math:`2^B` halmazokat!
* A halmazok kiszámítása előtt határozzuk meg azok elemszámát!

Határozzuk meg az :math:`|A^7 \times B^8|` értéket, hogy ha :math:`A = \{5, 9, x\}, B = \{\gamma, -4\}`.

Műveletek
---------

* Számítsuk ki a 90 és a 179 szorzatát Orosz-paraszt módszerrel! Nézzük meg mindkét sorrendben elvégezve a műveletet!
* Adjunk példákat alsó- és felsőegészrész, kerekítés és törtrész számítására pozitív és negatív racionális számok esetén!
* Vizsgáljuk meg a :math:`27` és :math:`5` értékekkel, a lehetséges pozitív és negatív előjelekkel a ``div`` és a ``mod`` műveletek eredményeit!
* Vizsgáljuk meg, hogy teljesül-e az alábbi összefüggés!

.. math::

    \text{Round}(x) =
    \left\lfloor x + \dfrac{1}{2} \right\rfloor =
    \left\lceil x - \dfrac{1}{2} \right\rceil

* Adjon példát olyan :math:`a, b \in \mathbb{Z}` értékekre, amelyekre teljesül, hogy :math:`a \text{ div } b = a \text{ mod } b`.

Számrendszerek
--------------

* Milyen értéket ábrázolnak a

.. math::

  7532_{(10)}, 10111010_{(2)}, 25136_{(7)}, 8FB2_{(16)}, 121020_{(3)}, 444_{(5)}, 5566_{(8)}

értékek?

* Írjuk fel a 2021 értéket 2, 3, 4, 7, 8, 10, 11, 16-os számrendszerben! Vizsgáljuk meg a 2, 4, 8, 16 számrendszerek közötti összefüggéseket a számalakok alapján!
* Ellenőrízzük a számításokat Horner sémával!
* Végezzük el a következő műveleteket számrendszeri átváltás nélkül:

.. math::

    &1011101_{(2)} + 11001_{(2)} \\
    &2133_{(4)} + 321_{(4)} \\
    &43705_{(8)} + 1162_{(8)} \\
    &30112_{(5)} + 4040_{(5)} \\

* Adjunk össze a 4190 és a 618 számokat 8-as, 9-es és 15-ös számrendszerben!
* Mennyi számjegyből fog állni a 62982 szám 2, 3, 6, 10, 15, 16-os számrendszerben?
