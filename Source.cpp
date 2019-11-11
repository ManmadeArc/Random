#include<iostream>
#include <ctime>
#include <vector>
#include <cstdlib>
#include <sstream>
#include <algorithm>




using namespace std;
string palos = "PDTC";
string Numeros = "A234567891JQK";
/////Structs
struct Carta {
	string numero;
	string palo;
	int numerico=0;
	void Numero() {
		if (numero == "A") {
			numerico = 14;
		}

		else
		{
			numerico = Numeros.find(numero[0]) + 1;
		}
	}
	bool operator<(Carta a2) { return numerico < a2.numerico; }
};

struct Victoria
{
	int indiceJugador;
	int JMano;
	bool operator<(Victoria a2) { return JMano < a2.JMano; }
};
struct ALTA
{
	int indiceJugador;
	int CartaAlta;
	bool operator<(ALTA a2) { return CartaAlta < a2.CartaAlta; }
};

////Variables
int NumPlayers;
bool usado[52] = { false };
int IndiceCartaAct=0;
vector<Carta> Mazo;
vector <Carta> MazoRandom;
vector<string> Jugadores;
vector<bool> Plantarse;
vector<vector<Carta>> Manos;
vector<Carta> Pool;
vector<int> InstaGanador;
vector<Victoria> JUGADAS;
vector<ALTA> CartaMasAlta;

int Jugada = 0;
int borrar;
string opc;
bool Jugando=true;


//Funciones
inline int random(int inicio, int limite) { return inicio + rand() % (1 + limite - inicio); }
void Seleccion();
void Nombres();
void CrearMazo();
void revolver();
void BarajarMazo();
void RepartirManos();
void MostrarMano(int JugadorAct);
void Jugar();
void ComprobarJugar(int& x);
void Ganar();
void  CondicionesVictoria(vector<Carta> ManoActual, int indice);
void DEFECTO();


////


int main() {
	srand(time(NULL));
	CrearMazo();
	string ayuda;
	for (;;) {
		cout << "Que Desea Realizar\n[1]Jugar\n[2]Terminar\n";
		cin >> ayuda;
		if (ayuda == "1") {
			DEFECTO();
			Seleccion();
			Nombres();
			revolver();
			RepartirManos();
			system("cls");
			Jugar();
			Ganar();
			system("pause>nul");
		}
		else if (ayuda == "2") {
			return 0;
		}
		else {
			cout << "Opcion Incorrecta;";
			system("pause>nul");
		}
		system("cls");
	}

}

void Seleccion() { system("cls"); string selec; cout << "Introduzca un numero entre 2 y 4 para la seleccion de jugadores\n"; cin >> selec; if (selec != "2" && selec != "3" && selec != "4") { cout << "Opcion invalida"; system("pause>nul"); Seleccion();  } else { stringstream lol(selec); lol >> NumPlayers; } }

void DEFECTO() {
	for (int i = 0; i < 52; i++) {
		usado[i] = false;
	}
	Jugando = true;
	borrar = 0;
	opc = "";
	Jugada = 0;
	CartaMasAlta.clear();
	JUGADAS.clear();
	InstaGanador.clear();
	Pool.clear();
	Manos.clear();
	Plantarse.clear();
	Jugadores.clear();
	MazoRandom.clear();
	IndiceCartaAct = 0;
}

void Nombres() {
	string Nombre;
	for (int i = 0; i < NumPlayers; i++) {
		cout << "Jugador " << i + 1 << " Introduca su nombre: ";
		cin >> Nombre;
		Jugadores.push_back(Nombre);
		Plantarse.push_back(false);
	}
	

}
void CrearMazo() {
	Carta Cartita;
	for (char x : palos) {
		Cartita.palo = x;
		for (char y : Numeros) {
			if (y == '1') { Cartita.numero = "10"; }
			else { Cartita.numero = y; }
			Mazo.push_back(Cartita);
		}
	}
}

void BarajarMazo() {
	int indice = random(0, 51);
	if (usado[indice] == false) {
		MazoRandom.push_back(Mazo[indice]);
		usado[indice] = true;
	}
	else {
		BarajarMazo();
	}

}

void revolver() {
	for (int i = 0; i < 52; i++) {
		BarajarMazo();
	}
}

void RepartirManos() {
	vector<Carta> Manox;

	for (int i = 0; i < NumPlayers; i++) {
		for (int j = 0; j < 5; j++) {
			Manox.push_back(MazoRandom[IndiceCartaAct]);
				IndiceCartaAct++;
		}
		Manos.push_back(Manox);
		Manox.clear();
	}

}

void MostrarMano(int JugadorAct) {
	for (Carta x : Manos[JugadorAct]) {
		cout << x.numero << x.palo << " ";
	}
	cout << endl;
}

void DarUnaCarta(vector<Carta> &ManoAct){
	ManoAct.push_back(MazoRandom[IndiceCartaAct]);
	IndiceCartaAct++;
}
void EliminarCarta(vector<Carta>& ManoAct, int i) {
	cout << "Seleccione por el orden, la carta que desee Eliminar\n";
	cin >> borrar;
	if (borrar < 1 || borrar>6) {
		cout << "Opcion Incorercta";
		system("cls");
		cout << Jugadores[i];
		cout << endl;
		MostrarMano(i);
		EliminarCarta(ManoAct, i);
	}
	else {
		Pool.push_back(ManoAct[borrar - 1]);
		ManoAct.erase(ManoAct.begin() + borrar - 1);
	}
}
void SeleccionarPool(vector<Carta>&ManoAct, int i){
	cout << "Quiere Agregar La Carta de la Pool a su Mano?\n[1]Si\n[2]No\n";
	cin >> opc;
	if (opc == "1") {
		ManoAct.push_back(Pool[Pool.size() - 1]);
		Pool.pop_back();
	}
	else if (opc == "2") {
		DarUnaCarta(ManoAct);
	}
	else
	{
		system("cls");
		cout << Jugadores[i];
		cout << endl;
		MostrarMano(i);
		SeleccionarPool(ManoAct, i);
	}
}

void ComprobarJugar(int &x) {
	if (NumPlayers == 4) {
		if (Plantarse[0] || Plantarse[1] || Plantarse[2] || Plantarse[3]) {
			x++;
		}
	}
	if (NumPlayers == 3) {
		if (Plantarse[0] || Plantarse[1] || Plantarse[2] ) {
			x++;
		}
	}
	if (NumPlayers == 2) {
		if (Plantarse[0] || Plantarse[1] ) {
			x++;
		}
	}
}

void Plantar(int i) {
	string opt;
	cout << "Desea Plantarse\n[1]Si\n[2]No\n";
	cin >> opt;
	if (opt == "1") {
		Plantarse[i] = true;
	}
	else if (opt == "2") {
	
	}
	else {
		system("cls");
		Plantar(i);
	}
}

void INSTAGANAR(vector<Carta> ManoActual, int i) {
	for (int i = 0; i < ManoActual.size(); i++) {
		ManoActual[i].Numero();
	}
	std::sort(ManoActual.begin(), ManoActual.end());
	////3 Pares
	if (ManoActual[0].numero == ManoActual[1].numero && ManoActual[2].numero == ManoActual[3].numero && ManoActual[4].numero == ManoActual[5].numero) {
		InstaGanador.push_back(i);
	}
	//// Escalera
	else if (ManoActual[1].numerico == ManoActual[0].numerico + 1 && ManoActual[2].numerico == ManoActual[0].numerico + 2 && ManoActual[3].numerico == ManoActual[0].numerico + 3 &&
		ManoActual[4].numerico == ManoActual[0].numerico + 4 && ManoActual[5].numerico == ManoActual[0].numerico + 5) {
		InstaGanador.push_back(i);
	}
	else if (ManoActual[1].numerico == ManoActual[0].numerico + 1 - 13 && ManoActual[2].numerico == ManoActual[0].numerico + 2 - 13 && ManoActual[3].numerico == ManoActual[0].numerico + 3 - 13 &&
		ManoActual[4].numerico == ManoActual[0].numerico + 4 - 13 && ManoActual[5].numerico == ManoActual[0].numerico + 5 - 13) {
		InstaGanador.push_back(i);
	}
	///1 Par y 4 Iguales
	else if (ManoActual[0].numero == ManoActual[1].numero && 
		ManoActual[2].numero == ManoActual[3].numero && ManoActual[4].numero == ManoActual[2].numero && ManoActual[5].numero == ManoActual[2].numero) {
		InstaGanador.push_back(i);
	}
	else if (ManoActual[4].numero == ManoActual[5].numero &&
		ManoActual[0].numero == ManoActual[1].numero && ManoActual[0].numero == ManoActual[2].numero && ManoActual[0].numero == ManoActual[3].numero) {
		InstaGanador.push_back(i);
	}
	///2 Tercias
	else if (ManoActual[0].numero == ManoActual[1].numero && ManoActual[2].numero == ManoActual[1].numero
		&& ManoActual[3].numero == ManoActual[4].numero && ManoActual[4].numero == ManoActual[5].numero) {
		InstaGanador.push_back(i);
	}

}

void Jugar() {
	int x=0;
	int rondaAct = 0;
	while (Jugando) {
		if (x == NumPlayers-1) {
			break;
		}
		if (InstaGanador.size() != 0) {
			break;
		}
		rondaAct++;
		if (IndiceCartaAct > 51) {
			break;
		}
		for (int i = 0; i < NumPlayers; i++) {
			if (x == NumPlayers - 1) {
				break;
			}
			
			if (!Plantarse[i]) {
				if (Jugada == 0) {
					Jugada++;
					DarUnaCarta(Manos[i]);
					cout << Jugadores[i] << endl;

					MostrarMano(i);
					cout << endl;
					
					INSTAGANAR(Manos[i],i);
					if (InstaGanador.size() != 0) {
						break;
					}
					EliminarCarta(Manos[i],i);
					system("cls");
					cout << Jugadores[i] << endl;
					MostrarMano(i);
					cout << endl;
					cout << "Presione Enter Para Pasar al siguiente jugador";
					system("pause>nul");
					system("cls");


				}
				else {
					cout << Jugadores[i] << endl;
					MostrarMano(i);
					cout << endl;
					cout << "Pozo\n";
					if (Pool.size() > 0) {
						cout << Pool[Pool.size() - 1].numero << Pool[Pool.size() - 1].palo << endl;
						SeleccionarPool(Manos[i],i);
						system("cls");
					}
					cout << Jugadores[i] << endl;
					MostrarMano(i);
					cout << endl;
					INSTAGANAR(Manos[i], i);
					if (InstaGanador.size() != 0) {
						break;
					}
					EliminarCarta(Manos[i],i);
					system("cls");
					cout << Jugadores[i] << endl;
					MostrarMano(i);
					cout << endl;
					ComprobarJugar(x);
					if (rondaAct > 1) {
						Plantar(i);
					}
					cout << x;
					cout << "Presione Enter Para Pasar al siguiente jugador";

					system("pause>nul");
					system("cls");

				}
			}
		}
	}
}

void  CondicionesVictoria(vector<Carta> ManoActual, int indice) {
	Victoria w;
	ALTA z;
	for (int i = 0; i < ManoActual.size(); i++) {
		ManoActual[i].Numero();
	}
	std::sort(ManoActual.begin(), ManoActual.end());
	if (ManoActual[0].numerico == ManoActual[1].numerico &&
		ManoActual[2].numerico != ManoActual[0].numerico && ManoActual[2].numerico != ManoActual[1].numerico && ManoActual[2].numerico != ManoActual[3].numerico && ManoActual[2].numerico != ManoActual[4].numerico &&
		ManoActual[3].numerico != ManoActual[0].numerico && ManoActual[3].numerico != ManoActual[1].numerico && ManoActual[3].numerico != ManoActual[4].numerico &&
		ManoActual[4].numerico != ManoActual[0].numerico && ManoActual[4].numerico != ManoActual[1].numerico) {
		w.indiceJugador = indice; w.JMano = 1;
		z.indiceJugador = indice; z.CartaAlta = ManoActual[ManoActual.size() - 1].numerico;
		JUGADAS.push_back(w);
		CartaMasAlta.push_back(z);
	}
	else if (ManoActual[1].numerico == ManoActual[2].numerico &&
		ManoActual[0].numerico != ManoActual[1].numerico && ManoActual[0].numerico != ManoActual[2].numerico && ManoActual[0].numerico != ManoActual[3].numerico && ManoActual[0].numerico != ManoActual[4].numerico &&
		ManoActual[3].numerico != ManoActual[1].numerico && ManoActual[3].numerico != ManoActual[2].numerico && ManoActual[3].numerico != ManoActual[4].numerico &&
		ManoActual[4].numerico != ManoActual[1].numerico && ManoActual[4].numerico != ManoActual[2].numerico) {
		w.indiceJugador = indice; w.JMano = 1;
		z.indiceJugador = indice; z.CartaAlta = ManoActual[ManoActual.size() - 1].numerico;
		JUGADAS.push_back(w);
		CartaMasAlta.push_back(z);
	}
	else if (ManoActual[2].numerico == ManoActual[3].numerico &&
		ManoActual[0].numerico != ManoActual[1].numerico && ManoActual[0].numerico != ManoActual[2].numerico && ManoActual[0].numerico != ManoActual[3].numerico && ManoActual[0].numerico != ManoActual[4].numerico &&
		ManoActual[1].numerico != ManoActual[2].numerico && ManoActual[1].numerico != ManoActual[3].numerico && ManoActual[1].numerico != ManoActual[4].numerico &&
		ManoActual[4].numerico != ManoActual[2].numerico && ManoActual[4].numerico != ManoActual[3].numerico) {
		w.indiceJugador = indice; w.JMano = 1;
		z.indiceJugador = indice; z.CartaAlta = ManoActual[ManoActual.size() - 1].numerico;
		JUGADAS.push_back(w);
		CartaMasAlta.push_back(z);
	}
	else if (ManoActual[3].numerico == ManoActual[4].numerico &&
		ManoActual[0].numerico != ManoActual[1].numerico && ManoActual[0].numerico != ManoActual[2].numerico && ManoActual[0].numerico != ManoActual[3].numerico && ManoActual[0].numerico != ManoActual[4].numerico &&
		ManoActual[1].numerico != ManoActual[2].numerico && ManoActual[1].numerico != ManoActual[3].numerico && ManoActual[1].numerico != ManoActual[4].numerico &&
		ManoActual[2].numerico != ManoActual[3].numerico && ManoActual[2].numerico != ManoActual[4].numerico) {
		w.indiceJugador = indice; w.JMano = 1;
		z.indiceJugador = indice; z.CartaAlta = ManoActual[ManoActual.size() - 1].numerico;
		JUGADAS.push_back(w);
		CartaMasAlta.push_back(z);
	}
	else if (ManoActual[0].numerico == ManoActual[1].numerico && ManoActual[2].numerico == ManoActual[3].numerico &&
		ManoActual[0].numerico != ManoActual[2].numerico && ManoActual[0].numerico != ManoActual[4].numerico &&
		ManoActual[2].numerico != ManoActual[4].numerico) {
		w.indiceJugador = indice; w.JMano = 2;
		z.indiceJugador = indice; z.CartaAlta = ManoActual[ManoActual.size() - 1].numerico;
		JUGADAS.push_back(w);
		CartaMasAlta.push_back(z);
	}
	else if (ManoActual[0].numerico == ManoActual[1].numerico && ManoActual[3].numerico == ManoActual[4].numerico &&
		ManoActual[0].numerico != ManoActual[2].numerico && ManoActual[0].numerico != ManoActual[4].numerico &&
		ManoActual[2].numerico != ManoActual[4].numerico) {
		w.indiceJugador = indice; w.JMano = 2;
		z.indiceJugador = indice; z.CartaAlta = ManoActual[ManoActual.size() - 1].numerico;
		JUGADAS.push_back(w);
		CartaMasAlta.push_back(z);
	}
	else if (ManoActual[1].numerico == ManoActual[2].numerico && ManoActual[3].numerico == ManoActual[4].numerico &&
		ManoActual[0].numerico != ManoActual[2].numerico && ManoActual[0].numerico != ManoActual[4].numerico &&
		ManoActual[2].numerico != ManoActual[4].numerico) {
		w.indiceJugador = indice; w.JMano = 2;
		z.indiceJugador = indice; z.CartaAlta = ManoActual[ManoActual.size() - 1].numerico;
		JUGADAS.push_back(w);
		CartaMasAlta.push_back(z);
	}
	else if (ManoActual[0].numerico== ManoActual[1].numerico && ManoActual[1].numerico== ManoActual[2].numerico &&
		ManoActual[0].numerico!= ManoActual[3].numerico && ManoActual[0].numerico!= ManoActual[4].numerico &&
		ManoActual[3].numerico!= ManoActual[4].numerico){
		w.indiceJugador = indice; w.JMano = 3;
		z.indiceJugador = indice; z.CartaAlta = ManoActual[ManoActual.size() - 1].numerico;
		JUGADAS.push_back(w);
		CartaMasAlta.push_back(z);
	}
	else if (ManoActual[1].numerico == ManoActual[2].numerico && ManoActual[2].numerico == ManoActual[3].numerico &&
		ManoActual[1].numerico != ManoActual[0].numerico && ManoActual[1].numerico != ManoActual[4].numerico &&
		ManoActual[0].numerico != ManoActual[4].numerico) {
		w.indiceJugador = indice; w.JMano = 3;
		z.indiceJugador = indice; z.CartaAlta = ManoActual[ManoActual.size() - 1].numerico;
		JUGADAS.push_back(w);
		CartaMasAlta.push_back(z);
	}
	else if (ManoActual[2].numerico == ManoActual[3].numerico && ManoActual[3].numerico == ManoActual[4].numerico &&
		ManoActual[3].numerico != ManoActual[0].numerico && ManoActual[3].numerico != ManoActual[1].numerico &&
		ManoActual[0].numerico != ManoActual[1].numerico) {
		w.indiceJugador = indice; w.JMano = 3;
		z.indiceJugador = indice; z.CartaAlta = ManoActual[ManoActual.size() - 1].numerico;
		JUGADAS.push_back(w);
		CartaMasAlta.push_back(z);
	}
	else if (ManoActual[0].numerico == 10 && ManoActual[1].numerico == 11 && ManoActual[2].numerico == 12 &&
		ManoActual[3].numerico == 13 && ManoActual[4].numerico == 14) {
		w.indiceJugador = indice; w.JMano = 7;
		z.indiceJugador = indice; z.CartaAlta = ManoActual[ManoActual.size() - 1].numerico;
		JUGADAS.push_back(w);
		CartaMasAlta.push_back(z);
	}
	else if (ManoActual[1].numerico == ManoActual[0].numerico + 1 && ManoActual[2].numerico == ManoActual[0].numerico + 2 && ManoActual[3].numerico == ManoActual[0].numerico + 3 &&
		ManoActual[4].numerico == ManoActual[0].numerico + 4 ) {
		w.indiceJugador = indice; w.JMano = 4;
		z.indiceJugador = indice; z.CartaAlta = ManoActual[ManoActual.size() - 1].numerico;
		JUGADAS.push_back(w);
		CartaMasAlta.push_back(z);
	}
	else if (ManoActual[1].numerico == ManoActual[0].numerico + 1 -13&& ManoActual[2].numerico == ManoActual[0].numerico + 2-13 && ManoActual[3].numerico == ManoActual[0].numerico + 3-13 &&
		ManoActual[4].numerico == ManoActual[0].numerico + 4-13 ) {
		w.indiceJugador = indice; w.JMano = 4;
		z.indiceJugador = indice; z.CartaAlta = ManoActual[ManoActual.size() - 1].numerico;
		JUGADAS.push_back(w);
		CartaMasAlta.push_back(z);
	}
	else if (ManoActual[0].numerico== ManoActual[1].numerico&& ManoActual[1].numerico== ManoActual[2].numerico&&
		ManoActual[3].numerico== ManoActual[4].numerico) {
		w.indiceJugador = indice; w.JMano = 5;
		z.indiceJugador = indice; z.CartaAlta = ManoActual[ManoActual.size() - 1].numerico;
		JUGADAS.push_back(w);
		CartaMasAlta.push_back(z);
	}
	else if (ManoActual[2].numerico == ManoActual[3].numerico && ManoActual[3].numerico == ManoActual[4].numerico &&
	ManoActual[0].numerico == ManoActual[1].numerico) {
	w.indiceJugador = indice; w.JMano = 5;
	z.indiceJugador = indice; z.CartaAlta = ManoActual[ManoActual.size() - 1].numerico;
	JUGADAS.push_back(w);
	CartaMasAlta.push_back(z);
	}
	else if (ManoActual[0].numerico== ManoActual[1].numerico && ManoActual[0].numerico== ManoActual[2].numerico && ManoActual[0].numerico== ManoActual[3].numerico) {
	w.indiceJugador = indice; w.JMano = 6;
	z.indiceJugador = indice; z.CartaAlta = ManoActual[ManoActual.size() - 1].numerico;
	JUGADAS.push_back(w);
	CartaMasAlta.push_back(z);
	}
	else if (ManoActual[1].numerico == ManoActual[2].numerico && ManoActual[1].numerico == ManoActual[3].numerico && ManoActual[1].numerico == ManoActual[4].numerico) {
	w.indiceJugador = indice; w.JMano = 6;
	z.indiceJugador = indice; z.CartaAlta = ManoActual[ManoActual.size() - 1].numerico;
	JUGADAS.push_back(w);
	CartaMasAlta.push_back(z);
	}
	else {
		w.indiceJugador = indice; w.JMano = 0;
		z.indiceJugador = indice; z.CartaAlta= ManoActual[ManoActual.size() - 1].numerico;
		JUGADAS.push_back(w);
		CartaMasAlta.push_back(z);
	}
}


void Ganar() {
	if (InstaGanador.size() > 0) {
		cout << "El Ganador Es " << Jugadores[InstaGanador[0]];
	}
	else
	{
		for (int i = 0; i < Manos.size(); i++) {
			CondicionesVictoria(Manos[i], i);
			cout << Jugadores[i] << endl;
			MostrarMano(i);
			cout << endl;
		}
		cout << endl;
		sort(JUGADAS.begin(), JUGADAS.end());
		sort(CartaMasAlta.begin(), CartaMasAlta.end());
		if (NumPlayers == 2) {
			if (JUGADAS[0].JMano == JUGADAS[1].JMano) {
				cout << "El Ganador Es " << Jugadores[CartaMasAlta[CartaMasAlta.size()-1].indiceJugador];
			}
			else
			{
				cout << "El Ganador Es " << Jugadores[JUGADAS[JUGADAS.size()-1].indiceJugador];
			}
		}
		if (NumPlayers == 3) {
			if (JUGADAS[0].JMano == JUGADAS[1].JMano && JUGADAS[1].JMano==JUGADAS[2].JMano) {
				cout << "El Ganador Es " << Jugadores[CartaMasAlta[CartaMasAlta.size() - 1].indiceJugador];
			}
			else if (JUGADAS[1].JMano == JUGADAS[2].JMano) {
				JUGADAS.erase(JUGADAS.begin());
				cout << "El Ganador Es " << Jugadores[CartaMasAlta[CartaMasAlta.size() - 1].indiceJugador];
			}
			else
			{
				cout << "El Ganador Es " << Jugadores[JUGADAS[JUGADAS.size() - 1].indiceJugador];
			}
		}
		if (NumPlayers == 4) {
			if (JUGADAS[0].JMano == JUGADAS[1].JMano && JUGADAS[1].JMano == JUGADAS[2].JMano&& JUGADAS[2].JMano== JUGADAS[3].JMano) {
				cout << "El Ganador Es " << Jugadores[CartaMasAlta[CartaMasAlta.size() - 1].indiceJugador];
			}
			else if (JUGADAS[1].JMano == JUGADAS[2].JMano && JUGADAS[3].JMano==JUGADAS[2].JMano) {
				JUGADAS.erase(JUGADAS.begin());
				cout << "El Ganador Es " << Jugadores[CartaMasAlta[CartaMasAlta.size() - 1].indiceJugador];
			}
			else if (JUGADAS[3].JMano == JUGADAS[2].JMano) {
				JUGADAS.erase(JUGADAS.begin(),JUGADAS.begin()+1);
				cout << "El Ganador Es " << Jugadores[CartaMasAlta[CartaMasAlta.size() - 1].indiceJugador];
			}
			else
			{
				cout << "El Ganador Es " << Jugadores[JUGADAS[JUGADAS.size() - 1].indiceJugador];
			}
		}
	}
}


/*
Par[1]
2pares[2]
Tercia[3]
Escalera[4]
Tercia y Par[5]
Poker[6]
Escalera Chida[7]

*/