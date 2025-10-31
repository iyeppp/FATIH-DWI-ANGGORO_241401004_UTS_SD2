#include <iostream>
#include <string> 
using namespace std;

struct Node{
    string namaB;
    int hargB;
    int jumlahB;
    Node *next;
};

Node *tail = NULL;
Node *head = NULL;

void tambahBarang(){
    Node *newNode = new Node();

    cout << "Masukkan Nama Barang: ";

    cin.ignore(); 
    getline(cin, newNode->namaB); 
    
    cout << "Masukkan Harga Barang: ";
    cin >> newNode->hargB;
    cout << "Masukkan Jumlah Barang: ";
    cin >> newNode->jumlahB;
    
    newNode->next = NULL; 

    if(head == NULL){
        head = newNode;
        tail = newNode;
    } else {
        tail->next = newNode;
        tail = newNode;
    }
}

int hapusBarang(string namaHapus){
    Node *current = head;
    Node *previous = NULL;

    while(current != NULL && current->namaB != namaHapus){
        previous = current;
        current = current->next;
    }

    if(current == NULL){
        return 0; 
    }

    if(previous == NULL){ 
        head = current->next;
    } 
    else {
        previous->next = current->next;
    }

    if(current == tail){
        tail = previous; 
    }
    
    if(head == NULL){
        tail = NULL;
    }

    delete current;
    return 1;
}

int displayBarang(){
    Node *current = head;
    if(current == NULL){
        cout << "Daftar Barang Kosong!" << endl;
        return 0;
    }

    current = head;
    int totalHarga = 0;
    int totalBarang = 0;
    while(current != NULL){
        cout << current->namaB << " - " << "Rp" << current->hargB << " x" << current->jumlahB;
        cout << endl;

        totalHarga += current->hargB * current->jumlahB;
        totalBarang += current->jumlahB;
        
        current = current->next;
    }
    cout << endl;
    cout << "Total Barang: ";
    cout << totalBarang << endl;
    cout << "Total Harga: Rp";
    cout << totalHarga << endl;

    return 1;
}

int main(){
    int n;
    cout << "Masukkan Jumlah Barang Awal: ";
    cin >> n;

    cout << endl;

    for(int i = 0; i < n; i++){
        cout << "--- Barang ke-" << i+1 << " ---" << endl;
        tambahBarang(); 
        cout << endl;
    }

    displayBarang();
    cout << endl;

    cout << "Apakah Anda Ingin Menghapus Barang? (y/n): ";
    char choice;
    cin >> choice;
    cin.ignore(); 

    if(choice == 'y' || choice == 'Y'){
        
        ulang:
        cout << "Masukkan Nama Barang yang Ingin Dihapus: ";
        string namaHapus;
        
        getline(cin, namaHapus); 

        if (hapusBarang(namaHapus)){
            cout << "Barang Berhasil Dihapus!" << endl;
        } else {
            cout << "Barang Tidak Ditemukan! Coba lagi." << endl;
            goto ulang;
        }
    }

    cout << endl;
    displayBarang();
}