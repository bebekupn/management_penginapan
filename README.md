# 🏨 Hotel Room Management System

**Hotel Room Management System** adalah aplikasi berbasis **Command-Line Interface (CLI)** yang dikembangkan menggunakan **C++** untuk mengelola reservasi kamar, proses check-in dan check-out, serta riwayat transaksi pelanggan.

Proyek ini mengimplementasikan struktur data **Doubly Linked List** dengan mekanisme **Sorted Insertion** berdasarkan **Unique Transaction Code**. Status ketersediaan kamar dikelola secara terpisah menggunakan array sehingga proses reservasi dan pengelolaan riwayat transaksi dapat dilakukan secara terstruktur.

---

## 📌 Overview

Sistem ini dirancang untuk mensimulasikan proses dasar manajemen kamar hotel, meliputi:

* Pemeriksaan ketersediaan kamar.
* Proses reservasi dan check-in pelanggan.
* Pembuatan kode transaksi secara otomatis.
* Penyimpanan transaksi menggunakan **Doubly Linked List**.
* Pengurutan transaksi berdasarkan kode unik.
* Proses check-out dan pembaruan status kamar.
* Penyajian laporan riwayat transaksi.
* Penghapusan data transaksi tertentu.
* Manajemen memori menggunakan dynamic allocation dan deallocation.

Proyek ini dibuat sebagai implementasi praktis konsep **struktur data, pointer, linked list, dynamic memory allocation, dan algoritma insertion** dalam C++.

---

## ✨ Features

### 1. 🛎️ Check-In & Room Reservation

Sistem menyediakan proses pemesanan kamar dengan beberapa validasi:

* Menampilkan daftar kamar yang tersedia.
* Memvalidasi nomor kamar.
* Mencegah pemesanan kamar yang sedang digunakan.
* Mencatat data pelanggan dan lama menginap.
* Menghasilkan **Unique Transaction Code** secara otomatis.
* Memasukkan transaksi ke dalam linked list secara terurut.

Kode transaksi menggunakan formula:

```text
(ID_Pelanggan × 100) + (Lama_Inap × 10) + No_Kamar
```

Contoh:

```text
ID Pelanggan : 12
Lama Inap    : 3 hari
No. Kamar    : 5

Kode Transaksi:
(12 × 100) + (3 × 10) + 5
= 1235
```

---

### 2. 🚪 Check-Out

Proses check-out digunakan untuk menyelesaikan masa inap pelanggan.

Ketika pelanggan melakukan check-out:

* Status kamar dikembalikan menjadi **tersedia**.
* Data transaksi tetap tersimpan dalam **historical record**.
* Riwayat pelanggan tidak langsung dihapus dari linked list.
* Kamar dapat digunakan kembali untuk reservasi berikutnya.

Pendekatan ini memisahkan antara **status kamar** dan **riwayat transaksi**.

---

### 3. 📊 Transaction History

Sistem menyediakan laporan seluruh transaksi yang tersimpan.

Informasi yang ditampilkan meliputi:

| Data             | Keterangan          |
| ---------------- | ------------------- |
| Transaction Code | Kode unik transaksi |
| Customer Name    | Nama pelanggan      |
| Stay Duration    | Lama menginap       |
| Room Number      | Nomor kamar         |

Data transaksi ditampilkan berdasarkan urutan **ascending Transaction Code**.

Contoh:

```text
========================================================
                 TRANSACTION HISTORY
========================================================
Code       Customer Name        Stay       Room
--------------------------------------------------------
1023       Budi                 2 Days     3
1245       Andi                 4 Days     5
1512       Rizky                1 Day      2
========================================================
```

---

### 4. 🗑️ Delete Transaction Record

Sistem memungkinkan administrator menghapus transaksi tertentu berdasarkan **Transaction Code**.

Fitur ini dilengkapi dengan validasi:

* Menolak penghapusan jika linked list kosong.
* Memberikan pesan apabila kode transaksi tidak ditemukan.
* Menangani penghapusan pada node:

  * `head`
  * `tail`
  * node di tengah linked list.
* Membebaskan memori menggunakan `delete`.

---

## 🧱 Data Structure

Proyek ini menggunakan **Doubly Linked List** sebagai struktur utama untuk menyimpan data transaksi.

Setiap node memiliki dua pointer:

```cpp
Node* prev;
Node* next;
```

Struktur sederhananya:

```text
NULL
  ↓
┌──────────┐      ┌──────────┐      ┌──────────┐
│  Node 1  │ ⇄    │  Node 2  │ ⇄    │  Node 3  │
└──────────┘      └──────────┘      └──────────┘
      ↑                                   ↓
    HEAD                                TAIL
```

Setiap node menyimpan objek `Lagu` pada contoh struktur sebelumnya; dalam proyek hotel, data tersebut disesuaikan menjadi data transaksi kamar.

Contoh struktur:

```cpp
struct Transaksi {
    int kode_transaksi;
    string nama_pelanggan;
    int lama_inap;
    int no_kamar;
};

struct Node {
    Transaksi data;
    Node* prev;
    Node* next;
};
```

---

## ⚙️ Algorithm & Implementation

| Component              | Implementation         |
| ---------------------- | ---------------------- |
| Primary Data Structure | Doubly Linked List     |
| Node Connection        | `prev` & `next`        |
| List Management        | `head` & `tail`        |
| Insertion              | Sorted Insertion       |
| Sorting Order          | Ascending              |
| Room Management        | Fixed Array            |
| Memory Allocation      | `new`                  |
| Memory Deallocation    | `delete`               |
| Memory Cleanup         | `clear()`              |
| Interface              | Command-Line Interface |
| Language Standard      | C++11                  |

### Sorted Insertion

Setiap transaksi baru tidak langsung ditempatkan di akhir list.

Sistem akan mencari posisi yang sesuai berdasarkan **Transaction Code**, kemudian memasukkan node pada posisi tersebut.

Contoh:

```text
Sebelum:
1001 ⇄ 1205 ⇄ 1502

Insert:
1300

Setelah:
1001 ⇄ 1205 ⇄ 1300 ⇄ 1502
```

Dengan pendekatan tersebut, data selalu berada dalam kondisi terurut tanpa memerlukan proses sorting ulang terhadap seluruh list setelah setiap insertion.

---

## ⏱️ Complexity Analysis

| Operation               | Time Complexity |
| ----------------------- | --------------: |
| Check Room Availability |            O(1) |
| Insert at Head          |            O(1) |
| Insert at Tail          |            O(1) |
| Sorted Insertion        |            O(N) |
| Search Transaction      |            O(N) |
| Delete Transaction      |            O(N) |
| Display History         |            O(N) |
| Clear Linked List       |            O(N) |

> **N** merupakan jumlah transaksi yang tersimpan di dalam linked list.

---

## 🗂️ Project Structure

Struktur repositori dapat dibuat seperti berikut:

```text
hotel-room-management/
│
├── src/
│   └── main.cpp
│
├── README.md
├── LICENSE
└── .gitignore
```

Untuk proyek yang lebih besar, struktur dapat dikembangkan menjadi:

```text
hotel-room-management/
│
├── include/
│   ├── hotel.hpp
│   ├── linked_list.hpp
│   └── transaction.hpp
│
├── src/
│   ├── hotel.cpp
│   ├── linked_list.cpp
│   ├── transaction.cpp
│   └── main.cpp
│
├── README.md
├── LICENSE
└── .gitignore
```

---

## 🚀 Getting Started

### Prerequisites

Pastikan perangkat telah memiliki compiler C++ yang mendukung minimal **C++11**, seperti:

* GCC / MinGW
* Clang
* Microsoft Visual C++
* G++

---

### 1. Clone Repository

```bash
git clone https://github.com/username-kamu/hotel-room-management.git
```

### 2. Masuk ke Directory

```bash
cd hotel-room-management
```

### 3. Compile Program

Menggunakan GCC:

```bash
g++ -std=c++11 src/main.cpp -o hotel
```

### 4. Run Program

**Windows:**

```bash
hotel.exe
```

**Linux / macOS:**

```bash
./hotel
```

---

## 🖥️ Application Flow

Alur utama sistem:

```text
                ┌───────────────┐
                │     START     │
                └───────┬───────┘
                        │
                        ▼
                ┌───────────────┐
                │  Main Menu    │
                └───────┬───────┘
                        │
        ┌───────────────┼────────────────┐
        │               │                │
        ▼               ▼                ▼
   ┌─────────┐    ┌──────────┐    ┌─────────────┐
   │ Check-In│    │ Check-Out│    │  History    │
   └────┬────┘    └────┬─────┘    └──────┬──────┘
        │              │                 │
        ▼              ▼                 ▼
  Check Room      Update Room       Display List
  Availability       Status         Sorted Data
        │
        ▼
 Generate Transaction
      Code
        │
        ▼
 Sorted Insertion
        │
        └──────────────┐
                       ▼
                 ┌───────────┐
                 │ Main Menu │
                 └───────────┘
```

---

## 🧠 Learning Objectives

Proyek ini berfokus pada penerapan konsep fundamental **Data Structures & Algorithms**, khususnya:

* Struct dalam C++.
* Pointer dan pointer manipulation.
* Dynamic memory allocation.
* Dynamic memory deallocation.
* Doubly Linked List.
* Node traversal.
* Insertion dan deletion.
* Sorted insertion.
* Searching.
* Array-based state management.
* Basic algorithmic complexity analysis.

---

## 🛡️ Memory Management

Karena linked list menggunakan dynamic allocation, setiap node yang dibuat menggunakan:

```cpp
new
```

harus dibersihkan menggunakan:

```cpp
delete
```

Program menyediakan mekanisme `clear()` untuk memastikan seluruh node dihapus ketika linked list tidak lagi digunakan.

Contoh:

```cpp
void clear() {
    Node* temp;

    while (head != nullptr) {
        temp = head;
        head = head->next;
        delete temp;
    }

    tail = nullptr;
}
```

Pendekatan ini membantu mencegah **memory leak** selama program berjalan.

---

## 📚 Concepts Demonstrated

Proyek ini mendemonstrasikan hubungan antara struktur data dan kebutuhan aplikasi sederhana:

```text
Hotel Management
       │
       ├── Room Availability
       │       └── Array
       │
       ├── Transaction Storage
       │       └── Doubly Linked List
       │
       ├── Transaction Ordering
       │       └── Sorted Insertion
       │
       └── Memory Management
               └── new / delete
```

---

## 🔮 Future Improvements

Beberapa pengembangan yang dapat ditambahkan:

* [ ] Sistem login administrator.
* [ ] Penyimpanan data menggunakan file/database.
* [ ] Sistem harga kamar dan perhitungan total biaya.
* [ ] Tanggal check-in dan check-out.
* [ ] Pencarian transaksi berdasarkan nama pelanggan.
* [ ] Filtering berdasarkan nomor kamar.
* [ ] Statistik okupansi kamar.
* [ ] Export laporan ke `.txt` atau `.csv`.
* [ ] Implementasi error handling yang lebih komprehensif.
* [ ] Pemisahan kode menjadi beberapa `.hpp` dan `.cpp`.
* [ ] Unit testing untuk fungsi linked list.

---

