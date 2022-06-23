#include <iostream>
#include <windows.h>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct DanePrzyjaciela {
    int idAdresata = 0;
    int idUzytkownika = 0;
    string imie = "",nazwisko = "", nrTelefonu = "", email = "", adres = "";
};

struct Uzytkownik {
    int id;
    string nazwa, haslo;
};

string konwerjsaIntNaString(int liczba) {
    ostringstream ss;
    ss << liczba;
    string str = ss.str();

    return str;
}

void dopiszUzytkownikaDoPliku (Uzytkownik user) {
    fstream plik;
    plik.open("Uzytkownicy.txt", ios::out | ios::app);

    if (plik.good() == true) {
        plik << user.id << '|';
        plik << user.nazwa << '|';
        plik << user.haslo << '|'<< endl;
        plik.close();

    } else {
        cout << "Nie udalo sie otworzyc pliku i zapisac w nim danych." << endl;
        system("pause");
    }
}
void zapiszWszystkichUzytkownikowDoPlikuTekstowego(vector<Uzytkownik> &Users) {
    fstream plik;
    string liniaZDanymiUzytkownika = "";

    plik.open("Uzytkownicy.txt", ios::out);
    if (plik.good()) {
        for (vector<Uzytkownik>::iterator itr = Users.begin(); itr != Users.end(); itr++) {
            liniaZDanymiUzytkownika += konwerjsaIntNaString(itr->id) + '|';
            liniaZDanymiUzytkownika += itr->nazwa + '|';
            liniaZDanymiUzytkownika += itr->haslo + '|';

            plik << liniaZDanymiUzytkownika << endl;
            liniaZDanymiUzytkownika = "";
        }
        plik.close();
    } else {
        cout << "Nie mozna otworzyc pliku Uzytkownicy.txt" << endl;
    }
}

int rejestracja(vector <Uzytkownik> &Users) {
    string nazwa, haslo;
    int usersCount = Users.size();
    Uzytkownik User;
    system ("cls");
    cout << "Podaj nazwe uzytkownika: ";
    cin >> nazwa;

    int i=0;
    while (i < Users.size()) {
        if (Users[i].nazwa == nazwa) {
            cout << "Taki uzytkownik istnieje. Podaj inna nazwe uzytkownika: ";
            cin >> nazwa;
            i = 0;
        } else {
            i++;
        }
    }

    cout << "Podaj haslo: ";
    cin >> haslo;
    User.nazwa = nazwa;
    User.haslo = haslo;
    User.id = usersCount+1;
    Users.push_back(User);
    dopiszUzytkownikaDoPliku(User);
    cout << "Konto zalozone" << endl;
    Sleep(1000);
    return User.id;
}

int logowanie (vector <Uzytkownik> &Users) {
    string nazwa, haslo;
    system("cls");
    cout << "Podaj login: ";
    cin >> nazwa;
    int iloscUzytkownikow = Users.size();
    int i=0;
    while (i <iloscUzytkownikow) {
        if (Users[i].nazwa == nazwa) {
            for (int proby=0; proby < 3; proby++) {
                cout << "Podaj haslo. Pozostalo prob " << 3-proby << ": ";
                cin >> haslo;
                if (Users[i].haslo == haslo) {
                    cout << "Zalogowales sie." <<endl;
                    Sleep(1000);
                    return Users[i].id;
                }
            }
            cout << "Podales 3 razy bledne haslo. Poczekaj 3 sekundy przed kolejna proba" << endl;
            Sleep(3000);
            return 0;
        }
        i++;
    }
    cout << "Nie ma uzytkownika z takim loginem" << endl;
    Sleep(1500);
    return 0;

}

int zmianaHasla(vector <Uzytkownik> &Users, int idZalogowanegoUzytkownika) {
    string haslo;
    cout << "Podaj nowe haslo: ";
    cin >> haslo;
    for (int i=0; i<Users.size(); i++) {
        if (Users[i].id == idZalogowanegoUzytkownika) {
            Users[i].haslo = haslo;
            zapiszWszystkichUzytkownikowDoPlikuTekstowego(Users);
            cout << "Haslo zostalo zmienione" << endl;
            Sleep(1500);
        }
    }
    return idZalogowanegoUzytkownika;
}

void dopiszPrzyjacielaDoPliku(DanePrzyjaciela adresat) {
    fstream plik;
    plik.open("wizytowki.txt", ios::out | ios::app);

    if (plik.good() == true) {
        plik << adresat.idAdresata << '|';
        plik << adresat.idUzytkownika<< '|';
        plik << adresat.imie << '|';
        plik << adresat.nazwisko << '|';
        plik << adresat.nrTelefonu << '|';
        plik << adresat.email << '|';
        plik << adresat.adres << '|' << endl;
        plik.close();

    } else {
        cout << "Nie udalo sie otworzyc pliku i zapisac w nim danych." << endl;
        system("pause");
    }
}

void odczytDanychZPlikuUzytkownicy(vector <Uzytkownik> &Users) {
    string linia = "";
    string daneDoZapisu = "";
    int nr_danych=1;
    Uzytkownik User;

    fstream plik;
    plik.open("Uzytkownicy.txt", ios::in);
    if (plik.good()==false) {
        plik.open("Uzytkownicy.txt", ios::out | ios::app);
        cout<< "Utworzono plik z Uzytkownikami";
        Sleep(3000);
        plik.close();
    }

    while (getline(plik, linia)) {


        for (int i=0; i<linia.length(); i++) {
            while (linia[i] != '|') {
                daneDoZapisu += linia[i];
                i++;
            }
            switch(nr_danych) {
            case 1:
                User.id=atoi(daneDoZapisu.c_str());
                break;
            case 2:
                User.nazwa=daneDoZapisu;
                break;
            case 3:
                User.haslo=daneDoZapisu;
                break;
            }

            nr_danych++;
            daneDoZapisu = "";


        }
        Users.push_back(User);
        nr_danych = 1;

    }
    plik.close();
}
void zapiszWszystkichAdresatowDoPlikuTekstowego(vector<DanePrzyjaciela> &Przyjaciele) {
    fstream plik;
    string liniaZDanymiAdresata = "";

    plik.open("wizytowki.txt", ios::out);
    if (plik.good()) {
        for (vector<DanePrzyjaciela>::iterator itr = Przyjaciele.begin(); itr != Przyjaciele.end(); itr++) {
            liniaZDanymiAdresata += konwerjsaIntNaString(itr->idAdresata) + '|';
            liniaZDanymiAdresata += konwerjsaIntNaString(itr->idUzytkownika) + '|';
            liniaZDanymiAdresata += itr->imie + '|';
            liniaZDanymiAdresata += itr->nazwisko + '|';
            liniaZDanymiAdresata += itr->nrTelefonu + '|';
            liniaZDanymiAdresata += itr->email + '|';
            liniaZDanymiAdresata += itr->adres + '|';

            plik << liniaZDanymiAdresata << endl;
            liniaZDanymiAdresata = "";
        }
        plik.close();
    } else {
        cout << "Nie mozna otworzyc pliku wizytowki.txt" << endl;
    }
}


void wczytywanieDanychPrzyjaciela(vector <DanePrzyjaciela> &Przyjaciele, int idZalogowanegoUzytkownika) {

    int idOstatniegoPrzyjaciela = 0;
    DanePrzyjaciela Adresat;

    system("cls");

    cout << "Podaj imie: ";
    cin >> Adresat.imie;
    cout << "Podaj nazwisko: ";
    cin >> Adresat.nazwisko;
    cout << "Podaj nr telefonu: ";
    cin >> Adresat.nrTelefonu;
    cout << "Podaj adres email: ";
    cin >> Adresat.email;
    cout << "Podaj adres zamieszkania: ";
    cin.sync();
    getline(cin, Adresat.adres);
    cout << endl;

    if (Przyjaciele.size() != 0) {
        idOstatniegoPrzyjaciela = Przyjaciele[Przyjaciele.size()-1].idAdresata;
    }

    Adresat.idAdresata = idOstatniegoPrzyjaciela+1;
    Adresat.idUzytkownika = idZalogowanegoUzytkownika;

    Przyjaciele.push_back(Adresat);

    dopiszPrzyjacielaDoPliku(Adresat);


    cout << "Dane przyjaciela zostaly zapisane" << endl;
    Sleep(1000);

}

void wyszukiwaniePoImieniu(string imie, vector <DanePrzyjaciela> & Przyjaciele) {
    int i=0;
    int id=0;
    while (i<Przyjaciele.size()) {
        if (Przyjaciele[i].imie == imie) {
            cout << Przyjaciele[i].idAdresata <<endl;
            cout << Przyjaciele[i].imie <<endl;
            cout << Przyjaciele[i].nazwisko <<endl;
            cout << Przyjaciele[i].nrTelefonu <<endl;
            cout << Przyjaciele[i].email <<endl;
            cout << Przyjaciele[i].adres <<endl;
            cout << endl;
            id = Przyjaciele[i].idAdresata;
        }
        i++;

    }
    if (id == 0) {
        cout << "W bazie danych nie ma osoby o podanym imieniu" << endl;
        Sleep(3000);
    }


}

void wyszukiwaniePoNazwisku(string nazwisko, vector <DanePrzyjaciela> &Przyjaciele) {
    int i=0;
    int id=0;
    while (i<Przyjaciele.size()) {
        if (Przyjaciele[i].nazwisko == nazwisko) {
            cout << Przyjaciele[i].idAdresata <<endl;
            cout << Przyjaciele[i].imie <<endl;
            cout << Przyjaciele[i].nazwisko <<endl;
            cout << Przyjaciele[i].nrTelefonu <<endl;
            cout << Przyjaciele[i].email <<endl;
            cout << Przyjaciele[i].adres <<endl;
            cout << endl;
            id = Przyjaciele[i].idAdresata;
        }
        i++;

    }
    if (id == 0) {
        cout << "W bazie danych nie ma osoby o podanym nazwisku" << endl;
        Sleep(3000);
    }


}

void wyswietlenieWszystkichZapisanychOsob(vector <DanePrzyjaciela> & Przyjaciele) {
    for (int i=0; i<Przyjaciele.size(); i++) {
        cout << Przyjaciele[i].idAdresata <<endl;
        cout << Przyjaciele[i].imie <<endl;
        cout << Przyjaciele[i].nazwisko <<endl;
        cout << Przyjaciele[i].nrTelefonu <<endl;
        cout << Przyjaciele[i].email <<endl;
        cout << Przyjaciele[i].adres <<endl;
        cout << endl;

    }
}

void odczytDanychZPliku( vector <DanePrzyjaciela> & Przyjaciele, int idZalogowanegoUzytkownika) {
    string linia = "";
    string daneDoZapisu = "";
    int nr_danych=1;
    DanePrzyjaciela Adresat;

    fstream plik;
    plik.open("wizytowki.txt", ios::in);
    if (plik.good()==false) {
        plik.open("wizytowki.txt", ios::out | ios::app);
        cout<< "Utworzono plik z wizytowkami";
        Sleep(3000);
        plik.close();
    }

    while (getline(plik, linia)) {


        for (int i=0; i<linia.length(); i++) {
            while (linia[i] != '|') {
                daneDoZapisu += linia[i];
                i++;
            }
            switch(nr_danych) {
            case 1:
                Adresat.idAdresata=atoi(daneDoZapisu.c_str());
                break;
            case 2:
                Adresat.idUzytkownika=atoi(daneDoZapisu.c_str());
            case 3:
                Adresat.imie=daneDoZapisu;
                break;
            case 4:
                Adresat.nazwisko=daneDoZapisu;
                break;
            case 5:
                Adresat.nrTelefonu=daneDoZapisu;
                break;
            case 6:
                Adresat.email=daneDoZapisu;
                break;
            case 7:
                Adresat.adres=daneDoZapisu;
                break;

            }

            nr_danych++;
            daneDoZapisu = "";


        }
        if (Adresat.idUzytkownika == idZalogowanegoUzytkownika)
        {
        Przyjaciele.push_back(Adresat);
        }
        nr_danych = 1;

    }
    plik.close();
}

void usuwanieAdresata(int idDoUsuniecia, vector <DanePrzyjaciela> & Przyjaciele) {
    int id=0;
    char wybor;
    cout << "Czy na pewno chcesz usunac wybranego adresata? (t/n)" << endl;
    cin >> wybor;
    if (wybor == 't') {
        for (int i=0; i < Przyjaciele.size(); i++) {
            if (Przyjaciele[i].idAdresata == idDoUsuniecia) {
                id = Przyjaciele[i].idAdresata;
                Przyjaciele.erase(Przyjaciele.begin()+i);

                cout << "Adresat zostal usuniety" << endl;
            }
        }

        zapiszWszystkichAdresatowDoPlikuTekstowego(Przyjaciele);
    }


    if (id == 0) {
        cout << "W bazie danych nie ma osoby o podanym id" << endl;
        Sleep(3000);
    }


}

int edycjaAdresata(int idDoEdycji, vector <DanePrzyjaciela> & Przyjaciele) {
    char wybor;
    int numerKontrolny = 0;
    string edytowaneImie, edytowaneNazwisko, edytowanyNrTelefonu, edytowanyEmail, edytowanyAdres;
    for (int i=0; i < Przyjaciele.size(); i++) {
        if (Przyjaciele[i].idAdresata == idDoEdycji) {
            system("cls");
            cout << "1 - imie" << endl;
            cout << "2 - nazwisko" << endl;
            cout << "3 - numer telefonu" << endl;
            cout << "4 - email" << endl;
            cout << "5 - adres" << endl;
            cout << "6 - powrot do menu" << endl<<endl;
            cout << "Twoj wybor: ";
            cin >> wybor;

            switch(wybor) {
            case '1': {
                system("cls");
                cout << "Podaj nowe imie: ";
                cin >> edytowaneImie;
                Przyjaciele[i].imie = edytowaneImie;
                zapiszWszystkichAdresatowDoPlikuTekstowego(Przyjaciele);
                cout << "Dane zostaly zmienione" << endl;
                numerKontrolny = 1;
                return numerKontrolny;
                break;

            }
            case '2': {
                system("cls");
                cout << "Podaj nowe nazwisko: ";
                cin >> edytowaneNazwisko;
                Przyjaciele[i].nazwisko = edytowaneNazwisko;
                zapiszWszystkichAdresatowDoPlikuTekstowego(Przyjaciele);
                cout << "Dane zostaly zmienione" << endl;
                numerKontrolny = 1;
                return numerKontrolny;
                break;
            }
            case '3': {
                system("cls");
                cout << "Podaj nowy numer telefonu: ";
                cin >> edytowanyNrTelefonu;
                Przyjaciele[i].nrTelefonu = edytowanyNrTelefonu;
                zapiszWszystkichAdresatowDoPlikuTekstowego(Przyjaciele);
                cout << "Dane zostaly zmienione" << endl;
                numerKontrolny = 1;
                return numerKontrolny;
                break;
            }
            case '4': {
                system("cls");
                cout << "Podaj nowy email: ";
                cin >> edytowanyEmail;
                Przyjaciele[i].email = edytowanyEmail;
                zapiszWszystkichAdresatowDoPlikuTekstowego(Przyjaciele);
                cout << "Dane zostaly zmienione" << endl;
                numerKontrolny = 1;
                return numerKontrolny;
                break;
            }
            case '5': {
                system("cls");
                cout << "Podaj nowy adres: ";
                cin.sync();
                getline(cin, edytowanyAdres);
                Przyjaciele[i].adres = edytowanyAdres;
                zapiszWszystkichAdresatowDoPlikuTekstowego(Przyjaciele);
                cout << "Dane zostaly zmienione" << endl;
                numerKontrolny = 1;
                return numerKontrolny;
                break;
            }
            case '6': {
                return numerKontrolny;
                break;
            }
            }


        } else cout << "W bazie danych nie ma osoby o podanym id" <<endl;
    }

}

int main() {
    vector <DanePrzyjaciela> Przyjaciele;
    vector <Uzytkownik> Users;
    int idZalogowanegoUzytkownika = 0;
    int numerKontrolny = 0;
    int iloscPrzyjaciol = 0;
    string szukaneImie, szukaneNazwisko;
    int idDoUsuniecia, idDoEdycji;
    char wybor;

    odczytDanychZPlikuUzytkownicy(Users);

    while (1) {
        if (idZalogowanegoUzytkownika != 0) {

            if (numerKontrolny == 0) {
                system("cls");
                cout << "KSIAZKA ADRESOWA" << endl;
                cout << "1. Dodaj adresata" << endl;
                cout << "2. Wyszukaj dane po imieniu" << endl;
                cout << "3. Wyszukaj dane po nazwisku" << endl;
                cout << "4. Wyswietl wszystkich adresatow" << endl;
                cout << "5. Usun adresata" << endl;
                cout << "6. Edytuj adresata" << endl;
                cout << "7. Zmien haslo" << endl;
                cout << "8. Wyloguj sie" << endl << endl;
                cout << "Twoj wybor: ";
                cin >> wybor;

                switch (wybor) {
                case '1': {
                    wczytywanieDanychPrzyjaciela(Przyjaciele, idZalogowanegoUzytkownika);
                    numerKontrolny = 1;
                    break;

                }
                case '2': {
                    system("cls");
                    cout << "Podaj imie szukanego przyjaciela: ";
                    cin >> szukaneImie;
                    wyszukiwaniePoImieniu(szukaneImie, Przyjaciele );
                    numerKontrolny = 1;
                    break;


                }
                case '3': {
                    system("cls");
                    cout << "Podaj nazwisko szukanego przyjaciela: ";
                    cin >> szukaneNazwisko;
                    wyszukiwaniePoNazwisku(szukaneNazwisko, Przyjaciele );
                    numerKontrolny = 1;
                    break;
                }
                case '4': {
                    system("cls");
                    wyswietlenieWszystkichZapisanychOsob(Przyjaciele);
                    numerKontrolny = 1;
                    break;

                }
                case '5': {
                    system("cls");
                    cout << "Podaj id adresata, ktorego chcesz usunac: ";
                    cin >> idDoUsuniecia;
                    usuwanieAdresata(idDoUsuniecia,  Przyjaciele);
                    numerKontrolny = 1;
                    break;

                }
                case '6': {
                    system("cls");
                    cout << "Podaj id adresata, ktorego dane chcesz edytowac: ";
                    cin >> idDoEdycji;
                    numerKontrolny = edycjaAdresata(idDoEdycji, Przyjaciele);
                    break;

                }
                case '7': {
                    system("cls");
                    idZalogowanegoUzytkownika = zmianaHasla(Users, idZalogowanegoUzytkownika);
                    numerKontrolny = 0;
                }
                case '8': {
                    idZalogowanegoUzytkownika = 0;
                    Przyjaciele.clear();
                    break;
                }
                }



            } else {
                cout << endl;
                cout << "1. Powrot do menu glownego" << endl;
                cout << "2. Zakoncz program" << endl;
                cin >> wybor;
                switch (wybor) {
                case '1': {
                    numerKontrolny = 0;
                    break;
                }
                case '2': {
                    exit(0);
                }
                }
            }
        } else {
            system("cls");
            cout << "1. Rejestracja" << endl;
            cout << "2. Logowanie" << endl;
            cout << "9. Zakoncz program" << endl;
            cin >> wybor;

            if (wybor == '1') {
                idZalogowanegoUzytkownika = rejestracja(Users);
            } else if (wybor == '2') {
                idZalogowanegoUzytkownika = logowanie(Users);
                odczytDanychZPliku(Przyjaciele, idZalogowanegoUzytkownika);
                iloscPrzyjaciol = Przyjaciele.size();

            } else if (wybor == '9') {
                exit(0);
            }
        }
    }
    return 0;
}
