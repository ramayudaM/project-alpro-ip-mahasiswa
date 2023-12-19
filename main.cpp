#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>

using namespace std;

const int JUMLAH_MATKUL = 9; 
const int JUMLAH_NILAI = 5;

const double SEPULUH_PERSEN = 0.10;
const double TIGALIMA_PERSEN = 0.35;
const double LIMABELAS_PERSEN = 0.15;
const double DUAPULUH_PERSEN = 0.20;

struct Mahasiswa {
  string npm;
  string nama;
  vector<vector<double>> nilai;
  vector<double> nilaiAkhir;
  vector<string> hurufMutu;
  vector<double> angkaMutu;
  vector<string> statusMatkul;
  double ip;
};

vector<double> nilaiAkhir(vector<vector<double>> nilai) {
  vector<double> totalList;

  for (int i = 0; i < JUMLAH_MATKUL; i++) {
    double total = 0.0;

    for (int j = 0; j < JUMLAH_NILAI; j++) {
      if (j == 0) total += (nilai[i][j] * SEPULUH_PERSEN);
      else if (j == 1) total += (nilai[i][j] * TIGALIMA_PERSEN);
      else if (j == 2) total += (nilai[i][j] * LIMABELAS_PERSEN);
      else total += (nilai[i][j] * DUAPULUH_PERSEN);
    }

    totalList.push_back(total);
  }

  return totalList;
}

string hurufMutu(double nilaiAkhir) {
  if (nilaiAkhir >= 76 && nilaiAkhir <= 85) return "A";
  else if (nilaiAkhir >= 71 && nilaiAkhir <= 75.9) return "B+";
  else if (nilaiAkhir >= 66 && nilaiAkhir <= 70.9) return "B";
  else if (nilaiAkhir >= 61 && nilaiAkhir <= 65.9) return "C+";
  else if (nilaiAkhir >= 55 && nilaiAkhir <= 60.9) return "C";
  else if (nilaiAkhir >= 50 && nilaiAkhir <= 54.9) return "D";
  else return "E";
}

double angkaMutu(string hurufMutu) {
  if (hurufMutu == "A") return 4;
  else if (hurufMutu == "B+") return 3.5;
  else if (hurufMutu == "B") return 3;
  else if (hurufMutu == "C+") return 2.5;
  else if (hurufMutu == "C") return 2;
  else if (hurufMutu == "D") return 1;
  else return 0;
}

string statusMatkul(double angkaMutu) {
  if (angkaMutu == 0) return "Tidak Lulus";
  return "Lulus";
}

double ip(vector<double> angkaMutu) {
  double totalIp = 0.0;

  for (int i = 0; i < angkaMutu.size(); i++) totalIp += angkaMutu[i];
  return totalIp / angkaMutu.size();
}

double maxMinNilai(double nilai) {
  if (nilai >= 85.0) return 85.0;
  if (nilai <= 0.0) return 0.0;
  return nilai;
}

vector<Mahasiswa> listMahasiswa;
vector<Mahasiswa> listReadMahasiswa;

string listMatkul[JUMLAH_MATKUL] = {"Teknik Digital", "Pengantar Teknologi Informasi", "Pengetahuan Lingkungan", "Kalkulus", "Pendidikan Pancasila", "Industri Pertanian", "Algoritma Pemrograman", "Pendidikan Bahasa Indonesia", "Pendidikan Etika dan Kearifan Lokal"};
string listNilai[JUMLAH_NILAI] = {"Keaktifan", "Tugas", "Kuis", "UTS", "UAS"};

void menu() {
  cout << "\nSelamat Datang di Aplikasi Nilai Mahasiswa\n";
  cout << "1. Tambahkan Data Mahasiswa\n";
  cout << "2. Simpan Data Mahasiswa\n";
  cout << "3. Tampilkan Semua Data Mahasiswa\n";
  cout << "4. Tampilkan Data Mahasiswa\n";
  cout << "5. Exit\n";
  cout << "Masukkan Pilihan Menu: ";
}

void borderTableAllMahasiswa() {
  cout << left << setw(5) << setfill('-') << "+" 
        << setw(15) << "+"
        << setw(25) << "+"
        << setw(13) << "+" << "+" << endl;
}

void borderTableMahasiswa() {
  cout << left << setw(33) << setfill('-') << "+" 
        << setw(41) << "+"
        << setw(7) << "+"
        << setw(7) << "+"
        << setw(7) << "+"
        << setw(13) << "+" << "+" << endl;
}

void addDataMahasiswa() {
  Mahasiswa mahasiswa;

  cout << "\nMasukkan NPM Mahasiswa: ";
  getline(cin, mahasiswa.npm);

  cout << "Masukkan Nama Mahasiswa: ";
  getline(cin, mahasiswa.nama);

  mahasiswa.nilai.resize(JUMLAH_MATKUL, vector<double>(JUMLAH_NILAI, 0));

  for (int i = 0; i < JUMLAH_MATKUL; i++) {
    double nilaiMahasiswa = 0.0;
    cout << "\nMata Kuliah " << listMatkul[i] << endl;

    for (int j = 0; j < JUMLAH_NILAI; j++) {
      cout << "\tMasukkan Nilai " << listNilai[j] << ": ";
      cin >> nilaiMahasiswa;
      mahasiswa.nilai[i][j] = maxMinNilai(nilaiMahasiswa);
    }
  }

  cin.ignore();
  listMahasiswa.push_back(mahasiswa);
}

void saveDataMahasiswa() {

  vector<Mahasiswa> dataMahasiswa;

  dataMahasiswa.assign(listMahasiswa.begin(), listMahasiswa.end());

  if (dataMahasiswa.empty()) {
    cout << "Data Mahasiswa Belum Dimasukkan." << endl;

  } else {
    ofstream outStream;

    outStream.open("dbMahasiswa.txt", ios::app);

    if (outStream.is_open()) {
      for (int i = 0; i < dataMahasiswa.size(); i++) {
        outStream << dataMahasiswa[i].npm << "#" << dataMahasiswa[i].nama << "#";  

        for (int j = 0; j < JUMLAH_MATKUL; j++) {
          for (int k = 0; k < JUMLAH_NILAI; k++) {
            outStream << dataMahasiswa[i].nilai[j][k];
            if (k < JUMLAH_NILAI - 1) outStream << ",";
          }

          if (j < JUMLAH_MATKUL - 1) outStream << "_";
        }

        outStream << "#";

        vector<double> listNilaiAkhir = nilaiAkhir(dataMahasiswa[i].nilai), listAngkaMutu;
        vector<string> listHurufMutu, listStatusMatkul;

        for (int j = 0; j < listNilaiAkhir.size(); j++) {
          outStream << listNilaiAkhir[j];
          listHurufMutu.push_back(hurufMutu(listNilaiAkhir[j]));
          if (j < JUMLAH_MATKUL - 1) outStream << "_";
        }

        outStream << "#";

        for (int j = 0; j < listHurufMutu.size(); j++) {
          outStream << listHurufMutu[j];
          listAngkaMutu.push_back(angkaMutu(listHurufMutu[j]));
          if (j < JUMLAH_MATKUL - 1) outStream << "_";
        }

        outStream << "#";

        for (int j = 0; j < listAngkaMutu.size(); j++) {
          outStream << listAngkaMutu[j];
          listStatusMatkul.push_back(statusMatkul(listAngkaMutu[j]));
          if (j < JUMLAH_MATKUL - 1) outStream << "_";
        }

        outStream << "#";

        for (int j = 0; j < listStatusMatkul.size(); j++) {
          outStream << listStatusMatkul[j];
          if (j < JUMLAH_MATKUL - 1) outStream << "_";
        }

        outStream << "#" << ip(listAngkaMutu) << "\n";
      }

      dataMahasiswa.clear();
      outStream.close();
      cout << "Data berhasil disimpan" << endl;

    } else {
      cout << "Gagal membuka file database" << endl;
    }
  }
}

void dataToListReadMahasiswa(string data) {
  Mahasiswa mahasiswa;

  int posNpm = data.find("#");
  int posNama = data.find("#", posNpm + 1);
  int posNilaiMatkul = data.find("#", posNama + 1);
  int posNilaiAkhir = data.find("#", posNilaiMatkul + 1);
  int posHurufMutu = data.find("#", posNilaiAkhir + 1);
  int posAngkaMutu = data.find("#", posHurufMutu + 1);
  int posStatusMatkul = data.find("#", posAngkaMutu + 1);

  mahasiswa.npm = data.substr(0, posNpm);
  mahasiswa.nama = data.substr(posNpm + 1, posNama - posNpm - 1);
  string nilaiMatkul = data.substr(posNama + 1, posNilaiMatkul - posNama - 1);
  string nilaiAkhir = data.substr(posNilaiMatkul + 1, posNilaiAkhir - posNilaiMatkul - 1);
  string hurufMutu = data.substr(posNilaiAkhir + 1, posHurufMutu - posNilaiAkhir - 1);
  string angkaMutu = data.substr(posHurufMutu + 1, posAngkaMutu - posHurufMutu - 1);
  string statusMatkul = data.substr(posAngkaMutu + 1, posStatusMatkul - posAngkaMutu - 1);
  mahasiswa.ip = stod(data.substr(posStatusMatkul + 1));
  
  mahasiswa.nilai.resize(JUMLAH_MATKUL, vector<double>(JUMLAH_NILAI, 0));

  for (int i = 0; i < JUMLAH_MATKUL; i++) {
    string nilaiPerMatkul;

    if (i == JUMLAH_MATKUL - 1) {
      nilaiPerMatkul = nilaiMatkul;
      mahasiswa.nilaiAkhir.push_back(stod(nilaiAkhir)); // add nilai akhir ke mahasiswa
      mahasiswa.hurufMutu.push_back(hurufMutu); // add huruf mutu ke mahasiswa
      mahasiswa.angkaMutu.push_back(stod(angkaMutu)); // add angka mutu ke mahasiswa
      mahasiswa.statusMatkul.push_back(statusMatkul); // add status matkul ke mahasiswa

    } else {
      int posNilaiMatkul = nilaiMatkul.find("_");
      nilaiPerMatkul = nilaiMatkul.substr(0, posNilaiMatkul);
      nilaiMatkul.erase(0, posNilaiMatkul + 1);

      // add nilai akhir ke mahasiswa
      int posNilaiAkhir = nilaiAkhir.find("_");
      mahasiswa.nilaiAkhir.push_back(stod(nilaiAkhir.substr(0, posNilaiAkhir)));
      nilaiAkhir.erase(0, posNilaiAkhir + 1);

      // add huruf mutu ke mahasiswa
      int posHurufMutu = hurufMutu.find("_");
      mahasiswa.hurufMutu.push_back(hurufMutu.substr(0, posHurufMutu));
      hurufMutu.erase(0, posHurufMutu + 1);

      // add angka mutu ke mahasiswa
      int posAngkaMutu = angkaMutu.find("_");
      mahasiswa.angkaMutu.push_back(stod(angkaMutu.substr(0, posAngkaMutu)));
      angkaMutu.erase(0, posAngkaMutu + 1);

      // add status matkul ke mahasiswa
      int posStatusMatkul = statusMatkul.find("_");
      mahasiswa.statusMatkul.push_back(statusMatkul.substr(0, posStatusMatkul));
      statusMatkul.erase(0, posStatusMatkul + 1);
    }

    for (int j = 0; j < JUMLAH_NILAI; j++) {

      // add nilai per matkul ke mahasiswa
      if (j == JUMLAH_NILAI - 1) {
        mahasiswa.nilai[i][j] = stod(nilaiPerMatkul);

      } else {
        int posNilaiPerMatkul = nilaiPerMatkul.find(",");
        mahasiswa.nilai[i][j] = stod(nilaiPerMatkul.substr(0, posNilaiPerMatkul));
        nilaiPerMatkul.erase(0, posNilaiPerMatkul + 1);
      }
    }
  }

  listReadMahasiswa.push_back(mahasiswa);
}

void readAllDataMahasiswa() {
  listReadMahasiswa.clear();

  string buffer;
  ifstream inStream;
  int noMahasiswa = 1;
  inStream.open("dbMahasiswa.txt");

  if (inStream.is_open()) {
    getline(inStream, buffer);
    dataToListReadMahasiswa(buffer);

    if (buffer != "") {
      while (!inStream.eof()) {
        getline(inStream, buffer);
        if (buffer != "") dataToListReadMahasiswa(buffer);
      }

      cout << "\n" << setfill (' ') << right << setw(35) << "DATA MAHASISWA" << endl;

      borderTableAllMahasiswa();

      cout << left << setfill(' ') << "| "
            << left << setw(2) << "No" << " | "
            << left << setw(12) << "NPM" << " | "
            << left << setw(22) << "Nama" << " | "
            << left << setw(10) << "IP" << " |" << endl;

      borderTableAllMahasiswa();

      for (int i = 0; i < listReadMahasiswa.size(); i++) {
        cout << left << setfill(' ') << "| "
              << left << setw(2) << i + 1 << " | "
              << left << setw(12) << listReadMahasiswa[i].npm << " | "
              << left << setw(22) << listReadMahasiswa[i].nama << " | "
              << left << setw(10) << listReadMahasiswa[i].ip << " |" << endl;
      }

      borderTableAllMahasiswa();
      inStream.close();

    } else {
      cout << "\nData Mahasiswa Tidak Ditemukan" << endl;
    }
  }
}

void readDataMahasiswa() {
  listReadMahasiswa.clear();

  string buffer;
  ifstream inStream;
  inStream.open("dbMahasiswa.txt");

  if (inStream.is_open()) {
    getline(inStream, buffer);
    dataToListReadMahasiswa(buffer);

    if (buffer != "") {
      while (!inStream.eof()) {
        getline(inStream, buffer);
        if (buffer != "") dataToListReadMahasiswa(buffer);
      }

      inStream.close();

    } else {
      cout << "\nData Mahasiswa Tidak Ditemukan" << endl;
    }
  }

  string npmMahasiswa;
  int posData = -1;

  cout << "\nMasukkan NPM Mahasiswa: ";
  getline(cin, npmMahasiswa);

  for (int i = 0; i < listReadMahasiswa.size(); i++) {
    if (npmMahasiswa == listReadMahasiswa[i].npm) posData = i;
  }

  if (posData == -1) {
    cout << "Npm mahasiswa tidak ditemukan" << endl;

  } else {

    cout << "\n" << setfill (' ') << right << setw(60) << "KARTU HASIL STUDI" << endl;

    cout  << "\n" << setfill(' ') 
          << left << setw(7) << " Nama : " 
          << left << setw(80) << listReadMahasiswa[posData].nama 
          << "Semester Ganjil" << endl
          << left << setw(7) << " NPM  : " 
          << left << setw(80) << listReadMahasiswa[posData].npm 
          << "Teknik Informatika" << endl;

    borderTableMahasiswa();

    cout << left << setfill(' ') << "| "
          << left << setw(30) << "" << " | "
          << left << setw(38) << "Nilai" << " | "
          << setw(4) << "" << " | "
          << setw(4) << "" << " | "
          << setw(4) << "" << " | "
          << left << setw(10) << "" << " |" << endl;

    cout << left << setw(33) << "| Mata Kuliah"
          << setw(41) << setfill('-') << "|" << "| "
          << left << setw(4) << setfill(' ') << "NA" << " | "
          << left << setw(4) << "HM" << " | "
          << left << setw(4) << "AM" << " | "
          << left << setw(10) << "Status" << " |" << endl;

    cout << left << setfill(' ') << "| "
          << left << setw(30) << "" << " | " 
          << left << setw(9) << "Keaktifan" << " | "
          << left << setw(5) << "Tugas" << " | "
          << left << setw(4) << "Kuis" << " | "
          << left << setw(4) << "UTS" << " | "
          << left << setw(4) << "UAS" << " | "
          << left << setw(4) << "" << " | "
          << left << setw(4) << "" << " | "
          << left << setw(4) << "" << " | "
          << left << setw(10) << "" << " |" << endl;

    borderTableMahasiswa();

    for (int i = 0; i < JUMLAH_MATKUL; i++) {
      cout << left << setfill(' ') << "| "
            << left << setw(30) << listMatkul[i] << " | ";

      for (int j = 0; j < JUMLAH_NILAI; j++) {
        if (j == 0) cout << left << setw(9) << setprecision(4) << listReadMahasiswa[posData].nilai[i][j] << " | ";
        else if (j == 1) cout << left << setw(5) << setprecision(4) << listReadMahasiswa[posData].nilai[i][j] << " | ";
        else cout << left << setw(4) << setprecision(4) << listReadMahasiswa[posData].nilai[i][j] << " | ";
      }

      cout << left << setw(4) << setprecision(4) << listReadMahasiswa[posData].nilaiAkhir[i] << " | "
            << left << setw(4) << setprecision(4) << listReadMahasiswa[posData].hurufMutu[i] << " | "
            << left << setw(4) << setprecision(4) << listReadMahasiswa[posData].angkaMutu[i] << " | "
            << left << setw(10) << setprecision(4) << listReadMahasiswa[posData].statusMatkul[i] << " |"<< endl;
    }

    borderTableMahasiswa();

    cout << left << setfill(' ') << "| "
          << left << "Indeks Prestasi: " 
          << left << setw(88) << listReadMahasiswa[posData].ip << " |" << endl;
    
    borderTableMahasiswa();
  }
}

int main() {
  char pilihan;

  do {
    menu();
    cin >> pilihan;
    cin.ignore();

    switch (pilihan) {
      case '1':
        addDataMahasiswa();
        break;

      case '2':
        saveDataMahasiswa();
        break;

      case '3':
        readAllDataMahasiswa();
        break;

      case '4':
        readDataMahasiswa();
        break;

      case '5':
        cout << "Terima kasih Telah Mengunjungi Aplikasi Nilai Mahasiswa" << endl;
        break;

      default:
        cout << "Pilihan tidak ditemukan." << endl;
        break;
    }
  } while (pilihan != '5');

  return 0;
}