#include <iostream>
#include <string>
#include <cctype>
using namespace std;

struct pesanan
{
    string nama;
    string menu;
    int urutan;
    int status; 
};

void to_upper(string &s)
{
    for (char &c : s)
        c = static_cast<char>(toupper(static_cast<unsigned char>(c)));
}

void enq(pesanan *&queue, int &size, int &capacity, pesanan data)
{
    if (size == capacity)
    {
        capacity *= 2;
        pesanan *baru = new pesanan[capacity];
        for (int j = 0; j < size; ++j)
            baru[j] = queue[j];
        delete[] queue;
        queue = baru;
    }

    queue[size] = data;
    ++size;
}

pesanan deq(pesanan *queue, int &size)
{
    if (size == 0)
    {
        pesanan kosong = {"", "", -1, 0};
        return kosong;
    }

    int prioritas = 0;
    for (int i = 1; i < size; ++i)
    {
        bool vip = queue[i].status > queue[prioritas].status;
        bool duluan = queue[i].status == queue[prioritas].status && queue[i].urutan < queue[prioritas].urutan;

        if (vip || duluan)
            prioritas = i;
    }

    pesanan dilayani = queue[prioritas];
    
    for (int i = prioritas; i < size - 1; ++i)
        queue[i] = queue[i + 1];
    --size;

    return dilayani;
}

void display(pesanan *queue, int size)
{
    cout << "\n=== Urutan Pelayanan ===\n";
    pesanan *tempQueue = new pesanan[size];
    int tempSize = size;
    for (int i = 0; i < size; ++i)
        tempQueue[i] = queue[i];

    for (int nomor = 1; tempSize > 0; ++nomor)
    {
        pesanan dilayani = deq(tempQueue, tempSize);
        
        to_upper(dilayani.nama);
        cout << nomor << ". " << dilayani.nama << " - " << dilayani.menu;
        if (dilayani.status == 2) 
            cout << " [VIP]";
        cout << '\n';
    }
    delete[] tempQueue;
}

int main()
{
    int n;
    cout << "Masukkan jumlah pesanan: ";
    cin >> n;
    cin.ignore(); 

    int capacity = max(1, n);
    int size = 0;
    pesanan *queue = new pesanan[capacity];

    for (int i = 0; i < n; ++i)
    {
        pesanan data;
        cout << "\nPesanan " << i + 1 << ":\n";
        cout << "Nama hewan: ";
        getline(cin, data.nama);
        cout << "Menu pesanan: ";
        getline(cin, data.menu);
        cout << "Status VIP (1=biasa, 2=VIP): ";
        cin >> data.status;
        cin.ignore(); 
        
        data.urutan = i;
        enq(queue, size, capacity, data);
    }

    display(queue, size);
    deq(queue, size);
    display(queue, size);

    delete[] queue;
    return 0;
}