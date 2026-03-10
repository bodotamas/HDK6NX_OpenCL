4. Adatstruktúrák
=================

Tömbök, vektorok
----------------

* Azonos típusú elemek sorozata.
* Minden elemet egy index segítségével tudunk hivatkozni.
* Matematikában az indexelés jellemzően 1-től indul, informatikában 0-tól.
* Ugyanazon elem/érték többször is előfordulhat az adatszerkezetben.

Halmaz típus
------------

* Elemek összessége.
* Minden elemről el tudjuk dönteni, hogy a halmazhoz tartozik-e vagy nem.
* Az :math:`\in` (*eleme*) operátor bináris operátornak is tekinthető.
* Minden elem csak egyszer szerepelhet a halmazban.
* Az elemek sorrendjére a halmazon belül nem vagyunk tekintettel. (Az elemek maguk egyébként lehetnek rendezhetőek.)
* A halmazokat jellemzően a latin ábécé nagy betűivel jelöljük.

Egy halmaz megadásának többféle módja van.

* Felsorolhatjuk az elemeit.
* Megadhatunk egy tulajdonságot, ami alapján el tudjuk dönteni, hogy egy elem a halmazhoz tartozik vagy sem.
* Mefogalmazhatunk halmazokra vonatkozó kifejezéseket.


Az üres halmazt :math:`\emptyset` jellel jelöljük.

Az alaphalmazt :math:`H`-val vagy :math:`U`-val szokták jelölni.

**Számosság**

* A halmazok számosságát függőleges vonalakkal jelöljük, például :math:`|A|`.

A halmaz számossága lehet

* véges,
* megszámlálhatóan végtelen,
* nem megszámlálhatóan végtelen (*kontinuum sok*).

Véges halmazok esetében teljesülnek az alábbiak.

.. math::

  |A| \geq 0

.. math::

  |X| = 0 \Leftrightarrow X = \emptyset

.. math::

  A \cap B = \emptyset \Leftrightarrow |A \cup B| = |A| + |B|

.. math::

  |A \cup B| = |A| + |B| - |A \cap B|

**Részhalmaz**

.. math::

  B \subseteq A

* Hogy ha egy elem eleme :math:`B`-nek, akkor szükségszerűen eleme :math:`A`-nak is.
* :math:`\forall x, x \in B \Rightarrow x \in A`.

**Valódi részhalmaz**

.. math::

  B \subset A

* :math:`B` részhalmaza :math:`A`-nak.
* :math:`A`-nak van olyan eleme, amely nem eleme :math:`B`-nek.
* :math:`\exists x, x \in A, x \notin B`.

.. math::

  B \subseteq A \Rightarrow |B| \leq |A| \\
  B \subset A \Rightarrow |B| < |A| \\


A szokásos relációs jelekhez hasonlóan használatban van a :math:`\supseteq` és a :math:`\supset` jelölés is.
(Nem annyira gyakori.)

Sajnos a jelölésrendszer nem egységes.

* Nem mindig különböztetik meg a valódi részhalmazt.
* A :math:`\subseteq` és a :math:`\subset` operátorokat van hogy szinonímaként használják.

https://hu.wikipedia.org/wiki/R%C3%A9szhalmaz

**Halmazok egyenlősége**

.. math::

  A = B \Leftrightarrow (A \subseteq B \text{ és } B \subseteq A)

.. math::

  A = B \Leftrightarrow (x \in A \Leftrightarrow x \in B)

Jelölhető az is, hogy ha nem egyenlőek: :math:`A \neq B`.

**Halmazok ekvivalenciája**

Két halmazt ekvivalensnek nevezünk, hogy ha létezik közöttük kölcsönösen egyértelmű megfeleltetés.

* Jelölése: :math:`A \sim B`

.. math::

  A \sim B \Rightarrow |A| = |B|

**Diszjunkt halmazok**

Két halmazt diszjunktnak nevezünk, hogy ha nincs közös elemük.

.. math::

  A \cap B = \emptyset

Halmaz műveletek
~~~~~~~~~~~~~~~~

**Komplementer képzés**

* Unáris művelet.
* A negáláshoz hasonlóan felülvonással jelöljük, például az :math:`A` halmaz komplementere :math:`\overline{A}`.

.. math::

  \overline{H} = \emptyset, \quad \overline{\emptyset} = H

Tegyük fel, hogy :math:`p` egy állítás (predikátum). Ennek egy tetszőleges elem a paramétere és logikai értéket ad vissza.
Definiáljuk az :math:`A` halmazt a következőképpen:

.. math::

  A = \{a \mid p(a) \text{ igaz}\}

Ekkor az :math:`A` komplementer halmaza:

.. math::

  \overline{A} = \{a \mid p(a) \text{ hamis}\}

Két halmaz között értelmezett bináris műveletek:

**Metszet**

.. math::

  A \cap B = \{ x \mid x \in A \text{ és } x \in B\}

**Unió**

.. math::

  A \cup B = \{ x \mid x \in A \text{ vagy } x \in B\}

**Különbség**

.. math::

  A \setminus B = \{ x \mid x \in A \text{ és } x \notin B\}

**Szimmetrikus differencia**

.. math::

  A \triangle B = (A \setminus B) \cup (B \setminus A)

A szimmetrikus differenciát az alábbi módokon szintén felírhatjuk.

.. math::

  \begin{align*}
  A \triangle B &= (A \cup B) \setminus (A \cap B) \\
  &= (A \cap \overline{B}) \cup (B \cap \overline{A}) \\
  &= (A \cup B) \cap (\overline{A} \cup \overline{B}) \\
  &= (A \cup B) \cap \overline{A \cap B}
  \end{align*}

.. warning::

	A korábban említett Descartes szorzat, halmaz hatványa és a hatványhalmaz is halmazművelet.


Műveletek tulajdonságai
~~~~~~~~~~~~~~~~~~~~~~~

.. math::

  \overline{\overline{A}} = A

**Kommutativitás**

.. math::

  A \cap B = B \cap A, \quad A \cup B = B \cup A

**Asszociativitás**

.. math::

  (A \cap B) \cap C = A \cap (B \cap C), \quad (A \cup B) \cup C = A \cup (B \cup C)

**Disztributivitás**

.. math::

  A \cap (B \cup C) = (A \cap B) \cup (A \cap C), \quad A \cup (B \cap C) = (A \cup B) \cap (A \cup C)

**De Morgan azonosság**

.. math::

  \overline{A \cap B} = \overline{A} \cup \overline{B}, \quad \overline{A \cup B} = \overline{A} \cap \overline{B}

**További összefüggések**

.. math::

  A \cap \emptyset = \emptyset, \quad A \cup \emptyset = A \\
  A \cap A = A, \quad A \cup A = A \\
  A \cap \overline{A} = \emptyset, \quad A \cup \overline{A} = H \\
  A \cap H = A, \quad A \cup H = H


Azonosságok vizsgálata
~~~~~~~~~~~~~~~~~~~~~~

Hogy ha halmazkifejezések egyenlőségét szeretnénk vizsgálni, azt hasonlóképpen tehetjük, mint a logikai kifejezések esetében. Praktikusan 3 féle megközelítés képzelhető el.

* Az egyenlőség bal oldalán szereplő kifejezést addig alakítjuk, amíg meg nem kapjuk a jobb oldalit.
* Az egyenlőség jobb oldalán szereplő kifejezést addig alakítjuk, amíg meg nem kapjuk a bal oldalit.
* Mind a két oldalon szereplő kifejezéseket elkezdjük alakítani, amíg azonos alakra nem sikerül hozni azokat.

**Példa**

Lássuk be, hogy a szimmetrikus differencia művelete asszociatív!

**Megoldás (formális levezetéssel)**

Az :math:`(A \triangle B) \triangle C = A \triangle (B \triangle C)` összefüggést kell belátni.

Bal oldal, és az átalakítása:

.. math::

  \begin{align*}
  &(A \triangle B) \triangle C = \\
  &((A \triangle B) \cap \overline{C}) \cup (C \cap \overline{A \triangle B}) = \\
  &(((A \cap \overline{B}) \cup (B \cap \overline{A})) \cap \overline{C}) \cup
  (C \cap \overline{(A \cup B) \cap (\overline{A} \cup \overline{B}}) = \\
  &(A \cap \overline{B} \cap \overline{C}) \cup (\overline{A} \cap B \cap \overline{C}
  \cup (\overline{A} \cap \overline{B} \cap C) \cup (A \cap B \cap C)
  \end{align*}

Jobb oldal, és az átalakítása:

.. math::

  \begin{align*}
  &A \triangle (B \triangle C) = \\
  &(A \cap \overline{B \triangle C}) \cup ((B \triangle C) \cap \overline{A}) = \\
  &(A \cap \overline{(B \cup C) \cap (\overline{B} \cup \overline{C})}) \cup
  (((B \cap \overline{C}) \cup (C \cap \overline{B})) \cap \overline{A}) = \\
  &(A \cap \overline{B} \cap \overline{C}) \cup (\overline{A} \cap B \cap \overline{C})
  \cup (\overline{A} \cap \overline{B} \cap C) \cup (A \cap B \cap C)
  \end{align*}

Láthatjuk, hogy mindkét oldal esetében azonos eredményt kaptuk, így kijelenthetjük, hogy a szimmetrikus differencia művelete asszociatív.

**Megoldás (Venn diagrammal)**

Mivel 3 halmazról van szó, ezért felrajzolhatjuk a bal és jobb oldalon szereplő kifejezések Venn diagramjait.

Az :math:`A \triangle B` elemeit a következőképpen ábrázolhatjuk:

.. image:: images/symdiff/a_b.svg

Ez alapján az :math:`(A \triangle B) \triangle C`:

.. image:: images/symdiff/a_b_c.svg

A :math:`B \triangle C` ábrázolása:

.. image:: images/symdiff/b_c.svg

Ez alapján az :math:`A \triangle (B \triangle C)`:

.. image:: images/symdiff/a_b_c.svg

Láthatjuk, hogy mindkettő esetében azonos eredményre jutottunk, így kijelenthetjük, hogy az összefüggés teljesül.

**Megoldás (halmazműveletre visszavezetéssel)**

Vegyük észre, hogy :math:`A \triangle B = \{x|(x \in A) \oplus (x \in B)\}` teljesül!

Ez alapján az azonosság ekvivalens az alábbi azonossággal:

.. math::

  (a \oplus b) \oplus c = a \oplus (b \oplus c),

ahol az :math:`a = (x \in A), b = (x \in B), c = (x \in C)` logikai értékek.

Amennyiben ismertnek tekintjük, hogy a :math:`\oplus` művelet asszociatív, úgy a szimmetrikus differenciára vonatkozó asszociativitás is közvetlenül következik.

Halmaz implementációja
~~~~~~~~~~~~~~~~~~~~~~

**Halmazhoz tartozás tárolása bitek tömbjében**

* Tegyük fel, hogy végessok elemünk van.
* Az elemeket egy tömbben tároljuk.
* Minden indexhez rendelhetünk egy bitet, annak megfelelően, hogy az adott elem a halmazhoz tartozik vagy sem.

Előnyei

* A halmazműveletek kézenfekvő módon, hatékonyan megvalósíthatók.
* Egyszerűen ellenőrízhető, hogy egy elem hozzátartozik-e az adott halmazhoz, vagy sem.

Hátrányai

* Előre tudni kell, hogy mennyi elemünk lesz.
* Az elemek sorrendjét és a bittömböt szinkronban kell tartani.
* A biteket közvetlenül tipikusan nem lehet elérni, csak byte szintjén.

**Halmazhoz tartozás jelölése az elemeken**

Minden elemhez megadhatunk plusz egy bit információt, attól függően, hogy az adott elem a halmazhoz tartozik-e vagy sem.

Előnyei

* A halmazhoz tartozás, mint adat hozzátartozik így az elemhez. Könnyen elérhető, állítható.
* Nem kell külön foglalkozni az elemsorrend megtartásával.

Hátrányai

* A halmazhoz való tartozás így szorosan kötődik az elemhez.
* Jellemzően nem egy olyan információról van szó, amit eleve az elemhez tartozónak tekintenénk.
* A plusz egy bit általában legalább egy byte lefoglalását jelenti.
* A halmazműveletek végrehajtásához minden elemen külön-külön végig kell menni.

**Halmazhoz való tartozás hivatkozásainak sorozata**

* Egy külön adatszerkezetbe összegyűjthetjük a halmazhoz tartozó elemek hivatkozásait.
* Ehhez az adatszerkezet lehet például tömb vagy lista.
* A hivatkozások lehetnek az indexek (vagy az elemek egyéb egyedi azonosítói).

Előnyei

* A tárigény a halmaz méretével arányos.
* A tárolt elemeken nem tesz szükségessé változtatást.
* A halmazműveleteket a hivatkozások szintjén el lehet végezni.

Hátrányai

* A halmazhoz való tartozás ellenörzése számításigényes.
* A hivatkozások mérete a biteknél jóval több tárat igényelnek.

Karakter adattípus
------------------

* Grafikus szimbólumok.
* Nyelvtől függ, hogy mennyi jelentés tartozik hozzájuk.
* Általában egy karakterkészletről van szó. (Kontextusukban tudjuk csak kezelni őket.)
* A céljunk velük, hogy bizonyos szabályokat követve szövegeket tudjunk velük megadni (*kódolni*).

Az informatikában a karaktereket tipikusan osztályozni szokták.

* Vezérlőkarakterek
* Betűk (kis- és nagy betűk)
* Számok
* Fehér karakterek
* Ablak rajzoló karakterek
* Emotikonok

.. warning::

  A felsorolás nem teljes. Bonyolultabb a problémakör, mint amilyennek tünik.

* A karakterkészlet jellemzően rendezett.
* Számok esetében a természetes-, betűk esetében a lexikális rendezés szokott előfordulni.

**ASCII**

* *American Standard Code for Information Interchange*
* Napjainkig is az egyik legelterjedtebb szabvány.
* Tartalmaz olyan karaktereket, amely a TUI (*Terminal User Interface*) elemeinek kirajzolásához szükséges.

Van 7 és 8 bites változata.

* 7 bit esetén a 8. bit hibajavító kódoláshoz fenntartható volt. (A kommunikáció alacsonyabb szintjén a hibamentességhez ez hozzá tudott segíteni.)
* A nemzetközi felhasználás során a felső 128 karaktert fenntartották különböző kódtáblák számára. Ide kerültek például a magyar ékezetes betűk is (Latin-2 kódtábla).
* A kódlap kiválasztására nem vezettek be/terjedt el külön szabvány. A szoftverben kellett azt megadni, hogy hogy szeretnénk az adatokat értelmezni.

https://hu.wikipedia.org/wiki/ASCII

https://en.wikipedia.org/wiki/ASCII_art

**Unicode**

* Az összes használatban lévő karaktert igyekeztek egységesíteni. (A névben az *uni* erre vonatkozik.)
* A szabvány 1.0 verziója 1991-ben jelent meg.
* Minden karakterhez egy egyedi kódpontot (gyakorlatilag sorszámot) rendeltek.
* [0, 10FFFF] számok tartománya
* Összesen 1114112 kódpont a kódtér mérete.
* Az európai nyelvekben használt karakterek az első 65536-ban benne vannak.

A kódpontok megadásához megadtak egy formátumot:

.. code::

  U+xxxx  U+xxxxx  U+xxxxxx

* Ebben az x-ek hexadecimális számjegyeket jelölnek.
* Hogy ha a kódpont kevesebb mint 4 hexadecimális számjegyet tartalmazna, akkor ki kell írni a 0-ákat elé.

A kódpont, mint számérték implementációjához 3 ajánlást is megadtak:

* UTF-8
* UTF-16
* UTF-32

UTF: *Unicode Transmission Format*

Ebben a számértékek a kezelési egységek méretét adják meg bitekben.

https://home.unicode.org/

**UTF-8**

* Byte orientált kódolás
* Ez aktuálisan az Internet-en történő kommunikáció javasolt szabványa.
* Valamelyest entrópia kódolásnak is tekinthető, mivel jellemzően a kisebb kódpontok gyakrabban fordulnak elő.

Egy keretformátumról van szó, amelyben a kódpont, mint számérték változó hosszúságú byte-sorozattal adható meg.

* A 0-ás bittel kezdődő byte-ok a 7 bites ASCII karaktereket írják le. (Így felülről kompatibilis tud lenni az ASCII 7 bites kódolással.)
* Több byte-os keret esetében az első byte-on az egymást követő 1-es bitek száma adja meg, hogy milyen hosszú lesz a keret.
* A folytatásbyte-ok az 10 bitsorozattal kezdődnek.

A keretformátum elvileg tetszőleges hosszúságú karaktert le tudna írni, de az RFC3629-ben 4 byte-ban maximálták.

.. code::

                             0.......
                    110..... 10......
           1110.... 10...... 10......
  11110... 10...... 10...... 10......

https://en.wikipedia.org/wiki/UTF-8

*Példa*

Kódoljuk az ``U+4CB3`` Unicode kódpontot UTF-8 kódolással!

Bináris alakban:

.. code::

  100 1100 1011 0011

A kódoláshoz 15 bitre van szükség. :math:`\Rightarrow` 3 byte-os keretben tárolható.

.. code::

  1110.... 10...... 10......
  11100100 10110010 10110011

Az ``U+4CB3`` karakter az ``E4 B2 B3`` hexadecimális alakban megadott byte-okon ábrázolható.

**Betűtípusok**

* A karakterkódoláshoz szorosan nem tartozik hozzá.
* Az egyes karakterkódokhoz tartoznak szimbólumok.
* Javaslatok vannak arra vonatkozóan, hogy egy-egy karaktert milyen formában kell/célszerű megjeleníteni.
* A karakterkészlet lefedettsége nem mindig teljes.

Sztring típus és műveletei
--------------------------

A karaktereket egymás után tudjuk fűzni, így karakterláncot, sztringeket kapunk.

**Üres szimbólum**

.. math::

  \varepsilon = A^0

**Halmaz * halmaza**

.. math::

  A^* = A^0 \cup A^1 \cup A^2 \ldots \cup A^n \cup \ldots

**Halmaz + halmaza**

.. math::

  A^+ = A^1 \cup A^2 \ldots \cup A^n \cup \ldots = A^* \setminus \varepsilon

**Sztring**

Jelölje :math:`X` a karakterek halmazát. Ekkor a sztring adattípus alaphalmazát az :math:`S = X^*` formában definiálhatjuk.
Az :math:`\varepsilon` ekkor az üres sztring.

**Karakter literálok**

* Egy karakterlánc közvetlenül leírt alakját karakter literálnak nevezzük. Ezt a programozási nyelvekben jellemzően aposztrófok vagy idézőjelek között adják meg.
* A C programozási nyelv esetében a sztring literálok megadásához idézőjelet használnak, például:

.. code:: cpp

  char[] s = "string literal";

**Hossz**

* A karakterláncok egyik legfontosabb attribútuma a hosszuk.
* Pszeudókódokban ezt majd a ``Hossz`` attribútumnévvel fogjuk megadni.

**Konkatenáció**

* Karakterláncokat a konkatenáció műveletével tudunk egymás mögé fűzni.
* Egy bináris műveletről van szó, mely két sztringhez egy harmadikat rendel.
* A művelet asszociatív, de nem kommutatív.
* Jelölése: :math:`\bullet`

*Példa*

.. math::

  s = '\text{abc}', \quad z = '\text{minta}', \quad s \bullet z = '\text{abcminta}'

**Implementációja**

*Pascal konvenció*

* Hossz prefixes tárolás
* Pascal sztringként szokás említeni, mivel az egyik elterjedt Pascal implementáció ezt a konvenciót követte.
* A tárolásnál az adatstruktúra elején a szöveg hossza szerepel, majd azt követően jönnek a karakterek.

https://en.wikipedia.org/wiki/String_(computer_science)#Length-prefixed

Például ábrázoljuk a ``minta`` szót!

.. code::

  __  m  i  n  t  a
  05 6D 69 6E 74 61

*C konvenció*

* Nullával végződő sztringek
* *Zero terminated string*, ASCIIZ implementáció
* A C nyelvre, és leszármazottjaira jellemző.
* Az adatstruktúra közvetlenül a tárolt karakterekkel kezdődik.
* A 0 érték jelzi azt, hogy véget ért a szöveg.

A ``minta`` szó ábrázolása:

.. code::

   m  i  n  t  a __
  6D 69 6E 74 61 00

**Fehér karakterek eltávolítása**

* Fehér karakterként jellemzően a szóköz, sortörés és a tabulátor karakter szokott előfordulni.
* Feltételezve, hogy a szöveg elején és végén nem szükségesek, ezért gyakori művelet ezek eltávolítása.
* *trim* vagy *strip* műveletként szokás emlegetni.
* Tulajdonképpen egy :math:`S \rightarrow S` függvényről van szó.

Példa: Távolítsuk el a sztringek elejéről és végéről a (decimálisan) 32-es kódú szóközöket! A szövegek nullra végződő szövegláncként kerültek tárolásra:

.. code::

  6D 69 20 20 00 20 61 74 00 69 20 69 00

A megoldás:

.. code::

  6D 69 00 61 74 00 69 20 69 00

Adjuk meg a Pascal konvenció szerinti változatát is:

.. code::

  02 6D 69 02 61 74 03 69 20 69

Rekordok
--------

* Adatokat egy rendezett :math:`n`-esként tudunk kezelni.
* Formailag egy Descartes szorzatról van szó.
* A C nyelvben a ``struct`` kulcsszóval megadott struktúra a megfelelője.

Dátum és idő kezelése
---------------------

* A dátumot tárolhatjuk például rekordként.
* Év, hónap, nap, óra, perc, másodperc, ezredmásodperc

Egy hatékonyabb megvalósítás a UNIX time.

* A másodperceket számolja 1970. január 1. óta.
* 32 bites előjeles egész értéket választottak az ábrázolásához.

https://en.wikipedia.org/wiki/Unix_time

Kérdések
========

* Hogyan láthatjuk be, hogy az :math:`A = [0, 4]` és a :math:`B = [10, 14]` halmazok ekvivalensek?
* Hogyan láthatjuk be, hogy az :math:`X = [0, 1)` és az :math:`Y = [10, 20)` halmazok ekvivalensek?
* Legalább és legfeljebb mennyi karakter ábrázolható 50 byte-on UTF-8 kódolással?
* 40 UTF-8 keretformátumú karakter tárolásához legalább és legfeljebb mennyi byte szükséges?
* Egy UTF-8 kódolású karakterben a folytatás byte értéke milyen intervallumon változhat előjel nélküli egészként értelmezve?
* Egy 3 byte hosszúságú UTF-8 karakter kezdőbyte-ja milyen értéket vehet fel előjel nélküli egészként értelmezve?

Feladatok
=========

Halmazok
--------

* Tegyük fel, hogy adottak az :math:`A` és :math:`B` halmazok. Tudjuk, hogy :math:`|A| = |B| = 8`. A halmazhoz való tartozást egy külön bittömb segítségével oldjuk meg.

.. math::

  A = [0, 1, 1, 0, 1, 1, 1, 0] \\
  B = [1, 1, 1, 0, 1, 0, 0, 1]

Számítsuk ki, hogy a :math:`C = A \triangle B` halmaz hogyan ábrázolható bittömb formájában!

* Igazoljuk a következő egyenlőségeket!

.. math::

  \overline{A \setminus B} \cap (\overline{A} \cup \overline{B}) = \overline{A}

.. math::

  A \cap (\overline{A \setminus B}) = A \cap B

.. math::

  \overline{(P \setminus Q) \bigtriangleup R} = (\overline{R} \cup P) \cap (\overline{R} \cup \overline{Q}) \cap (\overline{P} \cup Q \cup R)

.. math::

  A \setminus (B \setminus (C \setminus D)) = A \cap (\overline{B} \cup \overline{C} \cup D)

.. math::

  C \cap (A \bigtriangleup B) = A \cap \overline{B} \cap C, \text{ ha } B \text{ és } C \text{ diszjunkt}.

.. math::

  (K \cap L) \setminus (K \setminus M) = K \cap L \cap M

.. math::

  (K \setminus L) \setminus M = (K \setminus M) \setminus (L \setminus M)

.. math::

  \overline{P \bigtriangleup Q} \setminus R = (\overline{P} \cup Q) \cap (P \cup \overline{Q}) \cap \overline{R}

* Mennyi olyan halmazpár van, amelyeknek a metszete :math:`\{a, b, c\}` uniója pedig :math:`\{a, b, c, d, e, f\}`?

* Tekintsük az :math:`A = (-5; 4]` és a :math:`B = [3; 9)` intervallumokat. Határozzuk meg a következő kifejezések értékét:

.. math::

  A \cup B, A \cap B, A \setminus B, B \setminus A, A \bigtriangleup B, A \times B, 2^A, 2^B

* Írjuk fel a :math:`2^{2^{\{a, b\}} \setminus \{b\}}` halmaz elemeit!

* Ha :math:`|H| = 60, A \subset H, B \subset H, |A| = 48, |B| = 32` akkor mennyi lesz :math:`|A \cup B|` és :math:`|A \cap B|`?

Karakterkódolás
---------------

* Ábrázoljuk a következő karaktereket UTF-8 és UTF-32 ábrázolással!

.. code::

  U+0048, U+082C, U+10EE65, U+9AF1

* Adja meg UTF-8 kódolást feltételezve az ``E2 C3 D8`` byte-okon ábrázolt kódpontot!

* Adjuk meg az UTF-8 keretformátum szerint byte-onként az első és az utolsó ábrázolható Unicode kódpontot. (Sorrendnek a kódpontok számérték szerinti rendezettségét tekintjük.)

Sztringek
---------

* Írjuk fel az alábbi halmaz elemeit!

.. math::

  Z = \{z \mid z \in \{2, 3\}^*, \text{Hossz}[z] < 3\}

* 3 sztringet tárolunk ASCIIZ kódolással a következő byte-okon:

.. code::

  FA BC 00 AB 81 AC DE 00 CE CE 00

Írja fel Pascal konvenció szerint tárolva az ábrázoláshoz szükséges byte-okat!

* A következő byte-okon ASCIIZ kódolású szövegek szerepelnek. Rakja őket hosszúság szerint növekvő sorrendbe!

.. code::

  70 66 67 00 00 71 72 00 48 00

* Feltételezve, hogy alfanumerikus karaktereket tartalmazó Pascal konvenció szerint tárolt szövegekről van szó, rakja őket ábécé sorrendbe! (Az eredmény szintén Pascal konvenció szerint kerüljön tárolásra!)

.. code::


  02 80 77 03 63 71 72 01 81

* Konkatenálja össze a következő, ASCIIZ formátumban megadott szövegeket! Az eredményt ASCIIZ formátumban adja vissza!

.. code::

  FA BC 00 AB 81 AC DE 00 CE CE 00

* Konkatenálja össze a következő, Pascal konvenció szerint tárolt szövegeket! Az eredményt szintén ilyen konvenció szerint adja meg!

.. code::

  02 80 77 03 63 71 72 01 81

* A szőköz a (decimálisan) 32-es karakterkóddal ábrázolható ASCII kódolással. A következőkben megadott byte-ok szövegeket tárolnak Pascal konvenció szerint. Törölje a szövegek elejéről és végéről a szóközöket, majd adja meg az eredményt szintén Pascal konvenció szerint!

.. code::

  03 65 20 20 04 68 20 20 73 01 20
