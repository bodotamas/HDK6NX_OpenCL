# OpenCL órai munkák és rendezési algoritmusok (MergeSort & QuickSort)

Ez a repository órai munkákat és két klasszikus rendezési algoritmus OpenCL-es megvalósítását tartalmazza (beadando):

* **Merge Sort (összefésüléses rendezés)**
* **Quick Sort (gyorsrendezés)**

A projekt egy OpenCL beadandó feladat részeként készült, célja annak bemutatása, hogyan lehet hagyományos CPU-s algoritmusokat OpenCL segítségével párhuzamos környezetben futtatni.

---

## 📁 Mappaszerkezet

```text
HDK6NX_OpenCL/
└── opencl/
    └── examples/
        └── beadando/
            ├── mergesort/
            └── quicksort/
```

Mindkét algoritmus külön mappában található, azonos felépítéssel:

```text
algorithm/
├── Makefile
├── *_opencl.c        # OpenCL megvalósítás
├── *.c               # CPU (soros) megvalósítás
├── include/
│   └── kernel_loader.h
├── src/
│   └── kernel_loader.c
└── Kernels/ vagy kernels/
    └── *.cl          # OpenCL kernel
```

---

## ▶️ Futtatás

### CPU verzió

```bash
./mergesort_cpu
./quicksort_cpu
```

### OpenCL verzió

```bash
./mergesortopencl
./quicksortopencl
```

---

## 🧠 Megvalósítás részletei

### Merge Sort (OpenCL)

* **Iteratív (bottom-up) megközelítést használ**
* Rekurzió helyett lépésenként növeli a részhalmazok méretét: `1, 2, 4, 8...`
* Minden kernelhívás egy **merge (összefésülési) lépést** hajt végre
* Stabilabb és jobban illeszkedik az OpenCL működéséhez

### Quick Sort (OpenCL)

* **Iteratív megoldás saját veremmel (stack)**
* Nem használ rekurziót (kernelben nem praktikus)
* Egyetlen work-item végzi a rendezést
* Az algoritmus közvetlenül a device memórián dolgozik

---

## ⚡ Megjegyzések a teljesítményről

* A CPU verziók klasszikus rekurzív algoritmusok
* Az OpenCL verziók célja a párhuzamos működés bemutatása
* Kis adatmennyiségnél a CPU gyorsabb lehet az OpenCL overhead miatt
* A projekt célja **az OpenCL működésének megértése**, nem a maximális optimalizáció

---

## 🛠 Bemutatott OpenCL fogalmak

* Platform és eszköz kiválasztása
* Kontextus és parancssor létrehozása
* Kernel betöltése és fordítása
* Memóriakezelés (host ↔ device)
* Kernel futtatás és időmérés

---
