#include<iostream>
using namespace std;

struct kamar {
    int kode_unik;
    string nama;
    int lama_inap;
    int no_kamar;
};

struct Node {
    kamar kmr;
    Node* next;
    Node* prev;
};

Node* new_node;
Node* temp, *del;

int total_pelanggan;
int kamar_kosong[5];


void tampilkan_kamar_kosong() {
    cout << "\n===== STATUS KAMAR HOTEL =====" << endl;
    for (int i = 0; i < 5; i++) {
        if (kamar_kosong[i] == 0) {
            cout << "Kamar " << (i + 1) << " : [ KOSONG ]" << endl;
        } else {
            cout << "Kamar " << (i + 1) << " : [ TERISI ]" << endl;
        }
    }
    cout << "------------------------------" << endl;
}

bool insertSorted(Node*& head, Node*& tail, const kamar& data) {

    new_node = new Node{data, nullptr, nullptr};

    // KONDISI 1: List masih kosong
    if (head == nullptr) {
        head = new_node;
        tail = new_node;
        return true;
    }

    // KONDISI 2: Sisip di paling depan (sebelum head)
    if (data.kode_unik < head->kmr.kode_unik) {
        new_node->next = head;
        head->prev = new_node;
        head = new_node;
        return true;
    }

    // KONDISI 3: Sisip di paling belakang (setelah tail)
    if (data.kode_unik > tail->kmr.kode_unik) {
        new_node->prev = tail;
        tail->next = new_node;
        tail = new_node; // Update tail ke node baru
        return true;
    }

    // KONDISI 4: Sisip di tengah-tengah list
    Node* current = head;

    while (current->next != nullptr && current->next->kmr.kode_unik < data.kode_unik) {
        current = current->next;
    }

    // Sambungkan 4 arah pointer untuk posisi tengah
    new_node->next = current->next;
    new_node->prev = current;
    current->next->prev = new_node;
    current->next = new_node;

    return true;
}

void data_kamar(const Node* head) {


    if (head == nullptr){
        cout << "data masih kosong." << endl;
        return;
    }

    const Node* bantu = head;
    int number = 1;

    while (bantu != nullptr) {
        cout << "no ." << number << endl; 
        cout << "kode unik : " <<bantu->kmr.kode_unik << endl;
        cout << "nama : " <<bantu->kmr.nama << endl;
        cout << "lama inap : " <<bantu->kmr.lama_inap << endl;
        cout << "nomor kamar : " <<bantu->kmr.no_kamar << endl;
        
        bantu = bantu->next;
        number++;
    }

    std::cout << "\n";
}

Node* cari_kamar(Node* head, const int& target){

    if (head == nullptr){
        cout << "data kamar tidak ditemukan." << endl;
        return nullptr;
    }

    Node* bantu = head;
    do{

        if (bantu->kmr.kode_unik == target){
            cout << "kode unik : " <<bantu->kmr.kode_unik << endl;
            cout << "nama : " <<bantu->kmr.nama << endl;
            cout << "lama inap : " <<bantu->kmr.lama_inap << endl;
            cout << "nomor kamar : " <<bantu->kmr.no_kamar << endl;
            return bantu;
        }

        bantu = bantu->next;
    }while (bantu != nullptr);

    return nullptr;
}

bool hapus_data(Node*& head, Node*& tail, const int& target){

    if(head == nullptr){
        cout << "data masih kosong" << endl;

    }else if(target == head->kmr.kode_unik){

        del = head;

        if(head == tail){
            head = nullptr;
            tail = nullptr;
        }else{
            head = head->next;
            head->prev = nullptr;

        }
        delete(del);

    }else{
        temp = head->next;

        while(temp != nullptr && temp->kmr.kode_unik != target){    
            temp = temp->next;
        }
        del = temp;
    }

    if(del != nullptr){
        if(del->prev != nullptr){
            del->prev->next = del->next;
        }

        if(del->next != nullptr){
            del->next->prev = del->prev;
        }

        if(del == tail){
            tail = del->prev;
        }

        kamar_kosong[del->kmr.no_kamar - 1] = 0;
        delete(del);
        cout << "[Succes]data berhasil dihapus" << endl;

    }else{
        cout <<"[Error]data tidak ditemukan" << endl;
    }
}

void clear(Node*& head, Node*& tail){
    if (head == nullptr) {
        return;
    }

    Node* bantu = head;

    while (bantu != nullptr) {
        Node* hapus = bantu;
        bantu = bantu->next;
        delete hapus;
    }

    head = nullptr;
    tail = nullptr;


}



int main(){
    Node* head = nullptr;
    Node* tail = nullptr;
    kamar data_baru;
    int menu;

    for (int i = 0; i < 5; i++) {
        kamar_kosong[i] = 0;
    }

    while(menu != 0){
        
        cout << "1. pesan kamar" << endl;
        cout << "2. checkout kamar" << endl;
        cout << "3. cetak laporan" << endl;
        cout << "4. hapus data" << endl << endl;
    
        cout << "0. keluar" << endl;
        cout << "-----------------------------------------------" << endl;
        cout << "pilih menu : ";
        cin >> menu;

        switch (menu){

            case 1:{
                kamar data_baru;
                tampilkan_kamar_kosong();

                cout << "Masukkan Nomor Kamar (1-5): ";
                cin >> data_baru.no_kamar;

                // Validasi input nomor kamar
                if (data_baru.no_kamar < 1 || data_baru.no_kamar > 5) {
                    cout << "[Error] Nomor kamar tidak valid!\n" << endl;
                    break;
                }

                // Cek ketersediaan kamar
                if (kamar_kosong[data_baru.no_kamar - 1] == 1) {
                    cout << "[Error] Kamar " << data_baru.no_kamar << " tidak tersedia (sudah terisi)!\n" << endl;
                    break;
                }

                cout << "Masukkan Nama Penginap   : ";
                cin >> data_baru.nama;
                cout << "Masukkan Lama Menginap  : ";
                cin >> data_baru.lama_inap;

                // Increment total pelanggan untuk pembentukan ID Unik
                total_pelanggan++;

                // Format Kode Unik: (ID Pelanggan * 100) + (Lama Inap * 10) + No Kamar
                // Contoh: Pelanggan ke-7, 4 hari, kamar 3 -> 700 + 40 + 3 = 743
                data_baru.kode_unik = (total_pelanggan * 100) + (data_baru.lama_inap * 10) + data_baru.no_kamar;

                // Tandai kamar menjadi TERISI (1)
                kamar_kosong[data_baru.no_kamar - 1] = 1;

                // Masukkan data ke Linked List Laporan
                insertSorted(head, tail, data_baru);

                cout << "\n[Sukses] Pemesanan Berhasil!" << endl;
                cout << "Kode Unik Anda: " << data_baru.kode_unik << "\n" << endl;
                break;
                break;
            }

            case 2:{
                
                if (head == nullptr) {
                        cout << "[Error] Belum ada transaksi pemesanan.\n" << endl;
                        break;
                    }

                    int kode;
                    cout << "===== CHECKOUT KAMAR =====" << endl;
                    cout << "Masukkan Kode Unik: ";
                    cin >> kode;

                    Node* hasil = cari_kamar(head, kode);

                    if (hasil != nullptr) {
                        cout << "\n--- Detail Pemesanan ---" << endl;
                        cout << "Kode Unik   : " << hasil->kmr.kode_unik << endl;
                        cout << "Nama        : " << hasil->kmr.nama << endl;
                        cout << "Lama Inap   : " << hasil->kmr.lama_inap << " hari" << endl;
                        cout << "Nomor Kamar : " << hasil->kmr.no_kamar << endl;

                        kamar_kosong[hasil->kmr.no_kamar - 1] = 0;

                        cout << "\n[Sukses] Kamar " << hasil->kmr.no_kamar << " berhasil Checkout & kembali Kosong!\n" << endl;
                    } else {
                        cout << "[Error] Data tidak ditemukan!\n" << endl;
                    }

                break;
            }

            case 3:{
                cout << "=====cetak laporan=====" << endl;
                data_kamar(head);
                break;
            }

            case 4:{
                int kode;
                cout << "=====hapus data=====" << endl;
                cout << "masukkan kode unik kamar : ";
                cin >> kode;
                hapus_data(head, tail, kode);
                break;
            }
            
            default:{
                cout << " " << endl;
                break;
            }
        }
    }

    cout << "anda keluar dari program" << endl;
    clear(head, tail);
    return 0;

}