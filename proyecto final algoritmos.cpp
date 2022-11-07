#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <fstream>
#include <string.h>
#include <stdio.h>

using namespace std;
const char *nombre_archivo = "archivo.dat";

struct Palabra{
	
	char nombre[50];
	char traduccion[50];
	char funcionalidad[200];
};

void menu();
void leer();
void crear();
void actualizar();
void borrar();
void opcion2();
void traducir();

int main (){
	
int opc;
		system("cls");
		cout<<"          Universidad Mariano Galvez de Guatemala       "<<endl;
		cout<<"                    Facultad de Ingenieria              "<<endl;
		cout<<"                       Proyecto Final                   "<<endl;
		cout<<" "<<endl;
		cout<<"------------------------MENU-------------------------"<<endl;
		cout<<""<<endl;
		cout<<"1. Mostrar, modifcar y eliminar palabras "<<endl;
		cout<<"2. Escribir texto multilineas "<<endl;
		cout<<"3. Traducir palabras"<<endl;
		cout<<"4. Salir"<<endl;
		cin>>opc;
		system("cls");
		switch(opc){
			case 1:
			menu();
			break;	
				
		case 2:
		// Texto Multilinea
		system("cls");
            	opcion2();
            	system("pause");
		break;
		
		case 3:
		//Traducir
		system("cls");
		traducir();	
		break;
		case 4:
			cout<<"Muchas gracias por utilizar el programa :D";
			break;
		default:
			cout<<"La opcion que selecciono no esta disponible";
}
}


void menu(){
			int op2;
			cout<<"          Universidad Mariano Galvez de Guatemala       "<<endl;
			cout<<"                    Facultad de Ingenieria              "<<endl;
			cout<<"                       Proyecto Final                   "<<endl;
			cout<<" "<<endl;
			cout<<"------------------------MENU-------------------------"<<endl;
			cout<<""<<endl;
			cout<<"1. Mostrar palabras "<<endl;
			cout<<"2. Ingresar una nueva palabrar "<<endl;
			cout<<"3. Modifcar palabras "<<endl;
			cout<<"4. Eliminar una palabra "<<endl;
			cout<<"5. salir al menu principal"<<endl;
			cin>>op2;
			switch(op2){
				case 1:
				//********Mostrar********
				leer ();
				system("pause");
				system("cls");
				menu();
				break;
				
				case 2:
				//********crear********
				leer ();
			    crear();
				break;
				
				
				case 3:
				//********modificar********
				leer ();
			    actualizar();
				break;
				
				
				case 4:
				//********Eliminar********
				leer();
				borrar();
				break;
				
				
				case 5:
				//********Salir al menu principal********
				main();
				break;
				
				default:
            	cout<<"La opcion seleccionada no esta disponible, presione una tecla para continuar"<<endl;
            	system("pause");
            	system("cls");
            	menu();
            	break;
			}
}


void leer(){
	char r;
	system("cls");
	FILE* archivo=fopen(nombre_archivo,"rb");
	if (!archivo){
	archivo=fopen(nombre_archivo,"w+b");	
	}
	Palabra palabra;
	int id = 0;
	fread(&palabra,sizeof(Palabra),1,archivo);
	
	do{
	cout<<"_________________________________________"<<endl;	
	cout<<"ID"<<"|"<<"PALABRA"<<"|"<<"TRADUCCION"<<endl;	
	cout<<id<<" |"<<palabra.nombre<<"   |"<<palabra.traduccion<<endl;
	cout<<"FUCIONALIDAD"<<endl;
	cout<<palabra.funcionalidad<<endl;
	fread(&palabra,sizeof(Palabra),1,archivo);	
		id+=1;
	}while(feof(archivo)==0);
	fclose(archivo);
}


void crear(){
	FILE* archivo=fopen(nombre_archivo,"a+b");
	char res;
	Palabra palabra;
	do{
		fflush(stdin);
		
		cout<<"Ingrese una palabra:  ";
		cin.getline(palabra.nombre,50);
		cout<<"Ingrese su traduccion:  ";
		cin.getline(palabra.traduccion,50);
		cout<<"Defina la funcionalidad:  ";
		cin.getline(palabra.funcionalidad,200);
		
		
		fwrite(&palabra,sizeof(Palabra),1,archivo);
		cout<<"desea ingresar otra palabra (s/n): ";
		cin>>res;
	}while(res=='s'||res=='S');
		
	fclose(archivo);
	leer();
}


void actualizar(){
	char r;
    do{
    	FILE* archivo=fopen(nombre_archivo,"r+b");
		Palabra palabra;
		int id=0;
		cout<<"Ingresa el ID que desea modificar: ";
		cin>>id;
		fseek(archivo,id* sizeof(Palabra),SEEK_SET);
		
			fflush(stdin);
			cout<<"ingrese una palabra:  ";
			cin.getline(palabra.nombre,50);
			cout<<"ingrese su traduccion:  ";
			cin.getline(palabra.traduccion,50);
			cout<<"defina su funcionalidad:  ";
			cin.getline(palabra.funcionalidad,200);
			
			fwrite(&palabra,sizeof(Palabra),1,archivo);
					
		fclose(archivo);
		leer();	
		
		cout<<"Desea actualizar otra palabra? (s/S)"<<endl;
		cin>>r;
	}while(r=='s' || r=='S');
		system("cls");
		return menu();
	}


void borrar(){
	char r;
	do{
		const char *nombre_archivo_temp = "archivo_temp.dat";
		FILE* archivo=fopen(nombre_archivo,"rb");
		FILE* archivo_temp=fopen(nombre_archivo_temp,"w+b");
		
		Palabra palabra;
		int id=0, id_n=0;
		cout<<"ingrese el id que desea eliminar: ";
		cin>>id;
		while(fread(&palabra,sizeof(Palabra),1,archivo)){
		if(id_n!=id){
			fwrite(&palabra,sizeof(Palabra),1,archivo_temp);	
		}
		id_n++;
	}
		fclose(archivo);
		fclose(archivo_temp);
		archivo_temp=fopen(nombre_archivo_temp,"rb");
		archivo=fopen(nombre_archivo,"wb");
		
			while(fread(&palabra,sizeof(Palabra),1,archivo_temp)){
			fwrite(&palabra,sizeof(Palabra),1,archivo);	
		}
			fclose(archivo);
		fclose(archivo_temp);
		
		leer();
		cout<<"Desea eliminar otra palabra? (s/S)"<<endl;
		cin>>r;
	}while(r=='s' || r=='S');
		system("cls");
		return menu();
		
	
	}


void opcion2(){
	const int max = 2500;
	char pal[max];
	cout<< " Ingrese su texto multilinea "<<endl;
	cout<< " para terminar escriba $ "<<endl;
	cin.get (pal,max,'$');
	cout<<pal<<endl;;
	
	system("pause");
	return menu();	
}


void traducir(){
	char res;
	
	do{
		FILE* archivo=fopen(nombre_archivo,"rb");
	if (archivo==NULL)
		exit(1);
	cout<<"Ingrese la palabra a traducir: ";
	char pl;
	cin>>pl;
	
	Palabra palabra;
	int existe = 0;
	fread(&palabra, sizeof(Palabra), 1, archivo);
	
	while (!feof(archivo))
	{
		if (pl == palabra.nombre[50]){
			cout<<palabra.nombre<<"   |"<<palabra.traduccion<<endl;
	cout<<"FUCIONALIDAD"<<endl;
	cout<<palabra.funcionalidad<<endl;
			
			break;	
		}
		fread(&palabra, sizeof(Palabra), 1, archivo);
	}

	if (existe==0){
		cout<<"Palabra no encontrada";
		fclose(archivo);
	}
	
	cout<<"desea ingresar otra palabra (s/n): ";
	cin>>res;
	}while(res=='s'||res=='S');	
}





