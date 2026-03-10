10. Procedúrák, függvények
==========================

A procedúrák és függvények a korábbi témákban már tárgyalásra kerültek. Aktuálisan a programozási nyelvekben jellemző implementációjukat tekintjük át.

Procedúrák
----------

* Bizonyos nyelvekben/környezetekben szubrutinoknak is szokták őket nevezni.
* A kapcsolatot a program többi részével a paramétereiken keresztül tartják.
* Hogy ha valamilyen eredményt is vissza kell adnia, akkor a paraméterek között azok címként jelennek meg.

Függvények
----------

* Úgy tekintjük, hogy a meghívott függvény maga is egy érték.

A matematikai értelemben vett függvényeknek

* nincs olyan paramétere, amely kimenetként szolgál,
* bármennyiszer is hívjuk meg őket ugyanazon paraméterezésre, mindig ugyanazt az értéket kapjuk,
* nem okoznak mellékhatást a program többi részében.

**Megjelenési formáik**

* A programozási nyelvek változatosan használnak procedúrát és/vagy függvényeket.
* Van olyan, amelyikben mindkettő van, és van olyan, amelyekben csak az egyik. (Nagyon régi, vagy egyszerű nyelvek esetében előfordulhat, hogy egyik sem.)

Az érték átadásának lehetséges módjai
-------------------------------------

* Paraméterezésen keresztül
* Elérhető (tipikusan globális) változón keresztül

Paraméter azonosítása
~~~~~~~~~~~~~~~~~~~~~

A híváskor feltüntetett értékeket argumentumoknak nevezzük. Az argumentumok paraméterekhez rendelésének változatos módjai vannak.

* Pozíció szerint: Ez tekinthető a tipikus megoldásnak.
* Név szerint: Magasabb szintű nyelvek támogatják tipikusan (főként egyenlőség jel megadásával, például ``x=8``).
* Név egyezőség szerint: Feltételezi, hogy a hívó és a függvény/procedúra névterében azonos néven szerepel a változó. Manapság már nagyon ritka (szerencsére).

Érték átadása
~~~~~~~~~~~~~

Az argumentumként megadott értékeknek valahogyan át kell jutnia a függvény/procedúra névterébe. Erre az alábbi módok állnak rendelkezésre.

* Érték szerinti átadás
* Cím szerinti átadás (szokás még referencia szerintinek is nevezni)

.. warning::

	A C++ programozási nyelvben a referencia és a cím az külön típus.

Függvény, mint érték
--------------------

Bizonos nyelvekben a függvényt, mint objektumot is lehet kezelni, paraméterként át lehet adni.

λ-kalkulus
----------

* Alonso Church, 1930.
* A :math:`\lambda`-kalkulus a legkisebb univerzális programozási nyelv

A nyelv szintaktikája (Backus-Naur Forma)

.. code::

  <expression>  ::= <name> | <function> | <application>
  <function>    ::= 'λ' <name> '.' <expression>
  <application> ::= <expression> <expression>

* A nyelv két kulcsszava a ``λ``` és a ``.`` (pont).
* Zárójelezés használható a kifejezések körül.
* A függvényeknek nem adunk nevet, hanem helyett magát a függvény definícióját írjuk bele.

Az identikus függvény:

.. code::

  λx.x

Az identikus függvény az ``y``-ra alkalmazva:

.. code::

  (λx.x) y

Az előbbi alkalmazás szintén egy `λ`-kifejezés.

* A benne szereplő ``x`` kötött változó kötött.
* Az ``y`` változója szabad változó.

Példa aritmetikai kifejezésekkel:

.. math::

  \lambda x (\lambda y (x^2 + 5y)) \; 3 \; 2 =
  \lambda x (x^2 + 5 \cdot 3) \; 2 =
  x^2 + 5 \cdot 3 = 19

Church egészek:

.. code::

  0 := λs.λz.z
  1 := λs.λz.(s z)
  2 := λs.λz.(s (s z))
  3 := λs.λz.(s (s (s z)))

* Ebben a ``z`` a 0 (zero) értékre utal.
* Az ``s`` a rákövetkező értékre (successor).

forrás:

* https://en.wikipedia.org/wiki/Lambda_calculus
* https://personal.utdallas.edu/~gupta/courses/apl/lambda.pdf

Kérdések
========

* Az argumentumként kapott értékeket hogyan lehet paraméterhez rendelni?
* Melyek az előnyei és a hátrányai a cím és az érték szerinti paraméterátadásnak?
