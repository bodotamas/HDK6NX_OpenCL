6. Elemi algoritmusok
=====================

**Rendezési reláció**

Egy olyan bináris rendezésről van szó, amely

* reflexív,
* tranzitív,
* antiszimmetrikus.

Jellemzően *teljes rendezést* szoktunk vizsgálni, melyre teljesül a linearitás is.

A sorozatokról megköveteljük, hogy bármely két eleme összehasonlítható legyen.

.. warning::

	Az, hogy egy sorozat elemein értelmezve van egy rendezési reláció, hogy vagy a sorozat rendezett, az két külön fogalom.

:math:`T` **tulajdonság**

Jelölje :math:`A` egy sorozat elemeinek a halmazát. :math:`T` tulajdonság alatt egy olyan függvényt értünk, amely az :math:`A` minden eleméhez hozzárendel egy logikai értéket.

.. math::

  T: A \rightarrow \{igaz, hamis\}

.. math::

  T(a) = \begin{cases}
  \text{igaz}, & \text{ha }a \in A\text{ egy }T\text{ tulajdonságú elem}, \\
  \text{hamis}, & \text{egyébként.} \\
  \end{cases}

**Általános bináris művelet jelölése**

Az algoritmusok egy részében egy konkrét bináris művelet helyett egy általánosat adunk meg, amelyet egy :math:`\square` jellel jelölünk, például :math:`x \square y`.

**Null elem**

Főként inicializálásnál hasznos, hogy ha az adott művelethez meg tudjuk adni a null elemet, amelyre teljesül, hogy :math:`a \square Null = a`, bármilyen :math:`a \in A` esetén.

Például:

* :math:`A = \mathbb{R}, \square = +` esetén :math:`Null = 0`.
* :math:`A = \mathbb{R}, \square = \cdot` esetén :math:`Null = 1`.
* :math:`A = S, \square = \bullet` esetében :math:`Null = ''` (üres sztring, :math:`\varepsilon`).

Elemi algoritmusok
------------------

Sorozatszámítás
~~~~~~~~~~~~~~~

* A sorozat értékeit egy értékben "összesíti".
* Szokás még aggregációnak, redukciónak is nevezni.

.. math::

  &REDUCE(@X, @s) \\
  &// Input: X sorozat, x_i \in A \\
  &// Output: s \in A \\
  &s \leftarrow Null \\
  &\text{FOR }i \leftarrow 1\text{ TO Hossz}[X]\text{ DO} \\
  &\quad s \leftarrow s \square x_i \\
  &\text{RETURN}(s) \\

:math:`\rhd` Adjuk meg a szumma, produktum és a szövegek összefűzésének esetét!

Eldöntés
~~~~~~~~

* Egy sorozat elemeit vizsgáljuk meg, hogy teljesül-e rájuk valamilyen :math:`T` tulajdonság.
* Tulajdonképpen 2 algoritmusról van szó, amelyeket együtt érdemes említeni.

Létezik a sorozatban :math:`T` tulajdonságú elem?

.. math::

  &\text{EXISTS}(@X, @van) \\
  &// Input: X sorozat, x_i \in A \\
  &// Output: Van \in \{igaz, hamis\} \\
  &i \leftarrow 1 \\
  &\text{WHILE }i \leq \text{Hossz}[X]\text{ AND }\overline{T(x_i)}\text{ DO}\\
  &\quad \text{INC}(i)\\
  &van \leftarrow (i \leq \text{Hossz}[X])\\
  &\text{RETURN}(van)\\

A sorozat minden eleme :math:`T` tulajdonságú?

.. math::

  &\text{ALL}(@X, @mind) \\
  &// Input: X sorozat, x_i \in A \\
  &// Output: mind \in \{igaz, hamis\} \\
  &i \leftarrow 1 \\
  &\text{WHILE }i \leq \text{Hossz}[X]\text{ AND }T(x_i)\text{ DO}\\
  &\quad \text{INC}(i)\\
  &mind \leftarrow (i > \text{Hossz}[X])\\
  &\text{RETURN}(mind)\\

Kiválasztás
~~~~~~~~~~~

* Egy :math:`T` tulajdonságú elemet keres meg a sorozatban.
* Az elem értékét, vagy indexét is visszaadhatja. (Az index esetünkben informatívabb, ezért itt most azt fogjuk visszaadni.)
* Feltételezzük, hogy biztosan van :math:`T` tulajdonságú elem a sorozatban.

.. math::

  &\text{FIND}(@X, @index)\\
  &// Input: X sorozat, x_i \in A\\
  &// Output: index \in \mathbb{N}\\
  &i \leftarrow 1\\
  &\text{WHILE }\overline{T(x_i)}\text{ DO}\\
  &\quad \text{INC}(i)\\
  &index \leftarrow i\\
  &\text{RETURN}(index)\\

Lineáris keresés
~~~~~~~~~~~~~~~~

* Az elem létezésének vizsgálatát és indexének a keresését kombinálja.

.. math::

  &\text{LINEAR_SEARCH}(@X, @van, @index)\\
  &// Input: X sorozat, x_i \in A\\
  &// Output: van \in \{igaz, hamis\}\\
  &// \quad index \in \mathbb{N}\\
  &i \leftarrow 1\\
  &\text{WHILE }i \leq \text{Hossz}[X]\text{ AND }\overline{T(x_i)}\text{ DO}\\
  &\quad \text{INC}(i)\\
  &van \leftarrow (i \leq \text{Hossz}[X])\\
  &\text{IF }van\\
  &\quad \text{THEN }index \leftarrow i\\
  &\text{RETURN}(van, index)\\

Megszámlálás
~~~~~~~~~~~~

* A sorozatban a :math:`T` tulajdonságú elemek számát adja vissza.

.. math::

  &\text{COUNT}(@X, @count)\\
  &// Input: X sorozat, x_i \in A\\
  &// Output: count \in \mathbb{Z}\\
  &count \leftarrow 0\\
  &\text{FOR }i \leftarrow 1\text{ TO Hossz}[X]\text{ DO}\\
  &\quad \text{IF }T(x_i)\\
  &\quad \quad \text{THEN INC}(count)\\
  &\text{RETURN}(count)\\

Maximum kiválasztás
~~~~~~~~~~~~~~~~~~~

* Feltételezzük, hogy a sorozat elemein értelmezve van egy teljes rendezés.
* A maximális értékű elem indexével térünk vissza.
* Feltételezzük, hogy a sorozatnak legalább egy eleme van.

.. math::

  &\text{MAX}(@X, @index)\\
  &// Input: X sorozat, x_i \in A\\
  &// Output: index \in \mathbb{N},\text{ a maximális elem indexe}\\
  &index \leftarrow 1\\
  &\text{FOR }i \leftarrow 2\text{ TO Hossz}[X]\text{ DO}\\
  &\quad \text{IF }x_i > x_{index}\\
  &\quad \quad \text{THEN }index \leftarrow i\\
  &\text{RETURN}(index)\\


:math:`\rhd` Hogy ha több maximális értékű elem is van, akkor melyik indexe kerül visszaadásra?

:math:`\rhd` Hogyan kezelhető az üres sorozatok esete?

:math:`\rhd` Hasonlóképpen adjuk meg a minimum számítását is!

Másolás
~~~~~~~

* A bemeneti sorozatot transzformálást követően egy kimeneti sorozatba másolja át.
* A transzformációt egy :math:`f: A \rightarrow B` függvény formájában adhatjuk meg.

.. math::

  &\text{MAP}(@X, @Y)\\
  &// Input: X sorozat, x_i \in A\\
  &// Output: Y sorozat, y_i \in B\\
  &\text{Hossz}[Y] \leftarrow \text{Hossz}[X]\\
  &\text{FOR }i \leftarrow 1\text{ TO Hossz}[X]\text{ DO}\\
  &\quad y_i \leftarrow f(x_i)\\
  &\text{RETURN}(Y)\\

Kiválogatás
~~~~~~~~~~~

* A bemeneti sorozatból kigyűjtjük a :math:`T` tulajdonságú elemeket a kimeneti sorozatba.

.. math::

  &\text{COLLECT}(@X, @Y)\\
  &// Input: X sorozat, x_i \in A\\
  &// Output: Y sorozat, y_i \in A\\
  &\text{Hossz}[Y] \leftarrow 0\\
  &\text{FOR }i \leftarrow 1\text{ TO Hossz}[X]\text{ DO}\\
  &\quad \text{IF }T(x_i)\\
  &\quad \quad \text{THEN INC}(\text{Hossz}[Y])\\
  &\quad \quad \quad \quad \quad y_{\text{Hossz}[Y]} \leftarrow x_i\\
  &\text{RETURN}(Y)\\

:math:`\rhd` Hasonlóképpen adható algoritmus az indexek kigyűjtésére is.

Szétválogatás
~~~~~~~~~~~~~

* A :math:`T` és nem :math:`T` tulajdonságú elemeket külön sorozatokba gyűjti.

.. math::

  &\text{ASSORT}(@X, @Y, @Z)\\
  &// Input: X sorozat, x_i \in A\\
  &// Output: Y sorozat, y_i \in A\\
  &// \quad \quad Z sorozat, y_i \in A\\
  &\text{Hossz}[Y] \leftarrow 0\\
  &\text{Hossz}[Z] \leftarrow 0\\
  &\text{FOR }i \leftarrow 1\text{ TO Hossz}[X]\text{ DO}\\
  &\quad \text{IF }T(x_i)\\
  &\quad \quad \text{THEN INC}(\text{Hossz}[Y])\\
  &\quad \quad \quad \quad \quad y_{\text{Hossz}[Y]} \leftarrow x_i\\
  &\quad \quad \text{ELSE INC}(\text{Hossz}[Z])\\
  &\quad \quad \quad \quad \quad z_{\text{Hossz}[Z]} \leftarrow x_i\\
  &\text{RETURN}(Y, Z)\\

Metszet
~~~~~~~

* A két bemeneti sorozatról feltételezzük, hogy azokban csak különböző elemek vannak.
* Tulajdonképpen a halmaz sorozat implementációját használjuk.
* A bemenetként adott halmazok metszetét adjuk meg kimenetként.

.. math::

  &\text{INTERSECTION}(@X, @Y, @Z)\\
  &// Input: X sorozat, x_i \in A\\
  &// \quad \quad \quad \; Y sorozat, y_i \in A\\
  &// Output: Z sorozat, z_i \in A\\
  &\text{Hossz}[Z] \leftarrow 0\\
  &\text{FOR }i \leftarrow 1\text{ TO Hossz}[X]\text{ DO}\\
  &\quad j \leftarrow 1\\
  &\quad \text{WHILE }(j \leq \text{Hossz}[Y])\text{ AND }(x_i \neq y_j)\text{ DO}\\
  &\quad \quad \quad \text{INC}(j)\\
  &\quad \text{IF }j \leq \text{Hossz}[Y]\\
  &\quad \quad \text{THEN INC}(\text{Hossz}[Z])\\
  &\quad \quad \quad \quad \quad z_{\text{Hossz}[Z]} \leftarrow x_i\\
  &\text{RETURN}(Z)\\

Egyesítés
~~~~~~~~~

* A két bemeneti sorozatról feltételezzük, hogy azokban csak különböző elemek vannak.
* Tulajdonképpen a halmaz sorozat implementációját használjuk.
* A bemenetként adott halmazok unióját adjuk meg kimenetként.

.. math::

  &\text{UNION}(@X, @Y, @Z)\\
  &// Input: X sorozat, x_i \in A\\
  &// \quad \quad \quad \; Y sorozat, y_i \in A\\
  &// Output: Z sorozat, z_i \in A\\
  &\text{Hossz}[Z] \leftarrow \text{Hossz}[X]\\
  &\text{FOR }i \leftarrow 1\text{ TO Hossz}[X]\text{ DO}\\
  &\quad z_i \leftarrow x_i\\
  &\text{FOR }j \leftarrow 1\text{ TO Hossz}[Y]\text{ DO}\\
  &\quad i \leftarrow 1\\
  &\quad \text{WHILE }(i \leq \text{Hossz}[X])\text{ AND }(x_i \neq y_j)\text{ DO}\\
  &\quad \quad \quad \text{INC}(i)\\
  &\quad \text{IF }i > \text{Hossz}[X]\\
  &\quad \quad \text{THEN INC}(\text{Hossz}[Z])\\
  &\quad \quad \quad \quad \quad z_{\text{Hossz}[Z]} \leftarrow y_j\\
  &\text{RETURN}(Z)\\

Összefuttatás
~~~~~~~~~~~~~

* Két szigorúan monoton növekvő sorozatot egy harmadik rendezett sorozatba futtatunk/fűzünk össze.

.. math::

  &\text{MERGE}(@X, @Y, @Z)\\
  &// Input: X sorozat, x_i \in A\\
  &// \quad \quad \quad \; Y sorozat, y_i \in A\\
  &// Output: Z sorozat, z_i \in A\\
  &\text{Hossz}[Z] \leftarrow 0\\
  &i \leftarrow 1\\
  &j \leftarrow 1\\
  &\text{WHILE }i \leq \text{Hossz}[X]\text{ AND }j \leq \text{Hossz}[Y]\text{ DO}\\
  &\quad \text{INC}(\text{Hossz}[Z])\\
  &\quad \text{CASE}\\
  &\quad \quad x_i < y_j: z_{\text{Hossz}[Z]} \leftarrow x_i\\
  &\quad \quad \quad \quad \quad \quad \text{INC}(i)\\
  &\quad \quad x_i = y_j: z_{\text{Hossz}[Z]} \leftarrow x_i\\
  &\quad \quad \quad \quad \quad \quad \text{INC}(i)\\
  &\quad \quad \quad \quad \quad \quad \text{INC}(j)\\
  &\quad \quad x_i > y_j: z_{\text{Hossz}[Z]} \leftarrow y_i\\
  &\quad \quad \quad \quad \quad \quad \text{INC}(j)\\
  &\text{WHILE }i \leq \text{Hossz}[X]\text{ DO}\\
  &\quad \text{INC}(\text{Hossz}[Z])\\
  &\quad z_{\text{Hossz}[Z]} \leftarrow x_i\\
  &\quad \text{INC}(i)\\
  &\text{WHILE }j \leq \text{Hossz}[Y]\text{ DO}\\
  &\quad \text{INC}(\text{Hossz}[Z])\\
  &\quad z_{\text{Hossz}[Z]} \leftarrow y_j\\
  &\quad \text{INC}(j)\\
  &\text{RETURN}(Z)\\

Iteráció és rekurzió
--------------------

Amennyiben egy problémát vissza tudunk vezetni egy azonos jellegű, de kisebb méretű problémára, akkor használhatunk rekurziót.

Faktoriális számítása
~~~~~~~~~~~~~~~~~~~~~

.. math::

  f(n) = \begin{cases}
  n \cdot f(n - 1), & \text{ha } n > 1,\\
  1, & \text{ha } n = 1.\\
  \end{cases}

Rekurzív változat:

.. math::

  &\text{FACTORIAL}(n, @result)\\
  &// Input: n \in \mathbb{N}\\
  &// Output: result \in \mathbb{N}\\
  &\text{IF }n > 1\\
  &\quad \text{THEN CALL FACTORIAL}(n - 1, result)\\
  &\quad \quad \quad \quad result \leftarrow n \cdot result\\
  &\quad \text{ELSE }result \leftarrow 1\\
  &\text{RETURN}(result)\\

Fibonacci számsorozat
~~~~~~~~~~~~~~~~~~~~~

* A Fibonacci sorozat :math:`n`-edik elemét szeretnénk kiszámolni.

.. math::

  &F_0 = 0\\
  &F_1 = 1\\
  &\ldots\\
  &F_n = F_{n - 2} + F_{n - 1}\\

Rekurzív változat:

.. math::

  &\text{FIBONACCI}(n, @result)\\
  &// Input: n \in \mathbb{N}\\
  &// Output: result \in \mathbb{N}\\
  &\text{IF }n \geq 2\\
  &\quad \text{THEN CALL FIBONACCI}(n - 2, a)\\
  &\quad \quad \quad \quad \text{CALL FIBONACCI}(n - 1, b)\\
  &\quad \quad \quad \quad result \leftarrow a + b\\
  &\quad \text{ELSE } result \leftarrow n\\
  &\text{RETURN}(result)\\

Bináris keresés
~~~~~~~~~~~~~~~

* Feltételezzük, hogy van egy rendezett sorozatunk.
* A lineáris kereséshez hasonlóan egy elemet szeretnénk megkeresni a sorozatban.

.. math::

  &\text{BINARY_SEARCH}(@A, p, r, x, @index)\\
  &// Input: A, \text{rendezett sorozat}\\
  &// \quad \quad \quad p, r \in \mathbb{N}\\
  &// \quad \quad \quad x, \text{ a keresett elem}\\
  &// Output: index \in \mathbb{N}_0, \text{a keresett elem indexe}\\
  &\text{IF }p + 1 < r\\
  &\quad \text{THEN }q \leftarrow \left\lfloor \dfrac{p + r}{2}\right\rfloor\\
  &\quad \quad \quad \text{IF } a_q = x\\
  &\quad \quad \quad \quad \text{THEN }index \leftarrow q\\
  &\quad \quad \quad \quad \text{ELSE IF }x < a_q\\
  &\quad \quad \quad \quad \quad \quad \quad \quad \text{THEN CALL BINARY_SEARCH}(A, p, q, x, index)\\
  &\quad \quad \quad \quad \quad \quad \quad \quad \text{ELSE CALL BINARY_SEARCH}(A, q, r, x, index)\\
  &\quad \text{ELSE }index \leftarrow 0\\
  &\text{RETURN}(index)\\

Kérdések
========

* Hogyan írható fel a halmaz különbség, mint algoritmus?
* Hogyan írható fel a szimmetrikus differencia képzés, mint algoritmus?
* Hogyan írható fel a faktoriális számítása iteratív alakban?
* Hogyan írható fel az :math:`n.` Fibonacci szám kiszámítása iteratív alakban?
* Hogyan írható fel a bináris keresés iteratív alakban?

Feladatok
=========

Pszeudókód, folyamatábra
------------------------

A következő feladatokat oldjuk meg a pszeudókód felírásával és a folyamatábra felrajzolásával! (Minden esetben egy-egy procedúrát adjunk meg!)

* Cseréljük ki két változó értékét!

* Számoljuk meg egy sorozatban a páros számok darabszámát!

* Számoljuk ki egy sorozatban a páratlan számok összegét!

* Határozzuk meg a negatív számok maximumát!

* Vizsgáljuk meg, hogy egy sorozat tartalmaz-e egy bizonyos elemet!

* Vizsgáljuk meg, hogy egy sorozat rendezett-e!

* Ellenőrizzük, hogy egy sorozat minden eleme egyedi!

* Egy sorozatból gyűjtsük ki azon elemeket, amelyek megegyeznek az indexükkel!

* Számoljuk meg, hogy egy bináris vektorban mennyi 0 és 1 érték van!

* Két azonos hosszúságú bemeneti sorozatot fűzzünk össze úgy, hogy az első sorozat elemei a páratlan, a második sorozat elemei a páros indexekre kerüljenek.

Rekurzív függvények, procedúrák
-------------------------------

* Adottak a következő függvények!

.. math::

  f(n) =
  \begin{cases}
  2 \cdot f(n - 3), & \text{ha } n > 20, \\
  5, & \text{egyébként. }
  \end{cases}

.. math::

  g(n) =
  \begin{cases}
  g(n - 1) + 4 \cdot g(n - 2), & n > 0, \\
  8, & \text{egyébként. }
  \end{cases}

Számítsuk ki az :math:`f(30)` és :math:`g(5)` értékeket!

* Számítsuk ki az :math:`\binom{5}{3}` értékét!

Használjuk fel hozzá a következő rekurzív összefüggést!

.. math::

  \binom{n}{k} = \binom{n-1}{k-1} + \binom{n-1}{k}

Adjuk meg a procedúra pszeudó kódját, folyamatábráját! Ábrázoljuk a rekurzív hívási fát!
