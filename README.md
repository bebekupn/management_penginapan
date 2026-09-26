# 🏨 Hotel Room Management System

![C++](https://img.shields.io/badge/Language-C%2B%2B-blue.svg)
![Standard](https://img.shields.io/badge/Standard-C%2B%2B11-blue.svg)
![Data Structure](https://img.shields.io/badge/Data%20Structure-Doubly%20Linked%20List-orange.svg)
![Status](https://img.shields.io/badge/Status-Completed-brightgreen.svg)

**Hotel Room Management System** adalah aplikasi berbasis **Command-Line Interface (CLI)** yang dibuat menggunakan **C++** untuk mensimulasikan pengelolaan kamar hotel dan data transaksi pelanggan.

Program ini menggunakan struktur data **Doubly Linked List** untuk menyimpan data pemesanan serta array untuk mengelola status ketersediaan lima kamar hotel.

Data transaksi dimasukkan ke dalam linked list menggunakan metode **Sorted Insertion** berdasarkan **Kode Unik** secara ascending.

---

## 📌 Overview

Sistem ini menyediakan beberapa fungsi utama untuk pengelolaan kamar dan transaksi hotel:

* Melihat status ketersediaan kamar.
* Melakukan pemesanan kamar.
* Melakukan proses check-out.
* Membuat kode unik transaksi secara otomatis.
* Menyimpan data pemesanan menggunakan Doubly Linked List.
* Menampilkan seluruh data transaksi.
* Mencari transaksi berdasarkan kode unik.
* Menghapus data transaksi.
* Mengelola memori secara dinamis menggunakan `new` dan `delete`.

Program menyediakan **5 kamar hotel**, dengan status kamar yang dikelola menggunakan array:

```cpp
int kamar_kosong[5];
```

Nilai status kamar:

```text
0 = KOSONG
1 = TERISI
```

---

## ✨ Features

### 1. 🛏️ Pemesanan Kamar

Menu **Pemesanan Kamar** digunakan untuk melakukan reservasi kamar.

Sebelum melakukan pemesanan, program akan menampilkan status seluruh kamar.

Contoh:

```text
===== STATUS KAMAR HOTEL =====
Kamar 1 : [ KOSONG ]
Kamar 2 : [ TERISI ]
Kamar 3 : [ KOSONG ]
Kamar 4 : [ KOSONG ]
Kamar 5 : [ TERISI ]
------------------------------
```

Sistem melakukan validasi terhadap:

* Nomor kamar harus berada pada rentang **1–5**.
* Kamar tidak boleh sedang terisi.
* Data pelanggan harus dimasukkan sebelum transaksi dibuat.

Setelah pemesanan berhasil, status kamar akan berubah menjadi:

```text
0 → KOSONG
1 → TERISI
```

---

## 🔑 Kode Unik Transaksi

Setiap transaksi mendapatkan **kode unik** yang dibuat berdasarkan:

* ID pelanggan
* Lama menginap
* Nomor kamar

Formula yang digunakan:

```text
Kode Unik = (ID Pelanggan × 100)
          + (Lama Inap × 10)
          + Nomor Kamar
```

ID pelanggan dibuat berdasarkan urutan pelanggan yang melakukan pemesanan.

### Contoh

Jika:

```text
ID Pelanggan = 7
Lama Inap    = 4 hari
Nomor Kamar  = 3
```

Maka:

```text
(7 × 100) + (4 × 10) + 3

= 700 + 40 + 3

= 743
```

Sehingga kode transaksi pelanggan adalah:

```text
743
```

Kode tersebut kemudian digunakan sebagai identifier untuk mencari dan menghapus data transaksi.

---

## 2. 🚪 Check-Out Kamar

Menu **Check-Out Kamar** digunakan untuk mengubah status kamar yang sebelumnya terisi menjadi kosong.

Pengguna memasukkan:

```text
Kode Unik
```

Program kemudian melakukan pencarian transaksi menggunakan fungsi:

```cpp
cari_kamar()
```

Jika data ditemukan, program menampilkan detail pemesanan:

```text
--- Detail Pemesanan ---
Kode Unik   : 743
Nama        : Aditya
Lama Inap   : 4 hari
Nomor Kamar : 3
```

Kemudian status kamar dikembalikan menjadi kosong:

```cpp
kamar_kosong[hasil->kmr.no_kamar - 1] = 0;
```

### Catatan

**Check-out tidak menghapus node dari Doubly Linked List.**

Data transaksi tetap berada di dalam linked list sehingga masih dapat ditampilkan melalui menu **Cetak Laporan**.

Dengan demikian, program membedakan:

```text
Status Kamar
      │
      ├── KOSONG
      └── TERISI

Data Transaksi
      │
      └── Tetap tersimpan di Linked List
```

---

## 3. 📊 Cetak Laporan

Menu **Cetak Laporan** digunakan untuk menampilkan seluruh transaksi yang tersimpan di dalam Doubly Linked List.

Data yang ditampilkan:

| Informasi   | Keterangan           |
| ----------- | -------------------- |
| Kode Unik   | Identifier transaksi |
| Nama        | Nama pelanggan       |
| Lama Inap   | Durasi menginap      |
| Nomor Kamar | Kamar yang digunakan |

Contoh:

```text
=====cetak laporan=====
no .1
kode unik : 324
nama : Budi
lama inap : 2
nomor kamar : 4

no .2
kode unik : 743
nama : Aditya
lama inap : 4
nomor kamar : 3
```

Data ditampilkan dari `head` menuju `tail`.

Karena transaksi menggunakan **Sorted Insertion**, data pada linked list disusun berdasarkan kode unik secara ascending.

Contoh:

```text
324 ⇄ 512 ⇄ 743 ⇄ 915
```

---

## 4. 🗑️ Hapus Data Transaksi

Menu **Hapus Data** digunakan untuk menghapus transaksi berdasarkan kode unik.

Pengguna memasukkan:

```text
Masukkan kode unik kamar:
```

Program akan mencari node yang memiliki kode tersebut.

Jika ditemukan, node akan dilepaskan dari linked list dan memorinya dibebaskan menggunakan:

```cpp
delete(del);
```

Program menangani beberapa kondisi penghapusan:

* Menghapus `head`.
* Menghapus `tail`.
* Menghapus node di tengah.
* Menghapus satu-satunya node dalam list.
* Kode transaksi tidak ditemukan.
* Linked list masih kosong.

Setelah data dihapus, kamar terkait juga dikembalikan menjadi kosong.

---

# 🧱 Data Structure

Struktur data utama yang digunakan adalah **Doubly Linked List**.

### Struktur `kamar`

```cpp
struct kamar {

    int kode_unik;
    string nama;
    int lama_inap;
    int no_kamar;

};
```

Struktur tersebut menyimpan informasi setiap transaksi pelanggan.

### Struktur `Node`

```cpp
struct Node {

    kamar kmr;

    Node* next;
    Node* prev;

};
```

Setiap node memiliki:

* `kamar kmr` → menyimpan data transaksi.
* `next` → menunjuk ke node berikutnya.
* `prev` → menunjuk ke node sebelumnya.

Ilustrasi:

```text
NULL
  ↑
  │
HEAD
  │
  ▼
┌─────────────┐
│ Transaction │
│    Node     │
└─────────────┘
   │       │
 prev     next
   │       │
   ▼       ▼
 NULL   ┌─────────────┐
        │ Transaction │
        │    Node     │
        └─────────────┘
               │
              next
               ▼
              ...
               │
               ▼
              TAIL
```

---

# 🔄 Sorted Insertion

Program menggunakan fungsi:

```cpp
bool insertSorted(Node*& head, Node*& tail, const kamar& data)
```

Fungsi tersebut memasukkan transaksi berdasarkan `kode_unik`.

Terdapat empat kondisi utama:

### 1. Linked List Kosong

Jika:

```cpp
head == nullptr
```

node baru menjadi:

```text
head = new_node
tail = new_node
```

---

### 2. Insert di Awal

Jika kode transaksi lebih kecil daripada kode pada `head`:

```cpp
data.kode_unik < head->kmr.kode_unik
```

Node baru ditempatkan sebelum `head`.

```text
Before:

100 ⇄ 300 ⇄ 500

Insert 50:

50 ⇄ 100 ⇄ 300 ⇄ 500
```

---

### 3. Insert di Akhir

Jika kode transaksi lebih besar daripada kode pada `tail`:

```cpp
data.kode_unik > tail->kmr.kode_unik
```

Node baru ditempatkan setelah `tail`.

```text
Before:

100 ⇄ 300 ⇄ 500

Insert 700:

100 ⇄ 300 ⇄ 500 ⇄ 700
```

---

### 4. Insert di Tengah

Jika kode transaksi berada di antara dua node:

```text
Before:

100 ⇄ 300 ⇄ 500

Insert 400:

100 ⇄ 300 ⇄ 400 ⇄ 500
```

Program mengatur kembali hubungan:

```cpp
new_node->next
new_node->prev
current->next->prev
current->next
```

sehingga struktur Doubly Linked List tetap terhubung dengan benar.

---

# 🔍 Searching

Pencarian transaksi dilakukan menggunakan fungsi:

```cpp
Node* cari_kamar(Node* head, const int& target)
```

Fungsi melakukan traversal dari `head` menuju node berikutnya sampai:

1. Kode unik ditemukan, atau
2. Mencapai akhir linked list.

Kompleksitas pencarian:

```text
O(N)
```

---

# 🗑️ Deletion

Penghapusan dilakukan menggunakan fungsi:

```cpp
bool hapus_data(Node*& head, Node*& tail, const int& target)
```

Fungsi ini melakukan pencarian node terlebih dahulu, kemudian memperbarui pointer `prev` dan `next`.

Contoh penghapusan node tengah:

```text
Before:

A ⇄ B ⇄ C

Delete B:

A ⇄ C
```

Pointer diperbarui menjadi:

```cpp
A->next = C;
C->prev = A;
```

Node `B` kemudian dibebaskan:

```cpp
delete B;
```

---

# 🧹 Memory Management

Program menggunakan **dynamic memory allocation** untuk membuat node:

```cpp
new Node{data, nullptr, nullptr};
```

Setiap node yang dibuat harus dibebaskan menggunakan:

```cpp
delete;
```

Program menyediakan fungsi:

```cpp
void clear(Node*& head, Node*& tail)
```

untuk menghapus seluruh node ketika program akan ditutup.

Prosesnya:

```text
HEAD
 ↓
Node 1 → Node 2 → Node 3 → NULL
 ↓
delete Node 1
 ↓
delete Node 2
 ↓
delete Node 3
 ↓
HEAD = NULL
TAIL = NULL
```

Hal ini digunakan untuk mencegah **memory leak** ketika program selesai dijalankan.

---

# 📊 Complexity Analysis

| Operation                | Complexity |
| ------------------------ | ---------: |
| Menampilkan status kamar |       O(1) |
| Check ketersediaan kamar |       O(1) |
| Insert Sorted            |       O(N) |
| Search Transaction       |       O(N) |
| Delete Transaction       |       O(N) |
| Display Transaction      |       O(N) |
| Clear Linked List        |       O(N) |

Dengan jumlah kamar yang tetap sebanyak **5 kamar**, pengecekan status kamar dapat dianggap **O(1)** terhadap ukuran linked list transaksi.

---

# 🗂️ Program Structure

Secara konseptual, program terdiri dari beberapa komponen:

```text
Hotel Room Management System
│
├── Room Management
│   ├── kamar_kosong[5]
│   └── tampilkan_kamar_kosong()
│
├── Transaction Data
│   └── struct kamar
│
├── Doubly Linked List
│   ├── struct Node
│   ├── head
│   └── tail
│
├── Transaction Operations
│   ├── insertSorted()
│   ├── cari_kamar()
│   ├── hapus_data()
│   └── data_kamar()
│
└── Memory Management
    └── clear()
```

---

# 🖥️ Main Menu

Program menyediakan menu utama:

```text
1. pesan kamar
2. checkout kamar
3. cetak laporan
4. hapus data

0. keluar
```

### Menu 1 — Pesan Kamar

Digunakan untuk membuat transaksi baru dan mengubah status kamar menjadi terisi.

### Menu 2 — Checkout Kamar

Digunakan untuk mengubah status kamar menjadi kosong berdasarkan kode unik transaksi.

### Menu 3 — Cetak Laporan

Digunakan untuk menampilkan seluruh transaksi yang tersimpan.

### Menu 4 — Hapus Data

Digunakan untuk menghapus transaksi berdasarkan kode unik.

### Menu 0 — Keluar

Mengakhiri program dan menjalankan:

```cpp
clear(head, tail);
```

untuk membersihkan seluruh node yang masih berada di memori.

---

# 🚀 How to Run

## Prerequisites

Program membutuhkan compiler C++ yang mendukung minimal **C++11**, seperti:

* GCC
* MinGW
* Clang
* MSVC

---

## Compile

Jika file program bernama:

```text
main.cpp
```

gunakan:

```bash
g++ -std=c++11 main.cpp -o hotel
```

---

## Run

### Windows

```bash
hotel.exe
```

### Linux / macOS

```bash
./hotel
```

---

# 📁 Repository Structure

Untuk versi sederhana:

```text
hotel-room-management/
│
├── main.cpp
├── README.md
└── .gitignore
```

---

# 🎯 Learning Objectives

Project ini dibuat untuk menerapkan konsep **Data Structures and Algorithms** menggunakan C++.

Konsep yang digunakan meliputi:

* `struct`
* Pointer
* Reference
* Doubly Linked List
* Node traversal
* Sorted insertion
* Searching
* Node deletion
* Dynamic memory allocation
* Dynamic memory deallocation
* Array
* Conditional statements
* Looping
* Function
* Basic time complexity

---

# ⚠️ Current Limitations

Program saat ini masih merupakan aplikasi berbasis CLI sederhana dan memiliki beberapa batasan:

* Jumlah kamar ditetapkan sebanyak **5 kamar**.
* Nama pelanggan dibaca menggunakan `cin >>`, sehingga input nama dengan spasi belum didukung.
* Data transaksi hanya disimpan selama program berjalan.
* Belum menggunakan database atau file sebagai persistent storage.
* Belum terdapat autentikasi administrator.
* Belum terdapat sistem pembayaran atau perhitungan biaya kamar.
* Belum terdapat tanggal check-in dan check-out.
* `total_pelanggan` digunakan sebagai penghitung ID selama program berjalan dan tidak disimpan secara permanen.

---

# 🔮 Future Development

Beberapa pengembangan yang dapat dilakukan:

* [ ] Menambahkan penyimpanan data menggunakan file.
* [ ] Menggunakan database untuk persistent storage.
* [ ] Mendukung nama lengkap dengan `getline()`.
* [ ] Menambahkan harga kamar.
* [ ] Menambahkan total biaya berdasarkan lama menginap.
* [ ] Menambahkan tanggal check-in dan check-out.
* [ ] Menambahkan sistem login administrator.
* [ ] Menambahkan fitur pencarian berdasarkan nama pelanggan.
* [ ] Menambahkan fitur statistik penggunaan kamar.
* [ ] Memisahkan program menjadi beberapa file `.hpp` dan `.cpp`.
* [ ] Menambahkan validasi input yang lebih lengkap.

---

